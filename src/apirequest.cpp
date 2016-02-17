/*
 * apirequest.cpp
 *
 *  Created on: 2016/02/05
 *      Author: ytanaka-PC
 */

#include "apirequest.h"

#include <bb/data/JsonDataAccess>
#include <bb/cascades/GroupDataModel>

#include <QtCore/QDateTime>
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkReply>
#include <QtNetwork/QAuthenticator>
#include <QSettings>

#include "constants.h"
#include "requestheader.h"

using namespace bb::data;
using namespace bb::cascades;

const QString ApiRequest::mRoot = "https://api.github.com";

const QString ApiRequest::mAuth = "/authorizations";
const QString ApiRequest::mDelt = "/authorizations/:id";
const QString ApiRequest::mNoti = "/notifications";
const QString ApiRequest::mRepo = "/user/repos";
const QString ApiRequest::mOrga = "/user/orgs";
const QString ApiRequest::mIssu = "/user/issues";
const QString ApiRequest::mGist = "/gists";
const QString ApiRequest::mComm = "";

const QString ApiRequest::mSRep = "/search/repositories";

ApiRequest::ApiRequest(QObject* parent) :
        QObject(parent), mManager(new QNetworkAccessManager(this))
{
    // TODO Auto-generated constructor stub
}

QByteArray ApiRequest::getAuthRequestBody()
{
    QVariantMap map;
    map["note"] = Constants::mAppName;
    QVariantList scopes;
    scopes.append("notifications");
    scopes.append("read:org");
    scopes.append("repo");
    map["scopes"] = scopes;
    JsonDataAccess jda;
    QByteArray arr;
    jda.saveToBuffer(QVariant(map), &arr);
    return arr;
}

QVariantMap ApiRequest::replyToMap(QNetworkReply* reply)
{
    if (reply && reply->error() == QNetworkReply::NoError) {
        const QByteArray buffer(reply->readAll());

        JsonDataAccess jda;
        QVariant var = jda.loadFromBuffer(buffer);
        return var.value<QVariantMap>();
    }
    QVariantMap map;
    return map;
}

QVariantList ApiRequest::replyToList(QNetworkReply* reply)
{
    if (reply && reply->error() == QNetworkReply::NoError) {
        const QByteArray buffer(reply->readAll());

        JsonDataAccess jda;
        QVariant var = jda.loadFromBuffer(buffer);
        return var.value<QVariantList>();
    }
    QVariantList list;
    return list;
}

bool ApiRequest::alreadyAuthentication()
{
    QSettings settings(Constants::mOrgName, Constants::mAppName);
    return settings.value("token", -1) != -1;
}

void ApiRequest::authentication(QString username, QString password)
{
    QNetworkRequest request = RequestHeader::getRequestHeaderForAuthentication(username, password,
            QUrl(mRoot + mAuth));

    connect(mManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(onAuthenticationFinished(QNetworkReply*)));

    mManager->post(request, getAuthRequestBody());
}

void ApiRequest::twoFactorAuthentication(QString username, QString password, QString factorKey)
{
    QNetworkRequest request = RequestHeader::getRequestHeaderForAuthentication(username, password,
            QUrl(mRoot + mAuth));
    request.setRawHeader("X-GitHub-OTP", factorKey.trimmed().toLocal8Bit());

    connect(mManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(onAuthenticationFinished(QNetworkReply*)));

    mManager->post(request, getAuthRequestBody());
}

void ApiRequest::onAuthenticationFinished(QNetworkReply* reply)
{
    if (reply && reply->attribute(QNetworkRequest::HttpStatusCodeAttribute) == 401
            && reply->hasRawHeader("X-GitHub-OTP")) {
        emit twoFactorAuthenticationRequest();
        return;
    }
    QVariantMap map = replyToMap(reply);
    if (map.size() > 0) {
        QSettings settings(Constants::mOrgName, Constants::mAppName);

        settings.setValue("token", map["token"].value<QString>());
        settings.setValue("id", map["id"].value<QString>());
        reply->deleteLater();
        emit authRequestCompleted();
        return;
    }
    reply->deleteLater();
    emit authRequestFailed();
}

void ApiRequest::updateToken(QString username, QString password)
{
    QNetworkRequest request = RequestHeader::getRequestHeaderForAuthentication(username, password,
            QUrl(mRoot + mAuth));

    connect(mManager, SIGNAL(finished(QNetworkReply*)), this,
            SLOT(onUpdateFinished(QNetworkReply*)));

    mManager->sendCustomRequest(request, "PATCH");
}

void ApiRequest::onUpdateFinished(QNetworkReply* reply)
{
    QVariantMap map = replyToMap(reply);
    if (map.size() > 0) {
        QSettings settings(Constants::mOrgName, Constants::mAppName);
        settings.setValue("token", map["token"]);

        reply->deleteLater();
        emit authRequestCompleted();
        return;
    }
    reply->deleteLater();
    emit authRequestFailed();
}

void ApiRequest::deleteToken()
{
    QSettings settings(Constants::mOrgName, Constants::mAppName);
    QString id = settings.value("id", "").value<QString>();
    if (id.isEmpty()) {
        emit authRequestFailed();
        return;
    }
    QString del = QString(mDelt).replace(":id", id);
    QNetworkRequest request = RequestHeader::getRequestHeaderWithToken(QUrl(mRoot + del));

    connect(mManager, SIGNAL(finished(QNetworkReply*)), this,
            SLOT(onDeleteFinished(QNetworkReply*)));

    mManager->sendCustomRequest(request, "DELETE");
}

void ApiRequest::onDeleteFinished(QNetworkReply* reply)
{
    if (reply && reply->error() == QNetworkReply::NoError) {
        emit authRequestCompleted();
    }
    emit authRequestFailed();
}

void ApiRequest::getNotifications()
{
    QNetworkRequest request = RequestHeader::getRequestHeaderWithToken(QUrl(mRoot + mNoti));

    connect(mManager, SIGNAL(finished(QNetworkReply*)), this,
            SLOT(onNotificationFinished(QNetworkReply*)));

    mManager->get(request);
}

void ApiRequest::onNotificationFinished(QNetworkReply* reply)
{
    QVariantList list = replyToList(reply);
    if (list.size() > 0) {
        QVariantList model;
        for (int i = 0; i < list.size(); i++) {
            QVariantMap data;
            QVariantMap map = list[i].value<QVariantMap>();
            QVariantMap inside = map["subject"].value<QVariantMap>();
            QVariantMap rep = map["repository"].value<QVariantMap>();
            data["title"] = inside["title"];
            data["type"] = inside["type"];
            QDateTime time = QDateTime::fromString(map["updated_at"].value<QString>(),
                    "yyyy-MM-dd'T'HH:mm:ss'Z'");
            data["updatedAt"] = time.toMSecsSinceEpoch();
            data["name"] = rep["full_name"];
            data["url"] = rep["html_url"];
            model.append(data);
        }
        reply->deleteLater();
        emit requestCompleted(model);
        return;
    }
    emit requestFailed();
}

void ApiRequest::getComment()
{
    QNetworkRequest request = RequestHeader::getRequestHeaderWithToken(mRoot + mComm);

    connect(mManager, SIGNAL(finished(QNetworkReply*)), this,
            SLOT(onCommentFinished(QNetworkReply*)));
}

void ApiRequest::onCommentFinished(QNetworkReply* reply)
{
}

void ApiRequest::getRepositories()
{
    QNetworkRequest request = RequestHeader::getRequestHeaderWithToken(QUrl(mRoot + mRepo));

    connect(mManager, SIGNAL(finished(QNetworkReply*)), this,
            SLOT(onRepositoryFinished(QNetworkReply*)));

    mManager->get(request);
}

void ApiRequest::onRepositoryFinished(QNetworkReply* reply)
{
    QVariantList list = replyToList(reply);
    if (list.size() > 0) {
        QVariantList model;
        for (int i = 0; i < list.size(); i++) {
            QVariantMap data;
            QVariantMap map = list[i].value<QVariantMap>();
            data["title"] = map["name"];
            data["user"] = map["full_name"].value<QString>().split("/")[0];
            QVariantMap owner = map["owner"].value<QVariantMap>();
            data["isAdmin"] = owner["site_admin"];
            data["desc"] = map["description"];
            data["isPrivate"] = map["private"];
            data["isFork"] = map["fork"];
            data["language"] = map["language"];
            data["forksCount"] = map["forks_count"];
            data["stargazersCount"] = map["stargazers_count"];
            data["watchersCount"] = map["watchers_count"];
            model.append(data);
        }
        reply->deleteLater();
        emit requestCompleted(model);
        return;
    }
    reply->deleteLater();
    emit requestFailed();
}

void ApiRequest::getIssues()
{
    QNetworkRequest request = RequestHeader::getRequestHeaderWithToken(QUrl(mRoot + mIssu));

    connect(mManager, SIGNAL(finished(QNetworkReply*)), this,
            SLOT(onIssueFinished(QNetworkReply*)));

    mManager->get(request);
}

void ApiRequest::onIssueFinished(QNetworkReply* reply)
{
    QVariantList list = replyToList(reply);
    if (list.size() > 0) {
        QVariantList model;
        for (int i = 0; i < list.size(); i++) {
            QVariantMap data;
            QVariantMap map = list[i].value<QVariantMap>();
            data["title"] = map["title"];
            data["body"] = map["body"];
            if (map.contains("assignee") && !map["assignee"].isNull()) {
                data["assign_user"] = map["assignee"].value<QVariantMap>()["login"];
            }
            if (map.contains("user") && !map["user"].isNull()) {
                data["user"] = map["user"].value<QVariantMap>()["login"];
            }
            data["comments"] = map["comments"];
            model.append(data);
        }
        reply->deleteLater();
        emit requestCompleted(model);
        return;
    }
    reply->deleteLater();
    emit requestFailed();
}

void ApiRequest::getOrganizations()
{
    QNetworkRequest request = RequestHeader::getRequestHeaderWithToken(QUrl(mRoot + mOrga));

    connect(mManager, SIGNAL(finished(QNetworkReply*)), this,
            SLOT(onOrganizationFinished(QNetworkReply*)));

    mManager->get(request);
}

void ApiRequest::onOrganizationFinished(QNetworkReply* reply)
{
    QVariantList list = replyToList(reply);
    if (list.size() > 0) {
        QVariantList model;
        for (int i = 0; i < list.size(); i++) {
            QVariantMap data;
            QVariantMap map = list[i].value<QVariantMap>();
            data["title"] = map["login"];
            data["desc"] = map["description"];
            model.append(data);
        }
        reply->deleteLater();
        emit requestCompleted(model);
        return;
    }
    reply->deleteLater();
    emit requestFailed();
}

void ApiRequest::getGists()
{
    QNetworkRequest request = RequestHeader::getRequestHeaderWithToken(QUrl(mRoot + mGist));

    connect(mManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(onGistFinished(QNetworkReply*)));

    mManager->get(request);
}

void ApiRequest::onGistFinished(QNetworkReply* reply)
{
    QVariantList list = replyToList(reply);
    if (list.size() > 0) {
        QVariantList model;
        for (int i = 0; i < list.size(); i++) {
            QVariantMap data;
            QVariantMap map = list[i].value<QVariantMap>();
            data["title"] = map["description"];
            data["date"] = map["created_at"];
            data["url"] = map["html_url"];
            model.append(data);
        }
        reply->deleteLater();
        emit requestCompleted(model);
        return;
    }
    reply->deleteLater();
    emit requestFailed();
}

void ApiRequest::searchRepositories(QString q)
{
    QUrl url = mRoot + mSRep;
    url.addQueryItem("q", q);
    QNetworkRequest request = RequestHeader::getRequestHeaderWithToken(url);

    connect(mManager, SIGNAL(finished(QNetworkReply*)), this,
            SLOT(onSearchRepositoryFinished(QNetworkReply*)));

    mManager->get(request);
}

void ApiRequest::onSearchRepositoryFinished(QNetworkReply* reply)
{
    QVariantMap map = replyToMap(reply);
    if (map.size() > 0) {
        QVariantList model;
        QVariantList list = map["items"].value<QVariantList>();
        for (int i = 0; i < list.size(); i++) {
            QVariantMap data;
            QVariantMap map = list[i].value<QVariantMap>();
            data["title"] = map["full_name"];
            data["desc"] = map["description"];
            data["language"] = map["language"];
            data["forksCount"] = map["forks_count"];
            data["stargazersCount"] = map["stargazers_count"];
            data["watchersCount"] = map["watchers_count"];
            data["score"] = map["score"];
            model.append(data);
        }
        reply->deleteLater();
        emit requestCompleted(model);
        return;
    }
    reply->deleteLater();
    emit requestFailed();
}

/*
 * apirequest.h
 *
 *  Created on: 2016/02/05
 *      Author: ytanaka-PC
 */

#ifndef APIREQUEST_H_
#define APIREQUEST_H_

#include <QObject>

#include <bb/cascades/GroupDataModel>

#include <QtNetwork/QNetworkReply>
#include <QtNetwork/QAuthenticator>

using namespace bb::cascades;

class QNetworkAccessManager;

class ApiRequest : public QObject
{
    Q_OBJECT
public:
    ApiRequest(QObject *parent = 0);

    Q_INVOKABLE bool alreadyAuthentication();
    Q_INVOKABLE void authentication(QString username, QString password);
    Q_INVOKABLE void twoFactorAuthentication(QString username, QString password, QString factorKey);
    Q_INVOKABLE void updateToken(QString username, QString password);
    Q_INVOKABLE void deleteToken();

    Q_INVOKABLE void getNotifications();
    Q_INVOKABLE void getRepositories();
    Q_INVOKABLE void getOrganizations();
    Q_INVOKABLE void getIssues();
    Q_INVOKABLE void getGists();
    Q_INVOKABLE void getComment();

    Q_INVOKABLE void searchRepositories(QString q);

private Q_SLOTS:
    void onAuthenticationFinished(QNetworkReply* reply);
    void onUpdateFinished(QNetworkReply* reply);
    void onDeleteFinished(QNetworkReply* reply);
    void onNotificationFinished(QNetworkReply* reply);
    void onRepositoryFinished(QNetworkReply* reply);
    void onOrganizationFinished(QNetworkReply* reply);
    void onIssueFinished(QNetworkReply* reply);
    void onGistFinished(QNetworkReply* reply);
    void onCommentFinished(QNetworkReply* reply);

    void onSearchRepositoryFinished(QNetworkReply* reply);

private:
    QVariantMap replyToMap(QNetworkReply* reply);
    QVariantList replyToList(QNetworkReply* reply);
    QByteArray getAuthRequestBody();
    QNetworkAccessManager* mManager;
    static const QString mRoot;
    static const QString mAuth;
    static const QString mDelt;
    static const QString mNoti;
    static const QString mRepo;
    static const QString mOrga;
    static const QString mIssu;
    static const QString mGist;
    static const QString mComm;
    static const QString mSRep;

Q_SIGNALS:
    void twoFactorAuthenticationRequest();
    void authRequestCompleted();
    void authRequestFailed();
    void requestCompleted(QVariantList model);
    void requestFailed();
};

#endif /* APIREQUEST_H_ */

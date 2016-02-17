/*
 * requestheader.cpp
 *
 *  Created on: 2016/02/07
 *      Author: CORDEA
 */

#include <src/requestheader.h>

#include <QtNetwork/QNetworkRequest>
#include <QSettings>

#include "constants.h"

RequestHeader::RequestHeader()
{
    // TODO Auto-generated constructor stub

}

RequestHeader::~RequestHeader()
{
    // TODO Auto-generated destructor stub
}

QNetworkRequest RequestHeader::getRequestHeaderForAuthentication(QString username, QString password, QUrl url)
{
    QNetworkRequest request;
    request.setUrl(url);
    request.setRawHeader("Content-Type", "application/json");
    request.setRawHeader("Accept", "application/vnd.github.v3+json");

    QByteArray auth = QString("%1:%2").arg(username).arg(password).toLocal8Bit().toBase64();
    request.setRawHeader("Authorization", "Basic " + auth);

    return request;
}

QNetworkRequest RequestHeader::getRequestHeaderWithToken(QUrl url)
{
    QSettings settings(Constants::mOrgName, Constants::mAppName);
    QString token = settings.value("token", "").value<QString>();

    QNetworkRequest request;
    request.setUrl(url);
    request.setRawHeader("Content-Type", "application/json");
    request.setRawHeader("Accept", "application/vnd.github.v3+json");

    if (!token.isEmpty()) {
        request.setRawHeader("Authorization", "token " + token.toLocal8Bit());
    }

    return request;
}

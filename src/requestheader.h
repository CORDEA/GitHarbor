/*
 * requestheader.h
 *
 *  Created on: 2016/02/07
 *      Author: CORDEA
 */

#ifndef REQUESTHEADER_H_
#define REQUESTHEADER_H_

#include <QtNetwork/QNetworkRequest>

class RequestHeader
{
public:
    RequestHeader();
    virtual ~RequestHeader();

    static QNetworkRequest getRequestHeaderForAuthentication(QString username, QString password, QUrl url);
    static QNetworkRequest getRequestHeaderWithToken(QUrl url);
};

#endif /* REQUESTHEADER_H_ */

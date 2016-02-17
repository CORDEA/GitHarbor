/*
 * invokehelper.cpp
 *
 *  Created on: 2016/02/15
 *      Author: CORDEA
 */

#include <src/invokehelper.h>

#include <bb/system/InvokeRequest>
#include <bb/system/InvokeManager>

using namespace bb::system;

InvokeHelper::InvokeHelper(QObject *parent) :
        QObject(parent)
{
    // TODO Auto-generated constructor stub

}

void InvokeHelper::openBrowser(QString url)
{
    InvokeRequest request;
    request.setTarget("sys.browser");
    request.setAction("bb.action.OPEN");
    request.setMimeType("text/html");
    request.setUri(QUrl(url));
    InvokeManager manager;
    Q_UNUSED(manager.invoke(request));
}

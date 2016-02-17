/*
 * invokehelper.h
 *
 *  Created on: 2016/02/15
 *      Author: CORDEA
 */

#ifndef INVOKEHELPER_H_
#define INVOKEHELPER_H_
class InvokeHelper : public QObject
{
    Q_OBJECT
public:
    InvokeHelper(QObject *parent = 0);
    Q_INVOKABLE void openBrowser(QString url);
};

#endif /* INVOKEHELPER_H_ */

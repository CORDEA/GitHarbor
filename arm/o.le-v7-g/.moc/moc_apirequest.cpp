/****************************************************************************
** Meta object code from reading C++ file 'apirequest.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.6)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../src/apirequest.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'apirequest.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.6. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_ApiRequest[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      27,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       5,       // signalCount

 // signals: signature, parameters, type, tag, flags
      12,   11,   11,   11, 0x05,
      45,   11,   11,   11, 0x05,
      68,   11,   11,   11, 0x05,
      94,   88,   11,   11, 0x05,
     125,   11,   11,   11, 0x05,

 // slots: signature, parameters, type, tag, flags
     147,  141,   11,   11, 0x08,
     188,  141,   11,   11, 0x08,
     221,  141,   11,   11, 0x08,
     254,  141,   11,   11, 0x08,
     293,  141,   11,   11, 0x08,
     330,  141,   11,   11, 0x08,
     369,  141,   11,   11, 0x08,
     401,  141,   11,   11, 0x08,
     432,  141,   11,   11, 0x08,
     466,  141,   11,   11, 0x08,

 // methods: signature, parameters, type, tag, flags
     514,   11,  509,   11, 0x02,
     556,  538,   11,   11, 0x02,
     616,  588,   11,   11, 0x02,
     665,  538,   11,   11, 0x02,
     694,   11,   11,   11, 0x02,
     708,   11,   11,   11, 0x02,
     727,   11,   11,   11, 0x02,
     745,   11,   11,   11, 0x02,
     764,   11,   11,   11, 0x02,
     776,   11,   11,   11, 0x02,
     787,   11,   11,   11, 0x02,
     802,  800,   11,   11, 0x02,

       0        // eod
};

static const char qt_meta_stringdata_ApiRequest[] = {
    "ApiRequest\0\0twoFactorAuthenticationRequest()\0"
    "authRequestCompleted()\0authRequestFailed()\0"
    "model\0requestCompleted(QVariantList)\0"
    "requestFailed()\0reply\0"
    "onAuthenticationFinished(QNetworkReply*)\0"
    "onUpdateFinished(QNetworkReply*)\0"
    "onDeleteFinished(QNetworkReply*)\0"
    "onNotificationFinished(QNetworkReply*)\0"
    "onRepositoryFinished(QNetworkReply*)\0"
    "onOrganizationFinished(QNetworkReply*)\0"
    "onIssueFinished(QNetworkReply*)\0"
    "onGistFinished(QNetworkReply*)\0"
    "onCommentFinished(QNetworkReply*)\0"
    "onSearchRepositoryFinished(QNetworkReply*)\0"
    "bool\0alreadyAuthentication()\0"
    "username,password\0authentication(QString,QString)\0"
    "username,password,factorKey\0"
    "twoFactorAuthentication(QString,QString,QString)\0"
    "updateToken(QString,QString)\0deleteToken()\0"
    "getNotifications()\0getRepositories()\0"
    "getOrganizations()\0getIssues()\0"
    "getGists()\0getComment()\0q\0"
    "searchRepositories(QString)\0"
};

void ApiRequest::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        ApiRequest *_t = static_cast<ApiRequest *>(_o);
        switch (_id) {
        case 0: _t->twoFactorAuthenticationRequest(); break;
        case 1: _t->authRequestCompleted(); break;
        case 2: _t->authRequestFailed(); break;
        case 3: _t->requestCompleted((*reinterpret_cast< QVariantList(*)>(_a[1]))); break;
        case 4: _t->requestFailed(); break;
        case 5: _t->onAuthenticationFinished((*reinterpret_cast< QNetworkReply*(*)>(_a[1]))); break;
        case 6: _t->onUpdateFinished((*reinterpret_cast< QNetworkReply*(*)>(_a[1]))); break;
        case 7: _t->onDeleteFinished((*reinterpret_cast< QNetworkReply*(*)>(_a[1]))); break;
        case 8: _t->onNotificationFinished((*reinterpret_cast< QNetworkReply*(*)>(_a[1]))); break;
        case 9: _t->onRepositoryFinished((*reinterpret_cast< QNetworkReply*(*)>(_a[1]))); break;
        case 10: _t->onOrganizationFinished((*reinterpret_cast< QNetworkReply*(*)>(_a[1]))); break;
        case 11: _t->onIssueFinished((*reinterpret_cast< QNetworkReply*(*)>(_a[1]))); break;
        case 12: _t->onGistFinished((*reinterpret_cast< QNetworkReply*(*)>(_a[1]))); break;
        case 13: _t->onCommentFinished((*reinterpret_cast< QNetworkReply*(*)>(_a[1]))); break;
        case 14: _t->onSearchRepositoryFinished((*reinterpret_cast< QNetworkReply*(*)>(_a[1]))); break;
        case 15: { bool _r = _t->alreadyAuthentication();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 16: _t->authentication((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 17: _t->twoFactorAuthentication((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< QString(*)>(_a[3]))); break;
        case 18: _t->updateToken((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 19: _t->deleteToken(); break;
        case 20: _t->getNotifications(); break;
        case 21: _t->getRepositories(); break;
        case 22: _t->getOrganizations(); break;
        case 23: _t->getIssues(); break;
        case 24: _t->getGists(); break;
        case 25: _t->getComment(); break;
        case 26: _t->searchRepositories((*reinterpret_cast< QString(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData ApiRequest::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject ApiRequest::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_ApiRequest,
      qt_meta_data_ApiRequest, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &ApiRequest::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *ApiRequest::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *ApiRequest::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_ApiRequest))
        return static_cast<void*>(const_cast< ApiRequest*>(this));
    return QObject::qt_metacast(_clname);
}

int ApiRequest::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 27)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 27;
    }
    return _id;
}

// SIGNAL 0
void ApiRequest::twoFactorAuthenticationRequest()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}

// SIGNAL 1
void ApiRequest::authRequestCompleted()
{
    QMetaObject::activate(this, &staticMetaObject, 1, 0);
}

// SIGNAL 2
void ApiRequest::authRequestFailed()
{
    QMetaObject::activate(this, &staticMetaObject, 2, 0);
}

// SIGNAL 3
void ApiRequest::requestCompleted(QVariantList _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void ApiRequest::requestFailed()
{
    QMetaObject::activate(this, &staticMetaObject, 4, 0);
}
QT_END_MOC_NAMESPACE

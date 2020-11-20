/****************************************************************************
** Meta object code from reading C++ file 'HotplugWatcher.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.3.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../module/hotplug/HotplugWatcher.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'HotplugWatcher.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.3.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_HotplugDevice_t {
    QByteArrayData data[7];
    char stringdata[85];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_HotplugDevice_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_HotplugDevice_t qt_meta_stringdata_HotplugDevice = {
    {
QT_MOC_LITERAL(0, 0, 13),
QT_MOC_LITERAL(1, 14, 21),
QT_MOC_LITERAL(2, 36, 0),
QT_MOC_LITERAL(3, 37, 13),
QT_MOC_LITERAL(4, 51, 3),
QT_MOC_LITERAL(5, 55, 18),
QT_MOC_LITERAL(6, 74, 10)
    },
    "HotplugDevice\0sigFormatUnrecognized\0"
    "\0sendSysCmdMsg\0Cmd\0mediaConnectedFail\0"
    "onTimerOut"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_HotplugDevice[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   34,    2, 0x06 /* Public */,
       3,    1,   35,    2, 0x06 /* Public */,
       5,    0,   38,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       6,    0,   39,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    4,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,

       0        // eod
};

void HotplugDevice::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        HotplugDevice *_t = static_cast<HotplugDevice *>(_o);
        switch (_id) {
        case 0: _t->sigFormatUnrecognized(); break;
        case 1: _t->sendSysCmdMsg((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 2: _t->mediaConnectedFail(); break;
        case 3: _t->onTimerOut(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (HotplugDevice::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&HotplugDevice::sigFormatUnrecognized)) {
                *result = 0;
            }
        }
        {
            typedef void (HotplugDevice::*_t)(const QString & );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&HotplugDevice::sendSysCmdMsg)) {
                *result = 1;
            }
        }
        {
            typedef void (HotplugDevice::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&HotplugDevice::mediaConnectedFail)) {
                *result = 2;
            }
        }
    }
}

const QMetaObject HotplugDevice::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_HotplugDevice.data,
      qt_meta_data_HotplugDevice,  qt_static_metacall, 0, 0}
};


const QMetaObject *HotplugDevice::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *HotplugDevice::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_HotplugDevice.stringdata))
        return static_cast<void*>(const_cast< HotplugDevice*>(this));
    return QObject::qt_metacast(_clname);
}

int HotplugDevice::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 4)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 4;
    }
    return _id;
}

// SIGNAL 0
void HotplugDevice::sigFormatUnrecognized()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}

// SIGNAL 1
void HotplugDevice::sendSysCmdMsg(const QString & _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void HotplugDevice::mediaConnectedFail()
{
    QMetaObject::activate(this, &staticMetaObject, 2, 0);
}
struct qt_meta_stringdata_HotplugWatcher_t {
    QByteArrayData data[15];
    char stringdata[243];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_HotplugWatcher_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_HotplugWatcher_t qt_meta_stringdata_HotplugWatcher = {
    {
QT_MOC_LITERAL(0, 0, 14),
QT_MOC_LITERAL(1, 15, 17),
QT_MOC_LITERAL(2, 33, 0),
QT_MOC_LITERAL(3, 34, 17),
QT_MOC_LITERAL(4, 52, 19),
QT_MOC_LITERAL(5, 72, 19),
QT_MOC_LITERAL(6, 92, 19),
QT_MOC_LITERAL(7, 112, 19),
QT_MOC_LITERAL(8, 132, 20),
QT_MOC_LITERAL(9, 153, 6),
QT_MOC_LITERAL(10, 160, 3),
QT_MOC_LITERAL(11, 164, 20),
QT_MOC_LITERAL(12, 185, 22),
QT_MOC_LITERAL(13, 208, 20),
QT_MOC_LITERAL(14, 229, 13)
    },
    "HotplugWatcher\0sigUsbDeviceAdded\0\0"
    "sigMmcDeviceAdded\0sigUsbDeviceChanged\0"
    "sigMmcDeviceChanged\0sigUsbDeviceRemoved\0"
    "sigMmcDeviceRemoved\0sigUsbStorageUpdated\0"
    "action\0dev\0sigMmcStorageUpdated\0"
    "sigtmcUsbDeviceRemoved\0sigtmcUsbDeviceAdded\0"
    "slotReadyRead"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_HotplugWatcher[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      11,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
      10,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   69,    2, 0x06 /* Public */,
       3,    0,   70,    2, 0x06 /* Public */,
       4,    0,   71,    2, 0x06 /* Public */,
       5,    0,   72,    2, 0x06 /* Public */,
       6,    0,   73,    2, 0x06 /* Public */,
       7,    0,   74,    2, 0x06 /* Public */,
       8,    2,   75,    2, 0x06 /* Public */,
      11,    2,   80,    2, 0x06 /* Public */,
      12,    0,   85,    2, 0x06 /* Public */,
      13,    0,   86,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      14,    0,   87,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString, QMetaType::QString,    9,   10,
    QMetaType::Void, QMetaType::QString, QMetaType::QString,    9,   10,
    QMetaType::Void,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,

       0        // eod
};

void HotplugWatcher::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        HotplugWatcher *_t = static_cast<HotplugWatcher *>(_o);
        switch (_id) {
        case 0: _t->sigUsbDeviceAdded(); break;
        case 1: _t->sigMmcDeviceAdded(); break;
        case 2: _t->sigUsbDeviceChanged(); break;
        case 3: _t->sigMmcDeviceChanged(); break;
        case 4: _t->sigUsbDeviceRemoved(); break;
        case 5: _t->sigMmcDeviceRemoved(); break;
        case 6: _t->sigUsbStorageUpdated((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 7: _t->sigMmcStorageUpdated((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 8: _t->sigtmcUsbDeviceRemoved(); break;
        case 9: _t->sigtmcUsbDeviceAdded(); break;
        case 10: _t->slotReadyRead(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (HotplugWatcher::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&HotplugWatcher::sigUsbDeviceAdded)) {
                *result = 0;
            }
        }
        {
            typedef void (HotplugWatcher::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&HotplugWatcher::sigMmcDeviceAdded)) {
                *result = 1;
            }
        }
        {
            typedef void (HotplugWatcher::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&HotplugWatcher::sigUsbDeviceChanged)) {
                *result = 2;
            }
        }
        {
            typedef void (HotplugWatcher::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&HotplugWatcher::sigMmcDeviceChanged)) {
                *result = 3;
            }
        }
        {
            typedef void (HotplugWatcher::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&HotplugWatcher::sigUsbDeviceRemoved)) {
                *result = 4;
            }
        }
        {
            typedef void (HotplugWatcher::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&HotplugWatcher::sigMmcDeviceRemoved)) {
                *result = 5;
            }
        }
        {
            typedef void (HotplugWatcher::*_t)(QString , QString );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&HotplugWatcher::sigUsbStorageUpdated)) {
                *result = 6;
            }
        }
        {
            typedef void (HotplugWatcher::*_t)(QString , QString );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&HotplugWatcher::sigMmcStorageUpdated)) {
                *result = 7;
            }
        }
        {
            typedef void (HotplugWatcher::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&HotplugWatcher::sigtmcUsbDeviceRemoved)) {
                *result = 8;
            }
        }
        {
            typedef void (HotplugWatcher::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&HotplugWatcher::sigtmcUsbDeviceAdded)) {
                *result = 9;
            }
        }
    }
}

const QMetaObject HotplugWatcher::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_HotplugWatcher.data,
      qt_meta_data_HotplugWatcher,  qt_static_metacall, 0, 0}
};


const QMetaObject *HotplugWatcher::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *HotplugWatcher::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_HotplugWatcher.stringdata))
        return static_cast<void*>(const_cast< HotplugWatcher*>(this));
    return QObject::qt_metacast(_clname);
}

int HotplugWatcher::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 11)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 11;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 11)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 11;
    }
    return _id;
}

// SIGNAL 0
void HotplugWatcher::sigUsbDeviceAdded()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}

// SIGNAL 1
void HotplugWatcher::sigMmcDeviceAdded()
{
    QMetaObject::activate(this, &staticMetaObject, 1, 0);
}

// SIGNAL 2
void HotplugWatcher::sigUsbDeviceChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 2, 0);
}

// SIGNAL 3
void HotplugWatcher::sigMmcDeviceChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 3, 0);
}

// SIGNAL 4
void HotplugWatcher::sigUsbDeviceRemoved()
{
    QMetaObject::activate(this, &staticMetaObject, 4, 0);
}

// SIGNAL 5
void HotplugWatcher::sigMmcDeviceRemoved()
{
    QMetaObject::activate(this, &staticMetaObject, 5, 0);
}

// SIGNAL 6
void HotplugWatcher::sigUsbStorageUpdated(QString _t1, QString _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 6, _a);
}

// SIGNAL 7
void HotplugWatcher::sigMmcStorageUpdated(QString _t1, QString _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 7, _a);
}

// SIGNAL 8
void HotplugWatcher::sigtmcUsbDeviceRemoved()
{
    QMetaObject::activate(this, &staticMetaObject, 8, 0);
}

// SIGNAL 9
void HotplugWatcher::sigtmcUsbDeviceAdded()
{
    QMetaObject::activate(this, &staticMetaObject, 9, 0);
}
QT_END_MOC_NAMESPACE

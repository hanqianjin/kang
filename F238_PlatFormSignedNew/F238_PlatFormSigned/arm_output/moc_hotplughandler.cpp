/****************************************************************************
** Meta object code from reading C++ file 'hotplughandler.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.3.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../module/hotplug/hotplughandler.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'hotplughandler.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.3.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_HotplugManager_t {
    QByteArrayData data[17];
    char stringdata[271];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_HotplugManager_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_HotplugManager_t qt_meta_stringdata_HotplugManager = {
    {
QT_MOC_LITERAL(0, 0, 14),
QT_MOC_LITERAL(1, 15, 22),
QT_MOC_LITERAL(2, 38, 0),
QT_MOC_LITERAL(3, 39, 15),
QT_MOC_LITERAL(4, 55, 16),
QT_MOC_LITERAL(5, 72, 16),
QT_MOC_LITERAL(6, 89, 24),
QT_MOC_LITERAL(7, 114, 24),
QT_MOC_LITERAL(8, 139, 20),
QT_MOC_LITERAL(9, 160, 20),
QT_MOC_LITERAL(10, 181, 6),
QT_MOC_LITERAL(11, 188, 3),
QT_MOC_LITERAL(12, 192, 20),
QT_MOC_LITERAL(13, 213, 18),
QT_MOC_LITERAL(14, 232, 18),
QT_MOC_LITERAL(15, 251, 15),
QT_MOC_LITERAL(16, 267, 3)
    },
    "HotplugManager\0sigDeviceStatusUpdated\0"
    "\0sigTmcUsbPlugIn\0sigTmcUsbPlugOut\0"
    "slotUsbDeviceAdd\0slotUsbFormatUnrecognize\0"
    "slotMmcFormatUnrecognize\0onMediaConnectedFail\0"
    "slotUsbStorageUpdate\0action\0dev\0"
    "slotMmcStorageUpdate\0onMmcDeviceRemoved\0"
    "onUsbDeviceRemoved\0onSendSysCmdMsg\0"
    "cmd"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_HotplugManager[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      12,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   74,    2, 0x06 /* Public */,
       3,    0,   75,    2, 0x06 /* Public */,
       4,    0,   76,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       5,    0,   77,    2, 0x08 /* Private */,
       6,    0,   78,    2, 0x08 /* Private */,
       7,    0,   79,    2, 0x08 /* Private */,
       8,    0,   80,    2, 0x08 /* Private */,
       9,    2,   81,    2, 0x08 /* Private */,
      12,    2,   86,    2, 0x08 /* Private */,
      13,    0,   91,    2, 0x08 /* Private */,
      14,    0,   92,    2, 0x08 /* Private */,
      15,    1,   93,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString, QMetaType::QString,   10,   11,
    QMetaType::Void, QMetaType::QString, QMetaType::QString,   10,   11,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,   16,

       0        // eod
};

void HotplugManager::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        HotplugManager *_t = static_cast<HotplugManager *>(_o);
        switch (_id) {
        case 0: _t->sigDeviceStatusUpdated(); break;
        case 1: _t->sigTmcUsbPlugIn(); break;
        case 2: _t->sigTmcUsbPlugOut(); break;
        case 3: _t->slotUsbDeviceAdd(); break;
        case 4: _t->slotUsbFormatUnrecognize(); break;
        case 5: _t->slotMmcFormatUnrecognize(); break;
        case 6: _t->onMediaConnectedFail(); break;
        case 7: _t->slotUsbStorageUpdate((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 8: _t->slotMmcStorageUpdate((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 9: _t->onMmcDeviceRemoved(); break;
        case 10: _t->onUsbDeviceRemoved(); break;
        case 11: _t->onSendSysCmdMsg((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (HotplugManager::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&HotplugManager::sigDeviceStatusUpdated)) {
                *result = 0;
            }
        }
        {
            typedef void (HotplugManager::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&HotplugManager::sigTmcUsbPlugIn)) {
                *result = 1;
            }
        }
        {
            typedef void (HotplugManager::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&HotplugManager::sigTmcUsbPlugOut)) {
                *result = 2;
            }
        }
    }
}

const QMetaObject HotplugManager::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_HotplugManager.data,
      qt_meta_data_HotplugManager,  qt_static_metacall, 0, 0}
};


const QMetaObject *HotplugManager::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *HotplugManager::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_HotplugManager.stringdata))
        return static_cast<void*>(const_cast< HotplugManager*>(this));
    return QObject::qt_metacast(_clname);
}

int HotplugManager::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 12)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 12;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 12)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 12;
    }
    return _id;
}

// SIGNAL 0
void HotplugManager::sigDeviceStatusUpdated()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}

// SIGNAL 1
void HotplugManager::sigTmcUsbPlugIn()
{
    QMetaObject::activate(this, &staticMetaObject, 1, 0);
}

// SIGNAL 2
void HotplugManager::sigTmcUsbPlugOut()
{
    QMetaObject::activate(this, &staticMetaObject, 2, 0);
}
QT_END_MOC_NAMESPACE

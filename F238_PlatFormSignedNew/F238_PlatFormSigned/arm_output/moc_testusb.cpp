/****************************************************************************
** Meta object code from reading C++ file 'testusb.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.3.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../module/testusb.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'testusb.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.3.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_testUSB_t {
    QByteArrayData data[7];
    char stringdata[69];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_testUSB_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_testUSB_t qt_meta_stringdata_testUSB = {
    {
QT_MOC_LITERAL(0, 0, 7),
QT_MOC_LITERAL(1, 8, 8),
QT_MOC_LITERAL(2, 17, 0),
QT_MOC_LITERAL(3, 18, 6),
QT_MOC_LITERAL(4, 25, 6),
QT_MOC_LITERAL(5, 32, 13),
QT_MOC_LITERAL(6, 46, 22)
    },
    "testUSB\0testOnce\0\0wSpeed\0rSpeed\0"
    "StatusUpdated\0on_DeviceStatusUpdated"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_testUSB[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    2,   29,    2, 0x06 /* Public */,
       5,    1,   34,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       6,    0,   37,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, QMetaType::QString, QMetaType::QString,    3,    4,
    QMetaType::Void, QMetaType::Int,    2,

 // slots: parameters
    QMetaType::Void,

       0        // eod
};

void testUSB::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        testUSB *_t = static_cast<testUSB *>(_o);
        switch (_id) {
        case 0: _t->testOnce((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 1: _t->StatusUpdated((*reinterpret_cast< qint32(*)>(_a[1]))); break;
        case 2: _t->on_DeviceStatusUpdated(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (testUSB::*_t)(QString , QString );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&testUSB::testOnce)) {
                *result = 0;
            }
        }
        {
            typedef void (testUSB::*_t)(qint32 );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&testUSB::StatusUpdated)) {
                *result = 1;
            }
        }
    }
}

const QMetaObject testUSB::staticMetaObject = {
    { &QThread::staticMetaObject, qt_meta_stringdata_testUSB.data,
      qt_meta_data_testUSB,  qt_static_metacall, 0, 0}
};


const QMetaObject *testUSB::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *testUSB::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_testUSB.stringdata))
        return static_cast<void*>(const_cast< testUSB*>(this));
    return QThread::qt_metacast(_clname);
}

int testUSB::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QThread::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 3)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 3)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 3;
    }
    return _id;
}

// SIGNAL 0
void testUSB::testOnce(QString _t1, QString _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void testUSB::StatusUpdated(qint32 _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_END_MOC_NAMESPACE

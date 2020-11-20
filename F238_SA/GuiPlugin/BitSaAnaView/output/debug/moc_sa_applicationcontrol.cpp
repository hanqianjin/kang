/****************************************************************************
** Meta object code from reading C++ file 'sa_applicationcontrol.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.9.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../sa_applicationcontrol.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'sa_applicationcontrol.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.9.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_controlInterface_t {
    QByteArrayData data[12];
    char stringdata0[180];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_controlInterface_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_controlInterface_t qt_meta_stringdata_controlInterface = {
    {
QT_MOC_LITERAL(0, 0, 16), // "controlInterface"
QT_MOC_LITERAL(1, 17, 11), // "infoRefresh"
QT_MOC_LITERAL(2, 29, 0), // ""
QT_MOC_LITERAL(3, 30, 5), // "mType"
QT_MOC_LITERAL(4, 36, 6), // "mIndex"
QT_MOC_LITERAL(5, 43, 16), // "signalModeChange"
QT_MOC_LITERAL(6, 60, 21), // "signalZeroCalComplete"
QT_MOC_LITERAL(7, 82, 4), // "bRet"
QT_MOC_LITERAL(8, 87, 21), // "ZeroRestrainCelibrate"
QT_MOC_LITERAL(9, 109, 23), // "setZeroRestrainFromFile"
QT_MOC_LITERAL(10, 133, 22), // "setZeroRestrainCalStop"
QT_MOC_LITERAL(11, 156, 23) // "setBeginZeroRestrainCal"

    },
    "controlInterface\0infoRefresh\0\0mType\0"
    "mIndex\0signalModeChange\0signalZeroCalComplete\0"
    "bRet\0ZeroRestrainCelibrate\0"
    "setZeroRestrainFromFile\0setZeroRestrainCalStop\0"
    "setBeginZeroRestrainCal"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_controlInterface[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       7,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    2,   49,    2, 0x06 /* Public */,
       5,    0,   54,    2, 0x06 /* Public */,
       6,    1,   55,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       8,    0,   58,    2, 0x0a /* Public */,
       9,    0,   59,    2, 0x0a /* Public */,
      10,    0,   60,    2, 0x0a /* Public */,
      11,    0,   61,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::Int, QMetaType::Int,    3,    4,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool,    7,

 // slots: parameters
    QMetaType::Bool,
    QMetaType::Bool,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void controlInterface::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        controlInterface *_t = static_cast<controlInterface *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->infoRefresh((*reinterpret_cast< qint32(*)>(_a[1])),(*reinterpret_cast< qint32(*)>(_a[2]))); break;
        case 1: _t->signalModeChange(); break;
        case 2: _t->signalZeroCalComplete((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 3: { bool _r = _t->ZeroRestrainCelibrate();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 4: { bool _r = _t->setZeroRestrainFromFile();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 5: _t->setZeroRestrainCalStop(); break;
        case 6: _t->setBeginZeroRestrainCal(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (controlInterface::*_t)(qint32 , qint32 );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&controlInterface::infoRefresh)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (controlInterface::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&controlInterface::signalModeChange)) {
                *result = 1;
                return;
            }
        }
        {
            typedef void (controlInterface::*_t)(bool );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&controlInterface::signalZeroCalComplete)) {
                *result = 2;
                return;
            }
        }
    }
}

const QMetaObject controlInterface::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_controlInterface.data,
      qt_meta_data_controlInterface,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *controlInterface::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *controlInterface::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_controlInterface.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int controlInterface::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 7)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 7;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 7)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 7;
    }
    return _id;
}

// SIGNAL 0
void controlInterface::infoRefresh(qint32 _t1, qint32 _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void controlInterface::signalModeChange()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void controlInterface::signalZeroCalComplete(bool _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE

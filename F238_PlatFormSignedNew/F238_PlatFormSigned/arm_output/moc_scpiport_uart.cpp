/****************************************************************************
** Meta object code from reading C++ file 'scpiport_uart.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.3.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../multicommu/scpiport_uart.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'scpiport_uart.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.3.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_ScpiPort_uart_t {
    QByteArrayData data[8];
    char stringdata[114];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_ScpiPort_uart_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_ScpiPort_uart_t qt_meta_stringdata_ScpiPort_uart = {
    {
QT_MOC_LITERAL(0, 0, 13),
QT_MOC_LITERAL(1, 14, 20),
QT_MOC_LITERAL(2, 35, 0),
QT_MOC_LITERAL(3, 36, 21),
QT_MOC_LITERAL(4, 58, 11),
QT_MOC_LITERAL(5, 70, 28),
QT_MOC_LITERAL(6, 99, 1),
QT_MOC_LITERAL(7, 101, 12)
    },
    "ScpiPort_uart\0slotAcceptConnection\0\0"
    "slotReadUartConnected\0handleError\0"
    "QSerialPort::SerialPortError\0e\0"
    "slotRestConn"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ScpiPort_uart[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   34,    2, 0x0a /* Public */,
       3,    0,   35,    2, 0x0a /* Public */,
       4,    1,   36,    2, 0x0a /* Public */,
       7,    0,   39,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 5,    6,
    QMetaType::Void,

       0        // eod
};

void ScpiPort_uart::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        ScpiPort_uart *_t = static_cast<ScpiPort_uart *>(_o);
        switch (_id) {
        case 0: _t->slotAcceptConnection(); break;
        case 1: _t->slotReadUartConnected(); break;
        case 2: _t->handleError((*reinterpret_cast< QSerialPort::SerialPortError(*)>(_a[1]))); break;
        case 3: _t->slotRestConn(); break;
        default: ;
        }
    }
}

const QMetaObject ScpiPort_uart::staticMetaObject = {
    { &ScpiPort_common::staticMetaObject, qt_meta_stringdata_ScpiPort_uart.data,
      qt_meta_data_ScpiPort_uart,  qt_static_metacall, 0, 0}
};


const QMetaObject *ScpiPort_uart::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ScpiPort_uart::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_ScpiPort_uart.stringdata))
        return static_cast<void*>(const_cast< ScpiPort_uart*>(this));
    return ScpiPort_common::qt_metacast(_clname);
}

int ScpiPort_uart::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = ScpiPort_common::qt_metacall(_c, _id, _a);
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
QT_END_MOC_NAMESPACE

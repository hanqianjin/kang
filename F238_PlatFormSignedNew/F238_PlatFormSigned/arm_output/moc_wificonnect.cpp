/****************************************************************************
** Meta object code from reading C++ file 'wificonnect.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.3.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../module/wificonnect.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'wificonnect.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.3.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_WifiConnect_t {
    QByteArrayData data[9];
    char stringdata[143];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_WifiConnect_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_WifiConnect_t qt_meta_stringdata_WifiConnect = {
    {
QT_MOC_LITERAL(0, 0, 11),
QT_MOC_LITERAL(1, 12, 18),
QT_MOC_LITERAL(2, 31, 0),
QT_MOC_LITERAL(3, 32, 20),
QT_MOC_LITERAL(4, 53, 20),
QT_MOC_LITERAL(5, 74, 7),
QT_MOC_LITERAL(6, 82, 23),
QT_MOC_LITERAL(7, 106, 25),
QT_MOC_LITERAL(8, 132, 10)
    },
    "WifiConnect\0on_pb_pair_clicked\0\0"
    "on_pb_cancel_clicked\0on_pb_pwView_clicked\0"
    "checked\0on_passWordEdit_clicked\0"
    "on_passWordEdit_loseFocus\0on_timeout"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_WifiConnect[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   44,    2, 0x08 /* Private */,
       3,    0,   45,    2, 0x08 /* Private */,
       4,    1,   46,    2, 0x08 /* Private */,
       6,    0,   49,    2, 0x08 /* Private */,
       7,    0,   50,    2, 0x08 /* Private */,
       8,    0,   51,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool,    5,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void WifiConnect::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        WifiConnect *_t = static_cast<WifiConnect *>(_o);
        switch (_id) {
        case 0: _t->on_pb_pair_clicked(); break;
        case 1: _t->on_pb_cancel_clicked(); break;
        case 2: _t->on_pb_pwView_clicked((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 3: _t->on_passWordEdit_clicked(); break;
        case 4: _t->on_passWordEdit_loseFocus(); break;
        case 5: _t->on_timeout(); break;
        default: ;
        }
    }
}

const QMetaObject WifiConnect::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_WifiConnect.data,
      qt_meta_data_WifiConnect,  qt_static_metacall, 0, 0}
};


const QMetaObject *WifiConnect::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *WifiConnect::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_WifiConnect.stringdata))
        return static_cast<void*>(const_cast< WifiConnect*>(this));
    return QDialog::qt_metacast(_clname);
}

int WifiConnect::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 6)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 6)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 6;
    }
    return _id;
}
QT_END_MOC_NAMESPACE

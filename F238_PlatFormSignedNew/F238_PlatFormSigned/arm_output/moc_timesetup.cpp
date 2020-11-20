/****************************************************************************
** Meta object code from reading C++ file 'timesetup.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.3.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../plugin/timesetup.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'timesetup.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.3.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_timeSetup_t {
    QByteArrayData data[10];
    char stringdata[167];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_timeSetup_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_timeSetup_t qt_meta_stringdata_timeSetup = {
    {
QT_MOC_LITERAL(0, 0, 9),
QT_MOC_LITERAL(1, 10, 18),
QT_MOC_LITERAL(2, 29, 0),
QT_MOC_LITERAL(3, 30, 20),
QT_MOC_LITERAL(4, 51, 18),
QT_MOC_LITERAL(5, 70, 20),
QT_MOC_LITERAL(6, 91, 17),
QT_MOC_LITERAL(7, 109, 19),
QT_MOC_LITERAL(8, 129, 16),
QT_MOC_LITERAL(9, 146, 20)
    },
    "timeSetup\0on_up_hour_clicked\0\0"
    "on_down_hour_clicked\0on_up_minu_clicked\0"
    "on_down_minu_clicked\0on_up_sec_clicked\0"
    "on_down_sec_clicked\0on_pb_ok_clicked\0"
    "on_pb_cancel_clicked"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_timeSetup[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       8,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   54,    2, 0x08 /* Private */,
       3,    0,   55,    2, 0x08 /* Private */,
       4,    0,   56,    2, 0x08 /* Private */,
       5,    0,   57,    2, 0x08 /* Private */,
       6,    0,   58,    2, 0x08 /* Private */,
       7,    0,   59,    2, 0x08 /* Private */,
       8,    0,   60,    2, 0x08 /* Private */,
       9,    0,   61,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void timeSetup::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        timeSetup *_t = static_cast<timeSetup *>(_o);
        switch (_id) {
        case 0: _t->on_up_hour_clicked(); break;
        case 1: _t->on_down_hour_clicked(); break;
        case 2: _t->on_up_minu_clicked(); break;
        case 3: _t->on_down_minu_clicked(); break;
        case 4: _t->on_up_sec_clicked(); break;
        case 5: _t->on_down_sec_clicked(); break;
        case 6: _t->on_pb_ok_clicked(); break;
        case 7: _t->on_pb_cancel_clicked(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObject timeSetup::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_timeSetup.data,
      qt_meta_data_timeSetup,  qt_static_metacall, 0, 0}
};


const QMetaObject *timeSetup::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *timeSetup::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_timeSetup.stringdata))
        return static_cast<void*>(const_cast< timeSetup*>(this));
    return QDialog::qt_metacast(_clname);
}

int timeSetup::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 8)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 8;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 8)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 8;
    }
    return _id;
}
QT_END_MOC_NAMESPACE

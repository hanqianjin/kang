/****************************************************************************
** Meta object code from reading C++ file 'plusmode.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.9.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../plusmode.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'plusmode.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.9.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_plusmode_t {
    QByteArrayData data[14];
    char stringdata0[251];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_plusmode_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_plusmode_t qt_meta_stringdata_plusmode = {
    {
QT_MOC_LITERAL(0, 0, 8), // "plusmode"
QT_MOC_LITERAL(1, 9, 18), // "buttonGroupClicked"
QT_MOC_LITERAL(2, 28, 0), // ""
QT_MOC_LITERAL(3, 29, 7), // "idIndex"
QT_MOC_LITERAL(4, 37, 15), // "meaGroupClicked"
QT_MOC_LITERAL(5, 53, 19), // "rtsameaGroupClicked"
QT_MOC_LITERAL(6, 73, 20), // "intermeaGroupClicked"
QT_MOC_LITERAL(7, 94, 17), // "pmmeaGroupClicked"
QT_MOC_LITERAL(8, 112, 21), // "ltefddmeaGroupClicked"
QT_MOC_LITERAL(9, 134, 21), // "ltetddmeaGroupClicked"
QT_MOC_LITERAL(10, 156, 19), // "fgnrmeaGroupClicked"
QT_MOC_LITERAL(11, 176, 24), // "on_pushButton_15_clicked"
QT_MOC_LITERAL(12, 201, 24), // "on_pushButton_16_clicked"
QT_MOC_LITERAL(13, 226, 24) // "on_pushButton_17_clicked"

    },
    "plusmode\0buttonGroupClicked\0\0idIndex\0"
    "meaGroupClicked\0rtsameaGroupClicked\0"
    "intermeaGroupClicked\0pmmeaGroupClicked\0"
    "ltefddmeaGroupClicked\0ltetddmeaGroupClicked\0"
    "fgnrmeaGroupClicked\0on_pushButton_15_clicked\0"
    "on_pushButton_16_clicked\0"
    "on_pushButton_17_clicked"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_plusmode[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      11,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    1,   69,    2, 0x08 /* Private */,
       4,    1,   72,    2, 0x08 /* Private */,
       5,    1,   75,    2, 0x08 /* Private */,
       6,    1,   78,    2, 0x08 /* Private */,
       7,    1,   81,    2, 0x08 /* Private */,
       8,    1,   84,    2, 0x08 /* Private */,
       9,    1,   87,    2, 0x08 /* Private */,
      10,    1,   90,    2, 0x08 /* Private */,
      11,    0,   93,    2, 0x08 /* Private */,
      12,    0,   94,    2, 0x08 /* Private */,
      13,    0,   95,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void plusmode::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        plusmode *_t = static_cast<plusmode *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->buttonGroupClicked((*reinterpret_cast< qint32(*)>(_a[1]))); break;
        case 1: _t->meaGroupClicked((*reinterpret_cast< qint32(*)>(_a[1]))); break;
        case 2: _t->rtsameaGroupClicked((*reinterpret_cast< qint32(*)>(_a[1]))); break;
        case 3: _t->intermeaGroupClicked((*reinterpret_cast< qint32(*)>(_a[1]))); break;
        case 4: _t->pmmeaGroupClicked((*reinterpret_cast< qint32(*)>(_a[1]))); break;
        case 5: _t->ltefddmeaGroupClicked((*reinterpret_cast< qint32(*)>(_a[1]))); break;
        case 6: _t->ltetddmeaGroupClicked((*reinterpret_cast< qint32(*)>(_a[1]))); break;
        case 7: _t->fgnrmeaGroupClicked((*reinterpret_cast< qint32(*)>(_a[1]))); break;
        case 8: _t->on_pushButton_15_clicked(); break;
        case 9: _t->on_pushButton_16_clicked(); break;
        case 10: _t->on_pushButton_17_clicked(); break;
        default: ;
        }
    }
}

const QMetaObject plusmode::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_plusmode.data,
      qt_meta_data_plusmode,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *plusmode::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *plusmode::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_plusmode.stringdata0))
        return static_cast<void*>(this);
    return QDialog::qt_metacast(_clname);
}

int plusmode::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
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
QT_WARNING_POP
QT_END_MOC_NAMESPACE

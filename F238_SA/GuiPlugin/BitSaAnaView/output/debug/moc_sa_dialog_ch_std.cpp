/****************************************************************************
** Meta object code from reading C++ file 'sa_dialog_ch_std.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.9.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../sa_dialog_ch_std.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'sa_dialog_ch_std.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.9.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_SA_Dialog_CH_Std_t {
    QByteArrayData data[14];
    char stringdata0[211];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_SA_Dialog_CH_Std_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_SA_Dialog_CH_Std_t qt_meta_stringdata_SA_Dialog_CH_Std = {
    {
QT_MOC_LITERAL(0, 0, 16), // "SA_Dialog_CH_Std"
QT_MOC_LITERAL(1, 17, 20), // "on_pb_cancel_clicked"
QT_MOC_LITERAL(2, 38, 0), // ""
QT_MOC_LITERAL(3, 39, 16), // "on_pb_up_clicked"
QT_MOC_LITERAL(4, 56, 18), // "on_pb_down_clicked"
QT_MOC_LITERAL(5, 75, 18), // "runBtnTypeFunction"
QT_MOC_LITERAL(6, 94, 5), // "index"
QT_MOC_LITERAL(7, 100, 21), // "on_currentCellChanged"
QT_MOC_LITERAL(8, 122, 10), // "currentRow"
QT_MOC_LITERAL(9, 133, 13), // "currentColumn"
QT_MOC_LITERAL(10, 147, 11), // "previousRow"
QT_MOC_LITERAL(11, 159, 14), // "previousColumn"
QT_MOC_LITERAL(12, 174, 19), // "on_pb_close_clicked"
QT_MOC_LITERAL(13, 194, 16) // "on_pb_ok_clicked"

    },
    "SA_Dialog_CH_Std\0on_pb_cancel_clicked\0"
    "\0on_pb_up_clicked\0on_pb_down_clicked\0"
    "runBtnTypeFunction\0index\0on_currentCellChanged\0"
    "currentRow\0currentColumn\0previousRow\0"
    "previousColumn\0on_pb_close_clicked\0"
    "on_pb_ok_clicked"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_SA_Dialog_CH_Std[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       7,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   49,    2, 0x08 /* Private */,
       3,    0,   50,    2, 0x08 /* Private */,
       4,    0,   51,    2, 0x08 /* Private */,
       5,    1,   52,    2, 0x08 /* Private */,
       7,    4,   55,    2, 0x08 /* Private */,
      12,    0,   64,    2, 0x08 /* Private */,
      13,    0,   65,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    6,
    QMetaType::Void, QMetaType::Int, QMetaType::Int, QMetaType::Int, QMetaType::Int,    8,    9,   10,   11,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void SA_Dialog_CH_Std::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        SA_Dialog_CH_Std *_t = static_cast<SA_Dialog_CH_Std *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->on_pb_cancel_clicked(); break;
        case 1: _t->on_pb_up_clicked(); break;
        case 2: _t->on_pb_down_clicked(); break;
        case 3: _t->runBtnTypeFunction((*reinterpret_cast< qint32(*)>(_a[1]))); break;
        case 4: _t->on_currentCellChanged((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3])),(*reinterpret_cast< int(*)>(_a[4]))); break;
        case 5: _t->on_pb_close_clicked(); break;
        case 6: _t->on_pb_ok_clicked(); break;
        default: ;
        }
    }
}

const QMetaObject SA_Dialog_CH_Std::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_SA_Dialog_CH_Std.data,
      qt_meta_data_SA_Dialog_CH_Std,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *SA_Dialog_CH_Std::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *SA_Dialog_CH_Std::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_SA_Dialog_CH_Std.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int SA_Dialog_CH_Std::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
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
QT_WARNING_POP
QT_END_MOC_NAMESPACE

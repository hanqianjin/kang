/****************************************************************************
** Meta object code from reading C++ file 'sa_dialog_limittable.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.3.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../sa_dialog_limittable.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'sa_dialog_limittable.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.3.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_SA_Dialog_LimitTable_t {
    QByteArrayData data[21];
    char stringdata[330];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_SA_Dialog_LimitTable_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_SA_Dialog_LimitTable_t qt_meta_stringdata_SA_Dialog_LimitTable = {
    {
QT_MOC_LITERAL(0, 0, 20),
QT_MOC_LITERAL(1, 21, 13),
QT_MOC_LITERAL(2, 35, 0),
QT_MOC_LITERAL(3, 36, 10),
QT_MOC_LITERAL(4, 47, 5),
QT_MOC_LITERAL(5, 53, 15),
QT_MOC_LITERAL(6, 69, 14),
QT_MOC_LITERAL(7, 84, 5),
QT_MOC_LITERAL(8, 90, 23),
QT_MOC_LITERAL(9, 114, 23),
QT_MOC_LITERAL(10, 138, 25),
QT_MOC_LITERAL(11, 164, 20),
QT_MOC_LITERAL(12, 185, 26),
QT_MOC_LITERAL(13, 212, 3),
QT_MOC_LITERAL(14, 216, 6),
QT_MOC_LITERAL(15, 223, 11),
QT_MOC_LITERAL(16, 235, 12),
QT_MOC_LITERAL(17, 248, 5),
QT_MOC_LITERAL(18, 254, 22),
QT_MOC_LITERAL(19, 277, 26),
QT_MOC_LITERAL(20, 304, 25)
    },
    "SA_Dialog_LimitTable\0keyPressEvent\0\0"
    "QKeyEvent*\0event\0digitInputClose\0"
    "on_finishEntry\0index\0on_pb_InsertRow_clicked\0"
    "on_pb_DeleteRow_clicked\0"
    "on_pb_DeleteLimit_clicked\0"
    "on_pb_cancel_clicked\0on_tableWidget_cellClicked\0"
    "row\0column\0on_getFocus\0SA_LineEdit*\0"
    "mEdit\0on_tableWidget_clicked\0"
    "on_tableWidget_cellChanged\0"
    "on_LED_CurPtIndex_clicked"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_SA_Dialog_LimitTable[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      12,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    1,   74,    2, 0x08 /* Private */,
       5,    0,   77,    2, 0x08 /* Private */,
       6,    1,   78,    2, 0x08 /* Private */,
       8,    0,   81,    2, 0x08 /* Private */,
       9,    0,   82,    2, 0x08 /* Private */,
      10,    0,   83,    2, 0x08 /* Private */,
      11,    0,   84,    2, 0x08 /* Private */,
      12,    2,   85,    2, 0x08 /* Private */,
      15,    1,   90,    2, 0x08 /* Private */,
      18,    0,   93,    2, 0x08 /* Private */,
      19,    2,   94,    2, 0x08 /* Private */,
      20,    0,   99,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    7,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,   13,   14,
    QMetaType::Void, 0x80000000 | 16,   17,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,   13,   14,
    QMetaType::Void,

       0        // eod
};

void SA_Dialog_LimitTable::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        SA_Dialog_LimitTable *_t = static_cast<SA_Dialog_LimitTable *>(_o);
        switch (_id) {
        case 0: _t->keyPressEvent((*reinterpret_cast< QKeyEvent*(*)>(_a[1]))); break;
        case 1: _t->digitInputClose(); break;
        case 2: _t->on_finishEntry((*reinterpret_cast< qint32(*)>(_a[1]))); break;
        case 3: _t->on_pb_InsertRow_clicked(); break;
        case 4: _t->on_pb_DeleteRow_clicked(); break;
        case 5: _t->on_pb_DeleteLimit_clicked(); break;
        case 6: _t->on_pb_cancel_clicked(); break;
        case 7: _t->on_tableWidget_cellClicked((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 8: _t->on_getFocus((*reinterpret_cast< SA_LineEdit*(*)>(_a[1]))); break;
        case 9: _t->on_tableWidget_clicked(); break;
        case 10: _t->on_tableWidget_cellChanged((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 11: _t->on_LED_CurPtIndex_clicked(); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 8:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< SA_LineEdit* >(); break;
            }
            break;
        }
    }
}

const QMetaObject SA_Dialog_LimitTable::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_SA_Dialog_LimitTable.data,
      qt_meta_data_SA_Dialog_LimitTable,  qt_static_metacall, 0, 0}
};


const QMetaObject *SA_Dialog_LimitTable::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *SA_Dialog_LimitTable::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_SA_Dialog_LimitTable.stringdata))
        return static_cast<void*>(const_cast< SA_Dialog_LimitTable*>(this));
    return QWidget::qt_metacast(_clname);
}

int SA_Dialog_LimitTable::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 12)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 12;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 12)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 12;
    }
    return _id;
}
QT_END_MOC_NAMESPACE

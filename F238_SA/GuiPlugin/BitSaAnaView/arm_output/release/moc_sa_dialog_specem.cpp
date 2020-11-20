/****************************************************************************
** Meta object code from reading C++ file 'sa_dialog_specem.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.3.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../sa_dialog_specem.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'sa_dialog_specem.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.3.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_SA_Dialog_SpecEM_t {
    QByteArrayData data[23];
    char stringdata[435];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_SA_Dialog_SpecEM_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_SA_Dialog_SpecEM_t qt_meta_stringdata_SA_Dialog_SpecEM = {
    {
QT_MOC_LITERAL(0, 0, 16),
QT_MOC_LITERAL(1, 17, 11),
QT_MOC_LITERAL(2, 29, 0),
QT_MOC_LITERAL(3, 30, 25),
QT_MOC_LITERAL(4, 56, 25),
QT_MOC_LITERAL(5, 82, 29),
QT_MOC_LITERAL(6, 112, 26),
QT_MOC_LITERAL(7, 139, 21),
QT_MOC_LITERAL(8, 161, 24),
QT_MOC_LITERAL(9, 186, 20),
QT_MOC_LITERAL(10, 207, 30),
QT_MOC_LITERAL(11, 238, 5),
QT_MOC_LITERAL(12, 244, 33),
QT_MOC_LITERAL(13, 278, 29),
QT_MOC_LITERAL(14, 308, 19),
QT_MOC_LITERAL(15, 328, 12),
QT_MOC_LITERAL(16, 341, 4),
QT_MOC_LITERAL(17, 346, 19),
QT_MOC_LITERAL(18, 366, 22),
QT_MOC_LITERAL(19, 389, 11),
QT_MOC_LITERAL(20, 401, 12),
QT_MOC_LITERAL(21, 414, 5),
QT_MOC_LITERAL(22, 420, 14)
    },
    "SA_Dialog_SpecEM\0mDialogHide\0\0"
    "on_pb_Display_Abs_clicked\0"
    "on_pb_Display_Ref_clicked\0"
    "on_pb_Display_IntePwr_clicked\0"
    "on_pb_ref_TotalPwr_clicked\0"
    "on_pb_ref_PSD_clicked\0on_pb_ref_SpecPk_clicked\0"
    "on_pb_cancel_clicked\0"
    "on_MaskBox_currentIndexChanged\0index\0"
    "on_DisplayBox_currentIndexChanged\0"
    "on_RefBox_currentIndexChanged\0"
    "on_getComboBoxFocus\0SA_Combobox*\0mBox\0"
    "on_ChBwEdit_clicked\0on_BSPowerEdit_clicked\0"
    "on_getFocus\0SA_LineEdit*\0mEdit\0"
    "on_finishEntry"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_SA_Dialog_SpecEM[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      16,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   94,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       3,    0,   95,    2, 0x08 /* Private */,
       4,    0,   96,    2, 0x08 /* Private */,
       5,    0,   97,    2, 0x08 /* Private */,
       6,    0,   98,    2, 0x08 /* Private */,
       7,    0,   99,    2, 0x08 /* Private */,
       8,    0,  100,    2, 0x08 /* Private */,
       9,    0,  101,    2, 0x08 /* Private */,
      10,    1,  102,    2, 0x08 /* Private */,
      12,    1,  105,    2, 0x08 /* Private */,
      13,    1,  108,    2, 0x08 /* Private */,
      14,    1,  111,    2, 0x08 /* Private */,
      17,    0,  114,    2, 0x08 /* Private */,
      18,    0,  115,    2, 0x08 /* Private */,
      19,    1,  116,    2, 0x08 /* Private */,
      22,    1,  119,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,   11,
    QMetaType::Void, QMetaType::Int,   11,
    QMetaType::Void, QMetaType::Int,   11,
    QMetaType::Void, 0x80000000 | 15,   16,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 20,   21,
    QMetaType::Void, QMetaType::Int,   11,

       0        // eod
};

void SA_Dialog_SpecEM::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        SA_Dialog_SpecEM *_t = static_cast<SA_Dialog_SpecEM *>(_o);
        switch (_id) {
        case 0: _t->mDialogHide(); break;
        case 1: _t->on_pb_Display_Abs_clicked(); break;
        case 2: _t->on_pb_Display_Ref_clicked(); break;
        case 3: _t->on_pb_Display_IntePwr_clicked(); break;
        case 4: _t->on_pb_ref_TotalPwr_clicked(); break;
        case 5: _t->on_pb_ref_PSD_clicked(); break;
        case 6: _t->on_pb_ref_SpecPk_clicked(); break;
        case 7: _t->on_pb_cancel_clicked(); break;
        case 8: _t->on_MaskBox_currentIndexChanged((*reinterpret_cast< qint32(*)>(_a[1]))); break;
        case 9: _t->on_DisplayBox_currentIndexChanged((*reinterpret_cast< qint32(*)>(_a[1]))); break;
        case 10: _t->on_RefBox_currentIndexChanged((*reinterpret_cast< qint32(*)>(_a[1]))); break;
        case 11: _t->on_getComboBoxFocus((*reinterpret_cast< SA_Combobox*(*)>(_a[1]))); break;
        case 12: _t->on_ChBwEdit_clicked(); break;
        case 13: _t->on_BSPowerEdit_clicked(); break;
        case 14: _t->on_getFocus((*reinterpret_cast< SA_LineEdit*(*)>(_a[1]))); break;
        case 15: _t->on_finishEntry((*reinterpret_cast< qint32(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 11:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< SA_Combobox* >(); break;
            }
            break;
        case 14:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< SA_LineEdit* >(); break;
            }
            break;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (SA_Dialog_SpecEM::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&SA_Dialog_SpecEM::mDialogHide)) {
                *result = 0;
            }
        }
    }
}

const QMetaObject SA_Dialog_SpecEM::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_SA_Dialog_SpecEM.data,
      qt_meta_data_SA_Dialog_SpecEM,  qt_static_metacall, 0, 0}
};


const QMetaObject *SA_Dialog_SpecEM::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *SA_Dialog_SpecEM::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_SA_Dialog_SpecEM.stringdata))
        return static_cast<void*>(const_cast< SA_Dialog_SpecEM*>(this));
    if (!strcmp(_clname, "sa_interface_dialog"))
        return static_cast< sa_interface_dialog*>(const_cast< SA_Dialog_SpecEM*>(this));
    return QWidget::qt_metacast(_clname);
}

int SA_Dialog_SpecEM::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 16)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 16;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 16)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 16;
    }
    return _id;
}

// SIGNAL 0
void SA_Dialog_SpecEM::mDialogHide()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}
QT_END_MOC_NAMESPACE

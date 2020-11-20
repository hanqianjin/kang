/****************************************************************************
** Meta object code from reading C++ file 'sa_dialog_amptsetup.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.3.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../sa_dialog_amptsetup.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'sa_dialog_amptsetup.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.3.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_SA_Dialog_AmptSetup_t {
    QByteArrayData data[24];
    char stringdata[319];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_SA_Dialog_AmptSetup_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_SA_Dialog_AmptSetup_t qt_meta_stringdata_SA_Dialog_AmptSetup = {
    {
QT_MOC_LITERAL(0, 0, 19),
QT_MOC_LITERAL(1, 20, 11),
QT_MOC_LITERAL(2, 32, 0),
QT_MOC_LITERAL(3, 33, 14),
QT_MOC_LITERAL(4, 48, 5),
QT_MOC_LITERAL(5, 54, 12),
QT_MOC_LITERAL(6, 67, 24),
QT_MOC_LITERAL(7, 92, 10),
QT_MOC_LITERAL(8, 103, 4),
QT_MOC_LITERAL(9, 108, 20),
QT_MOC_LITERAL(10, 129, 20),
QT_MOC_LITERAL(11, 150, 20),
QT_MOC_LITERAL(12, 171, 7),
QT_MOC_LITERAL(13, 179, 11),
QT_MOC_LITERAL(14, 191, 12),
QT_MOC_LITERAL(15, 204, 5),
QT_MOC_LITERAL(16, 210, 19),
QT_MOC_LITERAL(17, 230, 12),
QT_MOC_LITERAL(18, 243, 4),
QT_MOC_LITERAL(19, 248, 13),
QT_MOC_LITERAL(20, 262, 10),
QT_MOC_LITERAL(21, 273, 5),
QT_MOC_LITERAL(22, 279, 18),
QT_MOC_LITERAL(23, 298, 20)
    },
    "SA_Dialog_AmptSetup\0mDialogHide\0\0"
    "on_finishEntry\0index\0edit_clicked\0"
    "on_pb_Scale_Auto_clicked\0unitSelect\0"
    "unit\0on_pb_Preamp_clicked\0"
    "on_pb_cancel_clicked\0on_pb_Preamp_toggled\0"
    "checked\0on_getFocus\0SA_LineEdit*\0mEdit\0"
    "on_getComboBoxFocus\0SA_Combobox*\0mBox\0"
    "keyPressEvent\0QKeyEvent*\0event\0"
    "on_pb_Auto_clicked\0on_pb_Manual_clicked"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_SA_Dialog_AmptSetup[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      13,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   79,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       3,    1,   80,    2, 0x08 /* Private */,
       5,    0,   83,    2, 0x08 /* Private */,
       6,    0,   84,    2, 0x08 /* Private */,
       7,    1,   85,    2, 0x08 /* Private */,
       9,    0,   88,    2, 0x08 /* Private */,
      10,    0,   89,    2, 0x08 /* Private */,
      11,    1,   90,    2, 0x08 /* Private */,
      13,    1,   93,    2, 0x08 /* Private */,
      16,    1,   96,    2, 0x08 /* Private */,
      19,    1,   99,    2, 0x08 /* Private */,
      22,    1,  102,    2, 0x08 /* Private */,
      23,    1,  105,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void, QMetaType::Int,    4,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    8,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool,   12,
    QMetaType::Void, 0x80000000 | 14,   15,
    QMetaType::Void, 0x80000000 | 17,   18,
    QMetaType::Void, 0x80000000 | 20,   21,
    QMetaType::Void, QMetaType::Bool,   12,
    QMetaType::Void, QMetaType::Bool,   12,

       0        // eod
};

void SA_Dialog_AmptSetup::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        SA_Dialog_AmptSetup *_t = static_cast<SA_Dialog_AmptSetup *>(_o);
        switch (_id) {
        case 0: _t->mDialogHide(); break;
        case 1: _t->on_finishEntry((*reinterpret_cast< qint32(*)>(_a[1]))); break;
        case 2: _t->edit_clicked(); break;
        case 3: _t->on_pb_Scale_Auto_clicked(); break;
        case 4: _t->unitSelect((*reinterpret_cast< qint32(*)>(_a[1]))); break;
        case 5: _t->on_pb_Preamp_clicked(); break;
        case 6: _t->on_pb_cancel_clicked(); break;
        case 7: _t->on_pb_Preamp_toggled((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 8: _t->on_getFocus((*reinterpret_cast< SA_LineEdit*(*)>(_a[1]))); break;
        case 9: _t->on_getComboBoxFocus((*reinterpret_cast< SA_Combobox*(*)>(_a[1]))); break;
        case 10: _t->keyPressEvent((*reinterpret_cast< QKeyEvent*(*)>(_a[1]))); break;
        case 11: _t->on_pb_Auto_clicked((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 12: _t->on_pb_Manual_clicked((*reinterpret_cast< bool(*)>(_a[1]))); break;
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
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (SA_Dialog_AmptSetup::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&SA_Dialog_AmptSetup::mDialogHide)) {
                *result = 0;
            }
        }
    }
}

const QMetaObject SA_Dialog_AmptSetup::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_SA_Dialog_AmptSetup.data,
      qt_meta_data_SA_Dialog_AmptSetup,  qt_static_metacall, 0, 0}
};


const QMetaObject *SA_Dialog_AmptSetup::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *SA_Dialog_AmptSetup::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_SA_Dialog_AmptSetup.stringdata))
        return static_cast<void*>(const_cast< SA_Dialog_AmptSetup*>(this));
    if (!strcmp(_clname, "sa_interface_dialog"))
        return static_cast< sa_interface_dialog*>(const_cast< SA_Dialog_AmptSetup*>(this));
    return QWidget::qt_metacast(_clname);
}

int SA_Dialog_AmptSetup::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 13)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 13;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 13)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 13;
    }
    return _id;
}

// SIGNAL 0
void SA_Dialog_AmptSetup::mDialogHide()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}
QT_END_MOC_NAMESPACE

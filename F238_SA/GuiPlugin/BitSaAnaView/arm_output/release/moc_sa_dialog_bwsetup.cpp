/****************************************************************************
** Meta object code from reading C++ file 'sa_dialog_bwsetup.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.3.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../sa_dialog_bwsetup.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'sa_dialog_bwsetup.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.3.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_SA_Dialog_BWSetup_t {
    QByteArrayData data[25];
    char stringdata[408];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_SA_Dialog_BWSetup_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_SA_Dialog_BWSetup_t qt_meta_stringdata_SA_Dialog_BWSetup = {
    {
QT_MOC_LITERAL(0, 0, 17),
QT_MOC_LITERAL(1, 18, 11),
QT_MOC_LITERAL(2, 30, 0),
QT_MOC_LITERAL(3, 31, 14),
QT_MOC_LITERAL(4, 46, 5),
QT_MOC_LITERAL(5, 52, 12),
QT_MOC_LITERAL(6, 65, 20),
QT_MOC_LITERAL(7, 86, 22),
QT_MOC_LITERAL(8, 109, 20),
QT_MOC_LITERAL(9, 130, 22),
QT_MOC_LITERAL(10, 153, 20),
QT_MOC_LITERAL(11, 174, 29),
QT_MOC_LITERAL(12, 204, 29),
QT_MOC_LITERAL(13, 234, 31),
QT_MOC_LITERAL(14, 266, 4),
QT_MOC_LITERAL(15, 271, 11),
QT_MOC_LITERAL(16, 283, 12),
QT_MOC_LITERAL(17, 296, 5),
QT_MOC_LITERAL(18, 302, 19),
QT_MOC_LITERAL(19, 322, 12),
QT_MOC_LITERAL(20, 335, 4),
QT_MOC_LITERAL(21, 340, 13),
QT_MOC_LITERAL(22, 354, 10),
QT_MOC_LITERAL(23, 365, 5),
QT_MOC_LITERAL(24, 371, 36)
    },
    "SA_Dialog_BWSetup\0mDialogHide\0\0"
    "on_finishEntry\0index\0edit_clicked\0"
    "on_RBWAutoPB_clicked\0on_RBWManualPB_clicked\0"
    "on_VBWAutoPB_clicked\0on_VBWManualPB_clicked\0"
    "on_pb_cancel_clicked\0on_RBWBox_currentIndexChanged\0"
    "on_VBWBox_currentIndexChanged\0"
    "on_ratioBox_currentIndexChanged\0text\0"
    "on_getFocus\0SA_LineEdit*\0mEdit\0"
    "on_getComboBoxFocus\0SA_Combobox*\0mBox\0"
    "keyPressEvent\0QKeyEvent*\0event\0"
    "on_IF_OutPut_Box_currentIndexChanged"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_SA_Dialog_BWSetup[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      15,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   89,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       3,    1,   90,    2, 0x08 /* Private */,
       5,    0,   93,    2, 0x08 /* Private */,
       6,    0,   94,    2, 0x08 /* Private */,
       7,    0,   95,    2, 0x08 /* Private */,
       8,    0,   96,    2, 0x08 /* Private */,
       9,    0,   97,    2, 0x08 /* Private */,
      10,    0,   98,    2, 0x08 /* Private */,
      11,    1,   99,    2, 0x08 /* Private */,
      12,    1,  102,    2, 0x08 /* Private */,
      13,    1,  105,    2, 0x08 /* Private */,
      15,    1,  108,    2, 0x08 /* Private */,
      18,    1,  111,    2, 0x08 /* Private */,
      21,    1,  114,    2, 0x08 /* Private */,
      24,    1,  117,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void, QMetaType::Int,    4,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    4,
    QMetaType::Void, QMetaType::Int,    4,
    QMetaType::Void, QMetaType::QString,   14,
    QMetaType::Void, 0x80000000 | 16,   17,
    QMetaType::Void, 0x80000000 | 19,   20,
    QMetaType::Void, 0x80000000 | 22,   23,
    QMetaType::Void, QMetaType::Int,    4,

       0        // eod
};

void SA_Dialog_BWSetup::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        SA_Dialog_BWSetup *_t = static_cast<SA_Dialog_BWSetup *>(_o);
        switch (_id) {
        case 0: _t->mDialogHide(); break;
        case 1: _t->on_finishEntry((*reinterpret_cast< qint32(*)>(_a[1]))); break;
        case 2: _t->edit_clicked(); break;
        case 3: _t->on_RBWAutoPB_clicked(); break;
        case 4: _t->on_RBWManualPB_clicked(); break;
        case 5: _t->on_VBWAutoPB_clicked(); break;
        case 6: _t->on_VBWManualPB_clicked(); break;
        case 7: _t->on_pb_cancel_clicked(); break;
        case 8: _t->on_RBWBox_currentIndexChanged((*reinterpret_cast< qint32(*)>(_a[1]))); break;
        case 9: _t->on_VBWBox_currentIndexChanged((*reinterpret_cast< qint32(*)>(_a[1]))); break;
        case 10: _t->on_ratioBox_currentIndexChanged((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 11: _t->on_getFocus((*reinterpret_cast< SA_LineEdit*(*)>(_a[1]))); break;
        case 12: _t->on_getComboBoxFocus((*reinterpret_cast< SA_Combobox*(*)>(_a[1]))); break;
        case 13: _t->keyPressEvent((*reinterpret_cast< QKeyEvent*(*)>(_a[1]))); break;
        case 14: _t->on_IF_OutPut_Box_currentIndexChanged((*reinterpret_cast< qint32(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 11:
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
            typedef void (SA_Dialog_BWSetup::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&SA_Dialog_BWSetup::mDialogHide)) {
                *result = 0;
            }
        }
    }
}

const QMetaObject SA_Dialog_BWSetup::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_SA_Dialog_BWSetup.data,
      qt_meta_data_SA_Dialog_BWSetup,  qt_static_metacall, 0, 0}
};


const QMetaObject *SA_Dialog_BWSetup::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *SA_Dialog_BWSetup::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_SA_Dialog_BWSetup.stringdata))
        return static_cast<void*>(const_cast< SA_Dialog_BWSetup*>(this));
    if (!strcmp(_clname, "sa_interface_dialog"))
        return static_cast< sa_interface_dialog*>(const_cast< SA_Dialog_BWSetup*>(this));
    return QWidget::qt_metacast(_clname);
}

int SA_Dialog_BWSetup::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 15)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 15;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 15)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 15;
    }
    return _id;
}

// SIGNAL 0
void SA_Dialog_BWSetup::mDialogHide()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}
QT_END_MOC_NAMESPACE

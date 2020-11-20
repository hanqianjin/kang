/****************************************************************************
** Meta object code from reading C++ file 'sa_dialog_occpdset.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.3.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../sa_dialog_occpdset.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'sa_dialog_occpdset.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.3.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_sa_dialog_occpdset_t {
    QByteArrayData data[14];
    char stringdata[180];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_sa_dialog_occpdset_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_sa_dialog_occpdset_t qt_meta_stringdata_sa_dialog_occpdset = {
    {
QT_MOC_LITERAL(0, 0, 18),
QT_MOC_LITERAL(1, 19, 11),
QT_MOC_LITERAL(2, 31, 0),
QT_MOC_LITERAL(3, 32, 19),
QT_MOC_LITERAL(4, 52, 14),
QT_MOC_LITERAL(5, 67, 5),
QT_MOC_LITERAL(6, 73, 22),
QT_MOC_LITERAL(7, 96, 21),
QT_MOC_LITERAL(8, 118, 11),
QT_MOC_LITERAL(9, 130, 12),
QT_MOC_LITERAL(10, 143, 5),
QT_MOC_LITERAL(11, 149, 13),
QT_MOC_LITERAL(12, 163, 10),
QT_MOC_LITERAL(13, 174, 5)
    },
    "sa_dialog_occpdset\0mDialogHide\0\0"
    "on_lineEdit_clicked\0on_finishEntry\0"
    "index\0on_pb_cancel_2_clicked\0"
    "on_lineEdit_1_clicked\0on_getFocus\0"
    "SA_LineEdit*\0mEdit\0keyPressEvent\0"
    "QKeyEvent*\0event"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_sa_dialog_occpdset[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       7,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   49,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       3,    0,   50,    2, 0x08 /* Private */,
       4,    1,   51,    2, 0x08 /* Private */,
       6,    0,   54,    2, 0x08 /* Private */,
       7,    0,   55,    2, 0x08 /* Private */,
       8,    1,   56,    2, 0x08 /* Private */,
      11,    1,   59,    2, 0x09 /* Protected */,

 // signals: parameters
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    5,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 9,   10,
    QMetaType::Void, 0x80000000 | 12,   13,

       0        // eod
};

void sa_dialog_occpdset::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        sa_dialog_occpdset *_t = static_cast<sa_dialog_occpdset *>(_o);
        switch (_id) {
        case 0: _t->mDialogHide(); break;
        case 1: _t->on_lineEdit_clicked(); break;
        case 2: _t->on_finishEntry((*reinterpret_cast< qint32(*)>(_a[1]))); break;
        case 3: _t->on_pb_cancel_2_clicked(); break;
        case 4: _t->on_lineEdit_1_clicked(); break;
        case 5: _t->on_getFocus((*reinterpret_cast< SA_LineEdit*(*)>(_a[1]))); break;
        case 6: _t->keyPressEvent((*reinterpret_cast< QKeyEvent*(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 5:
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
            typedef void (sa_dialog_occpdset::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&sa_dialog_occpdset::mDialogHide)) {
                *result = 0;
            }
        }
    }
}

const QMetaObject sa_dialog_occpdset::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_sa_dialog_occpdset.data,
      qt_meta_data_sa_dialog_occpdset,  qt_static_metacall, 0, 0}
};


const QMetaObject *sa_dialog_occpdset::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *sa_dialog_occpdset::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_sa_dialog_occpdset.stringdata))
        return static_cast<void*>(const_cast< sa_dialog_occpdset*>(this));
    if (!strcmp(_clname, "sa_interface_dialog"))
        return static_cast< sa_interface_dialog*>(const_cast< sa_dialog_occpdset*>(this));
    return QWidget::qt_metacast(_clname);
}

int sa_dialog_occpdset::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
            qt_static_metacall(this, _c, _id, _a);
        _id -= 7;
    }
    return _id;
}

// SIGNAL 0
void sa_dialog_occpdset::mDialogHide()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}
QT_END_MOC_NAMESPACE

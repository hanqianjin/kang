/****************************************************************************
** Meta object code from reading C++ file 'sa_dialog_quicksave.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.3.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../sa_dialog_quicksave.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'sa_dialog_quicksave.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.3.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_SA_Dialog_QuickSave_t {
    QByteArrayData data[6];
    char stringdata[100];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_SA_Dialog_QuickSave_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_SA_Dialog_QuickSave_t qt_meta_stringdata_SA_Dialog_QuickSave = {
    {
QT_MOC_LITERAL(0, 0, 19),
QT_MOC_LITERAL(1, 20, 20),
QT_MOC_LITERAL(2, 41, 0),
QT_MOC_LITERAL(3, 42, 16),
QT_MOC_LITERAL(4, 59, 20),
QT_MOC_LITERAL(5, 80, 19)
    },
    "SA_Dialog_QuickSave\0on_pb_cancel_clicked\0"
    "\0on_pb_ok_clicked\0on_pb_Cancel_clicked\0"
    "on_pb_clear_clicked"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_SA_Dialog_QuickSave[] = {

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
       1,    0,   34,    2, 0x08 /* Private */,
       3,    0,   35,    2, 0x08 /* Private */,
       4,    0,   36,    2, 0x08 /* Private */,
       5,    0,   37,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void SA_Dialog_QuickSave::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        SA_Dialog_QuickSave *_t = static_cast<SA_Dialog_QuickSave *>(_o);
        switch (_id) {
        case 0: _t->on_pb_cancel_clicked(); break;
        case 1: _t->on_pb_ok_clicked(); break;
        case 2: _t->on_pb_Cancel_clicked(); break;
        case 3: _t->on_pb_clear_clicked(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObject SA_Dialog_QuickSave::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_SA_Dialog_QuickSave.data,
      qt_meta_data_SA_Dialog_QuickSave,  qt_static_metacall, 0, 0}
};


const QMetaObject *SA_Dialog_QuickSave::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *SA_Dialog_QuickSave::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_SA_Dialog_QuickSave.stringdata))
        return static_cast<void*>(const_cast< SA_Dialog_QuickSave*>(this));
    return QDialog::qt_metacast(_clname);
}

int SA_Dialog_QuickSave::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
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

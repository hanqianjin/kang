/****************************************************************************
** Meta object code from reading C++ file 'sa_dialog_measuresetup.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.3.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../sa_dialog_measuresetup.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'sa_dialog_measuresetup.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.3.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_SA_Dialog_MeasureSetup_t {
    QByteArrayData data[8];
    char stringdata[100];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_SA_Dialog_MeasureSetup_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_SA_Dialog_MeasureSetup_t qt_meta_stringdata_SA_Dialog_MeasureSetup = {
    {
QT_MOC_LITERAL(0, 0, 22),
QT_MOC_LITERAL(1, 23, 11),
QT_MOC_LITERAL(2, 35, 0),
QT_MOC_LITERAL(3, 36, 14),
QT_MOC_LITERAL(4, 51, 5),
QT_MOC_LITERAL(5, 57, 20),
QT_MOC_LITERAL(6, 78, 14),
QT_MOC_LITERAL(7, 93, 6)
    },
    "SA_Dialog_MeasureSetup\0mDialogHide\0\0"
    "on_finishEntry\0index\0on_pb_cancel_clicked\0"
    "runBtnFunction\0menuID"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_SA_Dialog_MeasureSetup[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   34,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       3,    1,   35,    2, 0x08 /* Private */,
       5,    0,   38,    2, 0x08 /* Private */,
       6,    1,   39,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void, QMetaType::Int,    4,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    7,

       0        // eod
};

void SA_Dialog_MeasureSetup::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        SA_Dialog_MeasureSetup *_t = static_cast<SA_Dialog_MeasureSetup *>(_o);
        switch (_id) {
        case 0: _t->mDialogHide(); break;
        case 1: _t->on_finishEntry((*reinterpret_cast< qint32(*)>(_a[1]))); break;
        case 2: _t->on_pb_cancel_clicked(); break;
        case 3: _t->runBtnFunction((*reinterpret_cast< qint32(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (SA_Dialog_MeasureSetup::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&SA_Dialog_MeasureSetup::mDialogHide)) {
                *result = 0;
            }
        }
    }
}

const QMetaObject SA_Dialog_MeasureSetup::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_SA_Dialog_MeasureSetup.data,
      qt_meta_data_SA_Dialog_MeasureSetup,  qt_static_metacall, 0, 0}
};


const QMetaObject *SA_Dialog_MeasureSetup::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *SA_Dialog_MeasureSetup::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_SA_Dialog_MeasureSetup.stringdata))
        return static_cast<void*>(const_cast< SA_Dialog_MeasureSetup*>(this));
    if (!strcmp(_clname, "sa_interface_dialog"))
        return static_cast< sa_interface_dialog*>(const_cast< SA_Dialog_MeasureSetup*>(this));
    return QWidget::qt_metacast(_clname);
}

int SA_Dialog_MeasureSetup::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
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

// SIGNAL 0
void SA_Dialog_MeasureSetup::mDialogHide()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}
QT_END_MOC_NAMESPACE

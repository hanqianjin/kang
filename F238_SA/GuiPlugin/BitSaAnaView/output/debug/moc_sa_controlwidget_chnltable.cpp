/****************************************************************************
** Meta object code from reading C++ file 'sa_controlwidget_chnltable.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.9.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../sa_controlwidget_chnltable.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'sa_controlwidget_chnltable.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.9.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_sa_controlWidget_ChnlTable_t {
    QByteArrayData data[5];
    char stringdata0[74];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_sa_controlWidget_ChnlTable_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_sa_controlWidget_ChnlTable_t qt_meta_stringdata_sa_controlWidget_ChnlTable = {
    {
QT_MOC_LITERAL(0, 0, 26), // "sa_controlWidget_ChnlTable"
QT_MOC_LITERAL(1, 27, 15), // "signalHideTable"
QT_MOC_LITERAL(2, 43, 0), // ""
QT_MOC_LITERAL(3, 44, 7), // "tableID"
QT_MOC_LITERAL(4, 52, 21) // "on_pushButton_clicked"

    },
    "sa_controlWidget_ChnlTable\0signalHideTable\0"
    "\0tableID\0on_pushButton_clicked"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_sa_controlWidget_ChnlTable[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   24,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       4,    0,   27,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, QMetaType::UInt,    3,

 // slots: parameters
    QMetaType::Void,

       0        // eod
};

void sa_controlWidget_ChnlTable::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        sa_controlWidget_ChnlTable *_t = static_cast<sa_controlWidget_ChnlTable *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->signalHideTable((*reinterpret_cast< quint32(*)>(_a[1]))); break;
        case 1: _t->on_pushButton_clicked(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (sa_controlWidget_ChnlTable::*_t)(quint32 );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&sa_controlWidget_ChnlTable::signalHideTable)) {
                *result = 0;
                return;
            }
        }
    }
}

const QMetaObject sa_controlWidget_ChnlTable::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_sa_controlWidget_ChnlTable.data,
      qt_meta_data_sa_controlWidget_ChnlTable,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *sa_controlWidget_ChnlTable::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *sa_controlWidget_ChnlTable::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_sa_controlWidget_ChnlTable.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int sa_controlWidget_ChnlTable::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 2)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 2;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 2)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 2;
    }
    return _id;
}

// SIGNAL 0
void sa_controlWidget_ChnlTable::signalHideTable(quint32 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
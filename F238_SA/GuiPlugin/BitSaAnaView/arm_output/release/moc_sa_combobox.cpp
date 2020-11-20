/****************************************************************************
** Meta object code from reading C++ file 'sa_combobox.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.3.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../sa_combobox.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'sa_combobox.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.3.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_SA_Combobox_t {
    QByteArrayData data[8];
    char stringdata[59];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_SA_Combobox_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_SA_Combobox_t qt_meta_stringdata_SA_Combobox = {
    {
QT_MOC_LITERAL(0, 0, 11),
QT_MOC_LITERAL(1, 12, 9),
QT_MOC_LITERAL(2, 22, 0),
QT_MOC_LITERAL(3, 23, 5),
QT_MOC_LITERAL(4, 29, 6),
QT_MOC_LITERAL(5, 36, 12),
QT_MOC_LITERAL(6, 49, 1),
QT_MOC_LITERAL(7, 51, 7)
    },
    "SA_Combobox\0mFocusOut\0\0index\0mFocus\0"
    "SA_Combobox*\0e\0clicked"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_SA_Combobox[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   29,    2, 0x06 /* Public */,
       4,    1,   32,    2, 0x06 /* Public */,
       7,    1,   35,    2, 0x06 /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void, 0x80000000 | 5,    6,
    QMetaType::Void, 0x80000000 | 5,    6,

       0        // eod
};

void SA_Combobox::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        SA_Combobox *_t = static_cast<SA_Combobox *>(_o);
        switch (_id) {
        case 0: _t->mFocusOut((*reinterpret_cast< qint32(*)>(_a[1]))); break;
        case 1: _t->mFocus((*reinterpret_cast< SA_Combobox*(*)>(_a[1]))); break;
        case 2: _t->clicked((*reinterpret_cast< SA_Combobox*(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 1:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< SA_Combobox* >(); break;
            }
            break;
        case 2:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< SA_Combobox* >(); break;
            }
            break;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (SA_Combobox::*_t)(qint32 );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&SA_Combobox::mFocusOut)) {
                *result = 0;
            }
        }
        {
            typedef void (SA_Combobox::*_t)(SA_Combobox * );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&SA_Combobox::mFocus)) {
                *result = 1;
            }
        }
        {
            typedef void (SA_Combobox::*_t)(SA_Combobox * );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&SA_Combobox::clicked)) {
                *result = 2;
            }
        }
    }
}

const QMetaObject SA_Combobox::staticMetaObject = {
    { &QComboBox::staticMetaObject, qt_meta_stringdata_SA_Combobox.data,
      qt_meta_data_SA_Combobox,  qt_static_metacall, 0, 0}
};


const QMetaObject *SA_Combobox::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *SA_Combobox::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_SA_Combobox.stringdata))
        return static_cast<void*>(const_cast< SA_Combobox*>(this));
    return QComboBox::qt_metacast(_clname);
}

int SA_Combobox::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QComboBox::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 3)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 3)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    }
    return _id;
}

// SIGNAL 0
void SA_Combobox::mFocusOut(qint32 _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void SA_Combobox::mFocus(SA_Combobox * _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void SA_Combobox::clicked(SA_Combobox * _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}
QT_END_MOC_NAMESPACE

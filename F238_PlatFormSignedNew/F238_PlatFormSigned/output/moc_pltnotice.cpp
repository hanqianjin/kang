/****************************************************************************
** Meta object code from reading C++ file 'pltnotice.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.9.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../pltnotice.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'pltnotice.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.9.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_pltnotice_t {
    QByteArrayData data[7];
    char stringdata0[131];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_pltnotice_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_pltnotice_t qt_meta_stringdata_pltnotice = {
    {
QT_MOC_LITERAL(0, 0, 9), // "pltnotice"
QT_MOC_LITERAL(1, 10, 27), // "on_pushButtoncancel_clicked"
QT_MOC_LITERAL(2, 38, 0), // ""
QT_MOC_LITERAL(3, 39, 23), // "on_pushButtonok_clicked"
QT_MOC_LITERAL(4, 63, 25), // "on_lineEdit_returnPressed"
QT_MOC_LITERAL(5, 89, 21), // "on_pushButton_clicked"
QT_MOC_LITERAL(6, 111, 19) // "on_lineEdit_clicked"

    },
    "pltnotice\0on_pushButtoncancel_clicked\0"
    "\0on_pushButtonok_clicked\0"
    "on_lineEdit_returnPressed\0"
    "on_pushButton_clicked\0on_lineEdit_clicked"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_pltnotice[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   39,    2, 0x08 /* Private */,
       3,    0,   40,    2, 0x08 /* Private */,
       4,    0,   41,    2, 0x08 /* Private */,
       5,    0,   42,    2, 0x08 /* Private */,
       6,    0,   43,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void pltnotice::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        pltnotice *_t = static_cast<pltnotice *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->on_pushButtoncancel_clicked(); break;
        case 1: _t->on_pushButtonok_clicked(); break;
        case 2: _t->on_lineEdit_returnPressed(); break;
        case 3: _t->on_pushButton_clicked(); break;
        case 4: _t->on_lineEdit_clicked(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObject pltnotice::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_pltnotice.data,
      qt_meta_data_pltnotice,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *pltnotice::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *pltnotice::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_pltnotice.stringdata0))
        return static_cast<void*>(this);
    return QDialog::qt_metacast(_clname);
}

int pltnotice::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 5)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 5;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE

/****************************************************************************
** Meta object code from reading C++ file 'comset.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.3.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../comset.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'comset.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.3.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_comset_t {
    QByteArrayData data[16];
    char stringdata[337];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_comset_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_comset_t qt_meta_stringdata_comset = {
    {
QT_MOC_LITERAL(0, 0, 6),
QT_MOC_LITERAL(1, 7, 22),
QT_MOC_LITERAL(2, 30, 0),
QT_MOC_LITERAL(3, 31, 19),
QT_MOC_LITERAL(4, 51, 19),
QT_MOC_LITERAL(5, 71, 19),
QT_MOC_LITERAL(6, 91, 20),
QT_MOC_LITERAL(7, 112, 24),
QT_MOC_LITERAL(8, 137, 24),
QT_MOC_LITERAL(9, 162, 24),
QT_MOC_LITERAL(10, 187, 24),
QT_MOC_LITERAL(11, 212, 24),
QT_MOC_LITERAL(12, 237, 24),
QT_MOC_LITERAL(13, 262, 24),
QT_MOC_LITERAL(14, 287, 24),
QT_MOC_LITERAL(15, 312, 24)
    },
    "comset\0on_interrefbtn_clicked\0\0"
    "on_ext10btn_clicked\0on_ext13btn_clicked\0"
    "on_ext15btn_clicked\0on_gpsrefbtn_clicked\0"
    "on_pushButton_12_clicked\0"
    "on_pushButton_13_clicked\0"
    "on_pushButton_14_clicked\0"
    "on_pushButton_15_clicked\0"
    "on_pushButton_16_clicked\0"
    "on_pushButton_17_clicked\0"
    "on_pushButton_18_clicked\0"
    "on_pushButton_20_clicked\0"
    "on_pushButton_19_clicked"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_comset[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      14,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   84,    2, 0x08 /* Private */,
       3,    0,   85,    2, 0x08 /* Private */,
       4,    0,   86,    2, 0x08 /* Private */,
       5,    0,   87,    2, 0x08 /* Private */,
       6,    0,   88,    2, 0x08 /* Private */,
       7,    0,   89,    2, 0x08 /* Private */,
       8,    0,   90,    2, 0x08 /* Private */,
       9,    0,   91,    2, 0x08 /* Private */,
      10,    0,   92,    2, 0x08 /* Private */,
      11,    0,   93,    2, 0x08 /* Private */,
      12,    0,   94,    2, 0x08 /* Private */,
      13,    0,   95,    2, 0x08 /* Private */,
      14,    0,   96,    2, 0x08 /* Private */,
      15,    0,   97,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void comset::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        comset *_t = static_cast<comset *>(_o);
        switch (_id) {
        case 0: _t->on_interrefbtn_clicked(); break;
        case 1: _t->on_ext10btn_clicked(); break;
        case 2: _t->on_ext13btn_clicked(); break;
        case 3: _t->on_ext15btn_clicked(); break;
        case 4: _t->on_gpsrefbtn_clicked(); break;
        case 5: _t->on_pushButton_12_clicked(); break;
        case 6: _t->on_pushButton_13_clicked(); break;
        case 7: _t->on_pushButton_14_clicked(); break;
        case 8: _t->on_pushButton_15_clicked(); break;
        case 9: _t->on_pushButton_16_clicked(); break;
        case 10: _t->on_pushButton_17_clicked(); break;
        case 11: _t->on_pushButton_18_clicked(); break;
        case 12: _t->on_pushButton_20_clicked(); break;
        case 13: _t->on_pushButton_19_clicked(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObject comset::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_comset.data,
      qt_meta_data_comset,  qt_static_metacall, 0, 0}
};


const QMetaObject *comset::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *comset::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_comset.stringdata))
        return static_cast<void*>(const_cast< comset*>(this));
    return QWidget::qt_metacast(_clname);
}

int comset::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 14)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 14;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 14)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 14;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
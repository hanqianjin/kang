/****************************************************************************
** Meta object code from reading C++ file 'sa_customedTablewidget.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.3.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../sa_customedTablewidget.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'sa_customedTablewidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.3.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_ClickableTableWidget_t {
    QByteArrayData data[7];
    char stringdata[73];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_ClickableTableWidget_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_ClickableTableWidget_t qt_meta_stringdata_ClickableTableWidget = {
    {
QT_MOC_LITERAL(0, 0, 20),
QT_MOC_LITERAL(1, 21, 10),
QT_MOC_LITERAL(2, 32, 0),
QT_MOC_LITERAL(3, 33, 11),
QT_MOC_LITERAL(4, 45, 7),
QT_MOC_LITERAL(5, 53, 13),
QT_MOC_LITERAL(6, 67, 5)
    },
    "ClickableTableWidget\0editFinish\0\0"
    "contenJudge\0clicked\0headerClicked\0"
    "index"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ClickableTableWidget[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   34,    2, 0x06 /* Public */,
       3,    0,   35,    2, 0x06 /* Public */,
       4,    0,   36,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       5,    1,   37,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void, QMetaType::Int,    6,

       0        // eod
};

void ClickableTableWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        ClickableTableWidget *_t = static_cast<ClickableTableWidget *>(_o);
        switch (_id) {
        case 0: _t->editFinish(); break;
        case 1: _t->contenJudge(); break;
        case 2: _t->clicked(); break;
        case 3: _t->headerClicked((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (ClickableTableWidget::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&ClickableTableWidget::editFinish)) {
                *result = 0;
            }
        }
        {
            typedef void (ClickableTableWidget::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&ClickableTableWidget::contenJudge)) {
                *result = 1;
            }
        }
        {
            typedef void (ClickableTableWidget::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&ClickableTableWidget::clicked)) {
                *result = 2;
            }
        }
    }
}

const QMetaObject ClickableTableWidget::staticMetaObject = {
    { &QTableWidget::staticMetaObject, qt_meta_stringdata_ClickableTableWidget.data,
      qt_meta_data_ClickableTableWidget,  qt_static_metacall, 0, 0}
};


const QMetaObject *ClickableTableWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ClickableTableWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_ClickableTableWidget.stringdata))
        return static_cast<void*>(const_cast< ClickableTableWidget*>(this));
    return QTableWidget::qt_metacast(_clname);
}

int ClickableTableWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QTableWidget::qt_metacall(_c, _id, _a);
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
void ClickableTableWidget::editFinish()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}

// SIGNAL 1
void ClickableTableWidget::contenJudge()
{
    QMetaObject::activate(this, &staticMetaObject, 1, 0);
}

// SIGNAL 2
void ClickableTableWidget::clicked()
{
    QMetaObject::activate(this, &staticMetaObject, 2, 0);
}
QT_END_MOC_NAMESPACE

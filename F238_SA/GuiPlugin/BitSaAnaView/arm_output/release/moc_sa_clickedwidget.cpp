/****************************************************************************
** Meta object code from reading C++ file 'sa_clickedwidget.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.3.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../sa_clickedwidget.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'sa_clickedwidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.3.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_SA_ClickedWidget_t {
    QByteArrayData data[5];
    char stringdata[44];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_SA_ClickedWidget_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_SA_ClickedWidget_t qt_meta_stringdata_SA_ClickedWidget = {
    {
QT_MOC_LITERAL(0, 0, 16),
QT_MOC_LITERAL(1, 17, 7),
QT_MOC_LITERAL(2, 25, 0),
QT_MOC_LITERAL(3, 26, 7),
QT_MOC_LITERAL(4, 34, 9)
    },
    "SA_ClickedWidget\0clicked\0\0focusIn\0"
    "slotClick"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_SA_ClickedWidget[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   29,    2, 0x06 /* Public */,
       3,    0,   30,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       4,    0,   31,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,

       0        // eod
};

void SA_ClickedWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        SA_ClickedWidget *_t = static_cast<SA_ClickedWidget *>(_o);
        switch (_id) {
        case 0: _t->clicked(); break;
        case 1: _t->focusIn(); break;
        case 2: _t->slotClick(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (SA_ClickedWidget::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&SA_ClickedWidget::clicked)) {
                *result = 0;
            }
        }
        {
            typedef void (SA_ClickedWidget::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&SA_ClickedWidget::focusIn)) {
                *result = 1;
            }
        }
    }
    Q_UNUSED(_a);
}

const QMetaObject SA_ClickedWidget::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_SA_ClickedWidget.data,
      qt_meta_data_SA_ClickedWidget,  qt_static_metacall, 0, 0}
};


const QMetaObject *SA_ClickedWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *SA_ClickedWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_SA_ClickedWidget.stringdata))
        return static_cast<void*>(const_cast< SA_ClickedWidget*>(this));
    return QWidget::qt_metacast(_clname);
}

int SA_ClickedWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 3)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 3)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 3;
    }
    return _id;
}

// SIGNAL 0
void SA_ClickedWidget::clicked()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}

// SIGNAL 1
void SA_ClickedWidget::focusIn()
{
    QMetaObject::activate(this, &staticMetaObject, 1, 0);
}
QT_END_MOC_NAMESPACE

/****************************************************************************
** Meta object code from reading C++ file 'sa_dialog_digitinput.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.3.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../sa_dialog_digitinput.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'sa_dialog_digitinput.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.3.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_SA_Dialog_DigitInput_t {
    QByteArrayData data[16];
    char stringdata[331];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_SA_Dialog_DigitInput_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_SA_Dialog_DigitInput_t qt_meta_stringdata_SA_Dialog_DigitInput = {
    {
QT_MOC_LITERAL(0, 0, 20),
QT_MOC_LITERAL(1, 21, 11),
QT_MOC_LITERAL(2, 33, 0),
QT_MOC_LITERAL(3, 34, 20),
QT_MOC_LITERAL(4, 55, 11),
QT_MOC_LITERAL(5, 67, 23),
QT_MOC_LITERAL(6, 91, 23),
QT_MOC_LITERAL(7, 115, 23),
QT_MOC_LITERAL(8, 139, 23),
QT_MOC_LITERAL(9, 163, 23),
QT_MOC_LITERAL(10, 187, 23),
QT_MOC_LITERAL(11, 211, 23),
QT_MOC_LITERAL(12, 235, 23),
QT_MOC_LITERAL(13, 259, 23),
QT_MOC_LITERAL(14, 283, 23),
QT_MOC_LITERAL(15, 307, 23)
    },
    "SA_Dialog_DigitInput\0finishEntry\0\0"
    "on_pb_cancel_clicked\0btn_clicked\0"
    "on_freqBtnUnit1_clicked\0on_freqBtnUnit2_clicked\0"
    "on_freqBtnUnit3_clicked\0on_freqBtnUnit4_clicked\0"
    "on_amptBtnUnit1_clicked\0on_amptBtnUnit2_clicked\0"
    "on_amptBtnUnit3_clicked\0on_amptBtnUnit4_clicked\0"
    "on_amptBtnUnit5_clicked\0on_amptBtnUnit6_clicked\0"
    "on_amptBtnUnit7_clicked"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_SA_Dialog_DigitInput[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      14,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   84,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       3,    0,   87,    2, 0x08 /* Private */,
       4,    0,   88,    2, 0x08 /* Private */,
       5,    0,   89,    2, 0x08 /* Private */,
       6,    0,   90,    2, 0x08 /* Private */,
       7,    0,   91,    2, 0x08 /* Private */,
       8,    0,   92,    2, 0x08 /* Private */,
       9,    0,   93,    2, 0x08 /* Private */,
      10,    0,   94,    2, 0x08 /* Private */,
      11,    0,   95,    2, 0x08 /* Private */,
      12,    0,   96,    2, 0x08 /* Private */,
      13,    0,   97,    2, 0x08 /* Private */,
      14,    0,   98,    2, 0x08 /* Private */,
      15,    0,   99,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, QMetaType::Int,    2,

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

       0        // eod
};

void SA_Dialog_DigitInput::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        SA_Dialog_DigitInput *_t = static_cast<SA_Dialog_DigitInput *>(_o);
        switch (_id) {
        case 0: _t->finishEntry((*reinterpret_cast< qint32(*)>(_a[1]))); break;
        case 1: _t->on_pb_cancel_clicked(); break;
        case 2: _t->btn_clicked(); break;
        case 3: _t->on_freqBtnUnit1_clicked(); break;
        case 4: _t->on_freqBtnUnit2_clicked(); break;
        case 5: _t->on_freqBtnUnit3_clicked(); break;
        case 6: _t->on_freqBtnUnit4_clicked(); break;
        case 7: _t->on_amptBtnUnit1_clicked(); break;
        case 8: _t->on_amptBtnUnit2_clicked(); break;
        case 9: _t->on_amptBtnUnit3_clicked(); break;
        case 10: _t->on_amptBtnUnit4_clicked(); break;
        case 11: _t->on_amptBtnUnit5_clicked(); break;
        case 12: _t->on_amptBtnUnit6_clicked(); break;
        case 13: _t->on_amptBtnUnit7_clicked(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (SA_Dialog_DigitInput::*_t)(qint32 );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&SA_Dialog_DigitInput::finishEntry)) {
                *result = 0;
            }
        }
    }
}

const QMetaObject SA_Dialog_DigitInput::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_SA_Dialog_DigitInput.data,
      qt_meta_data_SA_Dialog_DigitInput,  qt_static_metacall, 0, 0}
};


const QMetaObject *SA_Dialog_DigitInput::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *SA_Dialog_DigitInput::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_SA_Dialog_DigitInput.stringdata))
        return static_cast<void*>(const_cast< SA_Dialog_DigitInput*>(this));
    return QDialog::qt_metacast(_clname);
}

int SA_Dialog_DigitInput::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
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

// SIGNAL 0
void SA_Dialog_DigitInput::finishEntry(qint32 _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_END_MOC_NAMESPACE

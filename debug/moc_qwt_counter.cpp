/****************************************************************************
** Meta object code from reading C++ file 'qwt_counter.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.3.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "C:/Qt/QWT/qwt_counter.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'qwt_counter.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.3.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_QwtCounter_t {
    QByteArrayData data[16];
    char stringdata[165];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_QwtCounter_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_QwtCounter_t qt_meta_stringdata_QwtCounter = {
    {
QT_MOC_LITERAL(0, 0, 10),
QT_MOC_LITERAL(1, 11, 14),
QT_MOC_LITERAL(2, 26, 0),
QT_MOC_LITERAL(3, 27, 5),
QT_MOC_LITERAL(4, 33, 12),
QT_MOC_LITERAL(5, 46, 11),
QT_MOC_LITERAL(6, 58, 10),
QT_MOC_LITERAL(7, 69, 11),
QT_MOC_LITERAL(8, 81, 10),
QT_MOC_LITERAL(9, 92, 9),
QT_MOC_LITERAL(10, 102, 8),
QT_MOC_LITERAL(11, 111, 8),
QT_MOC_LITERAL(12, 120, 11),
QT_MOC_LITERAL(13, 132, 11),
QT_MOC_LITERAL(14, 144, 11),
QT_MOC_LITERAL(15, 156, 8)
    },
    "QwtCounter\0buttonReleased\0\0value\0"
    "valueChanged\0btnReleased\0btnClicked\0"
    "textChanged\0numButtons\0basicstep\0"
    "minValue\0maxValue\0stepButton1\0stepButton2\0"
    "stepButton3\0editable"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_QwtCounter[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       9,   48, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   39,    2, 0x06 /* Public */,
       4,    1,   42,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       5,    0,   45,    2, 0x08 /* Private */,
       6,    0,   46,    2, 0x08 /* Private */,
       7,    0,   47,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, QMetaType::Double,    3,
    QMetaType::Void, QMetaType::Double,    3,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

 // properties: name, type, flags
       8, QMetaType::Int, 0x00095103,
       9, QMetaType::Double, 0x00095003,
      10, QMetaType::Double, 0x00095103,
      11, QMetaType::Double, 0x00095103,
      12, QMetaType::Int, 0x00095103,
      13, QMetaType::Int, 0x00095103,
      14, QMetaType::Int, 0x00095103,
       3, QMetaType::Double, 0x00095103,
      15, QMetaType::Bool, 0x00095103,

       0        // eod
};

void QwtCounter::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        QwtCounter *_t = static_cast<QwtCounter *>(_o);
        switch (_id) {
        case 0: _t->buttonReleased((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 1: _t->valueChanged((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 2: _t->btnReleased(); break;
        case 3: _t->btnClicked(); break;
        case 4: _t->textChanged(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (QwtCounter::*_t)(double );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&QwtCounter::buttonReleased)) {
                *result = 0;
            }
        }
        {
            typedef void (QwtCounter::*_t)(double );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&QwtCounter::valueChanged)) {
                *result = 1;
            }
        }
    }
}

const QMetaObject QwtCounter::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_QwtCounter.data,
      qt_meta_data_QwtCounter,  qt_static_metacall, 0, 0}
};


const QMetaObject *QwtCounter::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *QwtCounter::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_QwtCounter.stringdata))
        return static_cast<void*>(const_cast< QwtCounter*>(this));
    if (!strcmp(_clname, "QwtDoubleRange"))
        return static_cast< QwtDoubleRange*>(const_cast< QwtCounter*>(this));
    return QWidget::qt_metacast(_clname);
}

int QwtCounter::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
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
#ifndef QT_NO_PROPERTIES
      else if (_c == QMetaObject::ReadProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< int*>(_v) = numButtons(); break;
        case 1: *reinterpret_cast< double*>(_v) = step(); break;
        case 2: *reinterpret_cast< double*>(_v) = minValue(); break;
        case 3: *reinterpret_cast< double*>(_v) = maxValue(); break;
        case 4: *reinterpret_cast< int*>(_v) = stepButton1(); break;
        case 5: *reinterpret_cast< int*>(_v) = stepButton2(); break;
        case 6: *reinterpret_cast< int*>(_v) = stepButton3(); break;
        case 7: *reinterpret_cast< double*>(_v) = value(); break;
        case 8: *reinterpret_cast< bool*>(_v) = editable(); break;
        default: break;
        }
        _id -= 9;
    } else if (_c == QMetaObject::WriteProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: setNumButtons(*reinterpret_cast< int*>(_v)); break;
        case 1: setStep(*reinterpret_cast< double*>(_v)); break;
        case 2: setMinValue(*reinterpret_cast< double*>(_v)); break;
        case 3: setMaxValue(*reinterpret_cast< double*>(_v)); break;
        case 4: setStepButton1(*reinterpret_cast< int*>(_v)); break;
        case 5: setStepButton2(*reinterpret_cast< int*>(_v)); break;
        case 6: setStepButton3(*reinterpret_cast< int*>(_v)); break;
        case 7: setValue(*reinterpret_cast< double*>(_v)); break;
        case 8: setEditable(*reinterpret_cast< bool*>(_v)); break;
        default: break;
        }
        _id -= 9;
    } else if (_c == QMetaObject::ResetProperty) {
        _id -= 9;
    } else if (_c == QMetaObject::QueryPropertyDesignable) {
        _id -= 9;
    } else if (_c == QMetaObject::QueryPropertyScriptable) {
        _id -= 9;
    } else if (_c == QMetaObject::QueryPropertyStored) {
        _id -= 9;
    } else if (_c == QMetaObject::QueryPropertyEditable) {
        _id -= 9;
    } else if (_c == QMetaObject::QueryPropertyUser) {
        _id -= 9;
    } else if (_c == QMetaObject::RegisterPropertyMetaType) {
        if (_id < 9)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 9;
    }
#endif // QT_NO_PROPERTIES
    return _id;
}

// SIGNAL 0
void QwtCounter::buttonReleased(double _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void QwtCounter::valueChanged(double _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_END_MOC_NAMESPACE

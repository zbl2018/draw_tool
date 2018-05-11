/****************************************************************************
** Meta object code from reading C++ file 'paintsubmap.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.9.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../DEMO/paintsubmap.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'paintsubmap.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.9.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_PaintSubMap_t {
    QByteArrayData data[7];
    char stringdata0[87];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_PaintSubMap_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_PaintSubMap_t qt_meta_stringdata_PaintSubMap = {
    {
QT_MOC_LITERAL(0, 0, 11), // "PaintSubMap"
QT_MOC_LITERAL(1, 12, 18), // "sendsignallocation"
QT_MOC_LITERAL(2, 31, 0), // ""
QT_MOC_LITERAL(3, 32, 5), // "point"
QT_MOC_LITERAL(4, 38, 17), // "SendDrawMapSignal"
QT_MOC_LITERAL(5, 56, 12), // "PaintSubMap*"
QT_MOC_LITERAL(6, 69, 17) // "RotateSubmapAngle"

    },
    "PaintSubMap\0sendsignallocation\0\0point\0"
    "SendDrawMapSignal\0PaintSubMap*\0"
    "RotateSubmapAngle"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_PaintSubMap[] = {

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
       1,    1,   29,    2, 0x06 /* Public */,
       4,    1,   32,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       6,    0,   35,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    2,
    QMetaType::Void, 0x80000000 | 5,    2,

 // slots: parameters
    QMetaType::Void,

       0        // eod
};

void PaintSubMap::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        PaintSubMap *_t = static_cast<PaintSubMap *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->sendsignallocation((*reinterpret_cast< point(*)>(_a[1]))); break;
        case 1: _t->SendDrawMapSignal((*reinterpret_cast< PaintSubMap*(*)>(_a[1]))); break;
        case 2: _t->RotateSubmapAngle(); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 1:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< PaintSubMap* >(); break;
            }
            break;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (PaintSubMap::*_t)(point );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&PaintSubMap::sendsignallocation)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (PaintSubMap::*_t)(PaintSubMap * );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&PaintSubMap::SendDrawMapSignal)) {
                *result = 1;
                return;
            }
        }
    }
}

const QMetaObject PaintSubMap::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_PaintSubMap.data,
      qt_meta_data_PaintSubMap,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *PaintSubMap::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *PaintSubMap::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_PaintSubMap.stringdata0))
        return static_cast<void*>(const_cast< PaintSubMap*>(this));
    if (!strcmp(_clname, "QGraphicsItem"))
        return static_cast< QGraphicsItem*>(const_cast< PaintSubMap*>(this));
    return QObject::qt_metacast(_clname);
}

int PaintSubMap::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
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
void PaintSubMap::sendsignallocation(point _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void PaintSubMap::SendDrawMapSignal(PaintSubMap * _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE

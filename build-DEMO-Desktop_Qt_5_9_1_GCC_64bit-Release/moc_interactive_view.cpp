/****************************************************************************
** Meta object code from reading C++ file 'interactive_view.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.9.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../DEMO/interactive_view.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'interactive_view.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.9.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_InteractiveView_t {
    QByteArrayData data[11];
    char stringdata0[115];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_InteractiveView_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_InteractiveView_t qt_meta_stringdata_InteractiveView = {
    {
QT_MOC_LITERAL(0, 0, 15), // "InteractiveView"
QT_MOC_LITERAL(1, 16, 15), // "ReturnLastAngle"
QT_MOC_LITERAL(2, 32, 0), // ""
QT_MOC_LITERAL(3, 33, 13), // "SkipNextAngle"
QT_MOC_LITERAL(4, 47, 19), // "SubMapPressKeyEvent"
QT_MOC_LITERAL(5, 67, 6), // "zoomIn"
QT_MOC_LITERAL(6, 74, 7), // "zoomOut"
QT_MOC_LITERAL(7, 82, 4), // "zoom"
QT_MOC_LITERAL(8, 87, 11), // "scaleFactor"
QT_MOC_LITERAL(9, 99, 9), // "translate"
QT_MOC_LITERAL(10, 109, 5) // "delta"

    },
    "InteractiveView\0ReturnLastAngle\0\0"
    "SkipNextAngle\0SubMapPressKeyEvent\0"
    "zoomIn\0zoomOut\0zoom\0scaleFactor\0"
    "translate\0delta"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_InteractiveView[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       7,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   49,    2, 0x06 /* Public */,
       3,    1,   52,    2, 0x06 /* Public */,
       4,    1,   55,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       5,    0,   58,    2, 0x0a /* Public */,
       6,    0,   59,    2, 0x0a /* Public */,
       7,    1,   60,    2, 0x0a /* Public */,
       9,    1,   63,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::Bool,    2,
    QMetaType::Void, QMetaType::Bool,    2,
    QMetaType::Void, QMetaType::Int,    2,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Float,    8,
    QMetaType::Void, QMetaType::QPointF,   10,

       0        // eod
};

void InteractiveView::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        InteractiveView *_t = static_cast<InteractiveView *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->ReturnLastAngle((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 1: _t->SkipNextAngle((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 2: _t->SubMapPressKeyEvent((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: _t->zoomIn(); break;
        case 4: _t->zoomOut(); break;
        case 5: _t->zoom((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 6: _t->translate((*reinterpret_cast< QPointF(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (InteractiveView::*_t)(bool );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&InteractiveView::ReturnLastAngle)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (InteractiveView::*_t)(bool );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&InteractiveView::SkipNextAngle)) {
                *result = 1;
                return;
            }
        }
        {
            typedef void (InteractiveView::*_t)(int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&InteractiveView::SubMapPressKeyEvent)) {
                *result = 2;
                return;
            }
        }
    }
}

const QMetaObject InteractiveView::staticMetaObject = {
    { &QGraphicsView::staticMetaObject, qt_meta_stringdata_InteractiveView.data,
      qt_meta_data_InteractiveView,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *InteractiveView::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *InteractiveView::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_InteractiveView.stringdata0))
        return static_cast<void*>(const_cast< InteractiveView*>(this));
    return QGraphicsView::qt_metacast(_clname);
}

int InteractiveView::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QGraphicsView::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 7)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 7;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 7)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 7;
    }
    return _id;
}

// SIGNAL 0
void InteractiveView::ReturnLastAngle(bool _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void InteractiveView::SkipNextAngle(bool _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void InteractiveView::SubMapPressKeyEvent(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE

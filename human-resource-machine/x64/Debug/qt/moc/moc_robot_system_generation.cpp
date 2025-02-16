/****************************************************************************
** Meta object code from reading C++ file 'robot_system_generation.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.7.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../../../BasicFunctions/robot_system_generation.h"
#include <QtCore/qmetatype.h>

#include <QtCore/qtmochelpers.h>

#include <memory>


#include <QtCore/qxptype_traits.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'robot_system_generation.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 68
#error "This file was generated using the moc from 6.7.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

#ifndef Q_CONSTINIT
#define Q_CONSTINIT
#endif

QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
QT_WARNING_DISABLE_GCC("-Wuseless-cast")
namespace {

#ifdef QT_MOC_HAS_STRINGDATA
struct qt_meta_stringdata_CLASSROBOTSYSTEMENDCLASS_t {};
constexpr auto qt_meta_stringdata_CLASSROBOTSYSTEMENDCLASS = QtMocHelpers::stringData(
    "ROBOTSYSTEM",
    "fail_exe",
    "",
    "inbox_exe",
    "input_num",
    "outbox_exe",
    "add_exe",
    "sub_exe",
    "copyto_exe",
    "copyfrom_exe"
);
#else  // !QT_MOC_HAS_STRINGDATA
#error "qtmochelpers.h not found or too old."
#endif // !QT_MOC_HAS_STRINGDATA
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_CLASSROBOTSYSTEMENDCLASS[] = {

 // content:
      12,       // revision
       0,       // classname
       0,    0, // classinfo
       7,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       7,       // signalCount

 // signals: name, argc, parameters, tag, flags, initial metatype offsets
       1,    0,   56,    2, 0x06,    1 /* Public */,
       3,    1,   57,    2, 0x06,    2 /* Public */,
       5,    1,   60,    2, 0x06,    4 /* Public */,
       6,    1,   63,    2, 0x06,    6 /* Public */,
       7,    1,   66,    2, 0x06,    8 /* Public */,
       8,    1,   69,    2, 0x06,   10 /* Public */,
       9,    1,   72,    2, 0x06,   12 /* Public */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    4,
    QMetaType::Void, QMetaType::Int,    4,
    QMetaType::Void, QMetaType::Int,    4,
    QMetaType::Void, QMetaType::Int,    4,
    QMetaType::Void, QMetaType::Int,    4,
    QMetaType::Void, QMetaType::Int,    4,

       0        // eod
};

Q_CONSTINIT const QMetaObject ROBOTSYSTEM::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_CLASSROBOTSYSTEMENDCLASS.offsetsAndSizes,
    qt_meta_data_CLASSROBOTSYSTEMENDCLASS,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_stringdata_CLASSROBOTSYSTEMENDCLASS_t,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<ROBOTSYSTEM, std::true_type>,
        // method 'fail_exe'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'inbox_exe'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        // method 'outbox_exe'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        // method 'add_exe'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        // method 'sub_exe'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        // method 'copyto_exe'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        // method 'copyfrom_exe'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>
    >,
    nullptr
} };

void ROBOTSYSTEM::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<ROBOTSYSTEM *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->fail_exe(); break;
        case 1: _t->inbox_exe((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 2: _t->outbox_exe((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 3: _t->add_exe((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 4: _t->sub_exe((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 5: _t->copyto_exe((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 6: _t->copyfrom_exe((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (ROBOTSYSTEM::*)();
            if (_t _q_method = &ROBOTSYSTEM::fail_exe; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (ROBOTSYSTEM::*)(int );
            if (_t _q_method = &ROBOTSYSTEM::inbox_exe; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (ROBOTSYSTEM::*)(int );
            if (_t _q_method = &ROBOTSYSTEM::outbox_exe; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (ROBOTSYSTEM::*)(int );
            if (_t _q_method = &ROBOTSYSTEM::add_exe; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (ROBOTSYSTEM::*)(int );
            if (_t _q_method = &ROBOTSYSTEM::sub_exe; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 4;
                return;
            }
        }
        {
            using _t = void (ROBOTSYSTEM::*)(int );
            if (_t _q_method = &ROBOTSYSTEM::copyto_exe; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 5;
                return;
            }
        }
        {
            using _t = void (ROBOTSYSTEM::*)(int );
            if (_t _q_method = &ROBOTSYSTEM::copyfrom_exe; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 6;
                return;
            }
        }
    }
}

const QMetaObject *ROBOTSYSTEM::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ROBOTSYSTEM::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_CLASSROBOTSYSTEMENDCLASS.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int ROBOTSYSTEM::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 7)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 7;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 7)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 7;
    }
    return _id;
}

// SIGNAL 0
void ROBOTSYSTEM::fail_exe()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void ROBOTSYSTEM::inbox_exe(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void ROBOTSYSTEM::outbox_exe(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void ROBOTSYSTEM::add_exe(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void ROBOTSYSTEM::sub_exe(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void ROBOTSYSTEM::copyto_exe(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}

// SIGNAL 6
void ROBOTSYSTEM::copyfrom_exe(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 6, _a);
}
QT_WARNING_POP

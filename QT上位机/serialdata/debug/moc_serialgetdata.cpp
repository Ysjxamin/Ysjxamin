/****************************************************************************
** Meta object code from reading C++ file 'serialgetdata.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.9.9)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../serialgetdata.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'serialgetdata.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.9.9. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_SerialGetData_t {
    QByteArrayData data[11];
    char stringdata0[185];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_SerialGetData_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_SerialGetData_t qt_meta_stringdata_SerialGetData = {
    {
QT_MOC_LITERAL(0, 0, 13), // "SerialGetData"
QT_MOC_LITERAL(1, 14, 12), // "showdatabase"
QT_MOC_LITERAL(2, 27, 0), // ""
QT_MOC_LITERAL(3, 28, 24), // "on_scanSerialBtn_clicked"
QT_MOC_LITERAL(4, 53, 24), // "on_openSerialBtn_clicked"
QT_MOC_LITERAL(5, 78, 22), // "on_eConnectBtn_clicked"
QT_MOC_LITERAL(6, 101, 25), // "on_eDisconnectBtn_clicked"
QT_MOC_LITERAL(7, 127, 10), // "timerEvent"
QT_MOC_LITERAL(8, 138, 12), // "QTimerEvent*"
QT_MOC_LITERAL(9, 151, 5), // "event"
QT_MOC_LITERAL(10, 157, 27) // "on_eDisconnectBtn_2_clicked"

    },
    "SerialGetData\0showdatabase\0\0"
    "on_scanSerialBtn_clicked\0"
    "on_openSerialBtn_clicked\0"
    "on_eConnectBtn_clicked\0on_eDisconnectBtn_clicked\0"
    "timerEvent\0QTimerEvent*\0event\0"
    "on_eDisconnectBtn_2_clicked"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_SerialGetData[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       7,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   49,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       3,    0,   50,    2, 0x08 /* Private */,
       4,    0,   51,    2, 0x08 /* Private */,
       5,    0,   52,    2, 0x08 /* Private */,
       6,    0,   53,    2, 0x08 /* Private */,
       7,    1,   54,    2, 0x08 /* Private */,
      10,    0,   57,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 8,    9,
    QMetaType::Void,

       0        // eod
};

void SerialGetData::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        SerialGetData *_t = static_cast<SerialGetData *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->showdatabase(); break;
        case 1: _t->on_scanSerialBtn_clicked(); break;
        case 2: _t->on_openSerialBtn_clicked(); break;
        case 3: _t->on_eConnectBtn_clicked(); break;
        case 4: _t->on_eDisconnectBtn_clicked(); break;
        case 5: _t->timerEvent((*reinterpret_cast< QTimerEvent*(*)>(_a[1]))); break;
        case 6: _t->on_eDisconnectBtn_2_clicked(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            typedef void (SerialGetData::*_t)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&SerialGetData::showdatabase)) {
                *result = 0;
                return;
            }
        }
    }
}

const QMetaObject SerialGetData::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_SerialGetData.data,
      qt_meta_data_SerialGetData,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *SerialGetData::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *SerialGetData::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_SerialGetData.stringdata0))
        return static_cast<void*>(this);
    return QMainWindow::qt_metacast(_clname);
}

int SerialGetData::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
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
void SerialGetData::showdatabase()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE

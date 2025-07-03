/****************************************************************************
** Meta object code from reading C++ file 'musicprocessor.h'
**
** Created by: The Qt Meta Object Compiler version 69 (Qt 6.9.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../../../ap_project/music player/music_processor/musicprocessor.h"
#include <QtCore/qmetatype.h>

#include <QtCore/qtmochelpers.h>

#include <memory>


#include <QtCore/qxptype_traits.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'musicprocessor.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 69
#error "This file was generated using the moc from 6.9.0. It"
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
struct qt_meta_tag_ZN11musicplayerE_t {};
} // unnamed namespace

template <> constexpr inline auto musicplayer::qt_create_metaobjectdata<qt_meta_tag_ZN11musicplayerE_t>()
{
    namespace QMC = QtMocConstants;
    QtMocHelpers::StringRefStorage qt_stringData {
        "musicplayer",
        "loaduserfavoriteslist",
        "",
        "favoritepaths",
        "playselectedsong",
        "updateslider",
        "position",
        "setsliderrange",
        "duration",
        "handleplaybutton",
        "playselectedsongfromlist",
        "playnextsong",
        "playprevioussong",
        "changerepeatstate",
        "shufflestate",
        "playrandomsong",
        "savecurrentsongtofavorites",
        "loadfavoritesfromfile",
        "playselectedfavoritesong",
        "playselectedfavoritesongfromcontrols",
        "playnextfavoritesong",
        "playpreviousfavoritesong",
        "fav_changerepeatstate",
        "fav_shufflestate",
        "savetotempfavorites",
        "playselectedtempfavoritesong",
        "playnexttempfavoritesong",
        "playprevioustempfavoritesong",
        "temp_changerepeatstate",
        "temp_shufflestate",
        "handletempplaybutton",
        "setvolume",
        "volume",
        "startserver",
        "newconnection",
        "serverdisconnected",
        "readserverdata",
        "startclient",
        "clientConnected",
        "clientdisconnected",
        "readclientdata",
        "displayerror",
        "QAbstractSocket::SocketError",
        "socketerror",
        "sendsonginfo_slot",
        "processreceivedsonginfo",
        "songpath",
        "playreceivedsong"
    };

    QtMocHelpers::UintData qt_methods {
        // Slot 'loaduserfavoriteslist'
        QtMocHelpers::SlotData<void(const QStringList &)>(1, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::QStringList, 3 },
        }}),
        // Slot 'playselectedsong'
        QtMocHelpers::SlotData<void()>(4, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'updateslider'
        QtMocHelpers::SlotData<void(qint64)>(5, 2, QMC::AccessPrivate, QMetaType::Void, {{
            { QMetaType::LongLong, 6 },
        }}),
        // Slot 'setsliderrange'
        QtMocHelpers::SlotData<void(qint64)>(7, 2, QMC::AccessPrivate, QMetaType::Void, {{
            { QMetaType::LongLong, 8 },
        }}),
        // Slot 'handleplaybutton'
        QtMocHelpers::SlotData<void()>(9, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'playselectedsongfromlist'
        QtMocHelpers::SlotData<void()>(10, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'playnextsong'
        QtMocHelpers::SlotData<void()>(11, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'playprevioussong'
        QtMocHelpers::SlotData<void()>(12, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'changerepeatstate'
        QtMocHelpers::SlotData<void()>(13, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'shufflestate'
        QtMocHelpers::SlotData<void()>(14, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'playrandomsong'
        QtMocHelpers::SlotData<void()>(15, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'savecurrentsongtofavorites'
        QtMocHelpers::SlotData<void()>(16, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'loadfavoritesfromfile'
        QtMocHelpers::SlotData<void()>(17, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'playselectedfavoritesong'
        QtMocHelpers::SlotData<void()>(18, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'playselectedfavoritesongfromcontrols'
        QtMocHelpers::SlotData<void()>(19, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'playnextfavoritesong'
        QtMocHelpers::SlotData<void()>(20, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'playpreviousfavoritesong'
        QtMocHelpers::SlotData<void()>(21, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'fav_changerepeatstate'
        QtMocHelpers::SlotData<void()>(22, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'fav_shufflestate'
        QtMocHelpers::SlotData<void()>(23, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'savetotempfavorites'
        QtMocHelpers::SlotData<void()>(24, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'playselectedtempfavoritesong'
        QtMocHelpers::SlotData<void()>(25, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'playnexttempfavoritesong'
        QtMocHelpers::SlotData<void()>(26, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'playprevioustempfavoritesong'
        QtMocHelpers::SlotData<void()>(27, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'temp_changerepeatstate'
        QtMocHelpers::SlotData<void()>(28, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'temp_shufflestate'
        QtMocHelpers::SlotData<void()>(29, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'handletempplaybutton'
        QtMocHelpers::SlotData<void()>(30, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'setvolume'
        QtMocHelpers::SlotData<void(int)>(31, 2, QMC::AccessPrivate, QMetaType::Void, {{
            { QMetaType::Int, 32 },
        }}),
        // Slot 'startserver'
        QtMocHelpers::SlotData<void()>(33, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'newconnection'
        QtMocHelpers::SlotData<void()>(34, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'serverdisconnected'
        QtMocHelpers::SlotData<void()>(35, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'readserverdata'
        QtMocHelpers::SlotData<void()>(36, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'startclient'
        QtMocHelpers::SlotData<void()>(37, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'clientConnected'
        QtMocHelpers::SlotData<void()>(38, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'clientdisconnected'
        QtMocHelpers::SlotData<void()>(39, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'readclientdata'
        QtMocHelpers::SlotData<void()>(40, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'displayerror'
        QtMocHelpers::SlotData<void(QAbstractSocket::SocketError)>(41, 2, QMC::AccessPrivate, QMetaType::Void, {{
            { 0x80000000 | 42, 43 },
        }}),
        // Slot 'sendsonginfo_slot'
        QtMocHelpers::SlotData<void()>(44, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'processreceivedsonginfo'
        QtMocHelpers::SlotData<void(const QString &)>(45, 2, QMC::AccessPrivate, QMetaType::Void, {{
            { QMetaType::QString, 46 },
        }}),
        // Slot 'playreceivedsong'
        QtMocHelpers::SlotData<void()>(47, 2, QMC::AccessPrivate, QMetaType::Void),
    };
    QtMocHelpers::UintData qt_properties {
    };
    QtMocHelpers::UintData qt_enums {
    };
    return QtMocHelpers::metaObjectData<musicplayer, qt_meta_tag_ZN11musicplayerE_t>(QMC::MetaObjectFlag{}, qt_stringData,
            qt_methods, qt_properties, qt_enums);
}
Q_CONSTINIT const QMetaObject musicplayer::staticMetaObject = { {
    QMetaObject::SuperData::link<QWidget::staticMetaObject>(),
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN11musicplayerE_t>.stringdata,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN11musicplayerE_t>.data,
    qt_static_metacall,
    nullptr,
    qt_staticMetaObjectRelocatingContent<qt_meta_tag_ZN11musicplayerE_t>.metaTypes,
    nullptr
} };

void musicplayer::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<musicplayer *>(_o);
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: _t->loaduserfavoriteslist((*reinterpret_cast< std::add_pointer_t<QStringList>>(_a[1]))); break;
        case 1: _t->playselectedsong(); break;
        case 2: _t->updateslider((*reinterpret_cast< std::add_pointer_t<qint64>>(_a[1]))); break;
        case 3: _t->setsliderrange((*reinterpret_cast< std::add_pointer_t<qint64>>(_a[1]))); break;
        case 4: _t->handleplaybutton(); break;
        case 5: _t->playselectedsongfromlist(); break;
        case 6: _t->playnextsong(); break;
        case 7: _t->playprevioussong(); break;
        case 8: _t->changerepeatstate(); break;
        case 9: _t->shufflestate(); break;
        case 10: _t->playrandomsong(); break;
        case 11: _t->savecurrentsongtofavorites(); break;
        case 12: _t->loadfavoritesfromfile(); break;
        case 13: _t->playselectedfavoritesong(); break;
        case 14: _t->playselectedfavoritesongfromcontrols(); break;
        case 15: _t->playnextfavoritesong(); break;
        case 16: _t->playpreviousfavoritesong(); break;
        case 17: _t->fav_changerepeatstate(); break;
        case 18: _t->fav_shufflestate(); break;
        case 19: _t->savetotempfavorites(); break;
        case 20: _t->playselectedtempfavoritesong(); break;
        case 21: _t->playnexttempfavoritesong(); break;
        case 22: _t->playprevioustempfavoritesong(); break;
        case 23: _t->temp_changerepeatstate(); break;
        case 24: _t->temp_shufflestate(); break;
        case 25: _t->handletempplaybutton(); break;
        case 26: _t->setvolume((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 27: _t->startserver(); break;
        case 28: _t->newconnection(); break;
        case 29: _t->serverdisconnected(); break;
        case 30: _t->readserverdata(); break;
        case 31: _t->startclient(); break;
        case 32: _t->clientConnected(); break;
        case 33: _t->clientdisconnected(); break;
        case 34: _t->readclientdata(); break;
        case 35: _t->displayerror((*reinterpret_cast< std::add_pointer_t<QAbstractSocket::SocketError>>(_a[1]))); break;
        case 36: _t->sendsonginfo_slot(); break;
        case 37: _t->processreceivedsonginfo((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 38: _t->playreceivedsong(); break;
        default: ;
        }
    }
    if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
        case 35:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 0:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< QAbstractSocket::SocketError >(); break;
            }
            break;
        }
    }
}

const QMetaObject *musicplayer::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *musicplayer::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_staticMetaObjectStaticContent<qt_meta_tag_ZN11musicplayerE_t>.strings))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int musicplayer::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 39)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 39;
    }
    if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 39)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 39;
    }
    return _id;
}
QT_WARNING_POP

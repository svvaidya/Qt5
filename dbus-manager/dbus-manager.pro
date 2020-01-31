QT -= gui
QT += dbus

win32:CONFIG += console

HEADERS += dbus-manager.h \
    dbus-network-manager.h
SOURCES += dbus-manager.cpp \
    dbus-network-manager.cpp \
    main.cpp

target.path = .
INSTALLS += target

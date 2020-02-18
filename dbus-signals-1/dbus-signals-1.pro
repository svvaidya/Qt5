QT -= gui
QT += dbus

win32:CONFIG += console

HEADERS += receiver.h
SOURCES += main.cpp

target.path = .
INSTALLS += target

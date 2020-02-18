/****************************************************************************
**
** Copyright (C) 2015 The Qt Company Ltd.
** Contact: http://www.qt.io/licensing/
**
** This file is part of the examples of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:BSD$
** You may use this file under the terms of the BSD license as follows:
**
** "Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are
** met:
**   * Redistributions of source code must retain the above copyright
**     notice, this list of conditions and the following disclaimer.
**   * Redistributions in binary form must reproduce the above copyright
**     notice, this list of conditions and the following disclaimer in
**     the documentation and/or other materials provided with the
**     distribution.
**   * Neither the name of The Qt Company Ltd nor the names of its
**     contributors may be used to endorse or promote products derived
**     from this software without specific prior written permission.
**
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
**
** $QT_END_LICENSE$
**
****************************************************************************/

#ifndef DBUS_MANAGER_H
#define DBUS_MANAGER_H

#include <QtCore/QObject>
#include <QtDBus/QDBusError>
#include <QtDBus/QDBusInterface>
#include <QtDBus/QDBusMessage>
#include <QtDBus/QDBusReply>
#include <QtDBus/QDBusObjectPath>
#include <QtCore/QtCore>

#include <QtCore/QString>
#include <QtCore/QList>
#include <QtCore/QStringList>

//class DBus_Access: public QDBusInterface, public QDBusMessage, public QDBusReply, public QDBusError , public QDBusObjectPath, public QList, public QStringList, public QString, public QVariant {
class DBus_Access_Manager {

public:

    // bool callMethod(QString service, QString path, QString interface, QString methodName, QString& response);
    bool callMethod(const QString& service, const QString& path, const QString& interface, const QString& methodName, QStringList& responseList);

    bool getProperty(const QString& service, QString& path, const QString& interface, QStringList& propertyNameList, QStringList& responseList);
    bool getProperty(const QString& service, QString& path, const QString& interface, QString& propertyName, QString& response);

    bool getProperty(const QString& service, QString& path, const QString& interface, QStringList& propertyNameList, int *responseList);
    bool getProperty(const QString& service, QString& path, const QString& interface, QString& propertyName, int &response);


    static inline void displayDebugMessage(void) {
        qDebug() << __FILE__ << "::" << __FUNCTION__ << "(" <<   __LINE__ << ")";
    }

    static inline void displayDebugMessage(const char* data) {
        qDebug() << __FILE__ << "::" << __FUNCTION__ << "(" <<   __LINE__ << ") :: " << data;
    }

    static inline void displayDebugMessage(QString message) {
        qDebug() << __FILE__ << "::" << __FUNCTION__ << "(" <<   __LINE__ << ") :: " <<  message;
    }

};


void networkManagerMain(void);
#endif

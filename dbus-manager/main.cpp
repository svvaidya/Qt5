

#include <QtCore/QCoreApplication>
#include <QtCore/QDebug>
#include <QtCore/QStringList>
#include <QtDBus/QtDBus>
#include <QtDBus/QDBusConnectionInterface>
#include <QtDBus/QDBusConnection>
#include <QtCore/QObject>
#include <QtCore/QTimer>

#include <QtCore/QString>
#include <QtCore/QList>
#include <QtCore/QStringList>


#include <QtDBus/QDBusError>
#include <QtDBus/QDBusInterface>
#include <QtDBus/QDBusMessage>
#include <QtDBus/QDBusReply>
#include <QtDBus/QDBusObjectPath>
#include <QtDBus/QDBusContext>
#include <QMap>
#include <QtNetwork/QtNetwork>
#include <QtNetwork/QNetworkConfiguration>
#include <QtNetwork/QNetworkConfigurationManager>

#include <stdio.h>
#include <stdlib.h>
#include <iostream>


#include "dbus-network-manager.h"

int main(int argc, char **argv)
{
    bool flag = true;

    QCoreApplication app(argc, argv);

    if (argc > 1) {
        flag = false;
    }

    if (flag == true) {
        if (!QDBusConnection::systemBus().isConnected()) {
            fprintf(stderr, "Cannot connect to the D-Bus system bus.\n"
                    "To start it, run:\n"
                    "\teval `dbus-launch --auto-syntax`\n");
            return 1;
        }
        else {
             qDebug() << "!!!!!!!!!!!\n System Bus connected\n!!!!!!!!!!!!!!!!!!!!!";
        }

        QDBusConnection systemBus = QDBusConnection::systemBus();
        QStringList systemServiceNames = systemBus.interface()->registeredServiceNames();
        qDebug() << "System bus Registered Service names: " << systemServiceNames << "\n\n";
        systemBus.QDBusConnection::~QDBusConnection();

        QDBusConnection sessionBus = QDBusConnection::sessionBus();
        QStringList serviceNames = sessionBus.interface()->registeredServiceNames();
        qDebug() << "Session Bus Registered Service names: " << serviceNames << "\n\n";
        sessionBus.QDBusConnection::~QDBusConnection();

    }
    else {
        if (!QDBusConnection::sessionBus().isConnected()) {
            fprintf(stderr, "Cannot connect to the D-Bus session bus.\n"
                    "To start it, run:\n"
                    "\teval `dbus-launch --auto-syntax`\n");
            return 1;
        }
        else {
             qDebug() << "!!!!!!!!!!!\n Session Bus connected\n!!!!!!!!!!!!!!!!!!!!!";
        }
    }


    networkManagerMain();


    return 0;
}

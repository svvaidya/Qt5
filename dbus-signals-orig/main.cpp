

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
    QCoreApplication app(argc, argv);
    DBus_Network_Manager temp;
    DBus_Network_Manager testObj;

    //DBus_Network_Manager::networkManagerMain();
    testObj.networkManagerMain();

    return 0;
}

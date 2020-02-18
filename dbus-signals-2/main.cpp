
#include <QCoreApplication>
#include <QDBusConnection>
#include <QtCore/QTimer>
#include <QtCore/QDebug>
#include <QtNetwork/QtNetwork>


#include <QtCore/QCoreApplication>
#include <QtCore/QStringList>
#include <QtDBus/QtDBus>
#include <QtDBus/QDBusConnectionInterface>
#include <QtDBus/QDBusConnection>
#include <QtCore/QObject>

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

#include <QtNetwork/QNetworkConfiguration>
#include <QtNetwork/QNetworkConfigurationManager>


#include "receiver.h"


const QString networkManagerService("org.freedesktop.NetworkManager");
const QString networkManagerPath("/org/freedesktop/NetworkManager");
const QString nmInterface("org.freedesktop.NetworkManager");
const QString nmDeviceInterface("org.freedesktop.NetworkManager.Device");
const QString nmDeviceInterfaceEth("org.freedesktop.NetworkManager.Device/0");
const QString nmDeviceWirelessInterface("org.freedesktop.NetworkManager.Device.Wireless");
class Example1 : public QObject
{
    //Q_OBJECT
public:
    Example1(QObject* parent = NULL) : QObject(parent)
    {
    }
    void setupDBus()
    {
        // Get the system bus
        QDBusConnection dBusSystem = QDBusConnection::systemBus();
        // check if it is connected
        if (!dBusSystem.isConnected())
        {
            qFatal("Cannot connect to the D-Bus session bus.");
            return;
        }
        // register "device added"
        Q_ASSERT(dBusSystem.connect("org.freedesktop.NetworkManager",
                                "/org/freedesktop/NetworkManager",
                                "org.freedesktop.NetworkManager.Device/0",
                                "StateChanged",
                                this,
                                SLOT(deviceAdded(const QDBusObjectPath&))));
    }
private slots:
    // slot for "device added"
    void deviceAdded(const QDBusObjectPath &in)
    {
        qDebug() << "device added: "; //<< in.path();
    }
};


int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    Example1 example;
    example.setupDBus();
#if 0
    qDebug() << "\n\n\n ..... Starting 30 second Delay .... \n\n";
    QTime dieTime= QTime::currentTime().addSecs(30);
    while (QTime::currentTime() < dieTime) {
        QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
   }
#endif
   qDebug() << "\n\n\n ..... End 30 second Delay .... \n\n";

   return a.exec();
}


#if 0
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

#endif


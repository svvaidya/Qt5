
#include <QtCore/QObject>
#include <QtCore/QtCore>
#include <QtCore/QCoreApplication>
#include <QtCore/QDebug>

#include <QtDBus/QtDBus>
#include <QtDBus/QDBusError>
#include <QtDBus/QDBusInterface>
#include <QtDBus/QDBusMessage>
#include <QtDBus/QDBusReply>
#include <QtDBus/QDBusObjectPath>
#include <QtDBus/QDBusConnectionInterface>
#include <QtDBus/QDBusConnection>
#include <QtDBus/QDBusContext>

#include <QtCore/QTimer>

#include <QtCore/QString>
#include <QtCore/QList>
#include <QtCore/QStringList>

#include <QMap>
#include <QtNetwork/QtNetwork>
#include <QtNetwork/QNetworkConfiguration>
#include <QtNetwork/QNetworkConfigurationManager>

#include <stdio.h>
#include <stdlib.h>
#include <iostream>

#define NM_DEVICE_TYPE_ETHERNET  (0x01)
#define NM_DEVICE_TYPE_WIFI      (0x02)
#define NM_DEVICE_TYPE_BT        (0x05)

const QString networkManagerService("org.freedesktop.NetworkManager");
const QString networkManagerPath("/org/freedesktop/NetworkManager");
const QString nmInterface("org.freedesktop.NetworkManager");
const QString nmDeviceInterface("org.freedesktop.NetworkManager.Device");
const QString nmDeviceWirelessInterface("org.freedesktop.NetworkManager.Device.Wireless");
const QString getDeviceMethodName("GetDevices");
const QString ethernetDevicePath("/org/freedesktop/NetworkManager/Devices/0");

class DBus_Access_Manager: public QObject {

public:
    unsigned int eventCounter;
     unsigned int timeCounter;
    DBus_Access_Manager(unsigned int counter, unsigned int timeCount) {
        eventCounter = counter;
        timeCounter = timeCount;
    }
    unsigned int getEventCounter(void) {
        return eventCounter;
    }

    unsigned int getTimeCounter(void) {
        return timeCounter;
    }

    void incrementTimeCounter(void) {
        timeCounter++;
    }

public slots:
    void deviceStateChanged(unsigned int newState, unsigned int reason, unsigned int oldState);
    void deviceStateChanged(unsigned int newState);
    void deviceStateChanged(unsigned int *newState);
};

void DBus_Access_Manager::deviceStateChanged(unsigned int newState, unsigned int reason, unsigned int oldState) {
    eventCounter++;
    qDebug() << "Device state changed:: 3:: " << newState << " " << reason << " " << oldState;
}

void DBus_Access_Manager::deviceStateChanged(unsigned int newState) {
     eventCounter++;
    qDebug() << "Device state changed:: 1:: " << newState;
}

void DBus_Access_Manager::deviceStateChanged(unsigned int* newState) {
    eventCounter++;
    qDebug() << "Device state changed:: 1P:: " << *newState;
}

int main(int argc, char **argv)
{
    QCoreApplication nmTestApp(argc, argv);

    QDBusConnection systemBus = QDBusConnection::systemBus();
    //QDBusConnection systemBus = QDBusConnection::sessionBus();
    if (!systemBus.isConnected()) {
        qDebug() << "!!!!!!!!!!!\n System Bus not connected.Terminating ...\n!!!!!!!!!!!!!!!!!!!!!";
        return 1;
    }
    else {
         qDebug() << "!!!!!!!!!!!\n System Bus connected\n!!!!!!!!!!!!!!!!!!!!!";
    }

    QStringList systemServiceNames = systemBus.interface()->registeredServiceNames();
    qDebug() << "System bus Registered Service names: " << systemServiceNames << "\n\n";

    //bool result;
    DBus_Access_Manager nmObject(10, 100);
    QStringList networkDeviceList;

       //  if ( deviceTypeResponseList[0] == NM_DEVICE_TYPE_ETHERNET)
        {

            QDBusInterface *ethernetInterface = new QDBusInterface(networkManagerService,
                                                       ethernetDevicePath,
                                                       nmDeviceInterface,
                                                       systemBus);
                                                       //&nmObject);


            if(ethernetInterface->isValid()) {
                qDebug() << "Interface \"" << nmDeviceInterface << "\" is Valid";
                systemBus.connect(networkManagerService, ethernetDevicePath, nmDeviceInterface,
                                  "StateChanged", &nmObject,
                                  SLOT(deviceStateChanged(unsigned int*)));

            }
        }

#if 1
    qDebug() << "\n\n\n ..... Starting 30 second Delay Starting ....";
   qDebug() << "Event Counter: " << nmObject.getEventCounter() << " Time Counter:  " << nmObject.getTimeCounter() << " .... \n\n";

    QTime dieTime= QTime::currentTime().addSecs(30);
    while (QTime::currentTime() < dieTime) {
        QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
        nmObject.incrementTimeCounter();
   }
   qDebug() << "\n\n\n ..... End 30 second Delay .... ";
   qDebug() << "Event Counter: " << nmObject.getEventCounter() << " Time Counter:  " << nmObject.getTimeCounter() << " .... \n\n";
#else
    qDebug() << "\n\n\n ..... Waiting for Signal .... \n\n";
    nmTestApp.exec();
#endif

    return 0;
}

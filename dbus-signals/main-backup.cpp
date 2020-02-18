
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

class DBus_Access_Manager {

public:
    bool callMethod(QDBusConnection& connection, const QString& service, const QString& path,
                    const QString& interface, const QString& methodName, QStringList& responseList);
    bool getDeviceProperty(QDBusConnection& connection, const QString& service, const QString& path,
                           const QString& interface, QStringList& propertyNameList, int *responseList);
public slots:
    void deviceStateChanged(unsigned int newState, unsigned int reason, unsigned int oldState);
    void deviceStateChanged(unsigned int newState);
};
bool DBus_Access_Manager::callMethod(QDBusConnection& connection,
                                     const QString& service,
                                     const QString& path,
                                     const QString& interface,
                                     const QString& methodName,
                                      QStringList& responseList) {
      bool returnValue = false;
      responseList.clear();
      //QDBusInterface methodInterface(service, path, interface, QDBusConnection::systemBus());
      QDBusInterface methodInterface(service, path, interface, connection);
      if (methodInterface.isValid()) {
          QDBusReply<QList<QDBusObjectPath> > result = methodInterface.call(methodName);
          if (result.isValid()) {
              returnValue = true;
              foreach (const QDBusObjectPath& responseString, result.value()) {
                  responseList << responseString.path();
              }
          }
          else {
              qDebug() << "Method Call Failed";
          }
      }
      else {
          qDebug() << "Interface Object Creation Failed";
      }

      return returnValue;
}

bool DBus_Access_Manager::getDeviceProperty(QDBusConnection& connection,
                                            const QString& service,
                                            const QString& path,
                                            const QString& interface,
                                            QStringList& propertyNameList,
                                            int *responseList) {
     bool returnValue = false;

      QDBusInterface propertyInterface(service, path, interface, connection);
     if (propertyInterface.isValid()) {
         size_t numProperties = (size_t)propertyNameList.count();
         QVariant  interfaceString;
         size_t counter;
         for (counter = 0; counter < numProperties; counter++) {
             interfaceString = propertyInterface.property(((QString *)&propertyNameList.at(counter))->toStdString().c_str());
             if (interfaceString.isValid()) {
                 responseList[counter] = interfaceString.toInt();
                 returnValue = true;
             }
             else {
                 returnValue = false;
                 break;
             }
         }
     }
     else {
         qDebug() << "Interface Object Creation Failed";
     }

     return returnValue;
 }




int main(int argc, char **argv)
{
    QCoreApplication app(argc, argv);


    QDBusConnection systemBus = QDBusConnection::systemBus();
    if (!systemBus.isConnected()) {
        qDebug() << "!!!!!!!!!!!\n System Bus not connected.Terminating ...\n!!!!!!!!!!!!!!!!!!!!!";
        return 1;
    }
    else {
         qDebug() << "!!!!!!!!!!!\n System Bus connected\n!!!!!!!!!!!!!!!!!!!!!";
    }
    QStringList systemServiceNames = systemBus.interface()->registeredServiceNames();
    qDebug() << "System bus Registered Service names: " << systemServiceNames << "\n\n";


    QDBusConnection sessionBus = QDBusConnection::sessionBus();
    QStringList serviceNames = sessionBus.interface()->registeredServiceNames();
    qDebug() << "Session Bus Registered Service names: " << serviceNames << "\n\n";
    sessionBus.QDBusConnection::~QDBusConnection();

    bool result;
    DBus_Access_Manager nmObject;
    QStringList networkDeviceList;
#if 0
    result = nmObject.callMethod(systemBus,
                                 networkManagerService,
                                 networkManagerPath,
                                 nmInterface,
                                 getDeviceMethodName,
                                 networkDeviceList);
    // Print list of devices
    if (result == true) {
        QStringList propertyNameList;
        size_t numElements = (size_t)networkDeviceList.count();
        qDebug() << "Number of Network Devices Detected: "  << numElements;
        // Read state and Device Type properties
        propertyNameList.clear();
        propertyNameList << "DeviceType";
        propertyNameList << "State";
        int *deviceTypeResponseList = new int [propertyNameList.count()];

        for (size_t counter = 0; counter < numElements; counter++) {
            qDebug() << counter << ":: " << networkDeviceList.at(counter);
            result = nmObject.getDeviceProperty(systemBus,
                                            networkManagerService,
                                            (QString &)networkDeviceList.at(counter),
                                            nmDeviceInterface,
                                            propertyNameList,
                                            deviceTypeResponseList);
            if (result == true) {
                size_t numProperties = propertyNameList.count();
                qDebug() << "Number of properties Read: " << numProperties;
                for (size_t propertyCounter = 0; propertyCounter < numProperties; propertyCounter++) {
                    qDebug() << "Property: " << propertyNameList.at(propertyCounter) << " :: Value: " << deviceTypeResponseList[propertyCounter];
                }
            }
        }
    }
#endif
    // Test Ethernet up/down
    QString ethernetDevice("/org/freedesktop/NetworkManager/Devices/0");
    QStringList propertyNameList;
    // Read state and Device Type properties
    propertyNameList.clear();
    propertyNameList << "DeviceType";
    propertyNameList << "State";
    int *deviceTypeResponseList = new int [propertyNameList.count()];
    qDebug() << "Device Name:  " << ethernetDevice;

    result = nmObject.getDeviceProperty(systemBus,
                                    networkManagerService,
                                    ethernetDevice,
                                    nmDeviceInterface,
                                    propertyNameList,
                                    deviceTypeResponseList);
    if (result == true) {
        size_t numProperties = propertyNameList.count();
        qDebug() << "Number of properties Read: " << numProperties;
        for (size_t propertyCounter = 0; propertyCounter < numProperties; propertyCounter++) {
            qDebug() << "Property: " << propertyNameList.at(propertyCounter) << " :: Value: " << deviceTypeResponseList[propertyCounter];
        }
    }


    return 0;
}

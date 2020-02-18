
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
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
#include "dbus-manager.h"
#include "dbus-network-manager.h"

const QString DBus_Network_Manager::networkManagerService("org.freedesktop.NetworkManager");

const QString DBus_Network_Manager::networkManagerPath("/org/freedesktop/NetworkManager");

const QString DBus_Network_Manager::nmInterface("org.freedesktop.NetworkManager");
const QString DBus_Network_Manager::nmDeviceInterface("org.freedesktop.NetworkManager.Device");
const QString DBus_Network_Manager::nmDeviceWirelessInterface("org.freedesktop.NetworkManager.Device.Wireless");

const QString DBus_Network_Manager::getDeviceMethodName("GetDevices");
const QString DBus_Network_Manager::getAllApListMethodName("GetAllAccessPoints");

bool DBus_Network_Manager::getNetworkDeviceList(QStringList &deviceList) {
    bool result = this->callMethod(networkManagerService, networkManagerPath, nmInterface, getDeviceMethodName, deviceList);
    return result;
}

bool DBus_Network_Manager::getNetworkDeviceWirelessAPList(QString& path, QStringList &deviceList) {
    bool result = this->callMethod(networkManagerService, path, nmDeviceWirelessInterface, getAllApListMethodName, deviceList);
    return result;
}

bool DBus_Network_Manager::getDeviceProperty(QString& path, QStringList& propertyNameList, QStringList& responseList){
    bool result = this->getProperty(networkManagerService, path, nmDeviceInterface, propertyNameList, responseList);
    return result;
}

bool DBus_Network_Manager::getDeviceProperty(QString& path, QString& propertyName, QString& response){
     bool result = this->getProperty(networkManagerService, path, nmDeviceInterface, propertyName, response);
     return result;
}

bool DBus_Network_Manager::getDeviceProperty(QString& path, QStringList& propertyNameList, int *responseList){
    bool result = this->getProperty(networkManagerService, path, nmDeviceInterface, propertyNameList, responseList);
    return result;
}

bool DBus_Network_Manager::getDeviceProperty(QString& path, QString& propertyName, int& response){
     bool result = this->getProperty(networkManagerService, path, nmDeviceInterface, propertyName, response);
     return result;
}

void DBus_Network_Manager::deviceStateChanged(unsigned int newState, unsigned int reason, unsigned int oldState) {
    qDebug() << "Device state changed :: " << newState << " :: " << oldState  << " :: " << reason;
}
void DBus_Network_Manager::deviceStateChanged(unsigned int newState) {
    qDebug() << "Device state changed :: " << newState;
}

void DBus_Network_Manager::deviceStateChanged(const QDBusObjectPath &in) {
    qDebug() << "state changed !!!! \n";
}
/******************************************************************************************
 * **************** Start of Test Function ************************************************
 * ****************************************************************************************/

void DBus_Network_Manager::networkManagerMain(void) {
    bool result;
    QStringList networkDeviceList;
    DBus_Network_Manager nmObject;
    size_t numDevices;
    size_t ethernetDeviceNumber;


    qDebug() << "\n\n\n ---- Stage 1 ------- \n\n\n";
    QDBusConnection dBusSystem = QDBusConnection::systemBus();
    // check if it is connected
    if (!dBusSystem.isConnected()) {
        qDebug() << "Cannot connect to the D-Bus session bus.";
        return;
    }
    else {
        qDebug() << "System bus is connected \n";
    }

    QStringList serviceNames = dBusSystem.interface()->registeredServiceNames();
    qDebug() << "Registered Service names: " << serviceNames;


     qDebug() << "\n\n\n ---- Stage 2 ------- \n\n\n";
    result = nmObject.getNetworkDeviceList(networkDeviceList);
    if (result == true) {
        size_t numElements = (size_t)networkDeviceList.count();
        qDebug() << "Number of Network Devices Detected: "  << numElements;
        for (size_t counter = 0; counter < numElements; counter++) {
            qDebug() << counter << ":: " << networkDeviceList.at(counter);
        }
    }
    else {
        qDebug() << networkDeviceList.at(0);
    }

    qDebug() << "\n\n\n ---- Stage 3 ------- \n\n\n";
    if (result == true) {
        QStringList propertyNameList;
        QStringList propertyResponseList;
        QString propertyName;
        QString propertyResponse;

        // Demo use of multiple property read
        // Read the Interface and IpInterface string properties

        qDebug() << "Read Multiple string properties";
        numDevices = (size_t)networkDeviceList.count();
        for (size_t counter = 0; counter < numDevices; counter++) {
            propertyNameList.clear();
            propertyNameList << "Interface";
            propertyNameList << "IpInterface";
            result = nmObject.getDeviceProperty((QString &)networkDeviceList.at(counter),
                                                propertyNameList,
                                                propertyResponseList);

            if (result == true) {
                size_t numProperties = propertyNameList.count();
                for (size_t propertyCounter = 0; propertyCounter < numProperties; propertyCounter++) {
                    qDebug() << propertyCounter << " : " << networkDeviceList.at(counter) << " :: " << propertyResponseList.at(propertyCounter);
                }
            }
            else {
                qDebug() << "ERROR :: " << propertyResponseList.at(0);
            }

        }

        qDebug() << "\n\n\n";

        // Read state and Device Type properties
        qDebug() << "Read Multiple int properties";
        propertyNameList.clear();
        propertyNameList << "DeviceType";
        propertyNameList << "State";
        int *deviceTypeResponseList = new int [propertyNameList.count()];
        numDevices = (size_t)networkDeviceList.count();
        ethernetDeviceNumber = numDevices;

        for (size_t counter = 0; counter < numDevices; counter++) {
            //nmObject.displayDebugMessage(networkDeviceList.at(counter));
            result = nmObject.getDeviceProperty((QString &)networkDeviceList.at(counter),
                                                propertyNameList,
                                                deviceTypeResponseList);
            if (result == true) {
                size_t numProperties = propertyNameList.count();
                qDebug() << "Number of properties Read: " << numProperties;
                for (size_t propertyCounter = 0; propertyCounter < numProperties; propertyCounter++) {
                    qDebug() << "Property: " << networkDeviceList.at(counter) << " :: Value: " << deviceTypeResponseList[propertyCounter];
                    if (propertyCounter == 0) {
                        if (deviceTypeResponseList[propertyCounter] == 1) {
                            ethernetDeviceNumber = counter;
                            qDebug() << "Eth device found: " <<  networkDeviceList.at(counter) << "  " << ethernetDeviceNumber;
                        }
                    }
                }

                if (ethernetDeviceNumber != numDevices) {
                    // test the dbus signal logic
                    qDebug() << "\n\n\n ---- Stage 4 ------- \n\n\n";

                    Q_ASSERT(dBusSystem.connect(networkManagerService,
                                            networkManagerPath,
                                            nmDeviceInterface, //networkDeviceList.at(counter),
                                            SIGNAL(StateChanged(unsigned int)),  //StateChanged,
                                            this,
                                            SLOT(deviceStateChanged(unsigned int))));
                }

            }
            else {
                qDebug() << "ERROR :: Reading device Property";
            }

        }


        qDebug() << "---------------------------------------------------------------------------";
        qDebug() << "\n\n\n";
    }
    else {
        qDebug() << __FILE__ << __FUNCTION__  << __LINE__ << "Fail";
    }



}

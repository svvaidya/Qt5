
#include <stdio.h>
#include <stdlib.h>
#include <iostream>

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


/******************************************************************************************
 * **************** Start of Test Function ************************************************
 * ****************************************************************************************/

void networkManagerMain(void) {
    bool result;
    QStringList networkDeviceList;
    DBus_Network_Manager nmObject;
    size_t numDevices;

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

    qDebug() << "\n\n\n";

    if (result == true) {
        QStringList propertyNameList;
        QStringList propertyResponseList;
        QString propertyName;
        QString propertyResponse;


        // Demo use of multiple property read
        // Read te Interface and IpInterface string properties

        qDebug() << "Read Multiple string properties";

        numDevices = (size_t)networkDeviceList.count();
        for (size_t counter = 0; counter < numDevices; counter++) {
            propertyNameList.clear();
            propertyNameList << "Interface";
            propertyNameList << "IpInterface";
            //nmObject.displayDebugMessage(networkDeviceList.at(counter));
            result = nmObject.getDeviceProperty((QString &)networkDeviceList.at(counter),
                                                propertyNameList,
                                                propertyResponseList);

            if (result == true) {
                size_t numProperties = propertyNameList.count();
                for (size_t propertyCounter = 0; propertyCounter < numProperties; propertyCounter++) {
                    qDebug() << propertyCounter << " : " << propertyNameList.at(propertyCounter) << " :: " << propertyResponseList.at(propertyCounter);
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

        for (size_t counter = 0; counter < numDevices; counter++) {
            //nmObject.displayDebugMessage(networkDeviceList.at(counter));
            result = nmObject.getDeviceProperty((QString &)networkDeviceList.at(counter),
                                                propertyNameList,
                                                deviceTypeResponseList);

            if (result == true) {
                size_t numProperties = propertyNameList.count();
                qDebug() << "Number of properties Read: " << numProperties;
                for (size_t propertyCounter = 0; propertyCounter < numProperties; propertyCounter++) {
                    qDebug() << "Property: " << propertyNameList.at(propertyCounter) << " :: Value: " << deviceTypeResponseList[propertyCounter];
                }
            }
            else {
                qDebug() << "ERROR :: Reading device Property";
            }

        }
        qDebug() << "---------------------------------------------------------------------------";
        qDebug() << "\n\n\n";

        // Read the Interface and IpInterface string properties one at a time
        int deviceType;
        int deviceState;
        numDevices = (size_t)networkDeviceList.count();
        for (size_t counter = 0; counter < numDevices; counter++) {
            qDebug() << "\n\n\n";
            propertyNameList.clear();
            propertyNameList << "Interface";
            propertyNameList << "IpInterface";

            size_t numProperties = propertyNameList.count();
            for (size_t propertyCounter = 0; propertyCounter < numProperties; propertyCounter++) {
                propertyName.clear();
                propertyName.append(propertyNameList.at(propertyCounter));
                result = nmObject.getDeviceProperty((QString &)networkDeviceList.at(counter),
                                                    propertyName,
                                                    propertyResponse);
                if (result == true) {
                   qDebug() << "Property Name: " << propertyName << " :: " << "Value : " << propertyResponse;
                }
                else {
                    qDebug() << "ERROR :: " << propertyName << " : " << propertyResponse;
                }

            }

            propertyName.clear();
            propertyName.append("DeviceType");
            result = nmObject.getDeviceProperty((QString &)networkDeviceList.at(counter),
                                                propertyName,
                                                deviceType);
            if (result == true) {
               qDebug() << "Property Name: " << propertyName << " :: " << "Value : " << deviceType;
            }
            else {
                qDebug() << "ERROR Response for property:: " << propertyName;
            }


            propertyName.clear();
            propertyName.append("State");
            result = nmObject.getDeviceProperty((QString &)networkDeviceList.at(counter),
                                                propertyName,
                                                deviceState);
            if (result == true) {
               qDebug() << "Property Name: " << propertyName << " :: " << "Value : " << deviceState;
            }
            else {
                qDebug() << "ERROR Response for property:: " << propertyName;
            }

            if (deviceType == NM_DEVICE_TYPE_ETHERNET ) {
                qDebug() << "Device type is ethernet";

            }
            else if (deviceType == NM_DEVICE_TYPE_WIFI) {
               qDebug() << "Device type is WiFi";

               QStringList accessPointList;
               result = nmObject.getNetworkDeviceWirelessAPList((QString &)networkDeviceList.at(counter), accessPointList);

               if (result == true) {
                   size_t numAccessPoints = (size_t)accessPointList.count();
                   qDebug() << "Number of Access Points Detected: " << numAccessPoints;
                   for (size_t apCounter = 0; apCounter < numAccessPoints; apCounter++) {
                       qDebug() << apCounter << ":: " << accessPointList.at(apCounter);
                       // read AP SSID
                   }
               }
               else {
                   qDebug() << "Failed to get Access Point List";
               }
            }
        }

    }
    else {
        qDebug() << "Location 113";
        std::cout << "fail" << std::endl;
    }


    result = nmObject.getNetworkDeviceList(networkDeviceList);
    if (result == true) {
        QString propertyName;
        int deviceType;
        numDevices = (size_t)networkDeviceList.count();
        QString signalName("StateChanged");
        for (size_t counter = 0; counter < numDevices; counter++) {
            // get the device type property
            propertyName.clear();
            propertyName.append("DeviceType");
            result = nmObject.getDeviceProperty((QString &)networkDeviceList.at(counter),
                                                propertyName,
                                                deviceType);
            if (result == true) {
               if (deviceType == NM_DEVICE_TYPE_ETHERNET) {
                   qDebug() << "Property Name: " << propertyName << " :: " << "Value : " << deviceType;
                   qDebug() << "Configuring Signal on ethernet device";

                   QDBusInterface deviceInterface(DBus_Network_Manager::networkManagerService,
                                                  (QString &)networkDeviceList.at(counter),
                                                  DBus_Network_Manager::nmDeviceInterface,
                                                  QDBusConnection::systemBus());
                   if (deviceInterface.isValid()) {
                       //QDBusConnection signalConnection =
                       if (deviceInterface.connection().connect(DBus_Network_Manager::networkManagerService,
                                                            (QString &)networkDeviceList.at(counter),
                                                            DBus_Network_Manager::nmDeviceInterface,
                                                            signalName,
                                                            &nmObject,
                                                            SLOT(DBus_Network_Manager::deviceStateChanged(unsigned int, unsigned int, unsigned int))) == true) {
                           qDebug() << "Network State handler installed correctly";
                       }
                       else {
                           qDebug() << "Network State handler failed to install";
                       }

                       qDebug() << "\n\n\n ..... Starting 30 second Delay .... \n\n";
                       QTime dieTime= QTime::currentTime().addSecs(30);
                       while (QTime::currentTime() < dieTime) {
                           QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
                      }
                   }
               }

            }
            else {
                qDebug() << "ERROR Response for property:: " << propertyName;
            }
        }
    }
    else {
        qDebug() << __FILE__ << __FUNCTION__  << __LINE__ << "Fail";
    }



}

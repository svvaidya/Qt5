#ifndef DBUSNETWORKMANAGER_H
#define DBUSNETWORKMANAGER_H

#include <QtCore/QtCore>

#include <QtCore/QString>
#include <QtCore/QList>
#include <QtCore/QStringList>

#include <dbus-manager.h>

#define NM_DEVICE_TYPE_ETHERNET  (0x01)
#define NM_DEVICE_TYPE_WIFI      (0x02)
#define NM_DEVICE_TYPE_BT        (0x05)



class DBus_Network_Manager: public QObject, public DBus_Access_Manager {
public:
    static const QString networkManagerService;

    static const QString networkManagerPath;

    static const QString nmInterface;
    static const QString nmDeviceInterface;
    static const QString nmDeviceWirelessInterface;

    static const QString getDeviceMethodName;
    static const QString getAllApListMethodName;

    bool getNetworkDeviceList(QStringList &);
    bool getNetworkDeviceWirelessAPList(QString& path, QStringList &deviceList);

    bool getDeviceProperty(QString& path, QStringList& propertyNameList, QStringList& responseList);
    bool getDeviceProperty(QString& path, QString& propertyName, QString& response);
    bool getDeviceProperty(QString& path, QStringList& propertyNameList, int *responseList);
    bool getDeviceProperty(QString& path, QString& propertyName, int& response);
    void networkManagerMain(void);

public slots:
    void deviceStateChanged(unsigned int newState, unsigned int reason, unsigned int oldState);
    void deviceStateChanged(unsigned int newState);
private slots:
    // slot for "device added"
    void deviceStateChanged(const QDBusObjectPath &in);
};

#endif // DBUSNETWORKMANAGER_H


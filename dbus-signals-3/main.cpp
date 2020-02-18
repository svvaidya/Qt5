
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

#if 0
const QString networkManagerService("org.freedesktop.NetworkManager");
const QString networkManagerPath("/org/freedesktop/NetworkManager");
const QString nmInterface("org.freedesktop.NetworkManager");
const QString nmDeviceInterface("org.freedesktop.NetworkManager.Device");
const QString nmDeviceInterfaceEth("org.freedesktop.NetworkManager.Device/0");
const QString nmDeviceWirelessInterface("org.freedesktop.NetworkManager.Device.Wireless");
#endif



class UbuntuOneDBus : public QObject
{
  QString busName;
  QString path;
  QString interface;
  QString method;
  QString signature;

  void connectReturnSignals();

private slots:
  void credentialsFound(unsigned int);
  void credentialsNotFound();
  void credentialsError();

public:
  UbuntuOneDBus();

  void init();

};

UbuntuOneDBus::UbuntuOneDBus()
{
  busName = "org.freedesktop.NetworkManager";
  path = "/org/freedesktop/NetworkManager";
  //interface = "org.freedesktop.NetworkManager.Device/0";
  interface = "org.freedesktop.NetworkManager";
  method = "register";
  signature = "a{u}";

  connectReturnSignals();
}

void UbuntuOneDBus::init()
{
  QDBusMessage message = QDBusMessage::createMethodCall( busName, path, interface, method );
  QDBusConnection::systemBus().send( message );

}

void UbuntuOneDBus::connectReturnSignals()
{
  QDBusConnection::systemBus().connect( busName, path, interface, "StateChanged", this, SLOT(credentialsFound(unsigned int)));
}

void UbuntuOneDBus::credentialsFound(unsigned int)
{
  qDebug() << "Credentials found \n";
}

void UbuntuOneDBus::credentialsNotFound()
{
 qDebug() << "Credentials not found \n";
}

void UbuntuOneDBus::credentialsError()
{
  qDebug() << "Credentials error \n";
}



int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    UbuntuOneDBus *u1Dbus = new UbuntuOneDBus;
    u1Dbus->init();

#if 0
    qDebug() << "\n\n\n ..... Starting 30 second Delay .... \n\n";
    QTime dieTime= QTime::currentTime().addSecs(30);
    while (QTime::currentTime() < dieTime) {
        QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
   }
#endif
   qDebug() << "\n\n\n ..... End 30 second Delay .... \n\n";
   a.exec();
}

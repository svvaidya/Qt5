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

#include "dbus-manager.h"
#include "dbus-network-manager.h"


#include <stdio.h>
#include <stdlib.h>
#include <iostream>

bool DBus_Access_Manager::callMethod(const QString& service,
                                      const QString& path,
                                      const QString& interface,
                                      const QString& methodName,
                                      QStringList& responseList) {
      bool returnValue = false;

      responseList.clear();

      QDBusInterface methodInterface(service, path, interface, QDBusConnection::systemBus());
      if (methodInterface.isValid()) {
          //this->displayDebugMessage();
          QDBusReply<QList<QDBusObjectPath> > result = methodInterface.call(methodName);
          if (result.isValid()) {
              returnValue = true;

              foreach (const QDBusObjectPath& responseString, result.value()) {
                  //responseList.append(responseString.path());
                  responseList << responseString.path();
              }

#if 0
              size_t numElements = (size_t)responseList.count();

              qDebug() << __FUNCTION__ << "Number of Devices Detec_ted: "  << numElements;
              for (size_t counter = 0; counter < numElements; counter++) {
                  qDebug() << counter << ":: " << responseList.at(counter);
              }
#endif
          }
          else {
              //result.error().errorString(result.m_error);
              qDebug() << "Method Call Failed";
              responseList << "Method Call Failed";
          }
      }
      else {
          qDebug() << "Interface Object Creation Failed";
          responseList << "Interface Object Creation Failed";
      }

      return returnValue;
  }


 bool DBus_Access_Manager::getProperty(const QString& service,
                                       QString& path,
                                       const QString& interface,
                                       QStringList& propertyNameList,
                                       QStringList& responseList) {
      bool returnValue = false;

      responseList.clear();
      //qDebug() << service << "  " << path << "  " << interface;  // TDO: Remove
      QDBusInterface propertyInterface(service, path, interface, QDBusConnection::systemBus());
      if (propertyInterface.isValid()) {
          responseList.clear();
          size_t numProperties = (size_t)propertyNameList.count();
          QVariant  interfaceString;
            size_t counter;
          for (counter = 0; counter < numProperties; counter++) {
              // qDebug() << propertyNameList.at(counter);
              interfaceString = propertyInterface.property(((QString *)&propertyNameList.at(counter))->toStdString().c_str());
              if (interfaceString.isValid()) {
                  responseList << interfaceString.toString();
                  returnValue = true;
                  // qDebug() << __FUNCTION__ << __LINE__ << "PropertyName: " << propertyName.at(counter) << " :: Value: " << response.at(counter);
              }
              else {
                  responseList.clear();
                  QString errorResponse("Get " + propertyNameList.at(0) + " Failed");;
                  responseList << errorResponse;
                  returnValue = false;
                  break;
              }
          }
#if 0
          if (returnValue == true) {
              size_t numResponses = (size_t)responseList.count();
              for (size_t counter = 0; counter < numResponses; counter++) {
                      qDebug() << "Property: " << propertyNameList.at(counter) << "  Response: "  << responseList.at(counter);
              }
          }
#endif

      }
      else {
          qDebug() << "Interface Object Creation Failed";
          responseList << "Interface Object Creation Failed";
      }

      return returnValue;
  }


 bool DBus_Access_Manager::getProperty(const QString& service,
                                       QString& path,
                                       const QString& interface,
                                       QString& propertyName,
                                       QString& response) {
      bool returnValue = false;

      response.clear();

      QDBusInterface propertyInterface(service, path, interface, QDBusConnection::systemBus());
      if (propertyInterface.isValid()) {
          QVariant  interfaceString = propertyInterface.property(propertyName.toStdString().c_str());
          if (interfaceString.isValid()) {
             response.append(interfaceString.toString());
             returnValue = true;
             //qDebug() << __FUNCTION__ << __LINE__ << "PropertyName: " << propertyName << " :: Value: " << response;
          }
          else {
              response.append("Failed to get property: ");
              response.append(propertyName.toStdString().c_str());
          }
      }
      else {
          qDebug() << "Interface Object Creation Failed";
          response.append("Interface Object Creation Failed");
      }

      return returnValue;
  }

 bool DBus_Access_Manager::getProperty(const QString& service,
                                       QString& path,
                                       const QString& interface,
                                       QStringList& propertyNameList,
                                       int *responseList) {
      bool returnValue = false;

       QDBusInterface propertyInterface(service, path, interface, QDBusConnection::systemBus());
      if (propertyInterface.isValid()) {
          size_t numProperties = (size_t)propertyNameList.count();
          QVariant  interfaceString;
          size_t counter;
          for (counter = 0; counter < numProperties; counter++) {
              interfaceString = propertyInterface.property(((QString *)&propertyNameList.at(counter))->toStdString().c_str());
              if (interfaceString.isValid()) {
                  responseList[counter] = interfaceString.toInt();
                  returnValue = true;
                  //qDebug() << __FUNCTION__ << __LINE__ << "Property: " << propertyNameList.at(counter) << "  Response: "  << responseList[counter];
              }
              else {
                  //responseList.clear();
                  //QString errorResponse("Get " + propertyNameList.at(0) + " Failed");;
                  //responseList << errorResponse;
                  returnValue = false;
                  break;
              }
          }
      }
      else {
          qDebug() << "Interface Object Creation Failed";
          //responseList << "Interface Object Creation Failed";
      }

      return returnValue;
  }

 bool DBus_Access_Manager::getProperty(const QString& service,
                                       QString& path,
                                       const QString& interface,
                                       QString& propertyName,
                                       int &response) {
      bool returnValue = false;

       QDBusInterface propertyInterface(service, path, interface, QDBusConnection::systemBus());
      if (propertyInterface.isValid()) {
          QVariant  interfaceString = propertyInterface.property(propertyName.toStdString().c_str());
          if (interfaceString.isValid()) {
              response = interfaceString.toInt();
              returnValue = true;
              //qDebug() << __FUNCTION__ << __LINE__ << "Property: " << propertyName << ":: Value: " << response;
          }
          else {
                  //responseList.clear();
                  //QString errorResponse("Get " + propertyNameList.at(0) + " Failed");;
                  //responseList << errorResponse;
          }
      }
      else {
          qDebug() << "Interface Object Creation Failed";
          //responseList << "Interface Object Creation Failed";
      }

      return returnValue;
  }

#ifndef RECEIVER_H
#define RECEIVER_H

#include <iostream>
#include <QObject>

class Receiver : public QObject {
    Q_OBJECT
public slots:
    void receive(unsigned int) {
        std::cout << "Received!";
    }
};

#endif // RECEIVER_H

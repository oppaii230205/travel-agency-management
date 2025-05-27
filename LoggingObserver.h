#ifndef LOGGINGOBSERVER_H
#define LOGGINGOBSERVER_H

#include "IObserver.h"
#include <QDebug>

class LoggingObserver : public IObserver {
public:
    void onEvent(const Event& event) override {
        qDebug() << "[" << event.timestamp().toString(Qt::ISODate) << "]"
                 << event.name() << "event occurred with data:" << event.data();
    }
};

#endif // LOGGINGOBSERVER_H

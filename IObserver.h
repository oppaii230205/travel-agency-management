#ifndef IOBSERVER_H
#define IOBSERVER_H

#include <memory>
#include <QSharedPointer>
#include "Event.h"

class IObserver {
public:
    virtual ~IObserver() = default;
    virtual void onEvent(const Event& event) = 0;
};

using IObserverPtr = QSharedPointer<IObserver>;

#endif // IOBSERVER_H

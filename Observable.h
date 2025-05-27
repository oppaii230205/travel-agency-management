#ifndef OBSERVABLE_H
#define OBSERVABLE_H

#include <QObject>
#include <set>
#include <memory>
#include "IObserver.h"

class Observable : public QObject {
    Q_OBJECT
public:
    void subscribe(IObserverPtr observer);
    void unsubscribe(IObserverPtr observer);
    void notify(const Event& event);

protected:
    std::set<IObserverPtr> _observers;
};

#endif // OBSERVABLE_H

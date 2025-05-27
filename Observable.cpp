#include "Observable.h"

void Observable::subscribe(IObserverPtr observer) {
    _observers.insert(observer);
}

void Observable::unsubscribe(IObserverPtr observer) {
    _observers.erase(observer);
}

void Observable::notify(const Event& event) {
    for (const auto& observer : _observers) {
        observer->onEvent(event);
    }
}

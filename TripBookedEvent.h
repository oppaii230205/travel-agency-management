#ifndef TRIPBOOKEDEVENT_H
#define TRIPBOOKEDEVENT_H

#include "Event.h"
#include <QString>

class TripBookedEvent : public Event {
public:
    TripBookedEvent(int tripId, const QString& userEmail)
        : _tripId(tripId), _userEmail(userEmail) {}

    QString name() const override { return "TripBooked"; }

    QVariantMap data() const override {
        return {
            {"tripId", _tripId},
            {"userEmail", _userEmail}
        };
    }

    int tripId() const { return _tripId; }
    QString userEmail() const { return _userEmail; }

private:
    int _tripId;
    QString _userEmail;
};

#endif // TRIPBOOKEDEVENT_H

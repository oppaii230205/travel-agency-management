#ifndef ANALYTICSOBSERVER_H
#define ANALYTICSOBSERVER_H

#include "IObserver.h"
#include "TripBookedEvent.h"
#include <QMap>

class AnalyticsObserver : public IObserver {
public:
    AnalyticsObserver() {
        _tripBookingsCount.fill(0, 5); // For rating 1-5
    }

    void onEvent(const Event& event) override {
        if (event.name() == "TripBooked") {
            const auto& tripEvent = static_cast<const TripBookedEvent&>(event);
            _userBookings[tripEvent.userEmail()]++;
        }
        else if (event.name() == "ReviewSubmitted") {
            // Similar handling for review events
        }
    }

    int bookingsForUser(const QString& email) const {
        return _userBookings.value(email, 0);
    }

private:
    QMap<QString, int> _userBookings;
    QVector<int> _tripBookingsCount;
};

#endif // ANALYTICSOBSERVER_H

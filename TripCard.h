#ifndef _TRIP_CARD_H_
#define _TRIP_CARD_H_

#include <QWidget>
#include "Trip.h"

class TripCard : public QWidget
{
    Q_OBJECT
public:
    explicit TripCard(const Trip& trip, QWidget *parent = nullptr);

    bool eventFilter(QObject *obj, QEvent *event) override;

signals:
    void bookClicked(int tripId);
    void detailsClicked(int tripId);

protected:
    int _tripId;
};

#endif

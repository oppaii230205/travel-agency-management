#include <QWidget>
#include "Trip.h"

class TripCard : public QWidget
{
    Q_OBJECT
public:
    explicit TripCard(const Trip& trip, QWidget *parent = nullptr);

signals:
    void bookClicked(int tripId);
    void detailsClicked(int tripId);

private:
    int _tripId;
};

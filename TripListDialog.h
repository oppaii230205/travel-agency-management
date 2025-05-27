#ifndef TRIPLISTDIALOG_H
#define TRIPLISTDIALOG_H

#include "BaseTripDialog.h"

namespace Ui {
class TripListDialog;
}

class TripListDialog : public BaseTripDialog
{
    Q_OBJECT

public:
    explicit TripListDialog(QSharedPointer<TripService> tripService,
                            QSharedPointer<BookingService> bookingService,
                            QSharedPointer<ReviewService> reviewService,
                            QWidget *parent = nullptr);

protected:
    // Implementation of abstract methods from BaseTripDialog
    QString getWindowTitle() const override;
    QList<Trip> getTripsToDisplay() override;
    TripCard* createTripCard(const Trip& trip) override;

    // Hook method implementation
    void onTripCardCreated(TripCard* card, const Trip& trip) override;

private slots:
    void handleBookClicked(int tripId);
};

#endif // TRIPLISTDIALOG_H

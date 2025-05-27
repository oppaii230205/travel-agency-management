#ifndef BASETRIPDIALOG_H
#define BASETRIPDIALOG_H

#include <QDialog>
#include <QScrollArea>
#include <QWidget>
#include <QGridLayout>
#include <QResizeEvent>
#include <QPropertyAnimation>

#include "TripService.h"
#include "BookingService.h"
#include "ReviewService.h"
#include "TripCard.h"

// Abstract base class implementing Template Method Pattern
class BaseTripDialog : public QDialog
{
    Q_OBJECT

public:
    explicit BaseTripDialog(QSharedPointer<TripService> tripService,
                            QSharedPointer<BookingService> bookingService,
                            QSharedPointer<ReviewService> reviewService,
                            QWidget *parent = nullptr);

    virtual ~BaseTripDialog() = default; // Virtual destructor

protected:
    // Template method - defines the algorithm structure (NOT called in constructor)
    void initializeDialog();
    void refreshTripList();

    // Abstract methods to be implemented by subclasses
    virtual QString getWindowTitle() const = 0;
    virtual QList<Trip> getTripsToDisplay() = 0;
    virtual TripCard* createTripCard(const Trip& trip) = 0;

    // Hook methods (optional override)
    virtual void onTripCardCreated(TripCard* card, const Trip& trip) {}
    virtual void setupAdditionalUI() {}

    // Common event handlers
    void resizeEvent(QResizeEvent *event) override;
    void showEvent(QShowEvent *event) override;

protected slots:
    void handleDetailsClicked(int tripId);

protected:
    QSharedPointer<TripService> _tripService;
    QSharedPointer<BookingService> _bookingService;
    QSharedPointer<ReviewService> _reviewService;
    QGridLayout* _gridLayout;
    QScrollArea* _scrollArea;
    QWidget* _contentWidget;

private:
    void initializeUI();
    void arrangeCardsInGrid();
    bool _initialized;
};

#endif // BASETRIPDIALOG_H

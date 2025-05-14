#ifndef TRIPLISTDIALOG_H
#define TRIPLISTDIALOG_H

#include <QDialog>
#include <QScrollArea>
#include <QWidget>

#include <QStandardItemModel>
#include <qitemselectionmodel.h>

#include "TripService.h"
#include "BookingService.h"

namespace Ui {
class TripListDialog;
}

class TripListDialog : public QDialog
{
    Q_OBJECT
public:
    explicit TripListDialog(QSharedPointer<TripService> tripService,
                            QSharedPointer<BookingService> bookingService,
                            QWidget *parent = nullptr);

private slots:
    void handleBookClicked(int tripId);
    void handleDetailsClicked(int tripId);

private:
    void setupCards();
    QSharedPointer<TripService> _tripService;
    QSharedPointer<BookingService> _bookingService;
    QWidget *_cardsContainer;
};

#endif // TRIPLISTDIALOG_H

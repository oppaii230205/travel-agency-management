#ifndef TRIPLISTDIALOG_H
#define TRIPLISTDIALOG_H

#include <QDialog>
#include <QScrollArea>
#include <QWidget>
#include <QGridLayout>
#include <QResizeEvent> // Thêm cho xử lý resize

#include <QStandardItemModel>
#include <qitemselectionmodel.h>

#include "TripService.h"
#include "BookingService.h"
#include "TripCard.h"

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
    void refreshTripList();
    void resizeEvent(QResizeEvent *event);

private:
    QSharedPointer<TripService> _tripService;
    QSharedPointer<BookingService> _bookingService;
    QGridLayout* _gridLayout;
};

#endif // TRIPLISTDIALOG_H

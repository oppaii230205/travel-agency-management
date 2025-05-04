#ifndef _ADDTRIPDIALOG_H_
#define _ADDTRIPDIALOG_H_

#include <QDialog>
#include "Trip.h"
#include "TripService.h"

namespace Ui {
class AddTripDialog;
}

class AddTripDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AddTripDialog(QSharedPointer<TripService> service, QWidget* parent = nullptr);
    ~AddTripDialog();

private slots:
    void on_btnSave_clicked();
    void on_btnCancel_clicked();

private:
    Ui::AddTripDialog* ui;
    QSharedPointer<TripService> _tripService;
};
#endif

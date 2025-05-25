#ifndef _ADDTRIPDIALOG_H_
#define _ADDTRIPDIALOG_H_

#include <QDialog>
#include <QSharedPointer>
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
    void setupUI(); // Thêm phương thức setup giao diện

    Ui::AddTripDialog* ui;
    QSharedPointer<TripService> _tripService;
};
#endif

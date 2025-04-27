#ifndef TRIPLISTDIALOG_H
#define TRIPLISTDIALOG_H

#include <QDialog>
#include <QStandardItemModel>
#include "TripService.h"

namespace Ui {
class TripListDialog;
}

class TripListDialog : public QDialog
{
    Q_OBJECT

public:
    explicit TripListDialog(TripService* service, QWidget* parent = nullptr);
    ~TripListDialog();

private slots:
    // void on_btnRefresh_clicked();
    // void on_btnClose_clicked();

private:
    void setupModel();
    void refreshTripList();

    Ui::TripListDialog *ui;
    TripService* _tripService;
    QStandardItemModel* _model; // Model quản lý dữ liệu
};

#endif // TRIPLISTDIALOG_H

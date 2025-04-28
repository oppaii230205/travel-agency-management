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
    void showContextMenu(const QPoint& pos);
    void deleteSelectedTrip();
    // void on_btnRefresh_clicked();
    // void on_btnClose_clicked();

private:
    void setupModel();
    void refreshTripList();
    void setupActions(); // Thêm hàm thiết lập actions

private:
    Ui::TripListDialog *ui;
    TripService* _tripService;
    QStandardItemModel* _model; // Model quản lý dữ liệu

private:
    QAction* _deleteAction; // Action xóa
};

#endif // TRIPLISTDIALOG_H

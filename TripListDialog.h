#ifndef TRIPLISTDIALOG_H
#define TRIPLISTDIALOG_H

#include <QDialog>
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
    explicit TripListDialog(QSharedPointer<TripService> tripService, QSharedPointer<BookingService> bookingService, QWidget* parent = nullptr);
    ~TripListDialog();

private slots:
    void showContextMenu(const QPoint& pos);
    // void deleteSelectedTrip();
    void on_btnBook_clicked();
    void on_btnRefresh_clicked();
    void onSelectionChanged(const QItemSelection &selected, const QItemSelection &deselected);

private:
    void setupModel();
    void refreshTripList();
    void setupActions(); // Thêm hàm thiết lập actions
    void setupUI();

private:
    Ui::TripListDialog* ui;
    QSharedPointer<TripService> _tripService;
    QSharedPointer<BookingService> _bookingService;
    QStandardItemModel* _model; // Model quản lý dữ liệu
    int _selectedTripId = -1;

private:
    // QAction* _deleteAction; // Action xóa
    QAction* _refreshAction;
};

#endif // TRIPLISTDIALOG_H

#include "TripListDialog.h"
#include "ui_TripListDialog.h"
#include <QMessageBox>
#include <QSortFilterProxyModel>
#include <QMenu>

TripListDialog::TripListDialog(QSharedPointer<TripService> service, QWidget* parent)
    : QDialog(parent),
    ui(new Ui::TripListDialog),
    _tripService(service),
    _model(new QStandardItemModel(this)) // Khởi tạo model
{
    ui->setupUi(this);

    // Thiết lập model và nạp dữ liệu
    setupModel();
    refreshTripList();
    setupActions(); // <-- Thêm dòng này

    // Kết nối context menu
    ui->tableView->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(ui->tableView, &QTableView::customContextMenuRequested,
            this, &TripListDialog::showContextMenu);

    // Kết nối button
    // connect(ui->btnRefresh, &QPushButton::clicked,
    //         this, &TripListDialog::on_btnRefresh_clicked);
    // connect(ui->btnClose, &QPushButton::clicked,
    //         this, &TripListDialog::on_btnClose_clicked);
}

void TripListDialog::setupModel()
{
    // Cấu hình model
    _model->setColumnCount(4);
    _model->setHorizontalHeaderLabels({"ID", "Tên chuyến đi", "Giá", "Độ khó"});

    // Kết nối model với view
    ui->tableView->setModel(_model);
    // QSortFilterProxyModel* proxyModel = new QSortFilterProxyModel(this);
    // proxyModel->setSourceModel(_model);
    // ui->tableView->setModel(proxyModel);

    // Thiết lập hiển thị
    ui->tableView->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableView->horizontalHeader()->setStretchLastSection(true);

    // Highlight dòng được chọn
    ui->tableView->setStyleSheet(
        "QTableView { selection-background-color: #FFCCCB; }"
        );
}

void TripListDialog::refreshTripList()
{
    // Xóa dữ liệu cũ
    _model->removeRows(0, _model->rowCount());

    // Lấy dữ liệu từ service
    QList<Trip> trips = _tripService->getAllTrips();

    // Thêm dữ liệu vào model
    for (const Trip& trip : trips) {
        QList<QStandardItem*> rowItems;
        rowItems << new QStandardItem(QString::number(trip.getTripId()));
        rowItems << new QStandardItem(trip.getTripName());
        rowItems << new QStandardItem(QString::number(trip.getPrice()));
        rowItems << new QStandardItem(trip.getDifficulty());

        _model->appendRow(rowItems);
    }

    // Optional: Auto-resize columns
    ui->tableView->resizeColumnsToContents();
}

void TripListDialog::setupActions()
{
    _deleteAction = new QAction("Xóa chuyến đi", this);
    connect(_deleteAction, &QAction::triggered,
            this, &TripListDialog::deleteSelectedTrip);
    _deleteAction->setShortcut(QKeySequence::Delete);
    ui->tableView->addAction(_deleteAction); // Cho phép dùng phím Delete
}

void TripListDialog::showContextMenu(const QPoint& pos)
{
    QMenu contextMenu(this);
    contextMenu.addAction(_deleteAction);
    contextMenu.exec(ui->tableView->viewport()->mapToGlobal(pos));
}

void TripListDialog::deleteSelectedTrip()
{
    QModelIndexList selected = ui->tableView->selectionModel()->selectedRows();
    if (selected.isEmpty()) {
        QMessageBox::warning(this, "Cảnh báo", "Vui lòng chọn chuyến đi cần xóa");
        return;
    }

    int row = selected.first().row();
    int tripId = _model->item(row, 0)->text().toInt(); // Lấy ID từ cột 0

    if (QMessageBox::question(this, "Xác nhận",
                              "Bạn có chắc muốn xóa chuyến đi này?",
                              QMessageBox::Yes | QMessageBox::No) == QMessageBox::Yes)
    {
        if (_tripService->deleteTrip(tripId)) {
            refreshTripList(); // Cập nhật lại danh sách
            QMessageBox::information(this, "Thành công", "Đã xóa chuyến đi");
        } else {
            QMessageBox::critical(this, "Lỗi", "Xóa thất bại");
        }
    }
}

// void TripListDialog::on_btnRefresh_clicked()
// {
//     refreshTripList();
// }

// void TripListDialog::on_btnClose_clicked()
// {
//     this->accept();
// }

TripListDialog::~TripListDialog()
{
    delete ui;
}

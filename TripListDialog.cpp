#include "TripListDialog.h"
#include "ui_TripListDialog.h"
#include <QMessageBox>
#include <QSortFilterProxyModel>
#include <QMenu>

TripListDialog::TripListDialog(QSharedPointer<TripService> tripService, QSharedPointer<BookingService> bookingService, QWidget* parent)
    : QDialog(parent),
    ui(new Ui::TripListDialog),
    _tripService(tripService),
    _bookingService(bookingService),
    _model(new QStandardItemModel(this)) // Khởi tạo model
{
    ui->setupUi(this);

    // Thiết lập model và nạp dữ liệu
    setupModel();
    setupUI();
    setupActions(); // <-- Thêm dòng này
    refreshTripList();

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

void TripListDialog::setupUI()
{
    // Kết nối các nút
    connect(ui->btnBook, &QPushButton::clicked, this, &TripListDialog::on_btnBook_clicked);
    connect(ui->btnRefresh, &QPushButton::clicked, this, &TripListDialog::on_btnRefresh_clicked);

    // Kết nối sự kiện chọn hàng
    connect(ui->tableView->selectionModel(), SIGNAL(selectionChanged(QItemSelection,QItemSelection)),
            this, SLOT(onSelectionChanged(QItemSelection,QItemSelection)));

    // Ban đầu vô hiệu hóa nút Book khi chưa chọn chuyến đi
    ui->btnBook->setEnabled(false);
    _selectedTripId = -1; // Khởi tạo giá trị ban đầu
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
    _refreshAction = new QAction("Refresh", this);
    connect(_refreshAction, &QAction::triggered, this, &TripListDialog::refreshTripList);
    ui->tableView->addAction(_refreshAction);

    /*
    _deleteAction = new QAction("Xóa chuyến đi", this);
    connect(_deleteAction, &QAction::triggered,
            this, &TripListDialog::deleteSelectedTrip);
    _deleteAction->setShortcut(QKeySequence::Delete);
    ui->tableView->addAction(_deleteAction); // Cho phép dùng phím Delete
    */
}

void TripListDialog::showContextMenu(const QPoint& pos)
{
    QMenu contextMenu(this);
    contextMenu.addAction(_refreshAction);
    // contextMenu.addAction(_deleteAction);
    contextMenu.exec(ui->tableView->viewport()->mapToGlobal(pos));
}

/*
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
*/

void TripListDialog::onSelectionChanged(const QItemSelection &selected, const QItemSelection &deselected)
{
    Q_UNUSED(deselected);

    // Thêm debug để kiểm tra
    qDebug() << "Selection changed, selected count:" << selected.count();

    if (selected.isEmpty()) {
         qDebug() << "No selection";
        _selectedTripId = -1;
        ui->btnBook->setEnabled(false);
    } else {
        int row = selected.indexes().first().row();
        _selectedTripId = _model->item(row, 0)->text().toInt();
        qDebug() << "Selected trip ID:" << _selectedTripId;

        ui->btnBook->setEnabled(true);

        // Kiểm tra nếu user đã đặt chuyến này thì đổi text nút
        if (_bookingService->hasUserBooked(_selectedTripId)) {
            ui->btnBook->setText("Cancel this");
        } else {
            ui->btnBook->setText("Book now");
        }
    }
}

void TripListDialog::on_btnBook_clicked()
{
    // Kiểm tra nếu không có chuyến nào được chọn thì không làm gì cả
    if (_selectedTripId == -1) {
        return; // Đã bỏ QMessageBox để tránh gọi nhiều lần
    }

    if (_bookingService->hasUserBooked(_selectedTripId)) {
        // Hủy đặt chỗ
        if (_bookingService->cancelBooking(_selectedTripId)) {
            QMessageBox::information(this, "Thành công", "Đã hủy đặt chỗ thành công");
            ui->btnBook->setText("Book now");
        } else {
            QMessageBox::critical(this, "Lỗi", "Hủy đặt chỗ thất bại");
        }
    } else {
        // Đặt chỗ mới
        if (_bookingService->bookTrip(_selectedTripId)) {
            QMessageBox::information(this, "Thành công", "Đặt chỗ thành công!");
            ui->btnBook->setText("Cancel this");
        } else {
            QMessageBox::critical(this, "Lỗi", "Đặt chỗ thất bại");
        }
    }

    refreshTripList();
}

void TripListDialog::on_btnRefresh_clicked()
{
    refreshTripList();
}

TripListDialog::~TripListDialog()
{
    delete ui;
}

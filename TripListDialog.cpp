#include "TripListDialog.h"
#include "ui_TripListDialog.h"
#include <QMessageBox>

TripListDialog::TripListDialog(TripService* service, QWidget* parent)
    : QDialog(parent),
    ui(new Ui::TripListDialog),
    _tripService(service),
    _model(new QStandardItemModel(this)) // Khởi tạo model
{
    ui->setupUi(this);

    // Thiết lập model và nạp dữ liệu
    setupModel();
    refreshTripList();

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

    // Thiết lập hiển thị
    ui->tableView->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableView->horizontalHeader()->setStretchLastSection(true);
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

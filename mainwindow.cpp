#include "MainWindow.h"
#include "ui_MainWindow.h"
#include <QMessageBox>
#include <QTableWidgetItem>

MainWindow::MainWindow(TripService* tripService, QWidget* parent)
    : QMainWindow(parent), ui(new Ui::MainWindow), _tripService(tripService)
{
    ui->setupUi(this);
    setupTableWidget();
    
    // Kết nối signal-slot
    connect(_tripService, &TripService::tripAdded,
            this, &MainWindow::onTripAdded);
    connect(_tripService, &TripService::errorOccurred,
            this, &MainWindow::onErrorOccurred);
            
    refreshTripList();
}

void MainWindow::setupTableWidget()
{
    ui->tableTrips->setColumnCount(5);
    ui->tableTrips->setHorizontalHeaderLabels(
        {"ID", "Tên chuyến đi", "Độ khó", "Giá", "Số ngày"});
    ui->tableTrips->horizontalHeader()->setStretchLastSection(true);
}

void MainWindow::refreshTripList()
{
    ui->tableTrips->setRowCount(0);
    QList<Trip> trips = _tripService->getAllTrips();
    
    for (const Trip& trip : trips) {
        int row = ui->tableTrips->rowCount();
        ui->tableTrips->insertRow(row);
        
        ui->tableTrips->setItem(row, 0, new QTableWidgetItem(QString::number(trip.getTripId())));
        ui->tableTrips->setItem(row, 1, new QTableWidgetItem(trip.getTripName()));
        ui->tableTrips->setItem(row, 2, new QTableWidgetItem(trip.getDifficulty()));
        ui->tableTrips->setItem(row, 3, new QTableWidgetItem(QString::number(trip.getPrice())));
        ui->tableTrips->setItem(row, 4, new QTableWidgetItem(QString::number(trip.getDuration())));
    }
}

void MainWindow::on_btnAddTrip_clicked()
{
    // Lấy dữ liệu từ UI (giả sử đã có các QLineEdit, QComboBox...)
    QString name = ui->txtName->text();
    QString difficulty = ui->comboDifficulty->currentText();
    int price = ui->spinPrice->value();
    int duration = ui->spinDuration->value();
    
    Trip newTrip(0, name, duration, 0, difficulty, price, "", "");
    
    _tripService->createTrip(newTrip); // Business Layer xử lý
}

void MainWindow::onTripAdded(const Trip& newTrip)
{
    refreshTripList();
    QMessageBox::information(this, "Thành công", "Đã thêm chuyến đi mới!");
}

void MainWindow::onErrorOccurred(const QString& message)
{
    QMessageBox::critical(this, "Lỗi", message);
}
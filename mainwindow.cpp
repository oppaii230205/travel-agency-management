#include "MainWindow.h"
#include "ui_MainWindow.h"
#include "AddTripDialog.h"
#include <QMessageBox>
#include <QTableWidgetItem>
#include <iostream>

MainWindow::MainWindow(TripService* tripService, QWidget* parent)
    : QMainWindow(parent), ui(new Ui::MainWindow), _tripService(tripService)
{
    ui->setupUi(this);
    // setupTableWidget();
    
    // Kết nối signal-slot
    connect(_tripService, &TripService::tripAdded,
            this, &MainWindow::onTripAdded);
    connect(_tripService, &TripService::errorOccurred,
            this, &MainWindow::onErrorOccurred);
            
    // refreshTripList();
}

MainWindow::~MainWindow()
{
    delete ui; // Quan trọng: Giải phóng bộ nhớ của UI
    // Giải phóng các tài nguyên khác nếu có
}

/*
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
*/

void MainWindow::on_btnAddTrip_clicked()
{
    std::cout << "Add Trip Clicked\n";
    AddTripDialog dialog(_tripService, this);
    dialog.exec(); // Hiển thị dialog dạng modal
}

void MainWindow::onTripAdded(const Trip& newTrip)
{
    // refreshTripList();
    QMessageBox::information(this, "Thành công", "Đã thêm chuyến đi mới!");
}

void MainWindow::onErrorOccurred(const QString& message)
{
    QMessageBox::critical(this, "Lỗi", message);
}

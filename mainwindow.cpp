#include "MainWindow.h"
#include "ui_MainWindow.h"

#include "AddTripDialog.h"
#include "TripListDialog.h"
#include "ShowUserInformationDialog.h"

#include <QMessageBox>
#include <QTableWidgetItem>

MainWindow::MainWindow(QSharedPointer<UserService> userService, QSharedPointer<AuthService> authService, QSharedPointer<TripService> tripService, QWidget* parent)
    : QMainWindow(parent), ui(new Ui::MainWindow), _userService(userService), _authService(authService), _tripService(tripService)
{
    ui->setupUi(this);
    updateUI();
    
    // Kết nối signal-slot
    connect(_tripService.data(), &TripService::tripAdded,
            this, &MainWindow::onTripAdded);
    connect(_tripService.data(), &TripService::errorOccurred,
            this, &MainWindow::onErrorOccurred);
            
    // refreshTripList();
}

MainWindow::~MainWindow()
{
    delete ui; // Quan trọng: Giải phóng bộ nhớ của UI
    // Giải phóng các tài nguyên khác nếu có
}

void MainWindow::updateUI() {
    QSharedPointer<User> currentUser = _authService->getCurrentUser();
    // Cập nhật UI ngay lần đầu
    if (auto user = _authService->getCurrentUser()) {
        ui->labelWelcome->setText("Xin chào, " + user->name());
        ui->btnAddTrip->setVisible(_authService->hasPermission("admin")); // Ẩn nút nếu không phải admin
    } else {
        qWarning() << "No user logged in!"; // Debug nếu cần
    }
}


void MainWindow::on_btnAddTrip_clicked()
{
    AddTripDialog dialog(_tripService, this);
    dialog.exec(); // Hiển thị dialog dạng modal
}

void MainWindow::on_btnShowTrips_clicked() {
    TripListDialog dialog(_tripService, this);
    dialog.exec(); // Hiển thị dialog dạng modal    
}


void MainWindow::on_btnShowUserInfomation_clicked()
{

    QString currentUserEmail = _authService->getCurrentUser()->email(); // Cần implement hàm này


    ShowUserInformationDialog Dialog(_userService, currentUserEmail, this);
    Dialog.exec();
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


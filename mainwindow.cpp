#include "MainWindow.h"
#include "ui_MainWindow.h"

#include "AddTripDialog.h"
#include "TripListDialog.h"
#include "ShowUserInformationDialog.h"

#include <QMessageBox>
#include <QTableWidgetItem>

#include "CustomMessageBox.h"

MainWindow::MainWindow(QSharedPointer<UserService> userService, QSharedPointer<AuthService> authService, QSharedPointer<TripService> tripService, QSharedPointer<BookingService> bookingService, QSharedPointer<AzureStorageService> storageService,QSharedPointer<ReviewService> reviewService,  QWidget* parent)
    : QMainWindow(parent), ui(new Ui::MainWindow), _userService(userService), _authService(authService), _tripService(tripService), _bookingService(bookingService), _storageService(storageService), _reviewService(reviewService)
{
    ui->setupUi(this);
    
    // Kết nối signal-slot
    connect(_tripService.data(), &TripService::tripAdded,
            this, &MainWindow::onTripAdded);
    connect(_tripService.data(), &TripService::errorOccurred,
            this, &MainWindow::onErrorOccurred);
    connect(ui->btnLogOut, &QPushButton::clicked, this, &MainWindow::handleLogoutRequest);

    connect(_authService.data(), &AuthService::logoutPerformed, this, &MainWindow::handleLogout);
    // refreshTripList();
    updateUI();
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
        ui->labelWelcome->setText("Hello, " + user->name());
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
    TripListDialog dialog(_tripService, _bookingService, _reviewService, this);
    dialog.exec(); // Hiển thị dialog dạng modal    
}


void MainWindow::on_btnShowUserInfomation_clicked()
{

    QString currentUserEmail = _authService->getCurrentUser()->email(); // Cần implement hàm này


    ShowUserInformationDialog Dialog(_userService, _storageService, currentUserEmail, this);
    Dialog.exec();
}


void MainWindow::onTripAdded(const Trip& newTrip)
{
    // refreshTripList();
   CustomMessageBox::show("Thành công", "Đã thêm chuyến đi mới!");
}

void MainWindow::onErrorOccurred(const QString& message)
{
   CustomMessageBox::show("Lỗi", message);
}

void MainWindow::handleLogoutRequest()
{
    QMessageBox::StandardButton reply;
    reply = CustomMessageBox::question(
        "Xác nhận",
        "Bạn có chắc muốn đăng xuất?",this,
        QMessageBox::Yes | QMessageBox::No
        );
    if (reply == QMessageBox::Yes) {
        _authService->logout();
    }
}


void MainWindow::handleLogout()
{
    this->hide();
    emit logoutCompleted();
}




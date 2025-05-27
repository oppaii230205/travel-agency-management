#include "MainWindow.h"
#include "ui_MainWindow.h"

#include "AddTripDialog.h"
#include "TripListDialog.h"
#include "BookedTripsDialog.h"
#include "ShowUserInformationDialog.h"

#include <QMessageBox>
#include <QTableWidgetItem>
#include <QPropertyAnimation>
#include <QScreen>
#include <QGuiApplication>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QSpacerItem>
#include <QIcon>
#include <QMouseEvent>

#include "CustomMessageBox.h"

MainWindow::MainWindow(QSharedPointer<UserService> userService,
                       QSharedPointer<AuthService> authService,
                       QSharedPointer<TripService> tripService,
                       QSharedPointer<BookingService> bookingService,
                       QSharedPointer<AzureStorageService> storageService,
                       QSharedPointer<ReviewService> reviewService,
                       QWidget* parent)
    : QMainWindow(parent),
    ui(new Ui::MainWindow),
    _userService(userService),
    _authService(authService),
    _tripService(tripService),
    _bookingService(bookingService),
    _storageService(storageService),
    _reviewService(reviewService)
{
    ui->setupUi(this);

    // Kết nối signal-slot
    connect(_tripService.data(), &TripService::tripAdded, this, &MainWindow::onTripAdded);
    connect(_tripService.data(), &TripService::errorOccurred, this, &MainWindow::onErrorOccurred);
    connect(ui->btnLogOut, &QPushButton::clicked, this, &MainWindow::handleLogoutRequest);
    connect(_authService.data(), &AuthService::logoutPerformed, this, &MainWindow::handleLogout);

    setupUI(); // Thiết lập giao diện
    updateUI(); // Cập nhật thông tin người dùng
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setupUI()
{
    // Thiết lập kích thước cửa sổ
    QScreen *screen = QGuiApplication::primaryScreen();
    QRect screenGeometry = screen->geometry();
    int width = qMin(800, static_cast<int>(screenGeometry.width() * 0.7));
    int height = qMin(600, static_cast<int>(screenGeometry.height() * 0.7));
    resize(width, height);

    // Thiết lập style sheet
    this->setStyleSheet(R"(
    QMainWindow {
        background: qlineargradient(x1:0, y1:0, x2:1, y2:1,
                                  stop:0 #0077be, stop:1 #00a8e8); /* Gradient màu biển */
        font-family: 'Segoe UI', Arial, sans-serif;
    }

    QLabel#labelWelcome {
        font-size: 30px;
        color: #ffff00;
        font-weight: 800;
        padding: 10px;
        letter-spacing: 1px;
    }

    QFrame {  /* Style cho đường kẻ ngang */
        color: white;
        background-color: white;
    }

    QPushButton#btnLogOut {
        background-color: #e74c3c;
        color: white;
        border-radius: 5px;
        padding: 8px 15px;
        font-size: 14px;
        border: 1px solid white;  /* Viền trắng */
    }

    QPushButton#btnLogOut:hover {
        background-color: #c0392b;
    }

    QPushButton#btnAddTrip {
        background-color: #2ecc71;  /* Xanh lá cây */
        color: white;
        border-radius: 5px;
        padding: 10px 20px;
        font-size: 16px;
        min-width: 150px;
        border: 1px solid white;  /* Viền trắng */
    }

    QPushButton#btnAddTrip:hover {
        background-color: #27ae60;  /* Xanh lá cây đậm hơn khi hover */
    }

    .ClickableLabel, .ImageButton {
        border: 2px solid white;  /* Viền trắng */
        border-radius: 10px;
        padding: 5px;
        background-color: rgba(255, 255, 255, 0.9);  /* Nền trắng với độ trong suốt */
        qproperty-alignment: 'AlignCenter';
    }

    .ClickableLabel:hover, .ImageButton:hover {
        border-color: #f1c40f;  /* Viền vàng khi hover */
        background-color: white;
        cursor: pointer;
    }

    QLabel {
        background: transparent;
        color: #2c3e50;  /* Màu chữ tối cho dễ đọc */
    }
)");
    // Tạo layout chính
    QWidget *centralWidget = new QWidget(this);
    QVBoxLayout *mainLayout = new QVBoxLayout(centralWidget);
    mainLayout->setContentsMargins(20, 20, 20, 20);
    mainLayout->setSpacing(20);

    // Header (nút Add Trip và nút đăng xuất)
    QHBoxLayout *headerLayout = new QHBoxLayout();

    // Thêm nút Add Trip vào vị trí tiêu đề
    ui->btnAddTrip->setObjectName("btnAddTrip");
    headerLayout->addWidget(ui->btnAddTrip);

    headerLayout->addStretch();

    ui->labelWelcome->setStyleSheet("font-size: 16px; color: #7f8c8d;");
    headerLayout->addWidget(ui->labelWelcome);

    ui->btnLogOut->setObjectName("btnLogOut");
    headerLayout->addWidget(ui->btnLogOut);

    mainLayout->addLayout(headerLayout);

    // Thêm đường kẻ ngang phân cách
    QFrame *line = new QFrame();
    line->setFrameShape(QFrame::HLine);
    line->setFrameShadow(QFrame::Sunken);
    line->setStyleSheet("color: #bdc3c7;");
    mainLayout->addWidget(line);

    // Thêm khoảng trống
    mainLayout->addSpacing(30);

    // Các label chức năng chính (clickable)
    QHBoxLayout *labelLayout = new QHBoxLayout();
    labelLayout->setSpacing(30);
    labelLayout->setAlignment(Qt::AlignCenter); // Căn giữa các nút

    // Label Show Trips - Thiết kế giống code cũ nhưng dùng QLabel
    ui->labelShowTrips->setProperty("class", "ImageButton");
    ui->labelShowTrips->setFixedSize(200, 200);

    // Tạo layout con cho hình ảnh và text
    QVBoxLayout *tripLayout = new QVBoxLayout(ui->labelShowTrips);
    tripLayout->setContentsMargins(0, 0, 0, 0);
    tripLayout->setSpacing(0);

    ui->labelShowTrips->setProperty("class", "ImageButton");
    ui->labelShowTrips->setFixedSize(200, 200);
    ui->labelShowTrips->setAlignment(Qt::AlignCenter);
    ui->labelShowTrips->setPixmap(QPixmap(":/images/ShowTrips.png").scaled(
    ui->labelShowTrips->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
    ui->labelShowTrips->setToolTip("Xem danh sách các chuyến đi");
    ui->labelShowTrips->setMouseTracking(true);
    ui->labelShowTrips->installEventFilter(this);

    // Label My Bookings
    ui->labelMyBookings->setProperty("class", "ImageButton");
    ui->labelMyBookings->setFixedSize(200, 200);

    // Tạo layout con cho hình ảnh và text
    QVBoxLayout *bookingLayout = new QVBoxLayout(ui->labelMyBookings);
    bookingLayout->setContentsMargins(0, 0, 0, 0);
    bookingLayout->setSpacing(0);

    ui->labelMyBookings->setProperty("class", "ImageButton");
    ui->labelMyBookings->setFixedSize(200, 200);
    ui->labelMyBookings->setAlignment(Qt::AlignCenter);
    ui->labelMyBookings->setPixmap(QPixmap(":/images/default-trip.jpg").scaled(
    ui->labelMyBookings->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
    ui->labelMyBookings->setToolTip("Xem danh sách các chuyến đi đã đặt");
    ui->labelMyBookings->setMouseTracking(true);
    ui->labelMyBookings->installEventFilter(this);


    // Label Show User Information
    ui->labelShowUserInfo->setProperty("class", "ImageButton");
    ui->labelShowUserInfo->setFixedSize(200, 200);
    ui->labelShowUserInfo->setAlignment(Qt::AlignCenter);
    ui->labelShowUserInfo->setPixmap(QPixmap(":/images/UserInfo.png").scaled(
    ui->labelShowUserInfo->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
    ui->labelShowUserInfo->setToolTip("Xem thông tin người dùng");
    ui->labelShowUserInfo->setMouseTracking(true);
    ui->labelShowUserInfo->installEventFilter(this);

    labelLayout->addWidget(ui->labelShowTrips);
    labelLayout->addWidget(ui->labelMyBookings);
    labelLayout->addWidget(ui->labelShowUserInfo);

    mainLayout->addLayout(labelLayout, 1);
    mainLayout->addStretch();



    setCentralWidget(centralWidget);

    // Hiệu ứng fade in khi mở cửa sổ
    QPropertyAnimation *animation = new QPropertyAnimation(this, "windowOpacity");
    animation->setDuration(300);
    animation->setStartValue(0);
    animation->setEndValue(1);
    animation->start();
}

bool MainWindow::eventFilter(QObject *obj, QEvent *event)
{
    if (event->type() == QEvent::MouseButtonPress) {
        QMouseEvent *mouseEvent = static_cast<QMouseEvent*>(event);
        if (mouseEvent->button() == Qt::LeftButton) {
            if (obj == ui->labelShowTrips) {
                onLabelShowTripsClicked();
                return true;
            } else if (obj == ui->labelShowUserInfo) {
                onLabelShowUserInfoClicked();
                return true;
            }
        }
    }
    return QMainWindow::eventFilter(obj, event);
}

void MainWindow::onLabelShowTripsClicked()
{
    qDebug() << "Label ShowTrips clicked";
    TripListDialog dialog(_tripService, _bookingService, _reviewService, this);
    dialog.exec();
}

void MainWindow::onLabelMyBookingsClicked()
{
    qDebug() << "Label MyBookings clicked";
    BookedTripsDialog dialog(_tripService, _bookingService, _reviewService, this);
    dialog.exec();
}

void MainWindow::onLabelShowUserInfoClicked()
{
    QString currentUserEmail = _authService->getCurrentUser()->email();
    ShowUserInformationDialog Dialog(_userService, _storageService, currentUserEmail, this);
    Dialog.exec();
}
void MainWindow::updateUI() {
    QSharedPointer<User> currentUser = _authService->getCurrentUser();
    if (currentUser) {
        ui->labelWelcome->setText("Xin chào, " + currentUser->name());
        ui->btnAddTrip->setVisible(_authService->hasPermission("admin"));
    } else {
        qWarning() << "No user logged in!";
    }
}

void MainWindow::on_btnAddTrip_clicked()
{
    AddTripDialog dialog(_tripService, this);
    dialog.exec(); // Hiển thị dialog dạng modal
}

// void MainWindow::on_btnShowTrips_clicked() {
//     TripListDialog dialog(_tripService, _bookingService, _reviewService, this);
//     dialog.exec(); // Hiển thị dialog dạng modal
// }


// void MainWindow::on_btnShowUserInfomation_clicked()
// {

//     QString currentUserEmail = _authService->getCurrentUser()->email(); // Cần implement hàm này


//     ShowUserInformationDialog Dialog(_userService, _storageService, currentUserEmail, this);
//     Dialog.exec();
// }


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




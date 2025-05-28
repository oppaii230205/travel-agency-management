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
    connect(_authService.data(), &AuthService::logoutPerformed, this, &MainWindow::handleLogout);
    connect(ui->labelAddTrip, &QLabel::linkActivated, this, &MainWindow::onLabelAddTripClicked);
    connect(ui->labelLogOut, &QLabel::linkActivated, this, &MainWindow::onLabelLogOutClicked);

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

    // Thiết lập stylesheet
    this->setStyleSheet(R"(
        QLabel:not(#tripCard QLabel) {
            background: transparent;
            color: #2c3e50;
        }
        QWidget#centralWidget {
            background: white;
        }

        QLabel#labelWelcome {
            font-size: 16px;
            color: #7f8c8d;
            font-weight: 600;
            padding: 10px;
        }

        QFrame {
            color: white;
            background-color: white;
        }

        .ImageButton {
            border: 2px solid #3498db;
            border-radius: 10px;
            padding: 5px;
            background-color: rgba(255, 255, 255, 0.9);
            qproperty-alignment: 'AlignCenter';
        }

        .ImageButton:hover {
            border-color: #2980b9;
            background-color: white;
            cursor: pointer;
        }

        .SmallButton {
            border: 2px solid #2ecc71;
            border-radius: 8px;
            padding: 3px;
            background-color: rgba(255, 255, 255, 0.9);
        }

        .SmallButton:hover {
            border-color: #27ae60;
            background-color: rgba(46, 204, 113, 0.1);
        }

        .LogoutButton {
            border: 2px solid #e74c3c;
            border-radius: 8px;
            padding: 3px;
            background-color: rgba(255, 255, 255, 0.9);
        }

        .LogoutButton:hover {
            border-color: #c0392b;
            background-color: rgba(231, 76, 60, 0.1);
        }
    )");

    // Tạo layout chính
    QWidget *centralWidget = new QWidget(this);
    QVBoxLayout *mainLayout = new QVBoxLayout(centralWidget);
    mainLayout->setContentsMargins(20, 20, 20, 20);
    mainLayout->setSpacing(20);

    // Header layout (top section)
    QHBoxLayout *headerLayout = new QHBoxLayout();

    // Add Trip button (small, top-left)
    ui->labelAddTrip->setProperty("class", "SmallButton");
    ui->labelAddTrip->setFixedSize(60, 60);
    ui->labelAddTrip->setAlignment(Qt::AlignCenter);
    ui->labelAddTrip->setPixmap(QPixmap(":/images/AddTrip.png").scaled(
        40, 40, Qt::KeepAspectRatio, Qt::SmoothTransformation));
    ui->labelAddTrip->setToolTip("Thêm chuyến đi mới");
    ui->labelAddTrip->setMouseTracking(true);
    ui->labelAddTrip->installEventFilter(this);
    headerLayout->addWidget(ui->labelAddTrip);

    // Spacer to push welcome message and logout button to right
    headerLayout->addStretch();

    // Welcome message
    ui->labelWelcome->setStyleSheet("font-size: 16px; color: #7f8c8d;");
    headerLayout->addWidget(ui->labelWelcome);

    // Logout button (small, top-right, same size as AddTrip)
    ui->labelLogOut->setProperty("class", "LogoutButton");
    ui->labelLogOut->setFixedSize(60, 60);
    ui->labelLogOut->setAlignment(Qt::AlignCenter);
    ui->labelLogOut->setPixmap(QPixmap(":/images/LogOut.jpg").scaled(
        40, 40, Qt::KeepAspectRatio, Qt::SmoothTransformation));
    ui->labelLogOut->setToolTip("Đăng xuất");
    ui->labelLogOut->setMouseTracking(true);
    ui->labelLogOut->installEventFilter(this);
    headerLayout->addWidget(ui->labelLogOut);

    mainLayout->addLayout(headerLayout);

    // Horizontal line separator
    QFrame *line = new QFrame();
    line->setFrameShape(QFrame::HLine);
    line->setFrameShadow(QFrame::Sunken);
    line->setStyleSheet("color: #bdc3c7;");
    mainLayout->addWidget(line);

    // Main buttons layout (centered)
    QHBoxLayout *buttonLayout = new QHBoxLayout();
    buttonLayout->setSpacing(10);  // Giảm khoảng cách từ 20px xuống 10px
    buttonLayout->setAlignment(Qt::AlignCenter);

    // Show Trips button - tăng kích thước lên 300x300
    ui->labelShowTrips->setProperty("class", "ImageButton");
    ui->labelShowTrips->setFixedSize(300, 300);  // Tăng từ 250 lên 300
    ui->labelShowTrips->setAlignment(Qt::AlignCenter);
    ui->labelShowTrips->setPixmap(QPixmap(":/images/ShowTrips.png").scaled(
        220, 220, Qt::KeepAspectRatio, Qt::SmoothTransformation));  // Tăng kích thước ảnh
    ui->labelShowTrips->setToolTip("Xem danh sách các chuyến đi");
    ui->labelShowTrips->setMouseTracking(true);
    ui->labelShowTrips->installEventFilter(this);

    // My Bookings button - tăng kích thước lên 300x300
    ui->labelMyBookings->setProperty("class", "ImageButton");
    ui->labelMyBookings->setFixedSize(300, 300);  // Tăng từ 250 lên 300
    ui->labelMyBookings->setAlignment(Qt::AlignCenter);
    ui->labelMyBookings->setPixmap(QPixmap(":/images/default-trip.jpg").scaled(
        220, 220, Qt::KeepAspectRatio, Qt::SmoothTransformation));  // Tăng kích thước ảnh
    ui->labelMyBookings->setToolTip("Xem danh sách các chuyến đi đã đặt");
    ui->labelMyBookings->setMouseTracking(true);
    ui->labelMyBookings->installEventFilter(this);

    // User Info button - tăng kích thước lên 300x300
    ui->labelShowUserInfo->setProperty("class", "ImageButton");
    ui->labelShowUserInfo->setFixedSize(300, 300);  // Tăng từ 250 lên 300
    ui->labelShowUserInfo->setAlignment(Qt::AlignCenter);
    ui->labelShowUserInfo->setPixmap(QPixmap(":/images/UserInfo.png").scaled(
        220, 220, Qt::KeepAspectRatio, Qt::SmoothTransformation));  // Tăng kích thước ảnh
    ui->labelShowUserInfo->setToolTip("Xem thông tin người dùng");
    ui->labelShowUserInfo->setMouseTracking(true);
    ui->labelShowUserInfo->installEventFilter(this);

    // Add buttons to layout (chỉ còn 3 nút)
    buttonLayout->addWidget(ui->labelShowTrips);
    buttonLayout->addWidget(ui->labelMyBookings);
    buttonLayout->addWidget(ui->labelShowUserInfo);

    // Add button layout to main layout with stretch to center vertically
    mainLayout->addStretch();
    mainLayout->addLayout(buttonLayout);
    mainLayout->addStretch();

    setCentralWidget(centralWidget);

    // Fade-in animation
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
            } else if (obj == ui->labelMyBookings) {
                onLabelMyBookingsClicked();
                return true;
            } else if (obj == ui->labelShowUserInfo) {
                onLabelShowUserInfoClicked();
                return true;
            } else if (obj == ui->labelAddTrip) {
                onLabelAddTripClicked();
                return true;
            } else if (obj == ui->labelLogOut) {
                onLabelLogOutClicked();
                return true;
            }
        }
    }
    return QMainWindow::eventFilter(obj, event);
}

void MainWindow::onLabelAddTripClicked()
{
    AddTripDialog dialog(_tripService, _storageService, this);
    dialog.exec();
}

void MainWindow::onLabelLogOutClicked()
{
    handleLogoutRequest();
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
        ui->labelAddTrip->setVisible(_authService->hasPermission("admin"));
    } else {
        qWarning() << "No user logged in!";
    }
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




#include "MainWindow.h"
#include "DatabaseManager.h"
#include "SqlTripRepository.h"
#include "TripService.h"
#include <QApplication>
#include "SqlUserRepository.h"
#include "loginwindow.h"
#include "BookingService.h"
#include "SqlReviewRepository.h"
#include "ReviewService.h"
#include "SqlBookingRepository.h"
#include "AzureStorageService.h"
#include "CustomMessageBox.h"

#include "IDataProvider.h"
#include "SqlDao.h"
#include "Registry.h"

#include <QFile>

void loadGlobalStyles() {
    QFile styleFile(":/styles/style.css"); // Đường dẫn trong resource
    if (styleFile.open(QFile::ReadOnly | QFile::Text)) {
        QString styleSheet = QLatin1String(styleFile.readAll());
        qApp->setStyleSheet(styleSheet); // Áp dụng cho toàn bộ ứng dụng
        styleFile.close();
    }
}

int main(int argc, char* argv[])
{
    QApplication a(argc, argv);
    
    loadGlobalStyles();

    // Khởi tạo các dependency
    DatabaseManager& db = DatabaseManager::getInstance();
    
    // TODO: DI - Registry
    QSharedPointer<IDataProvider> dataProvider = QSharedPointer<SqlDao>::create(db); 
    /*
    QSharedPointer<SqlTripRepository> tripRepository = QSharedPointer<SqlTripRepository>::create(db);
    QSharedPointer<SqlUserRepository> userRepository = QSharedPointer<SqlUserRepository>::create(db);
    QSharedPointer<SqlBookingRepository> bookingRepository = QSharedPointer<SqlBookingRepository>::create(db);
    QSharedPointer<SqlReviewRepository> reviewRepository = QSharedPointer<SqlReviewRepository>::create(db);
    
   
    QSharedPointer<AuthService> authService = QSharedPointer<AuthService>::create(userRepository);
    QSharedPointer<TripService> tripService = QSharedPointer<TripService>::create(tripRepository);
    QSharedPointer<UserService> userService = QSharedPointer<UserService>::create(userRepository);
    QSharedPointer<BookingService> bookingService = QSharedPointer<BookingService>::create(bookingRepository, tripService, authService);
    QSharedPointer<ReviewService> reviewService = QSharedPointer<ReviewService>::create(reviewRepository, authService, bookingService);
    QSharedPointer<AzureStorageService> storageService(new AzureStorageService());
    */
    
    // TODO: Registry
    Registry::addSingleton<AuthService>(QSharedPointer<AuthService>::create(dataProvider->getUserRepository()));
    Registry::addSingleton<TripService>(QSharedPointer<TripService>::create(dataProvider->getTripRepository()));
    Registry::addSingleton<UserService>(QSharedPointer<UserService>::create(dataProvider->getUserRepository()));

    Registry::addSingleton<BookingService>(QSharedPointer<BookingService>::create(dataProvider->getBookingRepository(), 
                                                                                  Registry::getSingleton<TripService>(), 
                                                                                  Registry::getSingleton<AuthService>()));

    Registry::addSingleton<ReviewService>(QSharedPointer<ReviewService>::create(dataProvider->getReviewRepository(),
                                                                                  Registry::getSingleton<AuthService>(), 
                                                                                  Registry::getSingleton<BookingService>()));

    Registry::addSingleton<AzureStorageService>(QSharedPointer<AzureStorageService>::create());

    /*
    QSharedPointer<AuthService> authService = QSharedPointer<AuthService>::create(dataProvider->getUserRepository());
    QSharedPointer<TripService> tripService = QSharedPointer<TripService>::create(dataProvider->getTripRepository());
    QSharedPointer<UserService> userService = QSharedPointer<UserService>::create(dataProvider->getUserRepository());
    QSharedPointer<BookingService> bookingService = QSharedPointer<BookingService>::create(dataProvider->getBookingRepository(), tripService, authService);
    QSharedPointer<ReviewService> reviewService = QSharedPointer<ReviewService>::create(dataProvider->getReviewRepository(), authService, bookingService);
    QSharedPointer<AzureStorageService> storageService(new AzureStorageService());
    */

    LoginWindow loginWindow(Registry::getSingleton<AuthService>(), nullptr);
    QSharedPointer<MainWindow> mainWindow; // Khai báo bên ngoài lambda

    // Kết nối khi logout từ MainWindow
    QObject::connect(Registry::getSingleton<AuthService>().data(), &AuthService::logoutPerformed, [&]() {
        if (mainWindow) {
            mainWindow->hide();
        }
        loginWindow.show();
    });

    // Kết nối signal loginSuccess để tạo MainWindow sau khi login
    QObject::connect(&loginWindow, &LoginWindow::loginSuccess, [&]() {
        loginWindow.hide();

        // Tạo MainWindow sau khi login thành công
        mainWindow =  QSharedPointer<MainWindow>::create(
            Registry::getSingleton<UserService>(),
            Registry::getSingleton<AuthService>(),
            Registry::getSingleton<TripService>(),
            Registry::getSingleton<BookingService>(),
            Registry::getSingleton<AzureStorageService>(),
            Registry::getSingleton<ReviewService>()
        );
        mainWindow->show();
    });

    QObject::connect(mainWindow.data(), &MainWindow::logoutCompleted, [&]() {
        loginWindow.show();
    });

    // Khi người dùng nhấn nút 'x' để tắt bảng Login -> thông báo hủy đăng nhập -> tắt chương trình
    QObject::connect(&loginWindow, &LoginWindow::loginAborted, [&]() {
        CustomMessageBox::show("Thông báo", "Bạn đã hủy đăng nhập");
        QApplication::quit();
    });

    loginWindow.show();

    return a.exec();
}

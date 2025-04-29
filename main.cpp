#include "MainWindow.h"
#include "DatabaseManager.h"
#include "SqlTripRepository.h"
#include "TripService.h"
#include <QApplication>
#include "SqlUserRepository.h"
#include "loginwindow.h"


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    
    // Khởi tạo các dependency
    DatabaseManager& db = DatabaseManager::getInstance();
    QSharedPointer<SqlTripRepository> tripRepository = QSharedPointer<SqlTripRepository>::create(db);
    QSharedPointer<SqlUserRepository> userRepository = QSharedPointer<SqlUserRepository>::create(db);
    
    QSharedPointer<AuthService> authService = QSharedPointer<AuthService>::create(userRepository);
    QSharedPointer<TripService> tripService = QSharedPointer<TripService>::create(tripRepository);
    
    LoginWindow loginWindow(authService, nullptr);
    QSharedPointer<MainWindow> mainWindow; // Khai báo bên ngoài lambda

    // Kết nối signal loginSuccess để tạo MainWindow sau khi login
    QObject::connect(&loginWindow, &LoginWindow::loginSuccess, [&]() {
        loginWindow.close();

        // Tạo MainWindow sau khi login thành công
        mainWindow =  QSharedPointer<MainWindow>::create(authService, tripService);
        mainWindow->show();
    });

    // Khi người dùng nhấn nút 'x' để tắt bảng Login -> thông báo hủy đăng nhập -> tắt chương trình
    QObject::connect(&loginWindow, &LoginWindow::loginAborted, [&]() {
        QMessageBox::information(nullptr, "Thông báo", "Bạn đã hủy đăng nhập");
        QApplication::quit();
    });

    loginWindow.show();

    return a.exec();
}

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
    SqlTripRepository repository(db);
    TripService service(&repository);
    
    //Smart pointer
    QSharedPointer<SqlUserRepository> userRepo = QSharedPointer<SqlUserRepository>::create(db);
    QSharedPointer<AuthService> authService = QSharedPointer<AuthService>::create(userRepo);
    LoginWindow loginWindow(authService, nullptr);

    // Truyền service vào MainWindow
    MainWindow w(&service);

    //Nhận tín hiệu loginSuccess -> tắt bảng login -> mở MainWindow
    QObject::connect(&loginWindow, &LoginWindow::loginSuccess, [&](){
        loginWindow.close();
        //Lấy user authService->getCurrentUser()
        w.show();

    });

    // Khi người dùng nhấn nút 'x' để tắt bảng Login -> thông báo hủy đăng nhập -> tắt chương trình
    QObject::connect(&loginWindow, &LoginWindow::loginAborted, [&]() {
        QMessageBox::information(nullptr, "Thông báo", "Bạn đã hủy đăng nhập");
        QApplication::quit();
    });

    loginWindow.show();

    return a.exec();
}

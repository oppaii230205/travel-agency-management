#include "App.h"
#include <QApplication>
#include <QDebug>
#include <exception>

int main(int argc, char* argv[])
{
    // Tạo QApplication - qApp sẽ tự động được thiết lập
    QApplication a(argc, argv);

    qDebug() << "Starting application...";
    qDebug() << "Qt version:" << QT_VERSION_STR;
    qDebug() << "Application name:" << QCoreApplication::applicationName();

    try {
        // Tạo App instance
        App app;

        // Khởi tạo ứng dụng (sau khi QApplication đã được tạo)
        if (!app.config()) {
            qCritical() << "Failed to initialize application";
            return -1;
        }

        // Chạy ứng dụng
        return app.run();
    }
    catch (const std::exception& e) {
        qCritical() << "Unhandled exception in main:" << e.what();
        return -1;
    }
    catch (...) {
        qCritical() << "Unknown exception occurred in main";
        return -1;
    }
}

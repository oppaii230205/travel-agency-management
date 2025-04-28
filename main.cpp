#include "mainwindow.h"
#include "DatabaseManager.h"

#include <QApplication>
#include <QLocale>
#include <QTranslator>
#include "SqlUserRepository.h"
#include "loginwindow.h"
#include "authservice.h"


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // Khởi tạo database
    DatabaseManager& dbManager = DatabaseManager::getInstance();
    if (!dbManager.connect()) {
        QMessageBox::critical(nullptr, "Database Error", "Failed to connect to database");
        return -1;
    }

    QTranslator translator;
    const QStringList uiLanguages = QLocale::system().uiLanguages();
    for (const QString &locale : uiLanguages) {
        const QString baseName = "TravelAgencyGUI_" + QLocale(locale).name();
        if (translator.load(":/i18n/" + baseName)) {
            a.installTranslator(&translator);
            break;
        }
    }

    auto userRepo = QSharedPointer<SqlUserRepository>::create(dbManager.getDatabase());
    auto authService = QSharedPointer<AuthService>::create(userRepo);
    LoginWindow loginWindow(authService, nullptr);
    loginWindow.show();
    MainWindow w;
    w.show();
    return a.exec();
}

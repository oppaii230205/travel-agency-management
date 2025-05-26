#include "App.h"

// Qt includes
#include <QApplication>
#include <QFile>
#include <QDebug>

// Project includes
#include "MainWindow.h"
#include "DatabaseManager.h"
#include "SqlTripRepository.h"
#include "TripService.h"
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

App::App() {
    // Constructor - khởi tạo cơ bản
    qDebug() << "App constructor called";
}

App::~App() {
    // Cleanup Registry khi App bị hủy
    qDebug() << "App destructor called";
    Registry::clear();
}

void App::loadGlobalStyles() {
    // Kiểm tra xem QApplication đã được khởi tạo chưa
    if (!qApp) {
        qWarning() << "QApplication chưa được khởi tạo!";
        return;
    }

    QFile styleFile(":/styles/style.css");
    if (styleFile.open(QFile::ReadOnly | QFile::Text)) {
        QString styleSheet = QLatin1String(styleFile.readAll());
        qApp->setStyleSheet(styleSheet);
        styleFile.close();
        qDebug() << "Global styles loaded successfully";
    } else {
        qWarning() << "Failed to load global styles";
    }
}

void App::setupDependencies() {
    qDebug() << "Setting up dependencies...";

    try {
        // Khởi tạo DatabaseManager
        DatabaseManager& db = DatabaseManager::getInstance();

        // Khởi tạo DataProvider
        QSharedPointer<IDataProvider> dataProvider = QSharedPointer<SqlDao>::create(db);

        // Đăng ký các service theo thứ tự dependency

        // 1. Các service cơ bản không phụ thuộc vào service khác
        Registry::addSingleton<AuthService>(
            QSharedPointer<AuthService>::create(dataProvider->getUserRepository())
            );
        qDebug() << "AuthService registered";

        Registry::addSingleton<TripService>(
            QSharedPointer<TripService>::create(dataProvider->getTripRepository())
            );
        qDebug() << "TripService registered";

        Registry::addSingleton<UserService>(
            QSharedPointer<UserService>::create(dataProvider->getUserRepository())
            );
        qDebug() << "UserService registered";

        Registry::addSingleton<AzureStorageService>(
            QSharedPointer<AzureStorageService>::create()
            );
        qDebug() << "AzureStorageService registered";

        // 2. Các service phụ thuộc vào service khác
        Registry::addSingleton<BookingService>(
            QSharedPointer<BookingService>::create(
                dataProvider->getBookingRepository(),
                Registry::getSingleton<TripService>(),
                Registry::getSingleton<AuthService>()
                )
            );
        qDebug() << "BookingService registered";

        Registry::addSingleton<ReviewService>(
            QSharedPointer<ReviewService>::create(
                dataProvider->getReviewRepository(),
                Registry::getSingleton<AuthService>(),
                Registry::getSingleton<BookingService>()
                )
            );
        qDebug() << "ReviewService registered";

        qDebug() << "All dependencies set up successfully";
    }
    catch (const std::exception& e) {
        qCritical() << "Error setting up dependencies:" << e.what();
        throw;
    }
}

void App::setupConnections() {
    qDebug() << "Setting up connections...";

    try {
        // Khởi tạo LoginWindow
        _loginWindow = QSharedPointer<LoginWindow>::create(
            Registry::getSingleton<AuthService>(),
            nullptr
            );

        // Kết nối khi logout từ MainWindow
        QObject::connect(Registry::getSingleton<AuthService>().data(), &AuthService::logoutPerformed,
                         [this]() {
                             qDebug() << "Logout performed, hiding main window";
                             if (_mainWindow) {
                                 _mainWindow->hide();
                             }
                             _loginWindow->show();
                         });

        // Kết nối signal loginSuccess để tạo MainWindow sau khi login
        QObject::connect(_loginWindow.data(), &LoginWindow::loginSuccess, [this]() {
            qDebug() << "Login successful, creating main window";
            _loginWindow->hide();

            // Tạo MainWindow sau khi login thành công
            _mainWindow = QSharedPointer<MainWindow>::create(
                Registry::getSingleton<UserService>(),
                Registry::getSingleton<AuthService>(),
                Registry::getSingleton<TripService>(),
                Registry::getSingleton<BookingService>(),
                Registry::getSingleton<AzureStorageService>(),
                Registry::getSingleton<ReviewService>()
                );

            // Kết nối logout từ MainWindow sau khi MainWindow được tạo
            QObject::connect(_mainWindow.data(), &MainWindow::logoutCompleted, [this]() {
                qDebug() << "Logout completed from main window";
                _loginWindow->show();
            });

            _mainWindow->show();
        });

        // Khi người dùng nhấn nút 'x' để tắt bảng Login
        QObject::connect(_loginWindow.data(), &LoginWindow::loginAborted, [this]() {
            qDebug() << "Login aborted by user";
            CustomMessageBox::show("Thông báo", "Bạn đã hủy đăng nhập");
            if (qApp) {
                qApp->quit();
            }
        });

        qDebug() << "All connections set up successfully";
    }
    catch (const std::exception& e) {
        qCritical() << "Error setting up connections:" << e.what();
        throw;
    }
}

bool App::config() {
    qDebug() << "Initializing application...";

    // Kiểm tra xem QApplication đã được tạo chưa
    if (!qApp) {
        qCritical() << "QApplication chưa được khởi tạo! Vui lòng gọi App::initialize() sau khi tạo QApplication.";
        return false;
    }

    try {
        // Load styles
        loadGlobalStyles();

        // Setup dependency injection
        setupDependencies();

        // Setup UI connections
        setupConnections();

        qDebug() << "Application initialization completed successfully";
        return true;
    }
    catch (const std::exception& e) {
        qCritical() << "Failed to initialize application:" << e.what();
        return false;
    }
}

int App::run() {
    qDebug() << "Running application...";

    // Kiểm tra xem app đã được khởi tạo chưa
    if (!qApp) {
        qCritical() << "QApplication chưa được khởi tạo!";
        return -1;
    }

    if (!_loginWindow) {
        qCritical() << "LoginWindow chưa được khởi tạo! Vui lòng gọi initialize() trước.";
        return -1;
    }

    // Hiển thị login window
    _loginWindow->show();

    // Chạy event loop
    int result = qApp->exec();

    qDebug() << "Application finished with exit code:" << result;
    return result;
}

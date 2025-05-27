#ifndef APP_H
#define APP_H

#include <QSharedPointer>

// Forward declarations
class QApplication;
class LoginWindow;
class MainWindow;
class DatabaseManager;
class IDataProvider;

/**
 * @brief Lớp App chính quản lý toàn bộ vòng đời của ứng dụng
 *
 * Lớp này thực hiện vai trò Application Controller trong mô hình MVC,
 * chịu trách nhiệm khởi tạo dependencies, thiết lập connections và
 * quản lý flow của ứng dụng.
 */
class App {
private:
    // UI Components - sử dụng QSharedPointer để quản lý memory tự động
    QSharedPointer<LoginWindow> _loginWindow;
    QSharedPointer<MainWindow> _mainWindow;

    // Private methods cho việc thiết lập
    void loadGlobalStyles();
    void setupDependencies();
    void setupConnections();
    void setupObservers();

public:
    /**
     * @brief Constructor mặc định
     */
    App();

    /**
     * @brief Destructor - cleanup resources
     */
    ~App();

    /**
     * @brief Khởi tạo ứng dụng với tất cả dependencies và connections
     * @return true nếu khởi tạo thành công, false nếu có lỗi
     *
     * Phương thức này phải được gọi sau khi QApplication đã được tạo
     */
    bool config();

    /**
     * @brief Chạy ứng dụng
     * @return exit code của ứng dụng
     *
     * Phương thức này sẽ hiển thị LoginWindow và bắt đầu event loop
     */
    int run();

    // Disable copy constructor và assignment operator để đảm bảo singleton-like behavior
    App(const App&) = delete;
    App& operator=(const App&) = delete;
    App(App&&) = delete;
    App& operator=(App&&) = delete;
};

#endif // APP_H

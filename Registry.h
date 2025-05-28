/**
 * @file Registry.h
 * @brief Class Registry quản lý các singleton services trong ứng dụng
 * 
 * Class này triển khai Registry pattern để:
 * - Quản lý vòng đời của các singleton services
 * - Cung cấp cơ chế dependency injection
 * - Đảm bảo tính nhất quán của các services trong toàn bộ ứng dụng
 */

#ifndef REGISTRY_H
#define REGISTRY_H

#include <QHash>
#include <QString>
#include <QSharedPointer>
#include <typeinfo>
#include <any>

#include <QDebug>

/**
 * @brief Class quản lý các singleton services
 * 
 * Registry là một singleton global quản lý việc:
 * - Đăng ký các singleton services
 * - Truy xuất các services đã đăng ký
 * - Kiểm soát vòng đời của services
 * 
 * Sử dụng template và std::any để hỗ trợ đa kiểu dữ liệu.
 */
class Registry {
private:
    /**
     * @brief Hash table lưu trữ các singleton instances
     * 
     * Key: Tên của type (từ typeid)
     * Value: Instance của service được wrap trong std::any
     */
    inline static QHash<QString, std::any> _instances;

public:
    /**
     * @brief Đăng ký một singleton service mới
     * 
     * @tparam T Type của service cần đăng ký
     * @param instance Con trỏ thông minh đến instance của service
     */
    template<typename T>
    static void addSingleton(QSharedPointer<T> instance) {
        _instances.insert(QString::fromStdString(typeid(T).name()), instance);
    }

    /**
     * @brief Lấy instance của một singleton service
     * 
     * @tparam T Type của service cần lấy
     * @return QSharedPointer<T> Con trỏ đến service, hoặc nullptr nếu không tìm thấy
     * 
     * @note Phương thức này sẽ trả về nullptr trong các trường hợp:
     *       - Service chưa được đăng ký
     *       - Không thể cast type được lưu trữ sang type yêu cầu
     */
    template<typename T>
    static QSharedPointer<T> getSingleton() {
        auto it = _instances.constFind(QString::fromStdString(typeid(T).name()));
        if (it != _instances.constEnd()) {
            try {
                return std::any_cast<QSharedPointer<T>>(it.value());
            } catch (const std::bad_any_cast& e) {
                qWarning() << "Bad cast when getting singleton for type:" << typeid(T).name();
                return nullptr;
            }
        }
        return nullptr;
    }

    /**
     * @brief Xóa tất cả các singleton services đã đăng ký
     * 
     * Phương thức này được sử dụng để cleanup khi:
     * - Đóng ứng dụng
     * - Reset trạng thái của ứng dụng
     * - Thực hiện unit testing
     */
    static void clear() {
        _instances.clear();
    }

    /**
     * @brief Kiểm tra xem một service đã được đăng ký chưa
     * 
     * @tparam T Type của service cần kiểm tra
     * @return true nếu service đã được đăng ký
     * @return false nếu service chưa được đăng ký
     */
    template<typename T>
    static bool isRegistered() {
        return _instances.contains(QString::fromStdString(typeid(T).name()));
    }

    /**
     * @brief Lấy danh sách tên của tất cả các services đã đăng ký
     * 
     * @return QStringList Danh sách tên các types đã đăng ký
     * 
     * @note Tên types được trả về là tên được tạo bởi typeid,
     *       không phải tên class thông thường
     */
    static QStringList getRegisteredTypes() {
        return _instances.keys();
    }
};

#endif // REGISTRY_H

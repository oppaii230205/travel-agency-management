/**
 * @file Observable.h
 * @brief Class cơ sở cho Subject trong Observer Pattern
 * 
 * File này định nghĩa:
 * - Subject có thể được theo dõi bởi nhiều observers
 * - Quản lý việc đăng ký và hủy đăng ký của observers
 * - Thông báo sự kiện đến tất cả observers đã đăng ký
 */

#ifndef OBSERVABLE_H
#define OBSERVABLE_H

#include <QObject>
#include <set>
#include <memory>
#include "IObserver.h"

/**
 * @brief Class cơ sở cho các đối tượng có thể được theo dõi
 * 
 * Class này kế thừa từ QObject và:
 * - Quản lý danh sách các observers
 * - Cung cấp cơ chế đăng ký/hủy đăng ký
 * - Thông báo sự kiện đến tất cả observers
 * - Đảm bảo thread-safe khi thao tác với observers
 */
class Observable : public QObject {
    Q_OBJECT
public:
    /**
     * @brief Đăng ký một observer mới
     * 
     * Thêm observer vào danh sách theo dõi.
     * Nếu observer đã tồn tại, không thêm lại.
     * 
     * @param observer Con trỏ đến observer cần đăng ký
     */
    void subscribe(IObserverPtr observer);

    /**
     * @brief Hủy đăng ký một observer
     * 
     * Xóa observer khỏi danh sách theo dõi.
     * Nếu observer không tồn tại, không làm gì cả.
     * 
     * @param observer Con trỏ đến observer cần hủy đăng ký
     */
    void unsubscribe(IObserverPtr observer);

    /**
     * @brief Thông báo sự kiện đến tất cả observers
     * 
     * Gọi phương thức onEvent của tất cả observers đã đăng ký.
     * Đảm bảo thông báo theo thứ tự đăng ký.
     * 
     * @param event Sự kiện cần thông báo
     */
    void notify(const Event& event);

protected:
    std::set<IObserverPtr> _observers;    ///< Tập hợp các observers đã đăng ký, sử dụng set để đảm bảo không trùng lặp
};

#endif // OBSERVABLE_H

/**
 * @file IObserver.h
 * @brief Interface cho Observer trong Observer Pattern
 * 
 * File này định nghĩa:
 * - Interface cơ bản cho Observer Pattern
 * - Phương thức xử lý sự kiện cho observers
 * - Typedef cho smart pointer đến observer
 */

#ifndef IOBSERVER_H
#define IOBSERVER_H

#include <memory>
#include <QSharedPointer>
#include "Event.h"

/**
 * @brief Interface định nghĩa observer trong Observer Pattern
 * 
 * Interface này:
 * - Cho phép các observer đăng ký nhận thông báo về sự kiện
 * - Định nghĩa cách xử lý sự kiện cho mỗi observer
 * - Đảm bảo tính loose coupling giữa subject và observer
 */
class IObserver {
public:
    /**
     * @brief Destructor ảo cho phép kế thừa an toàn
     */
    virtual ~IObserver() = default;

    /**
     * @brief Xử lý sự kiện khi được thông báo
     * 
     * Phương thức này được gọi bởi subject khi có sự kiện xảy ra.
     * Mỗi observer cụ thể sẽ triển khai phương thức này để xử lý sự kiện
     * theo cách riêng của mình.
     * 
     * @param event Sự kiện cần xử lý
     */
    virtual void onEvent(const Event& event) = 0;
};

/**
 * @brief Typedef cho smart pointer đến IObserver
 * 
 * Sử dụng QSharedPointer để:
 * - Quản lý bộ nhớ tự động cho observer
 * - Đảm bảo observer được giải phóng khi không còn được sử dụng
 * - Cho phép chia sẻ observer giữa nhiều đối tượng
 */
using IObserverPtr = QSharedPointer<IObserver>;

#endif // IOBSERVER_H

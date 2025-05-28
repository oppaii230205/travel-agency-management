/**
 * @file Event.h
 * @brief Class cơ sở cho các sự kiện trong hệ thống
 * 
 * File này định nghĩa interface cơ bản cho các sự kiện:
 * - Cung cấp timestamp cho mỗi sự kiện
 * - Định nghĩa interface để lấy tên và dữ liệu của sự kiện
 * - Cho phép mở rộng với các loại sự kiện cụ thể
 */

#ifndef EVENT_H
#define EVENT_H

#include <QString>
#include <QVariant>
#include <QDateTime>

/**
 * @brief Class cơ sở trừu tượng cho tất cả các sự kiện trong hệ thống
 * 
 * Class này cung cấp:
 * - Cơ chế theo dõi thời gian xảy ra sự kiện
 * - Interface để lấy thông tin về sự kiện
 * - Cơ sở để xây dựng các loại sự kiện cụ thể
 */
class Event {
public:
    /**
     * @brief Constructor mặc định
     * 
     * Khởi tạo sự kiện với timestamp là thời điểm hiện tại
     */
    Event() : _timestamp(QDateTime::currentDateTime()) {}

    /**
     * @brief Destructor ảo cho phép kế thừa an toàn
     */
    virtual ~Event() = default;

    /**
     * @brief Lấy thời điểm xảy ra sự kiện
     * @return QDateTime Thời điểm sự kiện được tạo
     */
    QDateTime timestamp() const { return _timestamp; }

    /**
     * @brief Lấy tên của sự kiện
     * @return QString Tên định danh của sự kiện
     */
    virtual QString name() const = 0;

    /**
     * @brief Lấy dữ liệu của sự kiện
     * @return QVariantMap Map chứa các cặp key-value mô tả dữ liệu của sự kiện
     */
    virtual QVariantMap data() const = 0;

private:
    QDateTime _timestamp;    ///< Thời điểm sự kiện xảy ra
};

#endif // EVENT_H

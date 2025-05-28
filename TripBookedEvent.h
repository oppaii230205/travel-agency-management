/**
 * @file TripBookedEvent.h
 * @brief Sự kiện được phát khi một chuyến đi được đặt
 * 
 * File này định nghĩa:
 * - Sự kiện đặt chỗ thành công
 * - Thông tin về chuyến đi được đặt
 * - Thông tin về người đặt chỗ
 */

#ifndef TRIPBOOKEDEVENT_H
#define TRIPBOOKEDEVENT_H

#include "Event.h"
#include <QString>

/**
 * @brief Class đại diện cho sự kiện đặt chỗ chuyến đi
 * 
 * Class này kế thừa từ Event và:
 * - Lưu trữ thông tin về chuyến đi được đặt
 * - Lưu trữ thông tin về người đặt chỗ
 * - Cung cấp các phương thức truy xuất thông tin
 */
class TripBookedEvent : public Event {
public:
    /**
     * @brief Constructor cho sự kiện đặt chỗ
     * 
     * @param tripId ID của chuyến đi được đặt
     * @param userEmail Email của người đặt chỗ
     */
    TripBookedEvent(int tripId, const QString& userEmail)
        : _tripId(tripId), _userEmail(userEmail) {}

    /**
     * @brief Lấy tên của sự kiện
     * @return QString "TripBooked"
     */
    QString name() const override { return "TripBooked"; }

    /**
     * @brief Lấy dữ liệu của sự kiện dưới dạng map
     * 
     * Map bao gồm:
     * - "tripId": ID của chuyến đi
     * - "userEmail": Email của người đặt
     * 
     * @return QVariantMap Map chứa dữ liệu sự kiện
     */
    QVariantMap data() const override {
        return {
            {"tripId", _tripId},
            {"userEmail", _userEmail}
        };
    }

    /**
     * @brief Lấy ID của chuyến đi được đặt
     * @return int ID của chuyến đi
     */
    int tripId() const { return _tripId; }

    /**
     * @brief Lấy email của người đặt chỗ
     * @return QString Email của người đặt
     */
    QString userEmail() const { return _userEmail; }

private:
    int _tripId;        ///< ID của chuyến đi được đặt
    QString _userEmail; ///< Email của người đặt chỗ
};

#endif // TRIPBOOKEDEVENT_H

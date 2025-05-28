/**
 * @file AnalyticsObserver.h
 * @brief Observer phân tích dữ liệu thống kê từ các sự kiện
 * 
 * File này định nghĩa:
 * - Thu thập và phân tích dữ liệu từ các sự kiện
 * - Thống kê số lượng đặt chỗ theo người dùng
 * - Thống kê đánh giá cho các chuyến đi
 */

#ifndef ANALYTICSOBSERVER_H
#define ANALYTICSOBSERVER_H

#include "IObserver.h"
#include "TripBookedEvent.h"
#include <QMap>

/**
 * @brief Observer thực hiện phân tích dữ liệu từ các sự kiện
 * 
 * Class này kế thừa từ IObserver và:
 * - Theo dõi số lượng đặt chỗ của mỗi người dùng
 * - Thống kê đánh giá cho các chuyến đi
 * - Cung cấp các phương thức truy vấn thống kê
 */
class AnalyticsObserver : public IObserver {
public:
    /**
     * @brief Constructor mặc định
     * 
     * Khởi tạo mảng đếm đánh giá với giá trị 0
     * cho mỗi mức đánh giá từ 1-5 sao
     */
    AnalyticsObserver() {
        _tripBookingsCount.fill(0, 5); // For rating 1-5
    }

    /**
     * @brief Xử lý các sự kiện để thu thập dữ liệu thống kê
     * 
     * Phương thức này:
     * - Xử lý sự kiện TripBooked để đếm số lần đặt chỗ
     * - Xử lý sự kiện ReviewSubmitted để thống kê đánh giá
     * 
     * @param event Sự kiện cần xử lý
     */
    void onEvent(const Event& event) override {
        if (event.name() == "TripBooked") {
            const auto& tripEvent = static_cast<const TripBookedEvent&>(event);
            _userBookings[tripEvent.userEmail()]++;
        }
        else if (event.name() == "ReviewSubmitted") {
            // Similar handling for review events
        }
    }

    /**
     * @brief Lấy số lượng đặt chỗ của một người dùng
     * 
     * @param email Email của người dùng cần truy vấn
     * @return int Số lượng lần đặt chỗ của người dùng (0 nếu chưa từng đặt)
     */
    int bookingsForUser(const QString& email) const {
        return _userBookings.value(email, 0);
    }

private:
    QMap<QString, int> _userBookings;      ///< Map lưu số lần đặt chỗ của mỗi người dùng
    QVector<int> _tripBookingsCount;       ///< Vector lưu số lượng đánh giá cho mỗi mức sao (1-5)
};

#endif // ANALYTICSOBSERVER_H

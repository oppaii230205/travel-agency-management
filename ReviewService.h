/**
 * @file ReviewService.h
 * @brief Service xử lý logic nghiệp vụ cho đánh giá chuyến đi
 * 
 * Service này quản lý:
 * - Việc thêm đánh giá mới
 * - Truy xuất đánh giá của chuyến đi
 * - Tính toán điểm đánh giá trung bình
 * - Kiểm tra quyền đánh giá của người dùng
 */

#ifndef REVIEWSERVICE_H
#define REVIEWSERVICE_H

#include "ReviewRepository.h"
#include "AuthService.h"
#include "BookingService.h"
#include <QObject>

/**
 * @brief Service xử lý các thao tác liên quan đến đánh giá
 * 
 * Class này kết hợp:
 * - ReviewRepository để lưu trữ đánh giá
 * - AuthService để xác thực người dùng
 * - BookingService để kiểm tra điều kiện đánh giá
 */
class ReviewService : public QObject {
    Q_OBJECT
public:
    /**
     * @brief Constructor với đầy đủ dependencies
     * 
     * @param repo Repository quản lý dữ liệu đánh giá
     * @param authService Service xác thực người dùng
     * @param bookingService Service quản lý đặt chỗ
     * @param parent QObject cha (mặc định là nullptr)
     */
    ReviewService(QSharedPointer<ReviewRepository> repo,
                  QSharedPointer<AuthService> authService,
                  QSharedPointer<BookingService> bookingService,
                  QObject* parent = nullptr);

    /**
     * @brief Gửi đánh giá mới cho một chuyến đi
     * 
     * Phương thức này sẽ:
     * - Kiểm tra quyền đánh giá của người dùng
     * - Validate dữ liệu đánh giá
     * - Lưu đánh giá vào database
     * - Phát signal thông báo kết quả
     * 
     * @param tripId ID của chuyến đi cần đánh giá
     * @param rating Số sao đánh giá (1-5)
     * @param comment Nội dung bình luận
     * @return true nếu gửi đánh giá thành công
     * @return false nếu có lỗi xảy ra
     */
    Q_INVOKABLE bool submitReview(int tripId, int rating, const QString& comment);

    /**
     * @brief Lấy danh sách đánh giá của một chuyến đi
     * 
     * @param tripId ID của chuyến đi cần lấy đánh giá
     * @return QList<Review> Danh sách các đánh giá
     */
    Q_INVOKABLE QList<Review> getTripReviews(int tripId) const;

    /**
     * @brief Lấy điểm đánh giá trung bình của một chuyến đi
     * 
     * @param tripId ID của chuyến đi cần tính điểm
     * @return double Điểm trung bình (từ 1.0 đến 5.0)
     */
    Q_INVOKABLE double getTripAverageRating(int tripId) const;

    /**
     * @brief Kiểm tra xem người dùng có thể đánh giá chuyến đi không
     * 
     * Điều kiện để có thể đánh giá:
     * - Người dùng đã đăng nhập
     * - Người dùng đã từng đặt chuyến đi này
     * - Chuyến đi đã kết thúc
     * - Người dùng chưa đánh giá chuyến đi này
     * 
     * @param tripId ID của chuyến đi cần kiểm tra
     * @return true nếu người dùng có thể đánh giá
     * @return false nếu người dùng không thể đánh giá
     */
    Q_INVOKABLE bool canUserReview(int tripId) const;

signals:
    /**
     * @brief Signal được phát khi đánh giá được gửi thành công
     */
    void reviewSubmitted();

    /**
     * @brief Signal được phát khi có lỗi xảy ra trong quá trình đánh giá
     * @param message Thông báo lỗi
     */
    void reviewError(const QString& message);

private:
    QSharedPointer<ReviewRepository> _repo;        ///< Repository quản lý dữ liệu đánh giá
    QSharedPointer<AuthService> _authService;      ///< Service xác thực người dùng
    QSharedPointer<BookingService> _bookingService; ///< Service quản lý đặt chỗ
};

#endif // REVIEWSERVICE_H

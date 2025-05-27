/**
 * @file ReviewRepository.h
 * @brief Interface định nghĩa các thao tác với dữ liệu đánh giá
 * 
 * Interface này định nghĩa các phương thức để:
 * - Thêm đánh giá mới
 * - Truy vấn đánh giá theo chuyến đi
 * - Kiểm tra trạng thái đánh giá của người dùng
 * - Tính toán điểm đánh giá trung bình
 */

#ifndef REVIEWREPOSITORY_H
#define REVIEWREPOSITORY_H

#include "Review.h"
#include <QList>

/**
 * @brief Interface cho repository quản lý đánh giá
 * 
 * Interface này tuân theo Repository pattern và định nghĩa:
 * - Các thao tác CRUD với đánh giá
 * - Các truy vấn thống kê
 * - Các phương thức kiểm tra trạng thái
 */
class ReviewRepository {
public:
    /**
     * @brief Constructor mặc định
     */
    ReviewRepository() = default;

    /**
     * @brief Destructor ảo
     * 
     * Destructor được khai báo virtual để đảm bảo
     * các lớp kế thừa được hủy đúng cách
     */
    virtual ~ReviewRepository() = default;

    /**
     * @brief Thêm một đánh giá mới
     * 
     * @param review Đối tượng Review cần thêm
     * @return true nếu thêm thành công
     * @return false nếu thêm thất bại (ví dụ: đánh giá không hợp lệ)
     */
    virtual bool addReview(const Review& review) = 0;

    /**
     * @brief Lấy danh sách đánh giá của một chuyến đi
     * 
     * @param tripId ID của chuyến đi cần lấy đánh giá
     * @return QList<Review> Danh sách các đánh giá
     */
    virtual QList<Review> getReviewsByTrip(int tripId) = 0;

    /**
     * @brief Kiểm tra xem người dùng đã đánh giá chuyến đi chưa
     * 
     * @param tripId ID của chuyến đi cần kiểm tra
     * @param userEmail Email của người dùng cần kiểm tra
     * @return true nếu người dùng đã đánh giá
     * @return false nếu người dùng chưa đánh giá
     */
    virtual bool hasUserReviewed(int tripId, const QString& userEmail) = 0;

    /**
     * @brief Tính điểm đánh giá trung bình của một chuyến đi
     * 
     * @param tripId ID của chuyến đi cần tính điểm
     * @return double Điểm trung bình (từ 1.0 đến 5.0)
     * 
     * @note Nếu chuyến đi chưa có đánh giá nào, trả về 0.0
     */
    virtual double getAverageRating(int tripId) = 0;
};

#endif // IREVIEWREPOSITORY_H

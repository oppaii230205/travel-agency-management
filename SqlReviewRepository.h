/**
 * @file SqlReviewRepository.h
 * @brief Triển khai ReviewRepository interface sử dụng SQL database
 * 
 * Class này cung cấp các thao tác với đánh giá thông qua:
 * - Kết nối SQL database
 * - Thực thi các câu query
 * - Ánh xạ kết quả sang đối tượng Review
 * - Tính toán thống kê đánh giá
 */

#ifndef SQLREVIEWREPOSITORY_H
#define SQLREVIEWREPOSITORY_H

#include "ReviewRepository.h"
#include "DatabaseManager.h"
#include <QSqlQuery>

/**
 * @brief Class triển khai ReviewRepository sử dụng SQL database
 * 
 * Class này:
 * - Kế thừa interface ReviewRepository
 * - Sử dụng DatabaseManager để kết nối database
 * - Thực hiện các thao tác CRUD với bảng reviews
 * - Tính toán các chỉ số thống kê đánh giá
 */
class SqlReviewRepository : public ReviewRepository {
public:
    /**
     * @brief Constructor với DatabaseManager
     * 
     * @param dbManager Tham chiếu đến DatabaseManager singleton
     */
    explicit SqlReviewRepository(DatabaseManager& dbManager);

    /**
     * @brief Thêm một đánh giá mới vào database
     * 
     * @param review Đối tượng Review cần thêm
     * @return true nếu thêm thành công
     * @return false nếu có lỗi (ví dụ: vi phạm ràng buộc unique)
     */
    bool addReview(const Review& review) override;

    /**
     * @brief Lấy danh sách đánh giá của một chuyến đi
     * 
     * @param tripId ID của chuyến đi cần lấy đánh giá
     * @return QList<Review> Danh sách các đánh giá
     * 
     * @note Trả về danh sách rỗng nếu không tìm thấy đánh giá nào
     */
    QList<Review> getReviewsByTrip(int tripId) override;

    /**
     * @brief Kiểm tra xem người dùng đã đánh giá chuyến đi chưa
     * 
     * @param tripId ID của chuyến đi
     * @param userEmail Email của người dùng
     * @return true nếu người dùng đã đánh giá
     * @return false nếu chưa đánh giá hoặc có lỗi xảy ra
     */
    bool hasUserReviewed(int tripId, const QString& userEmail) override;

    /**
     * @brief Tính điểm đánh giá trung bình của một chuyến đi
     * 
     * @param tripId ID của chuyến đi cần tính điểm
     * @return double Điểm trung bình (từ 1.0 đến 5.0)
     * 
     * @note Trả về 0.0 nếu chuyến đi chưa có đánh giá nào
     */
    double getAverageRating(int tripId) override;

private:
    DatabaseManager& _dbManager;  ///< Tham chiếu đến DatabaseManager singleton

    /**
     * @brief Ánh xạ kết quả query thành đối tượng Review
     * 
     * @param query Query đã thực thi thành công
     * @return Review Đối tượng review được tạo từ dữ liệu query
     * 
     * @note Query phải chứa đầy đủ các trường của bảng reviews
     */
    Review mapToReview(const QSqlQuery& query) const;
};

#endif // SQLREVIEWREPOSITORY_H

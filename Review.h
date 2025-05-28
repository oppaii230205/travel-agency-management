/**
 * @file Review.h
 * @brief Class quản lý đánh giá của người dùng cho các chuyến đi
 * 
 * Class này định nghĩa cấu trúc dữ liệu cho:
 * - Đánh giá sao (1-5 sao)
 * - Bình luận của người dùng
 * - Thông tin về chuyến đi được đánh giá
 * - Thông tin người đánh giá
 * - Thời gian đánh giá
 */

#ifndef REVIEW_H
#define REVIEW_H

#include <QDateTime>
#include <QString>

/**
 * @brief Class đại diện cho một đánh giá chuyến đi
 * 
 * Mỗi đánh giá bao gồm:
 * - Số sao đánh giá (1-5)
 * - Nội dung bình luận
 * - Thông tin người đánh giá
 * - Thông tin chuyến đi
 * - Metadata (thời gian tạo)
 */
class Review {
private:
    int _tripId;        ///< ID của chuyến đi được đánh giá
    QString _userEmail; ///< Email của người đánh giá
    int _rating;        ///< Số sao đánh giá (1-5 sao)
    QString _comment;   ///< Nội dung bình luận
    QDateTime _createdAt; ///< Thời điểm tạo đánh giá

public:
    /**
     * @brief Constructor mặc định
     */
    Review() = default;

    /**
     * @brief Constructor với đầy đủ thông tin
     * 
     * @param tripId ID của chuyến đi được đánh giá
     * @param userEmail Email của người đánh giá
     * @param rating Số sao đánh giá (1-5)
     * @param comment Nội dung bình luận
     * @param createdAt Thời điểm tạo đánh giá (mặc định là thời điểm hiện tại)
     */
    Review(int tripId = 0,
           const QString& userEmail = "",
           int rating = 0,
           const QString& comment = "",
           const QDateTime& createdAt = QDateTime::currentDateTime());

    /**
     * @brief Lấy ID của chuyến đi được đánh giá
     * @return int ID của chuyến đi
     */
    int getTripId() const;

    /**
     * @brief Lấy email của người đánh giá
     * @return QString Email của người đánh giá
     */
    QString getUserEmail() const;

    /**
     * @brief Lấy số sao đánh giá
     * @return int Số sao (1-5)
     */
    int getRating() const;

    /**
     * @brief Lấy nội dung bình luận
     * @return QString Nội dung bình luận
     */
    QString getComment() const;

    /**
     * @brief Lấy thời điểm tạo đánh giá
     * @return QDateTime Thời điểm tạo
     */
    QDateTime getCreatedAt() const;

    /**
     * @brief Kiểm tra tính hợp lệ của đánh giá
     * 
     * Một đánh giá được coi là hợp lệ khi:
     * - Có ID chuyến đi hợp lệ (> 0)
     * - Có email người đánh giá
     * - Số sao trong khoảng 1-5
     * - Có thời gian tạo hợp lệ
     * 
     * @return true nếu đánh giá hợp lệ
     * @return false nếu đánh giá không hợp lệ
     */
    bool isValid() const;
};

#endif // REVIEW_H

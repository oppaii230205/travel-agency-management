/**
 * @file Trip.h
 * @brief Class đại diện cho một chuyến đi trong hệ thống
 * 
 * Class này định nghĩa:
 * - Thông tin cơ bản của chuyến đi
 * - Các thuộc tính mô tả chuyến đi
 * - Các phương thức truy xuất và cập nhật
 * - Các ràng buộc về dữ liệu
 */

#ifndef TRIP_H
#define TRIP_H

#include <QString>
#include <QDate>

/**
 * @brief Class mô tả một chuyến đi du lịch
 * 
 * Chứa các thông tin:
 * - Thông tin định danh (ID, tên)
 * - Thông tin tổ chức (thời gian, số người)
 * - Thông tin mô tả (độ khó, giá, mô tả)
 * - Tài nguyên đa phương tiện (hình ảnh)
 */
class Trip {
private:
    int _tripId;           ///< ID định danh chuyến đi
    QString _tripName;     ///< Tên chuyến đi
    int _duration;         ///< Thời gian (số ngày)
    int _maxGroupSize;     ///< Số người tối đa trong nhóm
    QString _difficulty;   ///< Độ khó (Easy/Medium/Hard)
    int _price;           ///< Giá chuyến đi (VND)
    QString _summary;      ///< Tóm tắt ngắn gọn
    QString _description;  ///< Mô tả chi tiết
    QString _imagePath;    ///< Đường dẫn đến ảnh đại diện

public:
    /**
     * @brief Constructor mặc định
     */
    Trip();

    /**
     * @brief Constructor với đầy đủ thông tin
     * 
     * @param tripId ID chuyến đi
     * @param tripName Tên chuyến đi
     * @param duration Thời gian (ngày)
     * @param maxGroupSize Số người tối đa
     * @param difficulty Độ khó
     * @param price Giá (VND)
     * @param summary Tóm tắt
     * @param description Mô tả chi tiết
     * @param _imagePath Đường dẫn ảnh
     */
    Trip(int tripId, const QString& tripName, int duration, int maxGroupSize, const QString& difficulty,
         int price, const QString& summary, const QString& description, const QString& _imagePath);

    /**
     * @brief Lấy ID chuyến đi
     * @return int ID của chuyến đi
     */
    int getTripId() const;

    /**
     * @brief Lấy tên chuyến đi
     * @return QString Tên của chuyến đi
     */
    QString getTripName() const;

    /**
     * @brief Lấy thời gian chuyến đi
     * @return int Số ngày của chuyến đi
     */
    int getDuration() const;

    /**
     * @brief Lấy số người tối đa
     * @return int Số người tối đa trong nhóm
     */
    int getMaxGroupSize() const;

    /**
     * @brief Lấy độ khó của chuyến đi
     * @return QString Độ khó (Easy/Medium/Hard)
     */
    QString getDifficulty() const;

    /**
     * @brief Lấy giá chuyến đi
     * @return int Giá (VND)
     */
    int getPrice() const;

    /**
     * @brief Lấy tóm tắt chuyến đi
     * @return QString Tóm tắt ngắn gọn
     */
    QString getSummary() const;

    /**
     * @brief Lấy mô tả chi tiết
     * @return QString Mô tả đầy đủ
     */
    QString getDescription() const;

    /**
     * @brief Lấy đường dẫn ảnh
     * @return QString Đường dẫn đến ảnh đại diện
     */
    QString getImagePath() const;

    /**
     * @brief Cập nhật tên chuyến đi
     * @param tripName Tên mới
     */
    void setTripName(const QString& tripName);

    /**
     * @brief Cập nhật thời gian
     * @param duration Số ngày mới
     */
    void setDuration(int duration);

    /**
     * @brief Cập nhật số người tối đa
     * @param maxGroupSize Số người tối đa mới
     */
    void setMaxGroupSize(int maxGroupSize);

    /**
     * @brief Cập nhật độ khó
     * @param difficulty Độ khó mới
     */
    void setDifficulty(const QString& difficulty);

    /**
     * @brief Cập nhật giá
     * @param price Giá mới (VND)
     */
    void setPrice(int price);

    /**
     * @brief Cập nhật tóm tắt
     * @param summary Tóm tắt mới
     */
    void setSummary(const QString& summary);

    /**
     * @brief Cập nhật mô tả
     * @param description Mô tả mới
     */
    void setDescription(const QString& description);

    /**
     * @brief Cập nhật đường dẫn ảnh
     * @param imagePath Đường dẫn mới
     */
    void setImagePath(const QString& imagePath);
};

#endif // TRIP_H

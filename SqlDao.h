/**
 * @file SqlDao.h
 * @brief Triển khai IDataProvider interface cho SQL database
 * 
 * Class này đóng vai trò là Data Access Object (DAO) cho SQL:
 * - Quản lý các repository cho từng entity
 * - Cung cấp truy cập đến các repository
 * - Đảm bảo tính nhất quán của dữ liệu
 * - Tập trung quản lý kết nối database
 */

#ifndef SQLDAO_H
#define SQLDAO_H

#include "IDataProvider.h"
#include "DatabaseManager.h"
#include "SqlTripRepository.h"
#include "SqlUserRepository.h"
#include "SqlBookingRepository.h"
#include "SqlReviewRepository.h"

/**
 * @brief Class triển khai IDataProvider cho SQL database
 * 
 * Class này:
 * - Kế thừa interface IDataProvider
 * - Sử dụng DatabaseManager để quản lý kết nối
 * - Tạo và quản lý các SQL repository
 * - Đảm bảo tính nhất quán của dữ liệu
 */
class SqlDao : public IDataProvider {
private:
    DatabaseManager& _dbManager;  ///< Tham chiếu đến DatabaseManager singleton

public:
    /**
     * @brief Constructor với DatabaseManager
     * 
     * @param db Tham chiếu đến DatabaseManager singleton
     */
    explicit SqlDao(DatabaseManager& db);

    /**
     * @brief Destructor mặc định
     */
    ~SqlDao() = default;

    /**
     * @brief Lấy repository quản lý chuyến đi
     * 
     * @return QSharedPointer<TripRepository> Con trỏ thông minh đến TripRepository
     * 
     * @note Repository được tạo mới mỗi lần gọi để tránh lưu trạng thái
     */
    QSharedPointer<TripRepository> getTripRepository() const override;

    /**
     * @brief Lấy repository quản lý người dùng
     * 
     * @return QSharedPointer<UserRepository> Con trỏ thông minh đến UserRepository
     * 
     * @note Repository được tạo mới mỗi lần gọi để tránh lưu trạng thái
     */
    QSharedPointer<UserRepository> getUserRepository() const override;

    /**
     * @brief Lấy repository quản lý đặt chỗ
     * 
     * @return QSharedPointer<BookingRepository> Con trỏ thông minh đến BookingRepository
     * 
     * @note Repository được tạo mới mỗi lần gọi để tránh lưu trạng thái
     */
    QSharedPointer<BookingRepository> getBookingRepository() const override;

    /**
     * @brief Lấy repository quản lý đánh giá
     * 
     * @return QSharedPointer<ReviewRepository> Con trỏ thông minh đến ReviewRepository
     * 
     * @note Repository được tạo mới mỗi lần gọi để tránh lưu trạng thái
     */
    QSharedPointer<ReviewRepository> getReviewRepository() const override;
};

#endif // SQLDAO_H

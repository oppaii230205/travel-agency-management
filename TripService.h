/**
 * @file TripService.h
 * @brief Service xử lý logic nghiệp vụ cho các chuyến đi
 * 
 * Service này cung cấp:
 * - Các thao tác CRUD cơ bản với chuyến đi
 * - Các phương thức tìm kiếm và lọc chuyến đi
 * - Xử lý logic nghiệp vụ và validation
 * - Phát signal khi có thay đổi dữ liệu
 */

#ifndef TRIPSERVICE_H
#define TRIPSERVICE_H

#include <QObject>
#include <QList>
#include "Trip.h"
#include "TripRepository.h"
#include "constants.h"

/**
 * @brief Service xử lý các thao tác và logic nghiệp vụ liên quan đến chuyến đi
 * 
 * Class này kế thừa từ QObject và:
 * - Đóng gói các thao tác với repository
 * - Thêm các logic nghiệp vụ (validation, tìm kiếm, lọc)
 * - Phát các signal thông báo thay đổi dữ liệu
 * - Đảm bảo tính toàn vẹn dữ liệu
 */
class TripService : public QObject
{
    Q_OBJECT

public:
    /**
     * @brief Constructor khởi tạo service quản lý chuyến đi
     * @param repository Con trỏ đến repository xử lý dữ liệu chuyến đi
     * @param parent QObject cha (mặc định là nullptr)
     */
    explicit TripService(QSharedPointer<TripRepository> repository, QObject* parent = nullptr);

    // Basic CRUD operations
    /**
     * @brief Lấy danh sách tất cả các chuyến đi
     * @return QList<Trip> Danh sách các chuyến đi
     */
    QList<Trip> getAllTrips();

    /**
     * @brief Lấy thông tin một chuyến đi theo ID
     * @param tripId ID của chuyến đi cần tìm
     * @return Trip Thông tin chuyến đi
     */
    Trip getTripById(int tripId);

    /**
     * @brief Tạo một chuyến đi mới
     * @param trip Thông tin chuyến đi cần tạo
     * @return true nếu tạo thành công, false nếu thất bại
     */
    bool createTrip(const Trip& trip);

    /**
     * @brief Cập nhật thông tin một chuyến đi
     * @param trip Thông tin chuyến đi cần cập nhật
     * @return true nếu cập nhật thành công, false nếu thất bại
     */
    bool updateTrip(const Trip& trip);

    /**
     * @brief Xóa một chuyến đi
     * @param tripId ID của chuyến đi cần xóa
     * @return true nếu xóa thành công, false nếu thất bại
     */
    bool deleteTrip(int tripId);

    // Business logic methods
    /**
     * @brief Tìm các chuyến đi theo mức độ khó
     * @param difficulty Mức độ khó cần tìm
     * @return QList<Trip> Danh sách các chuyến đi phù hợp
     */
    QList<Trip> findTripsByDifficulty(const QString& difficulty);

    /**
     * @brief Tìm các chuyến đi trong khoảng giá
     * @param minPrice Giá thấp nhất
     * @param maxPrice Giá cao nhất
     * @return QList<Trip> Danh sách các chuyến đi phù hợp
     */
    QList<Trip> findTripsInPriceRange(int minPrice, int maxPrice);

    /**
     * @brief Kiểm tra tên chuyến đi đã tồn tại chưa
     * @param tripName Tên chuyến đi cần kiểm tra
     * @return true nếu tên chưa được sử dụng, false nếu đã tồn tại
     */
    bool isTripNameAvailable(const QString& tripName) const;

signals:
    /**
     * @brief Signal phát ra khi có chuyến đi mới được thêm
     * @param newTrip Thông tin chuyến đi mới
     */
    void tripAdded(const Trip& newTrip);

    /**
     * @brief Signal phát ra khi có chuyến đi được cập nhật
     * @param updatedTrip Thông tin chuyến đi sau khi cập nhật
     */
    void tripUpdated(const Trip& updatedTrip);

    /**
     * @brief Signal phát ra khi có chuyến đi bị xóa
     * @param tripId ID của chuyến đi bị xóa
     */
    void tripDeleted(int tripId);

    /**
     * @brief Signal phát ra khi có lỗi xảy ra
     * @param errorMessage Thông báo lỗi
     */
    void errorOccurred(const QString& errorMessage);

private:
    QSharedPointer<TripRepository> _repository; ///< Repository xử lý dữ liệu chuyến đi

    /**
     * @brief Kiểm tra tính hợp lệ của thông tin chuyến đi
     * @param trip Thông tin chuyến đi cần kiểm tra
     * @return true nếu thông tin hợp lệ, false nếu không hợp lệ
     */
    bool validateTrip(const Trip& trip) const;
};

#endif // TRIPSERVICE_H

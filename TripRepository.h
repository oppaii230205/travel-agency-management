/**
 * @file TripRepository.h
 * @brief Interface định nghĩa các thao tác với dữ liệu chuyến đi
 * 
 * Interface này định nghĩa các phương thức cơ bản để:
 * - Truy xuất thông tin chuyến đi
 * - Thêm chuyến đi mới
 * - Cập nhật thông tin chuyến đi
 * - Xóa chuyến đi
 */

#ifndef TRIPREPOSITORY_H
#define TRIPREPOSITORY_H

#include <QList>
#include "Trip.h"

/**
 * @brief Interface cho repository quản lý dữ liệu chuyến đi
 * 
 * Interface này định nghĩa các phương thức ảo thuần túy để:
 * - Thực hiện các thao tác CRUD với dữ liệu chuyến đi
 * - Cho phép thay đổi implementation của repository (ví dụ: SQL, NoSQL, File,...)
 * - Đảm bảo tính loose coupling trong hệ thống
 */
class TripRepository {
public:
    /**
     * @brief Destructor ảo mặc định
     */
    virtual ~TripRepository() = default;

    /**
     * @brief Lấy danh sách tất cả các chuyến đi
     * @return QList<Trip> Danh sách các chuyến đi
     */
    virtual QList<Trip> getAllTrips() = 0;

    /**
     * @brief Lấy thông tin một chuyến đi theo ID
     * @param id ID của chuyến đi cần tìm
     * @return Trip Thông tin chuyến đi
     */
    virtual Trip getTripById(int id) = 0;

    /**
     * @brief Thêm một chuyến đi mới
     * @param trip Thông tin chuyến đi cần thêm
     * @return true nếu thêm thành công, false nếu thất bại
     */
    virtual bool addTrip(const Trip& trip) = 0;

    /**
     * @brief Cập nhật thông tin một chuyến đi
     * @param trip Thông tin chuyến đi cần cập nhật (ID phải tồn tại)
     * @return true nếu cập nhật thành công, false nếu thất bại
     */
    virtual bool updateTrip(const Trip& trip) = 0;

    /**
     * @brief Xóa một chuyến đi
     * @param id ID của chuyến đi cần xóa
     * @return true nếu xóa thành công, false nếu thất bại
     */
    virtual bool deleteTrip(int id) = 0;
};

#endif // TRIPREPOSITORY_H

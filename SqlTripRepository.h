/**
 * @file SqlTripRepository.h
 * @brief Triển khai TripRepository interface sử dụng SQL database
 * 
 * Class này cung cấp các thao tác với chuyến đi thông qua:
 * - Kết nối SQL database
 * - Thực thi các câu query
 * - Ánh xạ kết quả sang đối tượng Trip
 * - Quản lý CRUD cho chuyến đi
 */

#ifndef SQLTRIPREPOSITORY_H
#define SQLTRIPREPOSITORY_H

#include "TripRepository.h"
#include "DatabaseManager.h"

/**
 * @brief Class triển khai TripRepository sử dụng SQL database
 * 
 * Class này:
 * - Kế thừa interface TripRepository
 * - Sử dụng DatabaseManager để kết nối database
 * - Thực hiện các thao tác CRUD với bảng trips
 * - Quản lý toàn bộ vòng đời của chuyến đi
 */
class SqlTripRepository : public TripRepository {
public:
    /**
     * @brief Constructor với DatabaseManager
     * 
     * @param dbManager Tham chiếu đến DatabaseManager singleton
     */
    explicit SqlTripRepository(DatabaseManager& dbManager);

    /**
     * @brief Lấy danh sách tất cả các chuyến đi
     * 
     * @return QList<Trip> Danh sách các chuyến đi
     * 
     * @note Trả về danh sách rỗng nếu không có chuyến đi nào
     */
    QList<Trip> getAllTrips() override;

    /**
     * @brief Lấy thông tin một chuyến đi theo ID
     * 
     * @param id ID của chuyến đi cần lấy thông tin
     * @return Trip Đối tượng Trip chứa thông tin chuyến đi
     * 
     * @note Trả về Trip rỗng nếu không tìm thấy chuyến đi
     */
    Trip getTripById(int id) override;

    /**
     * @brief Thêm một chuyến đi mới vào database
     * 
     * @param trip Đối tượng Trip cần thêm
     * @return true nếu thêm thành công
     * @return false nếu có lỗi (ví dụ: vi phạm ràng buộc)
     */
    bool addTrip(const Trip& trip) override;

    /**
     * @brief Cập nhật thông tin một chuyến đi
     * 
     * @param trip Đối tượng Trip chứa thông tin cần cập nhật
     * @return true nếu cập nhật thành công
     * @return false nếu không tìm thấy chuyến đi hoặc có lỗi
     */
    bool updateTrip(const Trip& trip) override;

    /**
     * @brief Xóa một chuyến đi khỏi database
     * 
     * @param id ID của chuyến đi cần xóa
     * @return true nếu xóa thành công
     * @return false nếu không tìm thấy chuyến đi hoặc có lỗi
     * 
     * @note Việc xóa có thể thất bại nếu có các ràng buộc khóa ngoại
     */
    bool deleteTrip(int id) override;

private:
    DatabaseManager& _dbManager;  ///< Tham chiếu đến DatabaseManager singleton
};

#endif // SQLTRIPREPOSITORY_H

/**
 * @file constants.h
 * @brief Định nghĩa các hằng số được sử dụng trong toàn bộ ứng dụng
 */

#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <QString>

/**
 * @brief Giá trị số 0, được sử dụng làm giá trị mặc định hoặc giá trị khởi tạo
 */
constexpr int zero = 0;

/**
 * @brief Độ dài tối thiểu của mật khẩu người dùng
 * 
 * Được sử dụng để validate mật khẩu khi đăng ký và đăng nhập.
 * Giá trị hiện tại là 6 ký tự.
 */
constexpr int minPasswordLength = 6;

/**
 * @brief Thời gian tối thiểu của một chuyến đi (tính bằng ngày)
 * 
 * Được sử dụng để validate thời gian khi tạo hoặc cập nhật chuyến đi.
 * Giá trị hiện tại là 0 ngày.
 */
constexpr int minTripDuration = 0;

/**
 * @brief Giá tiền tối thiểu của một chuyến đi
 * 
 * Được sử dụng để validate giá tiền khi tạo hoặc cập nhật chuyến đi.
 * Giá trị hiện tại là 0 (đơn vị tiền tệ).
 */
constexpr int minTripPrice = 0;

/**
 * @brief Khóa mã hóa được sử dụng trong ứng dụng
 * 
 * Khóa này được sử dụng để:
 * - Mã hóa thông tin nhạy cảm
 * - Xác thực dữ liệu
 * - Bảo mật thông tin người dùng
 * 
 * @warning Không nên thay đổi giá trị này sau khi đã có dữ liệu được mã hóa
 */
const QString eKey = "mykey-hcmus-oop-travelagency-pro";

#endif // CONSTANTS_H

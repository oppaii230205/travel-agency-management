/**
 * @file CustomMessageBox.h
 * @brief Class cung cấp hộp thoại thông báo tùy chỉnh với giao diện đẹp
 */

#ifndef CUSTOMMESSAGEBOX_H
#define CUSTOMMESSAGEBOX_H

#include <QMessageBox>

/**
 * @brief Class kế thừa từ QMessageBox, cung cấp hộp thoại thông báo với style tùy chỉnh
 * 
 * Class này cung cấp các phương thức static để hiển thị:
 * - Hộp thoại thông báo đơn giản
 * - Hộp thoại xác nhận với các nút tùy chọn
 * 
 * Tất cả các hộp thoại đều được áp dụng style tùy chỉnh thống nhất
 */
class CustomMessageBox : public QMessageBox {
    Q_OBJECT
public:
    /**
     * @brief Hiển thị hộp thoại thông báo đơn giản
     * 
     * Phương thức này tạo và hiển thị một hộp thoại thông báo
     * với một nút OK và style tùy chỉnh.
     * 
     * @param title Tiêu đề của hộp thoại
     * @param message Nội dung thông báo
     * @param parent Widget cha (mặc định là nullptr)
     */
    static void show(const QString& title, const QString& message, QWidget* parent = nullptr);

    /**
     * @brief Hiển thị hộp thoại xác nhận với các nút tùy chọn
     * 
     * Phương thức này tạo và hiển thị một hộp thoại xác nhận
     * cho phép người dùng chọn một trong các tùy chọn được cung cấp.
     * 
     * @param title Tiêu đề của hộp thoại
     * @param message Nội dung câu hỏi
     * @param parent Widget cha (mặc định là nullptr)
     * @param buttons Các nút tùy chọn (mặc định là Yes|No)
     * @return StandardButton Nút được người dùng chọn
     */
    static StandardButton question(const QString& title, const QString& message, 
                                 QWidget* parent = nullptr, 
                                 StandardButtons buttons = Yes|No);

private:
    /**
     * @brief Constructor riêng cho CustomMessageBox
     * 
     * Constructor này được đặt ở private để đảm bảo class chỉ được
     * sử dụng thông qua các phương thức static.
     * 
     * @param parent Widget cha (mặc định là nullptr)
     */
    explicit CustomMessageBox(QWidget* parent = nullptr);

    /**
     * @brief Áp dụng style tùy chỉnh cho hộp thoại
     * 
     * Phương thức này áp dụng các style như:
     * - Màu sắc và font chữ
     * - Kích thước và padding
     * - Style cho các nút
     * - Hiệu ứng hover và focus
     * 
     * @param msgBox Hộp thoại cần áp dụng style
     */
    static void applyStyle(QMessageBox& msgBox);
};

#endif // CUSTOMMESSAGEBOX_H

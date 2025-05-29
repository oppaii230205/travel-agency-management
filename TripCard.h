/**
 * @file TripCard.h
 * @brief Widget hiển thị thông tin chuyến đi dưới dạng thẻ
 * 
 * Class này định nghĩa một widget tùy chỉnh để hiển thị:
 * - Thông tin cơ bản của chuyến đi
 * - Giao diện tương tác cho người dùng
 * - Xử lý sự kiện click cho đặt vé và xem chi tiết
 */

#ifndef _TRIP_CARD_H_
#define _TRIP_CARD_H_

#include <QWidget>
#include "Trip.h"
#include <QNetworkAccessManager>
#include <QLabel>
#include <QNetworkReply>

/**
 * @brief Class widget hiển thị thông tin chuyến đi dưới dạng thẻ
 * 
 * TripCard là một widget tùy chỉnh kế thừa từ QWidget, được sử dụng để:
 * - Hiển thị thông tin chuyến đi theo định dạng thẻ
 * - Cung cấp các nút tương tác (đặt vé, xem chi tiết)
 * - Xử lý các sự kiện người dùng
 * 
 * Thẻ này hiển thị các thông tin:
 * - Hình ảnh chuyến đi
 * - Tên chuyến đi
 * - Giá
 * - Độ khó
 * - Thời gian
 * - Các nút tương tác
 */
class TripCard : public QWidget
{
    Q_OBJECT
public:
    /**
     * @brief Constructor khởi tạo thẻ chuyến đi
     * @param trip Thông tin chuyến đi cần hiển thị
     * @param parent Widget cha (mặc định là nullptr)
     * 
     * Constructor này sẽ:
     * - Khởi tạo giao diện thẻ
     * - Thiết lập các hiệu ứng (shadow, hover)
     * - Kết nối các signals và slots
     */
    explicit TripCard(const Trip& trip, QWidget *parent = nullptr);

    /**
     * @brief Xử lý sự kiện từ các đối tượng con
     * @param obj Đối tượng phát sinh sự kiện
     * @param event Sự kiện cần xử lý
     * @return true nếu sự kiện đã được xử lý, false nếu ngược lại
     * 
     * Phương thức này xử lý:
     * - Sự kiện hover để tạo hiệu ứng nổi
     * - Animation khi di chuột vào/ra
     * - Các sự kiện tương tác khác
     */
    bool eventFilter(QObject *obj, QEvent *event) override;

signals:
    /**
     * @brief Signal phát sinh khi người dùng nhấn nút đặt vé
     * @param tripId ID của chuyến đi được chọn
     * 
     * Signal này được kết nối với slot xử lý đặt vé trong main window
     */
    void bookClicked(int tripId);

    /**
     * @brief Signal phát sinh khi người dùng nhấn nút xem chi tiết
     * @param tripId ID của chuyến đi được chọn
     * 
     * Signal này được kết nối với slot hiển thị dialog chi tiết chuyến đi
     */
    void detailsClicked(int tripId);

protected:
    int _tripId; ///< ID của chuyến đi đang hiển thị

private:
    QNetworkAccessManager* _networkManager; ///< Manager xử lý các request tải ảnh từ mạng

    /**
     * @brief Tải và hiển thị ảnh từ URL
     * @param url URL của ảnh cần tải
     * @param imageLabel Label để hiển thị ảnh
     * 
     * Phương thức này sẽ:
     * - Tải ảnh từ URL qua network
     * - Scale ảnh về kích thước phù hợp
     * - Hiển thị lên label được chỉ định
     */
    void loadImageFromUrl(const QString &url, QLabel *imageLabel);

    /**
     * @brief Tải và hiển thị ảnh mặc định
     * @param imageLabel Label để hiển thị ảnh
     * 
     * Được gọi khi:
     * - Không có URL ảnh
     * - Lỗi khi tải ảnh từ URL
     * - URL ảnh không hợp lệ
     */
    void loadDefaultImage(QLabel *imageLabel);
};

#endif

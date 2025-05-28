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
 */
class TripCard : public QWidget
{
    Q_OBJECT
public:
    /**
     * @brief Constructor khởi tạo thẻ chuyến đi
     * @param trip Thông tin chuyến đi cần hiển thị
     * @param parent Widget cha (mặc định là nullptr)
     */
    explicit TripCard(const Trip& trip, QWidget *parent = nullptr);

    /**
     * @brief Xử lý sự kiện từ các đối tượng con
     * @param obj Đối tượng phát sinh sự kiện
     * @param event Sự kiện cần xử lý
     * @return true nếu sự kiện đã được xử lý, false nếu ngược lại
     */
    bool eventFilter(QObject *obj, QEvent *event) override;

signals:
    /**
     * @brief Signal phát sinh khi người dùng nhấn nút đặt vé
     * @param tripId ID của chuyến đi được chọn
     */
    void bookClicked(int tripId);

    /**
     * @brief Signal phát sinh khi người dùng nhấn nút xem chi tiết
     * @param tripId ID của chuyến đi được chọn
     */
    void detailsClicked(int tripId);

protected:
    int _tripId; ///< ID của chuyến đi đang hiển thị

private:
    QNetworkAccessManager* _networkManager;

    void loadImageFromUrl(const QString &url, QLabel *imageLabel);
    void loadDefaultImage(QLabel *imageLabel);
};

#endif

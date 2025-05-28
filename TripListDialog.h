/**
 * @file TripListDialog.h
 * @brief Dialog hiển thị danh sách các chuyến đi
 * 
 * Dialog này kế thừa từ BaseTripDialog và cung cấp:
 * - Hiển thị danh sách các chuyến đi dưới dạng grid
 * - Xử lý tương tác người dùng với các thẻ chuyến đi
 * - Quản lý việc đặt vé cho chuyến đi
 */

#ifndef TRIPLISTDIALOG_H
#define TRIPLISTDIALOG_H

#include "BaseTripDialog.h"

namespace Ui {
class TripListDialog;
}

/**
 * @brief Dialog hiển thị và quản lý danh sách các chuyến đi
 * 
 * Class này kế thừa từ BaseTripDialog và:
 * - Hiển thị các chuyến đi dưới dạng lưới các thẻ (TripCard)
 * - Cho phép người dùng xem chi tiết và đặt vé cho từng chuyến đi
 * - Tùy chỉnh cách hiển thị và xử lý sự kiện cho mỗi thẻ chuyến đi
 */
class TripListDialog : public BaseTripDialog
{
    Q_OBJECT

public:
    /**
     * @brief Constructor khởi tạo dialog danh sách chuyến đi
     * @param tripService Service xử lý các thao tác với chuyến đi
     * @param bookingService Service xử lý các thao tác đặt vé
     * @param reviewService Service xử lý các thao tác đánh giá
     * @param parent Widget cha (mặc định là nullptr)
     */
    explicit TripListDialog(QSharedPointer<TripService> tripService,
                          QSharedPointer<BookingService> bookingService,
                          QSharedPointer<ReviewService> reviewService,
                          QWidget *parent = nullptr);

protected:
    /**
     * @brief Lấy tiêu đề cho cửa sổ dialog
     * @return QString chứa tiêu đề của dialog
     */
    QString getWindowTitle() const override;

    /**
     * @brief Lấy danh sách các chuyến đi cần hiển thị
     * @return QList<Trip> danh sách các chuyến đi
     */
    QList<Trip> getTripsToDisplay() override;

    /**
     * @brief Tạo một thẻ chuyến đi mới
     * @param trip Thông tin chuyến đi cần hiển thị
     * @return Con trỏ đến TripCard mới được tạo
     */
    TripCard* createTripCard(const Trip& trip) override;

    /**
     * @brief Hook method được gọi sau khi tạo mỗi thẻ chuyến đi
     * @param card Con trỏ đến thẻ chuyến đi vừa được tạo
     * @param trip Thông tin chuyến đi được hiển thị
     */
    void onTripCardCreated(TripCard* card, const Trip& trip) override;

private slots:
    /**
     * @brief Slot xử lý sự kiện khi người dùng nhấn nút đặt vé
     * @param tripId ID của chuyến đi được chọn để đặt vé
     */
    void handleBookClicked(int tripId);
};

#endif // TRIPLISTDIALOG_H

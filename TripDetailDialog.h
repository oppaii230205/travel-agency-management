/**
 * @file TripDetailDialog.h
 * @brief Dialog hiển thị chi tiết chuyến đi và quản lý đánh giá
 * 
 * Dialog này cung cấp giao diện để:
 * - Hiển thị thông tin chi tiết của một chuyến đi
 * - Cho phép người dùng xem các đánh giá hiện có
 * - Cho phép người dùng thêm đánh giá mới
 * 
 * Dialog này sử dụng:
 * - QDialog làm base class
 * - ReviewService để quản lý đánh giá
 * - QNetworkAccessManager để tải ảnh từ cloud
 */

#include <QDialog>
#include "Trip.h"

#include "ReviewService.h"
#include <QFormLayout>
#include <QComboBox>
#include <QTextEdit>
#include <QMessageBox>
#include <QNetworkAccessManager>
#include <QNetworkReply>

class QLabel;
class QScrollArea;

/**
 * @brief Dialog hiển thị thông tin chi tiết chuyến đi và quản lý đánh giá
 * 
 * Class này kế thừa từ QDialog và cung cấp:
 * - Hiển thị đầy đủ thông tin của chuyến đi (hình ảnh, tiêu đề, giá, độ khó,...)
 * - Giao diện để xem các đánh giá từ người dùng khác
 * - Form để thêm đánh giá mới
 * 
 * Các tính năng chính:
 * - Hiển thị hình ảnh chuyến đi với khả năng tải từ cloud
 * - Hiển thị thông tin chi tiết với layout tối ưu
 * - Quản lý và hiển thị đánh giá theo thời gian thực
 * - Cho phép người dùng thêm đánh giá mới với rating và comment
 */
class TripDetailDialog : public QDialog
{
    Q_OBJECT
public:
    /**
     * @brief Constructor khởi tạo dialog chi tiết chuyến đi
     * @param trip Thông tin chuyến đi cần hiển thị
     * @param reviewService Service xử lý các thao tác với đánh giá
     * @param parent Widget cha (mặc định là nullptr)
     * 
     * Constructor này sẽ:
     * - Khởi tạo giao diện dialog
     * - Thiết lập kết nối với ReviewService
     * - Tải và hiển thị thông tin chuyến đi
     * - Tải các đánh giá hiện có
     */
    explicit TripDetailDialog(const Trip& trip,
                              QSharedPointer<ReviewService> reviewService,
                              QWidget *parent = nullptr);

private slots:
    /**
     * @brief Slot xử lý khi người dùng gửi đánh giá mới
     * 
     * Xử lý:
     * - Kiểm tra tính hợp lệ của đánh giá
     * - Lưu đánh giá thông qua ReviewService
     * - Cập nhật giao diện hiển thị đánh giá
     * - Hiển thị thông báo thành công/thất bại
     */
    void onSubmitReview();

    /**
     * @brief Slot cập nhật giao diện phần đánh giá
     * 
     * Thực hiện:
     * - Tải lại danh sách đánh giá mới nhất
     * - Cập nhật hiển thị các đánh giá
     * - Làm mới form nhập đánh giá
     */
    void updateReviewUI();

private:
    /**
     * @brief Thiết lập giao diện người dùng
     * 
     * Khởi tạo và cấu hình:
     * - Layout tổng thể của dialog
     * - Phần hiển thị thông tin chuyến đi
     * - Phần hiển thị và nhập đánh giá
     * - Các nút tương tác
     */
    void setupUI();

    /**
     * @brief Tải và áp dụng styles cho dialog
     * 
     * Đọc và áp dụng:
     * - CSS từ file resource
     * - Style cho các thành phần UI
     * - Hiệu ứng và animation
     */
    void loadStyles();

    /**
     * @brief Thiết lập form nhập đánh giá
     * 
     * Tạo và cấu hình:
     * - ComboBox chọn số sao
     * - TextEdit nhập nội dung đánh giá
     * - Nút gửi đánh giá
     * - Kiểm tra quyền đánh giá của user
     */
    void setupReviewForm();

    /**
     * @brief Tải và hiển thị các đánh giá hiện có
     * 
     * Thực hiện:
     * - Lấy danh sách đánh giá từ service
     * - Tạo widget hiển thị cho mỗi đánh giá
     * - Sắp xếp theo thời gian
     * - Hiển thị thông báo nếu chưa có đánh giá
     */
    void loadExistingReviews();

    /**
     * @brief Tải ảnh từ URL và hiển thị
     * @param url URL của ảnh cần tải
     * @param imageLabel Label để hiển thị ảnh
     * 
     * Xử lý:
     * - Tải ảnh từ URL qua network
     * - Scale ảnh về kích thước phù hợp
     * - Xử lý lỗi khi tải ảnh
     */
    void loadImageFromUrl(const QString &url, QLabel *imageLabel);

    /**
     * @brief Tải ảnh mặc định khi không có ảnh hoặc lỗi tải
     * @param imageLabel Label để hiển thị ảnh
     * 
     * Được gọi khi:
     * - URL ảnh không hợp lệ
     * - Lỗi khi tải ảnh từ network
     * - Không có ảnh được chỉ định
     */
    void loadDefaultImage(QLabel *imageLabel);

    const Trip& _trip; ///< Thông tin chuyến đi đang hiển thị
    QSharedPointer<ReviewService> _reviewService; ///< Service xử lý các thao tác với đánh giá

    // Labels hiển thị thông tin chuyến đi
    QLabel* _imageLabel; ///< Label hiển thị hình ảnh chuyến đi
    QLabel* _titleLabel; ///< Label hiển thị tiêu đề
    QLabel* _priceLabel; ///< Label hiển thị giá
    QLabel* _difficultyLabel; ///< Label hiển thị độ khó
    QLabel* _durationLabel; ///< Label hiển thị thời gian
    QLabel* _summaryLabel; ///< Label hiển thị tóm tắt
    QLabel* _descriptionLabel; ///< Label hiển thị mô tả chi tiết

    // Widgets cho phần đánh giá
    QWidget* _reviewFormContainer; ///< Container chứa form đánh giá
    QComboBox* _ratingComboBox; ///< Combobox chọn số sao đánh giá
    QTextEdit* _reviewTextEdit; ///< Textbox nhập nội dung đánh giá
    QPushButton* _submitReviewButton; ///< Nút gửi đánh giá

    QWidget* _reviewsContainer; ///< Container hiển thị danh sách đánh giá

    QNetworkAccessManager* _networkManager; ///< Manager xử lý các request mạng
};

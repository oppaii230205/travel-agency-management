/**
 * @file TripDetailDialog.h
 * @brief Dialog hiển thị chi tiết chuyến đi và quản lý đánh giá
 * 
 * Dialog này cung cấp giao diện để:
 * - Hiển thị thông tin chi tiết của một chuyến đi
 * - Cho phép người dùng xem các đánh giá hiện có
 * - Cho phép người dùng thêm đánh giá mới
 */

#include <QDialog>
#include "Trip.h"

#include "ReviewService.h"
#include <QFormLayout>
#include <QComboBox>
#include <QTextEdit>
#include <QMessageBox>

class QLabel;
class QScrollArea;

/**
 * @brief Dialog hiển thị thông tin chi tiết chuyến đi và quản lý đánh giá
 * 
 * Class này kế thừa từ QDialog và cung cấp:
 * - Hiển thị đầy đủ thông tin của chuyến đi (hình ảnh, tiêu đề, giá, độ khó,...)
 * - Giao diện để xem các đánh giá từ người dùng khác
 * - Form để thêm đánh giá mới
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
     */
    explicit TripDetailDialog(const Trip& trip,
                              QSharedPointer<ReviewService> reviewService,
                              QWidget *parent = nullptr);

private slots:
    /**
     * @brief Slot xử lý khi người dùng gửi đánh giá mới
     */
    void onSubmitReview();
    /**
     * @brief Slot cập nhật giao diện phần đánh giá
     */
    void updateReviewUI();

private:
    /**
     * @brief Thiết lập giao diện người dùng
     */
    void setupUI();
    /**
     * @brief Tải và áp dụng styles cho dialog
     */
    void loadStyles();
    /**
     * @brief Thiết lập form nhập đánh giá
     */
    void setupReviewForm();
    /**
     * @brief Tải và hiển thị các đánh giá hiện có
     */
    void loadExistingReviews();

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
};

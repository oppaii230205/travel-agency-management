#ifndef _ADDTRIPDIALOG_H_
#define _ADDTRIPDIALOG_H_

#include <QDialog>
#include <QSharedPointer>
#include "Trip.h"
#include "TripService.h"
#include "AzureStorageService.h"


namespace Ui {
class AddTripDialog;
}

/**
 * @brief Dialog cho phép thêm một chuyến đi mới vào hệ thống
 * 
 * Dialog này cung cấp giao diện người dùng để nhập thông tin cho một chuyến đi mới,
 * bao gồm tên, thời gian, kích thước nhóm, độ khó, giá và mô tả.
 */
class AddTripDialog : public QDialog
{
    Q_OBJECT

public:
    /**
     * @brief Constructor cho AddTripDialog
     * @param service Con trỏ thông minh đến TripService để thao tác với dữ liệu chuyến đi
     * @param parent Widget cha (mặc định là nullptr)
     */
    explicit AddTripDialog(QSharedPointer<TripService> tripService, QSharedPointer<AzureStorageService> storageService, QWidget* parent = nullptr);

    /**
     * @brief Destructor
     */
    ~AddTripDialog();

private slots:
    /**
     * @brief Xử lý sự kiện khi nút Save được click
     * 
     * Kiểm tra tính hợp lệ của dữ liệu nhập vào và tạo một chuyến đi mới
     * thông qua TripService nếu dữ liệu hợp lệ.
     */
    void on_btnSave_clicked();
    void on_btnChooseImage_clicked();
    void onImageUploaded(const QString& imageUrl);

    /**
     * @brief Xử lý sự kiện khi nút Cancel được click
     * 
     * Đóng dialog và hủy thao tác thêm chuyến đi mới.
     */
    void on_btnCancel_clicked();

signals:
    void imageUploaded(const QString& imageUrl);

private:
    /**
     * @brief Thiết lập giao diện người dùng
     * 
     * Khởi tạo và cấu hình các thành phần giao diện như layout,
     * các widget nhập liệu, và style của dialog.
     */
    QString _tempImagePath; // Đường dẫn tạm thời của ảnh
    QString _uploadedImageUrl;
    QSharedPointer<AzureStorageService> _storageService;

    void setupUI();

    Ui::AddTripDialog* ui;                    ///< Con trỏ đến UI được tạo bởi Qt Designer
    QSharedPointer<TripService> _tripService; ///< Service xử lý các thao tác với chuyến đi
};
#endif

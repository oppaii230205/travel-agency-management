/**
 * @file ShowUserInformationDialog.h
 * @brief Dialog hiển thị và chỉnh sửa thông tin người dùng
 * 
 * Dialog này cho phép:
 * - Xem thông tin cá nhân của người dùng
 * - Cập nhật thông tin cơ bản
 * - Thay đổi và tải lên ảnh đại diện
 * - Xem trước ảnh đại diện
 */

#ifndef SHOWUSERINFORMATIONDIALOG_H
#define SHOWUSERINFORMATIONDIALOG_H

#include <QDialog>
#include <QSharedPointer>
#include "UserService.h"
#include "AzureStorageService.h"

namespace Ui {
class ShowUserInformationDialog;
}

/**
 * @brief Dialog hiển thị và chỉnh sửa thông tin người dùng
 * 
 * Dialog này cung cấp giao diện để:
 * - Hiển thị thông tin cá nhân
 * - Cập nhật thông tin cơ bản
 * - Quản lý ảnh đại diện (upload/preview)
 * - Lưu thay đổi thông tin
 */
class ShowUserInformationDialog : public QDialog
{
    Q_OBJECT

public:
    /**
     * @brief Constructor với đầy đủ dependencies
     * 
     * @param userService Service quản lý thông tin người dùng
     * @param storageService Service lưu trữ ảnh đại diện
     * @param email Email của người dùng cần hiển thị thông tin
     * @param parent Widget cha (mặc định là nullptr)
     */
    explicit ShowUserInformationDialog(QSharedPointer<UserService> userService,
                                       QSharedPointer<AzureStorageService> storageService,
                                       const QString& email,
                                       QWidget* parent = nullptr);

    /**
     * @brief Destructor
     */
    ~ShowUserInformationDialog();

private slots:
    /**
     * @brief Xử lý sự kiện click nút Lưu
     * 
     * Lưu các thay đổi thông tin người dùng vào database
     */
    void on_btnSave_clicked();

    /**
     * @brief Xử lý sự kiện click nút Hủy
     * 
     * Đóng dialog mà không lưu thay đổi
     */
    void on_btnCancel_clicked();

    /**
     * @brief Xử lý sự kiện click nút chọn ảnh đại diện
     * 
     * Mở dialog cho phép người dùng chọn ảnh từ máy tính
     */
    void on_btnSelectAvatar_clicked();

    /**
     * @brief Xử lý khi ảnh đại diện được tải lên thành công
     * 
     * @param imageUrl URL của ảnh đã được tải lên Azure Storage
     */
    void onImageUploaded(const QString &imageUrl);

protected:
    /**
     * @brief Override phương thức lọc sự kiện
     * 
     * Xử lý các sự kiện mouse hover và click cho các widget
     * 
     * @param obj Đối tượng nhận sự kiện
     * @param event Sự kiện cần xử lý
     * @return true nếu sự kiện đã được xử lý
     * @return false nếu sự kiện chưa được xử lý
     */
    bool eventFilter(QObject *obj, QEvent *event);

private:
    /**
     * @brief Tải thông tin người dùng từ database
     */
    void loadUserData();

    /**
     * @brief Cập nhật preview ảnh đại diện
     * @param imagePath Đường dẫn đến file ảnh
     */
    void updateAvatarPreview(const QString &imagePath);

    /**
     * @brief Tải và hiển thị ảnh đại diện từ URL
     * @param url URL của ảnh đại diện trên Azure Storage
     */
    void loadAvatarFromUrl(const QString &url);

    /**
     * @brief Thiết lập giao diện người dùng
     */
    void setupUI();

    /**
     * @brief Xử lý sự kiện click vào ảnh đại diện
     */
    void onAvatarClicked();

    Ui::ShowUserInformationDialog* ui;              ///< Con trỏ đến giao diện người dùng
    QSharedPointer<UserService> _userService;       ///< Service quản lý thông tin người dùng
    QSharedPointer<AzureStorageService> _storageService; ///< Service lưu trữ ảnh
    QNetworkAccessManager* _networkManager;         ///< Manager xử lý network requests
    QString _email;                                 ///< Email của người dùng
    QString _tempAvatarPath;                        ///< Đường dẫn tạm thời cho ảnh đại diện
};

#endif // SHOWUSERINFORMATIONDIALOG_H

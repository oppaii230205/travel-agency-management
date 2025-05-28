/**
 * @file AzureStorageService.h
 * @brief Service quản lý việc lưu trữ và tải file trên Azure Blob Storage
 */

#ifndef AZURESTORAGESERVICE_H
#define AZURESTORAGESERVICE_H

#include <QObject>
#include <QtNetwork/QNetworkAccessManager>
#include <QUrl>
#include <QNetworkReply>
#include <QFile>

/**
 * @brief Class cung cấp các chức năng tương tác với Azure Blob Storage
 * 
 * Class này cung cấp các chức năng:
 * - Upload ảnh lên Azure Blob Storage
 * - Quản lý kết nối và xử lý phản hồi từ Azure
 * - Tạo URL cho các blob đã upload
 */
class AzureStorageService : public QObject
{
    Q_OBJECT
public:
    /**
     * @brief Constructor cho AzureStorageService
     * @param parent QObject cha (mặc định là nullptr)
     */
    explicit AzureStorageService(QObject *parent = nullptr);

    /**
     * @brief Upload một file ảnh lên Azure Blob Storage
     * 
     * Phương thức này sẽ:
     * - Đọc file ảnh từ đường dẫn local
     * - Upload lên Azure Blob Storage sử dụng SAS token
     * - Phát signal uploadCompleted khi thành công với URL của blob
     * - Phát signal uploadFailed nếu có lỗi xảy ra
     * 
     * @param filePath Đường dẫn đến file ảnh cần upload
     * @param blobName Tên blob sẽ được sử dụng trên Azure Storage
     */
    void uploadImage(const QString &filePath, const QString &blobName);

signals:
    /**
     * @brief Signal được phát khi upload hoàn tất thành công
     * @param imageUrl URL của ảnh đã được upload lên Azure
     */
    void uploadCompleted(const QString &imageUrl);

    /**
     * @brief Signal được phát khi upload thất bại
     * @param error Thông báo lỗi chi tiết
     */
    void uploadFailed(const QString &error);

private:
    QNetworkAccessManager *networkManager;    ///< Manager xử lý các network request
    QString sasToken = "sv=2024-11-04&ss=bfqt&srt=co&sp=rwdctfx&se=2025-07-17T13:08:21Z&st=2025-05-17T05:08:21Z&sip=0.0.0.0-255.255.255.255&spr=https,http&sig=awquCygF%2FTINZl9iBMWbpEc09RstGlbIsRQ4cU%2FLoW8%3D";                         ///< Shared Access Signature token để xác thực với Azure
    QString storageAccount = "tripagency";                   ///< Tên storage account trên Azure
    QString containerName = "user-avatars";                    ///< Tên container chứa các blob
};

#endif // AZURESTORAGESERVICE_H

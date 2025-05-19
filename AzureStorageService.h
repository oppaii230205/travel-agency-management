// AzureStorageService.h
#ifndef AZURESTORAGESERVICE_H
#define AZURESTORAGESERVICE_H

#include <QObject>
#include <QtNetwork/QNetworkAccessManager>
#include <QUrl>
#include <QNetworkReply>
#include <QFile>

class AzureStorageService : public QObject
{
    Q_OBJECT
public:
    explicit AzureStorageService(QObject *parent = nullptr);

    void uploadImage(const QString &filePath, const QString &blobName);

signals:
    void uploadCompleted(const QString &imageUrl);
    void uploadFailed(const QString &error);

private:
    QNetworkAccessManager *networkManager;
    QString sasToken = "sv=2024-11-04&ss=bfqt&srt=co&sp=rwdctfx&se=2025-07-17T13:08:21Z&st=2025-05-17T05:08:21Z&sip=0.0.0.0-255.255.255.255&spr=https,http&sig=awquCygF%2FTINZl9iBMWbpEc09RstGlbIsRQ4cU%2FLoW8%3D";
    QString storageAccount = "tripagency";
    QString containerName = "user-avatars";
};

#endif // AZURESTORAGESERVICE_H

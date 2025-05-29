// AzureStorageService.cpp
#include "AzureStorageService.h"
#include <QFile>
#include <QNetworkRequest>
#include <QHttpMultiPart>
#include <QHttpPart>
#include <QFileInfo>

AzureStorageService::AzureStorageService(QObject *parent) : QObject(parent)
{
    _networkManager = new QNetworkAccessManager(this);
}

void AzureStorageService::uploadImage(const QString &filePath, const QString &blobName)
{
    QFile *file = new QFile(filePath);
    if (!file->open(QIODevice::ReadOnly)) {
        emit uploadFailed("Cannot open file");
        file->deleteLater();
        return;
    }

    QString fullUrl = QString("https://%1.blob.core.windows.net/%2/%3?%4")
                          .arg(_storageAccount)
                          .arg(_containerName)
                          .arg(blobName)
                          .arg(_sasToken);
    QUrl url(fullUrl);


    QNetworkRequest request(url);
    request.setRawHeader("x-ms-blob-type", "BlockBlob");
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/octet-stream");

    request.setTransferTimeout(30000);

    QNetworkReply *reply = _networkManager->put(request, file);

    file->setParent(reply);

    connect(reply, &QNetworkReply::finished, [this, reply]() {
        if (reply->error() == QNetworkReply::NoError) {
            QString imageUrl = reply->url().toString().split("?").first();
            emit uploadCompleted(imageUrl);
        } else {
            emit uploadFailed(reply->errorString());
        }
        reply->deleteLater(); // File sẽ tự động xóa cùng reply
    });
}

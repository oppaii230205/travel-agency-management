#include "CryptoUtils.h"
#include "qaesencryption.h" // Thư viện QAESEncryption
#include <QCryptographicHash>
#include <QRandomGenerator>
#include <QDebug>

// Mã hóa QString → Base64 QString
QString CryptoUtils::encrypt(const QString &plaintext, const QString &key) {
    QByteArray keyData = key.toUtf8();
    if (!validateKey(keyData)) {
        qWarning() << "Key must be 32 bytes long!";
        return "";
    }

    QByteArray iv = generateIV();
    QByteArray plaintextData = plaintext.toUtf8();

    QAESEncryption aes(QAESEncryption::AES_256, QAESEncryption::CBC);
    QByteArray encrypted = aes.encode(plaintextData, keyData, iv);

    return QString((iv + encrypted).toBase64());
}

// Giải mã Base64 QString → QString
QString CryptoUtils::decrypt(const QString &encryptedBase64, const QString &key) {
    QByteArray keyData = key.toUtf8();
    if (!validateKey(keyData)) {
        qWarning() << "Key must be 32 bytes long!";
        return "";
    }

    QByteArray encryptedData = QByteArray::fromBase64(encryptedBase64.toUtf8());
    if (encryptedData.size() <= 16) {
        qWarning() << "Invalid encrypted data!";
        return "";
    }

    QByteArray iv = encryptedData.left(16);
    QByteArray ciphertext = encryptedData.mid(16);

    QAESEncryption aes(QAESEncryption::AES_256, QAESEncryption::CBC);
    QByteArray decrypted = aes.decode(ciphertext, keyData, iv);

    return QString(aes.removePadding(decrypted));
}

// Kiểm tra key có đủ 32 byte không
bool CryptoUtils::validateKey(const QByteArray &key) {
    return (key.size() == 32);
}

// Tạo IV ngẫu nhiên 16 byte
QByteArray CryptoUtils::generateIV() {
    QByteArray iv(16, 0);
    QRandomGenerator::global()->fillRange(reinterpret_cast<quint32*>(iv.data()), iv.size() / sizeof(quint32));
    return iv;
}

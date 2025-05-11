#ifndef CRYPTOUTILS_H
#define CRYPTOUTILS_H

#include <QString>
#include <QByteArray>


class CryptoUtils {
public:
    static QString encrypt(const QString &plaintext, const QString &key);

    static QString decrypt(const QString &encryptedBase64, const QString &key);

private:
    // Kiểm tra key có đủ 32 byte không
    static bool validateKey(const QByteArray &key);

    static QByteArray generateIV();
};

#endif // CRYPTOUTILS_H

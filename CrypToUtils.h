/**
 * @file CrypToUtils.h
 * @brief Utility class cung cấp các phương thức mã hóa và giải mã dữ liệu
 */

#ifndef CRYPTOUTILS_H
#define CRYPTOUTILS_H

#include <QString>
#include <QByteArray>

/**
 * @brief Class cung cấp các phương thức static để mã hóa và giải mã dữ liệu
 * 
 * Class này sử dụng thuật toán AES để:
 * - Mã hóa dữ liệu nhạy cảm
 * - Giải mã dữ liệu đã được mã hóa
 * - Đảm bảo tính bảo mật của thông tin
 */
class CryptoUtils {
public:
    /**
     * @brief Mã hóa một chuỗi văn bản
     * 
     * Phương thức này sẽ:
     * - Tạo IV (Initialization Vector) ngẫu nhiên
     * - Mã hóa dữ liệu sử dụng thuật toán AES
     * - Kết hợp IV với dữ liệu đã mã hóa
     * - Chuyển đổi kết quả sang Base64
     * 
     * @param plaintext Chuỗi văn bản cần mã hóa
     * @param key Khóa được sử dụng để mã hóa
     * @return Chuỗi đã được mã hóa dưới dạng Base64
     */
    static QString encrypt(const QString &plaintext, const QString &key);

    /**
     * @brief Giải mã một chuỗi đã được mã hóa
     * 
     * Phương thức này sẽ:
     * - Giải mã chuỗi Base64
     * - Tách IV từ dữ liệu đã mã hóa
     * - Giải mã dữ liệu sử dụng thuật toán AES
     * 
     * @param encryptedBase64 Chuỗi đã mã hóa dưới dạng Base64
     * @param key Khóa được sử dụng để giải mã
     * @return Chuỗi văn bản gốc sau khi giải mã
     */
    static QString decrypt(const QString &encryptedBase64, const QString &key);

private:
    /**
     * @brief Kiểm tra độ dài của khóa
     * 
     * Phương thức này đảm bảo khóa có đủ độ dài 32 byte cho thuật toán AES-256
     * 
     * @param key Khóa cần kiểm tra
     * @return true nếu khóa hợp lệ, false nếu không đủ độ dài
     */
    static bool validateKey(const QByteArray &key);

    /**
     * @brief Tạo Initialization Vector (IV) ngẫu nhiên
     * 
     * IV là một vector 16 byte được sử dụng trong quá trình mã hóa
     * để tăng tính bảo mật và ngẫu nhiên của kết quả mã hóa
     * 
     * @return IV ngẫu nhiên dưới dạng QByteArray
     */
    static QByteArray generateIV();
};

#endif // CRYPTOUTILS_H

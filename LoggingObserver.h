/**
 * @file LoggingObserver.h
 * @brief Observer ghi log các sự kiện trong hệ thống
 * 
 * File này định nghĩa:
 * - Observer để ghi log tất cả các sự kiện
 * - Sử dụng QDebug để xuất log
 * - Format log theo chuẩn ISO với timestamp
 */

#ifndef LOGGINGOBSERVER_H
#define LOGGINGOBSERVER_H

#include "IObserver.h"
#include <QDebug>

/**
 * @brief Observer chuyên ghi log các sự kiện hệ thống
 * 
 * Class này kế thừa từ IObserver và:
 * - Ghi log mọi sự kiện xảy ra trong hệ thống
 * - Sử dụng QDebug để xuất log ra console
 * - Format log bao gồm timestamp, tên sự kiện và dữ liệu
 * 
 * Format log: [timestamp] event_name event occurred with data: event_data
 */
class LoggingObserver : public IObserver {
public:
    /**
     * @brief Xử lý sự kiện bằng cách ghi log
     * 
     * Phương thức này:
     * - Ghi log với timestamp theo định dạng ISO
     * - Ghi tên sự kiện
     * - Ghi dữ liệu kèm theo của sự kiện
     * 
     * @param event Sự kiện cần ghi log
     */
    void onEvent(const Event& event) override {
        qDebug() << "[" << event.timestamp().toString(Qt::ISODate) << "]"
                 << event.name() << "event occurred with data:" << event.data();
    }
};

#endif // LOGGINGOBSERVER_H

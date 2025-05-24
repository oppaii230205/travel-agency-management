// custommessagebox.cpp
#include "custommessagebox.h"
#include <QPushButton>

CustomMessageBox::CustomMessageBox(QWidget* parent) : QMessageBox(parent) {}

void CustomMessageBox::show(const QString& title, const QString& message, QWidget* parent) {
    QMessageBox msgBox(parent);
    msgBox.setWindowTitle(title);
    msgBox.setText(message);
    msgBox.setIcon(QMessageBox::NoIcon);
    msgBox.setStandardButtons(QMessageBox::Ok);

    applyStyle(msgBox);
    msgBox.exec();
}

QMessageBox::StandardButton CustomMessageBox::question(const QString& title,
                                                       const QString& message,
                                                       QWidget* parent,
                                                       QMessageBox::StandardButtons buttons) {
    QMessageBox msgBox(parent);
    msgBox.setWindowTitle(title);
    msgBox.setText(message);
    msgBox.setIcon(QMessageBox::Question);
    msgBox.setStandardButtons(buttons);

    applyStyle(msgBox); // Áp dụng style giống như các message box khác

    // Thêm style đặc biệt cho nút Yes/No nếu cần
    msgBox.setStyleSheet(msgBox.styleSheet() + R"(
        QMessageBox QPushButton {
            min-width: 80px;
            margin: 5px;
        }
        QMessageBox QPushButton#YesButton {
            background-color: #2ecc71;
        }
        QMessageBox QPushButton#NoButton {
            background-color: #e74c3c;
        }
    )");

    return static_cast<StandardButton>(msgBox.exec());
}

void CustomMessageBox::applyStyle(QMessageBox& msgBox) {
    // Thiết lập style sheet chung với ẩn icon hoàn toàn
    msgBox.setStyleSheet(R"(
        QMessageBox {
            background: qlineargradient(x1:0, y1:0, x2:1, y2:1,
                                    stop:0 #f5f7fa, stop:1 #c3cfe2);
            font-family: 'Segoe UI', Arial, sans-serif;
            border: 2px solid #3498db;
            border-radius: 8px;
        }

        /* Ẩn hoàn toàn vùng icon */
        QMessageBox QLabel#qt_msgboxex_icon_label {
            display: none;
        }

        /* Style cho text chính - căn giữa hoàn toàn */
        QMessageBox QLabel#qt_msgbox_label {
            min-width: 300px;
            padding: 15px;
            font-size: 14px;
            text-align: center;
            margin: 0 auto;
            qproperty-alignment: 'AlignCenter';
        }

        /* Style chung cho các nút */
        QMessageBox QPushButton {
            min-width: 80px;
            min-height: 30px;
            padding: 5px 10px;
            font-size: 14px;
            border-radius: 5px;
            background-color: #3498db;
            color: white;
            margin: 0 5px;
        }

        QMessageBox QPushButton:hover {
            background-color: #2980b9;
        }

        /* Style riêng cho nút Yes */
        QMessageBox QPushButton#YesButton {
            background-color: #2ecc71;
        }

        QMessageBox QPushButton#YesButton:hover {
            background-color: #27ae60;
        }

        /* Style riêng cho nút No */
        QMessageBox QPushButton#NoButton {
            background-color: #e74c3c;
        }

        QMessageBox QPushButton#NoButton:hover {
            background-color: #c0392b;
        }
    )");

    // Xử lý nút OK nếu có
    if (QAbstractButton* okButton = msgBox.button(QMessageBox::Ok)) {
        okButton->setFocus();
    }
}


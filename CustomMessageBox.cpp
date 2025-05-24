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

void CustomMessageBox::applyStyle(QMessageBox& msgBox) {
    msgBox.setStyleSheet(R"(
        QMessageBox {
            background: qlineargradient(x1:0, y1:0, x2:1, y2:1,
                                    stop:0 #f5f7fa, stop:1 #c3cfe2);
            font-family: 'Segoe UI', Arial, sans-serif;
            border: 2px solid #3498db;
            border-radius: 8px;
        }

        QMessageBox QLabel {
            min-width: 300px;
            padding: 15px;
            font-size: 14px;
            text-align: center;
        }

        QMessageBox QPushButton {
            min-width: 80px;
            min-height: 30px;
            padding: 5px 10px;
            font-size: 14px;
            border-radius: 5px;
            background-color: #3498db;
            color: white;
            margin: 0 auto;
        }

        QMessageBox QPushButton:hover {
            background-color: #2980b9;
        }
    )");

    // Sửa dòng này bằng cách thêm ép kiểu động
    if (QAbstractButton* abstractButton = msgBox.button(QMessageBox::Ok)) {
        QPushButton* okButton = qobject_cast<QPushButton*>(abstractButton);
        if (okButton) {
            okButton->setFocus();
        }
    }
}

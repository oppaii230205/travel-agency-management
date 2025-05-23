// custommessagebox.h
#ifndef CUSTOMMESSAGEBOX_H
#define CUSTOMMESSAGEBOX_H

#include <QMessageBox>

class CustomMessageBox : public QMessageBox {
    Q_OBJECT
public:
    static void show(const QString& title, const QString& message, QWidget* parent = nullptr);
    static StandardButton question(const QString& title, const QString& message, QWidget* parent = nullptr, StandardButtons buttons = Yes|No);

private:
    explicit CustomMessageBox(QWidget* parent = nullptr);
    static void applyStyle(QMessageBox& msgBox);
};

#endif // CUSTOMMESSAGEBOX_H

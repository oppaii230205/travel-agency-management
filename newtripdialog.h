#ifndef NEWTRIPDIALOG_H
#define NEWTRIPDIALOG_H

#include <QDialog>

namespace Ui {
class NewTripDialog;
}

class NewTripDialog : public QDialog
{
    Q_OBJECT

public:
    explicit NewTripDialog(QWidget *parent = nullptr);
    ~NewTripDialog();

private slots:
    void on_btnSubmit_clicked();

private:
    Ui::NewTripDialog *ui;
};

#endif // NEWTRIPDIALOG_H

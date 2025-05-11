#ifndef REVIEWDIALOG_H
#define REVIEWDIALOG_H

// ReviewDialog.h
#include <QDialog>
#include <QMessageBox>
#include <QPushButton>
#include "ReviewService.h"

/*
namespace Ui {
class ReviewDialog;
}

class ReviewDialog : public QDialog {
    Q_OBJECT
public:
    ReviewDialog(QSharedPointer<ReviewService> reviewService,
                 int tripId,
                 QWidget* parent = nullptr);
    ~ReviewDialog();

private slots:
    void onSubmitClicked();

private:
    Ui::ReviewDialog *ui;
    QSharedPointer<ReviewService> _reviewService;
    int _tripId;
};
*/
#endif // REVIEWDIALOG_H

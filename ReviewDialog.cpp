#include "ReviewDialog.h"
#include "ui_ReviewDialog.h"

/*
ReviewDialog::ReviewDialog(QSharedPointer<ReviewService> reviewService,
                           int tripId,
                           QWidget* parent)
    : QDialog(parent), _reviewService(reviewService), _tripId(tripId) {
    ui->setupUi(this);

    // Thiết lập rating widget (vd: QRatingStar)
    connect(ui->submitButton, &QPushButton::clicked,
            this, &ReviewDialog::onSubmitClicked);

    // Hiển thị thông báo lỗi/thành công
    connect(_reviewService.data(), &ReviewService::reviewSubmitted,
            this, [this]() {
                QMessageBox::information(this, "Success", "Review submitted!");
                this->accept();
            });
    connect(_reviewService.data(), &ReviewService::reviewError,
            this, [this](const QString& err) {
                QMessageBox::critical(this, "Error", err);
            });
}

void ReviewDialog::onSubmitClicked() {
    int rating = ui->ratingWidget->getRating(); // Giả sử có widget đánh giá sao
    QString comment = ui->commentEdit->toPlainText();

    _reviewService->submitReview(_tripId, rating, comment);
}
*/

// TripDetailDialog.h
#include <QDialog>
#include "Trip.h"

#include "ReviewService.h"
#include <QFormLayout>
#include <QComboBox>
#include <QTextEdit>
#include <QMessageBox>

class QLabel;
class QScrollArea;

class TripDetailDialog : public QDialog
{
    Q_OBJECT
public:
    explicit TripDetailDialog(const Trip& trip,
                              QSharedPointer<ReviewService> reviewService,
                              QWidget *parent = nullptr);

private slots:
    void onSubmitReview();
    void updateReviewUI();

private:
    void setupUI();
    void loadStyles();
    void setupReviewForm();
    void loadExistingReviews();

    const Trip& _trip;
    QSharedPointer<ReviewService> _reviewService;

    QLabel* _imageLabel;
    QLabel* _titleLabel;
    QLabel* _priceLabel;
    QLabel* _difficultyLabel;
    QLabel* _durationLabel;
    QLabel* _summaryLabel;
    QLabel* _descriptionLabel;

    // Thêm các widget mới cho review
    QWidget* _reviewFormContainer;
    QComboBox* _ratingComboBox;
    QTextEdit* _reviewTextEdit;
    QPushButton* _submitReviewButton;

    QWidget* _reviewsContainer;
};

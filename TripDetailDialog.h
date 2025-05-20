// TripDetailDialog.h
#include <QDialog>
#include "Trip.h"

class QLabel;
class QScrollArea;

class TripDetailDialog : public QDialog
{
    Q_OBJECT
public:
    explicit TripDetailDialog(const Trip& trip, QWidget *parent = nullptr);

private:
    void setupUI();
    void loadStyles();

    const Trip& _trip;
    QLabel* _imageLabel;
    QLabel* _titleLabel;
    QLabel* _priceLabel;
    QLabel* _difficultyLabel;
    QLabel* _durationLabel;
    QLabel* _summaryLabel;
    QLabel* _descriptionLabel;
};

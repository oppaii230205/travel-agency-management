#include "AddTripDialog.h"
#include "ui_AddTripDialog.h"

AddTripDialog::AddTripDialog(TripService* service, QWidget* parent)
    : QDialog(parent), ui(new Ui::AddTripDialog), _tripService(service)
{
    ui->setupUi(this);

    // Thiết lập validator cho các field
    ui->linePrice->setValidator(new QIntValidator(0, 10000000, this));

    ui->comboDifficulty->addItem("Easy");
    ui->comboDifficulty->addItem("Medium");
    ui->comboDifficulty->addItem("Difficult");
}

AddTripDialog::~AddTripDialog() {
    delete ui;
}

void AddTripDialog::on_btnSave_clicked()
{
    Trip newTrip(
        0, // ID sẽ được DB tự sinh
        ui->lineName->text(),
        ui->spinDuration->value(),
        ui->spinGroupSize->value(),
        ui->comboDifficulty->currentText(),
        ui->linePrice->text().toInt(),
        ui->textSummary->toPlainText(),
        ui->textDescription->toPlainText()
        );

    if (_tripService->createTrip(newTrip)) {
        accept(); // Đóng dialog nếu thành công
    }
}

void AddTripDialog::on_btnCancel_clicked()
{
    this->reject(); // Đóng dialog và trả về QDialog::Rejected
}

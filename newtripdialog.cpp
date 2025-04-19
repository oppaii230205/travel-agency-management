#include "newtripdialog.h"
#include "ui_newtripdialog.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <QMessageBox>


NewTripDialog::NewTripDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::NewTripDialog)
{
    ui->setupUi(this);

    QSqlQuery query("SELECT t_id, t_trip FROM travelagencytrips_tb");

    while (query.next()) {
        QString id = query.value(0).toString();
        QString name = query.value(1).toString();
        ui->comboBoxTripPlans->addItem(name, id); // stores id as data
    }
}

void NewTripDialog::on_btnSubmit_clicked()
{
    QString name = ui->lineEditName->text();
    QString address = ui->lineEditAddress->text();
    QString phone = ui->lineEditPhone->text();
    QString email = ui->lineEditEmail->text();
    QString tripDate = ui->dateEditTripDate->date().toString("yyyy-MM-dd");
    QString tripPlan = ui->comboBoxTripPlans->currentText();
    QString cost = ui->lineEditCost->text();

    QSqlQuery query;
    query.prepare("INSERT INTO travelagency_tb "
                  "(t_username, t_useraddress, t_userphone, t_useremail, t_usertripdate, t_usertripplan, t_usertripcost) "
                  "VALUES (?, ?, ?, ?, ?, ?, ?)");

    query.addBindValue(name);
    query.addBindValue(address);
    query.addBindValue(phone);
    query.addBindValue(email);
    query.addBindValue(tripDate);
    query.addBindValue(tripPlan);
    query.addBindValue(cost);

    if (query.exec()) {
        QMessageBox::information(this, "Success", "Trip added successfully!");
        this->accept();
    } else {
        QMessageBox::critical(this, "Error", query.lastError().text());
    }
}

NewTripDialog::~NewTripDialog()
{
    delete ui;
}


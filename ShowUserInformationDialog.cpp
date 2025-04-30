#include "ShowUserInformationDialog.h"
#include "ui_ShowUserInformationDialog.h"
#include <QMessageBox>

ShowUserInformationDialog::ShowUserInformationDialog(QSharedPointer<UserService> userService, const QString& email, QWidget *parent) : QDialog(parent), ui(new Ui::ShowUserInformationDialog), _userService(userService), _email(email){
    ui->setupUi(this);
    setWindowTitle("Thông tin người dùng");

    connect(ui->ptnSave, &QPushButton::clicked, this, &ShowUserInformationDialog::on_btnSave_clicked);
    connect(ui->ptnCancel, &QPushButton::clicked, this, &ShowUserInformationDialog::on_btnCancel_clicked);

    loadUserData();

    ui->lineEditEmail->setReadOnly(true);
    ui->lineEditRole->setReadOnly(true);
    ui->lineEditRole->setEchoMode(QLineEdit::Password);
}

ShowUserInformationDialog::~ShowUserInformationDialog()
{
    delete ui;
}

void ShowUserInformationDialog::loadUserData(){
    auto user = _userService->getUserByEmail(_email);
    if(user){
        ui->lineEditEmail->setText(user->email());
        ui->lineEditName->setText(user->name());
        ui->lineEditPass->clear();
        ui->lineEditRole->setText(user->role());
    }
}

void ShowUserInformationDialog::on_btnSave_clicked(){
    QString newName = ui->lineEditName->text();
    QString newPassword = ui->lineEditPass->text();

    if(newName.isEmpty()){
        QMessageBox::warning(this, tr("Error"), tr("Name cannot be empty"));
        return;
    }

    if(_userService->updateUser(_email, newPassword, newName)){
        QMessageBox::information(this, tr("Success"), tr("User information updated"));
        accept();
    }
    else{
        QMessageBox::warning(this, tr("Error"), tr("Failed to update user"));
    }
}

void ShowUserInformationDialog::on_btnCancel_clicked()
{
    reject();
}

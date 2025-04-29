#include "ShowUserInfomationDialog.h"
#include "ui_ShowUserInfomationDialog.h"
#include <QMessageBox>

ShowUserInfomationDialog::ShowUserInfomationDialog(QSharedPointer<UserService> userService, const QString& email, QWidget *parent) : QDialog(parent), ui(new Ui::ShowUserInfomationDialog), _userService(userService), _email(email){
    ui->setupUi(this);
    setWindowTitle("Thông tin người dùng");

    connect(ui->saveButton, &QPushButton::clicked, this, &ShowUserInformationDialog::onSaveClicked);
    connect(ui->cancelButton, &QPushButton::clicked, this, &ShowUserInformationDialog::onCancelClicked);

    loadUserData();

    ui->lineEditEmail->setReadOnly(true);
    ui->lineEditRole->setReadOnly(true);
    ui->lineEditRole->setEchoMode(QLineEdit::Password);
}

ShowUserInfomationDialog::~ShowUserInfomationDialog()
{
    delete ui;
}

void ShowUserInfomationDialog::loadUserData(){
    auto user = _userService->getUserByEmail(_email);
    if(user){
        ui->lineEditEmail->setText(user->email());
        ui->lineEditName->setText(user->name());
        ui->lineEditPass->clear();
        ui->lineEditRole->setText(user->role());
    }
}

void ShowUserInfomationDialog::onSaveClicked(){
    QString newName = ui->lineEditEmail->text().trimmed();
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

void ShowUserInformationDialog::onCancelClicked()
{
    reject();
}

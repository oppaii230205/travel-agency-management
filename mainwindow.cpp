#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "newtripdialog.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

void MainWindow::on_btnNewTrip_clicked()
{
    NewTripDialog dialog(this);
    dialog.exec();
}

MainWindow::~MainWindow()
{
    delete ui;
}

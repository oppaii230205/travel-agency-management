#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "TripService.h"
#include "UserService.h"
#include <QSharedPointer>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(TripService* tripService,QSharedPointer<UserService> userService, QWidget* parent = nullptr);
    ~MainWindow();

private slots:
    void on_btnAddTrip_clicked();
    void on_btnShowTrips_clicked();
    void on_btnShowUserInfomation_clicked();
    // void on_btnRefresh_clicked();
    void onTripAdded(const Trip& newTrip);
    void onErrorOccurred(const QString& message);

private:
    // void refreshTripList();
    // void setupTableWidget();
    
    Ui::MainWindow *ui;
    TripService* _tripService;
    QSharedPointer<UserService> _userService;

};

#endif // MAINWINDOW_H

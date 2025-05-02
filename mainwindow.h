#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "TripService.h"
#include "authservice.h"
#include "UserService.h"
#include "loginwindow.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QSharedPointer<UserService> userService, QSharedPointer<AuthService> authService, QSharedPointer<TripService> tripService, QWidget* parent = nullptr);
    ~MainWindow();

public:
    void updateUI();

private slots:
    void on_btnAddTrip_clicked();
    void on_btnShowTrips_clicked();
    void on_btnShowUserInfomation_clicked();
    void handleLogoutRequest();
    // void on_btnRefresh_clicked();
    void onTripAdded(const Trip& newTrip);
    void onErrorOccurred(const QString& message);
    void handleLogout();
signals:
    void logoutCompleted();
private:
    Ui::MainWindow *ui;
    QSharedPointer<AuthService> _authService;  // Truyền qua DI
    QSharedPointer<TripService> _tripService;
    QSharedPointer<UserService> _userService;
};

#endif // MAINWINDOW_H

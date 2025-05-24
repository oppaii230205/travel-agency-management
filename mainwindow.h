#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "TripService.h"
#include "authservice.h"
#include "UserService.h"
#include "BookingService.h"
#include "ReviewService.h"
#include "loginwindow.h"
#include "AzureStorageService.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QSharedPointer<UserService> userService,
               QSharedPointer<AuthService> authService,
               QSharedPointer<TripService> tripService,
               QSharedPointer<BookingService> bookingService,
               QSharedPointer<AzureStorageService> storageService,
               QSharedPointer<ReviewService> reviewService,
               QWidget* parent = nullptr);
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
    Ui::MainWindow* ui;
    QSharedPointer<AuthService> _authService;  // Truyền qua DI
    QSharedPointer<TripService> _tripService;
    QSharedPointer<UserService> _userService;
    QSharedPointer<BookingService> _bookingService;
    QSharedPointer<AzureStorageService> _storageService;
    QSharedPointer<ReviewService> _reviewService;
};

#endif // MAINWINDOW_H

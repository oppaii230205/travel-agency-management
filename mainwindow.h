#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "TripService.h"
#include "authservice.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QSharedPointer<AuthService> authService, TripService* tripService, QWidget* parent = nullptr);
    ~MainWindow();

public:
    void updateUI();

private slots:
    void on_btnAddTrip_clicked();
    void on_btnShowTrips_clicked();
    // void on_btnRefresh_clicked();
    void onTripAdded(const Trip& newTrip);
    void onErrorOccurred(const QString& message);

private:
    Ui::MainWindow *ui;
    QSharedPointer<AuthService> _authService;  // Truyền qua DI
    TripService* _tripService;
};

#endif // MAINWINDOW_H

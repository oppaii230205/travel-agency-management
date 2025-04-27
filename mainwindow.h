#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "TripService.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(TripService* tripService, QWidget* parent = nullptr);
    ~MainWindow();

private slots:
    void on_btnAddTrip_clicked();
    // void on_btnRefresh_clicked();
    void onTripAdded(const Trip& newTrip);
    void onErrorOccurred(const QString& message);

private:
    // void refreshTripList();
    // void setupTableWidget();
    
    Ui::MainWindow *ui;
    TripService* _tripService;
};

#endif // MAINWINDOW_H

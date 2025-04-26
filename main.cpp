#include "MainWindow.h"
#include "DatabaseManager.h"
#include "SqlTripRepository.h"
#include "TripService.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    
    // Khởi tạo các dependency
    DatabaseManager& db = DatabaseManager::getInstance();
    SqlTripRepository repository(db);
    TripService service(&repository);
    
    // Truyền service vào MainWindow
    MainWindow w(&service);
    w.show();
    
    return a.exec();
}
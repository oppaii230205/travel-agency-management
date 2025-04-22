#ifndef TRIP_H
#define TRIP_H

#include <QString>
#include <QDate>

class Trip {
private:
    int _id;
    QString _departure;
    QString _destination;
    double _price;
public:
    Trip(int id, const QString& departure, const QString& destination, double price);

    int getId() const;
    QString getDeparture() const; 
    QString getDestination() const;
    double getPrice() const; 
    void setDeparture(const QString& departure); 
    void setDestination(const QString& destination); 
    void setPrice(double price); 
};

#endif // TRIP_H

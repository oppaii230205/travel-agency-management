#include "Trip.h"

Trip::Trip(int id, const QString& departure, const QString& destination, double price)
        : _id(id), _departure(departure), _destination(destination), _price(price) {}

int Trip::getId() const { return _id; }

QString Trip::getDeparture() const { return _departure; }

QString Trip::getDestination() const { return _destination; }

double Trip::getPrice() const { return _price; }

void Trip::setDeparture(const QString& departure) { _departure = departure; }

void Trip::setDestination(const QString& destination) { _destination = destination; }

void Trip::setPrice(double price) { _price = price; }
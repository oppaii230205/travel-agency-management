#include "Trip.h"

Trip::Trip(): _tripId(0), _tripName(""), _duration(0), _maxGroupSize(0), _difficulty(""), _price(0), _summary(""), _description(""), _imagePath(""){}

Trip::Trip(int tripId, const QString& tripName, int duration, int maxGroupSize, const QString& difficulty,
    int price, const QString& summary, const QString& description, const QString& imagePath)
   : _tripId(tripId), _tripName(tripName), _duration(duration), _maxGroupSize(maxGroupSize),
    _difficulty(difficulty), _price(price), _summary(summary), _description(description), _imagePath(imagePath) {}

int Trip::getTripId() const { return _tripId; }
QString Trip::getTripName() const { return _tripName; }
int Trip::getDuration() const { return _duration; }
int Trip::getMaxGroupSize() const { return _maxGroupSize; }
QString Trip::getDifficulty() const { return _difficulty; }
int Trip::getPrice() const { return _price; }
QString Trip::getSummary() const { return _summary; }
QString Trip::getDescription() const { return _description; }
QString Trip::getImagePath() const {return _imagePath; }

void Trip::setTripName(const QString& tripName) { _tripName = tripName; }
void Trip::setDuration(int duration) { _duration = duration; }
void Trip::setMaxGroupSize(int maxGroupSize) { _maxGroupSize = maxGroupSize; }
void Trip::setDifficulty(const QString& difficulty) { _difficulty = difficulty; }
void Trip::setPrice(int price) { _price = price; }
void Trip::setSummary(const QString& summary) { _summary = summary; }
void Trip::setDescription(const QString& description) { _description = description; }
void Trip::setImagePath(const QString& imagePath) { _imagePath = imagePath; }

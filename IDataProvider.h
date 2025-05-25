#ifndef IDATAPROVIDER_H
#define IDATAPROVIDER_H

#include "TripRepository.h"
#include "UserRepository.h"
#include "BookingRepository.h"
#include "ReviewRepository.h"

class IDataProvider {
public:
  IDataProvider() = default;
  virtual ~IDataProvider() = default;

  virtual QSharedPointer<TripRepository> getTripRepository() const = 0;
  virtual QSharedPointer<UserRepository> getUserRepository() const = 0;
  virtual QSharedPointer<BookingRepository> getBookingRepository() const = 0;
  virtual QSharedPointer<ReviewRepository> getReviewRepository() const = 0;
}

#endif // IDATAPROVIDER_H

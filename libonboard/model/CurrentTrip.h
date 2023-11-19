#ifndef CURRENTTRIP_H
#define CURRENTTRIP_H

#include "Trip.h"
#include "IDeserializable.h"

class LIB_ONBOARD_EXPORT CurrentTrip : public IDeserializable {
    Q_OBJECT
public:
    Q_INVOKABLE explicit CurrentTrip(QObject *parent = nullptr) : IDeserializable(parent) {};

    DECL_PROPERTY(trip, Trip*)
};

Q_DECLARE_METATYPE(CurrentTrip*)

#endif // CURRENTTRIP_H

#ifndef TRIP_H
#define TRIP_H

#include "Stop.h"
#include "TripStopInfo.h"
#include "IDeserializable.h"

class LIB_ONBOARD_EXPORT Trip : public IDeserializable {
    Q_OBJECT
public:
    Q_INVOKABLE explicit Trip(QObject *parent = nullptr) : IDeserializable(parent) {};

    DECL_PROPERTY(tripDate, QString)
    DECL_PROPERTY(trainType, QString)
    DECL_PROPERTY(vzn, QString)
    DECL_PROPERTY(actualPosition, long)
    DECL_PROPERTY(distanceFromLastStop, long)
    DECL_PROPERTY(totalDistance, long)

    DECL_PROPERTY(stopInfo, TripStopInfo*)

    DECL_ARRAY_PROPERTY(stops, Stop*)
};

Q_DECLARE_METATYPE(Trip*)

#endif // TRIP_H

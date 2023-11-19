#ifndef STOPTIMETABLE_H
#define STOPTIMETABLE_H

#include "IDeserializable.h"

class LIB_ONBOARD_EXPORT StopTimetable : public IDeserializable {
    Q_OBJECT
public:
    Q_INVOKABLE explicit StopTimetable(QObject *parent = nullptr) : IDeserializable(parent) {};

    DECL_PROPERTY(scheduledArrivalTime, long) // nullable
    DECL_PROPERTY(actualArrivalTime, long) // nullable
    DECL_PROPERTY(showActualArrivalTime, bool) // nullable
    DECL_PROPERTY(arrivalDelay, QString)
    DECL_PROPERTY(scheduledDepartureTime, long) // nullable
    DECL_PROPERTY(actualDepartureTime, long) // nullable
    DECL_PROPERTY(showActualDepartureTime, bool) // nullable
    DECL_PROPERTY(departureDelay, QString)
};

Q_DECLARE_METATYPE(StopTimetable*)

#endif // STOPTIMETABLE_H

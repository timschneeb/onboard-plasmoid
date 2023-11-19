#ifndef STOP_H
#define STOP_H

#include "IDeserializable.h"

#include "DelayReason.h"
#include "Station.h"
#include "StopInfo.h"
#include "StopTimetable.h"
#include "Track.h"

class LIB_ONBOARD_EXPORT Stop : public IDeserializable {
    Q_OBJECT
public:
    Q_INVOKABLE explicit Stop(QObject *parent = nullptr) : IDeserializable(parent) {};

    DECL_PROPERTY(station, Station*)
    DECL_PROPERTY(track, Track*)
    DECL_PROPERTY(info, StopInfo*)
    DECL_PROPERTY(timetable, StopTimetable*)

    DECL_ARRAY_PROPERTY(delayReasons, DelayReason*)
};

Q_DECLARE_METATYPE(Stop*)

#endif // STOP_H

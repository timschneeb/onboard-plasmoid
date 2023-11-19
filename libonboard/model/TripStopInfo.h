#ifndef TRIPSTOPINFO_H
#define TRIPSTOPINFO_H

#include "IDeserializable.h"

class LIB_ONBOARD_EXPORT TripStopInfo : public IDeserializable {
    Q_OBJECT
public:
    Q_INVOKABLE explicit TripStopInfo(QObject *parent = nullptr) : IDeserializable(parent) {};

    DECL_PROPERTY(scheduledNext, QString)
    DECL_PROPERTY(actualNext, QString)
    DECL_PROPERTY(actualLast, QString)
    DECL_PROPERTY(actualLastStarted, QString)
    DECL_PROPERTY(finalStationName, QString)
    DECL_PROPERTY(finalStationEvaNr, QString)
};

Q_DECLARE_METATYPE(TripStopInfo*)

#endif // TRIPSTOPINFO_H

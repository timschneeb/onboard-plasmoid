#ifndef STOPINFO_H
#define STOPINFO_H

#include "IDeserializable.h"

class LIB_ONBOARD_EXPORT StopInfo : public IDeserializable {
    Q_OBJECT
public:
    Q_INVOKABLE explicit StopInfo(QObject *parent = nullptr) : IDeserializable(parent) {};

    DECL_PROPERTY(status, int)
    DECL_PROPERTY(passed, bool)
    DECL_PROPERTY(positionStatus, QString) // nullable
    DECL_PROPERTY(distance, long)
    DECL_PROPERTY(distanceFromStart, long)
};

Q_DECLARE_METATYPE(StopInfo*)

#endif // STOPINFO_H

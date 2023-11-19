#ifndef STATION_H
#define STATION_H

#include "Connectivity.h"
#include "IDeserializable.h"

class LIB_ONBOARD_EXPORT Station : public IDeserializable {
    Q_OBJECT
public:
    Q_INVOKABLE explicit Station(QObject *parent = nullptr) : IDeserializable(parent) {};

    DECL_PROPERTY(name, QString)
    DECL_PROPERTY(evaNr, QString)
    DECL_PROPERTY(code, QString) // nullable
    // DECL_PROPERTY(geocoordinates, Geocoordinates) // nullable

};

Q_DECLARE_METATYPE(Station*)

#endif // STATION_H

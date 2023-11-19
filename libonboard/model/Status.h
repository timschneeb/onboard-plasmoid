#ifndef STATUS_H
#define STATUS_H

#include "Connectivity.h"
#include "IDeserializable.h"

class LIB_ONBOARD_EXPORT Status : public IDeserializable {
    Q_OBJECT
public:
    Q_INVOKABLE explicit Status(QObject *parent = nullptr) : IDeserializable(parent) {};

    DECL_PROPERTY(connection, bool)
    DECL_PROPERTY(serviceLevel, QString)
    DECL_PROPERTY(gpsStatus, QString)
    DECL_PROPERTY(internet, QString)
    DECL_PROPERTY(latitude, double)
    DECL_PROPERTY(longitude, double)
    DECL_PROPERTY(series, QString)
    DECL_PROPERTY(serverTime, ulong)
    DECL_PROPERTY(speed, float)
    DECL_PROPERTY(trainType, QString)
    DECL_PROPERTY(tzn, QString)
    DECL_PROPERTY(wagonClass, QString)
    DECL_PROPERTY(bapInstalled, bool)

    DECL_PROPERTY(connectivity, Connectivity*)

};

Q_DECLARE_METATYPE(Status*)

#endif // STATUS_H

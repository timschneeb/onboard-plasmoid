#ifndef TRACK_H
#define TRACK_H

#include "IDeserializable.h"

class LIB_ONBOARD_EXPORT Track : public IDeserializable {
    Q_OBJECT
public:
    Q_INVOKABLE explicit Track(QObject *parent = nullptr) : IDeserializable(parent) {};

    DECL_PROPERTY(scheduled, QString)
    DECL_PROPERTY(actual, QString)
};

Q_DECLARE_METATYPE(Track*)

#endif // TRACK_H

#ifndef CONNECTIVITY_H
#define CONNECTIVITY_H

#include "IDeserializable.h"

class LIB_ONBOARD_EXPORT Connectivity : public IDeserializable {
    Q_OBJECT
public:
    Q_INVOKABLE explicit Connectivity(QObject *parent = nullptr) : IDeserializable(parent) {};

    DECL_PROPERTY(currentState, QString)
    DECL_PROPERTY(nextState, QString)
    DECL_PROPERTY(remainingTimeSeconds, int)
};

Q_DECLARE_METATYPE(Connectivity*)

#endif // CONNECTIVITY_H

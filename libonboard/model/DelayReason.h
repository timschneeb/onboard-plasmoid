#ifndef DELAYREASON_H
#define DELAYREASON_H

#include "IDeserializable.h"

class LIB_ONBOARD_EXPORT DelayReason : public IDeserializable {
    Q_OBJECT
public:
    Q_INVOKABLE explicit DelayReason(QObject *parent = nullptr) : IDeserializable(parent) {};

    DECL_PROPERTY(code, QString)
    DECL_PROPERTY(text, QString)
};

Q_DECLARE_METATYPE(DelayReason*)

#endif // DELAYREASON_H

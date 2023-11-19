#ifndef IDESERIALIZABLE_H
#define IDESERIALIZABLE_H

#include "../global.h"
#include "../Log.h"

#include <QDebug>
#include <QJsonValue>
#include <QJsonObject>
#include <QMetaProperty>
#include <QObject>

class LIB_ONBOARD_EXPORT IDeserializable : public QObject
{
    Q_OBJECT
public:
    virtual ~IDeserializable();

    bool deserialize(const QJsonObject &object);
    bool deserialize(const QString &json);

    void dump(QString &output, int indentLevel = 0);

    template<typename T>
    static T *fromJson(const QJsonObject &object, QObject *parent = nullptr)
    {
        auto clazz = new T(parent);
        clazz->deserialize(object);
        return clazz;
    }

    template<typename T>
    static T *fromJson(const QString &json, QObject *parent = nullptr)
    {
        auto clazz = new T(parent);
        clazz->deserialize(json);
        return clazz;
    }

public slots:
    void reset();

protected:
    explicit IDeserializable(QObject *parent = nullptr);

private:
    void deallocateLists();

    bool fresh = true;

};

// TODO: check if nested objects get updated by the setter
#define DECL_PROPERTY(name, type) \
public: \
    type name() const { return _##name; }; \
    signals: \
    void name##Changed(){}; \
    private: \
    type _##name; \
    void set_##name(type value) { \
        if(value != _##name) { \
            _##name = value; \
            emit name##Changed(); \
        } \
    }; \
    Q_PROPERTY(type name READ name WRITE set_##name NOTIFY name##Changed FINAL)

#define DECL_ARRAY_PROPERTY(name, itemType) \
    public: \
        int name##Count() const { return _##name.count(); }; \
        itemType name##At(int i) const { return _##name.at(i).value<itemType>();}; \
        QVariantList name() const { return _##name; } \
    signals: \
        void name##Changed(){}; \
    private: \
        QVariantList _##name; \
        QString __internal_##name##ItemType() { return #itemType; } \
        void set_##name(QVariantList value) { \
            _##name = value; \
            emit name##Changed(); \
        } \
        Q_PROPERTY(QString __internal_##name##_ItemType READ __internal_##name##ItemType FINAL) \
        Q_PROPERTY(QVariantList name READ name WRITE set_##name NOTIFY name##Changed FINAL)

#endif // IDESERIALIZABLE_H

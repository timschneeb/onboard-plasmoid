#include "IDeserializable.h"

#include <QJsonArray>
#include <QJsonDocument>

IDeserializable::IDeserializable(QObject *parent) : QObject(parent) {}

IDeserializable::~IDeserializable()
{
    deallocateLists();
}

void IDeserializable::deallocateLists()
{
    // Clean up lists that use pointers to custom objects manually, since those are not managed by Qt
    for(int propI = metaObject()->propertyOffset(); propI < metaObject()->propertyCount(); propI++) {
        QMetaProperty prop = metaObject()->property(propI);
        if(prop.type() == QVariant::List) {
            QVariantList list = prop.read(this).toList();
            for(int i = 0; i < list.count(); i++) {
                delete list.at(i).value<IDeserializable*>();
            }
        }
    }
}


void IDeserializable::reset()
{
    if(!fresh)
        deallocateLists();

    fresh = false;

    const QMetaObject *meta = this->metaObject();
    for (int i = meta->propertyOffset(); i < meta->propertyCount(); ++i) {
        QMetaProperty prop = meta->property(i);

        // For some reason, Qt does not expose all QMetaType IDs inside QVariant, so we need to mix the enum
        switch(prop.type()) {
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wenum-compare-switch"
#pragma GCC diagnostic ignored "-Wswitch"
        case QVariant::Bool:
        case QVariant::Char:
        case QVariant::Int:
        case QVariant::UInt:
        case QVariant::LongLong:
        case QVariant::ULongLong:
        case QVariant::Double:
        case QMetaType::Float:
        case QMetaType::Long:
        case QMetaType::ULong:
        case QMetaType::Short:
        case QMetaType::UShort:
            prop.write(this, 0);
            break;
        case QVariant::List:
            prop.write(this, QVariant(QVariant::List));
            break;
        case QVariant::String:
            prop.write(this, "");
            break;
        case QVariant::UserType:
            prop.write(this, QVariant::fromValue<IDeserializable*>(nullptr));
            break;
        default:
            Log::error(QString("Unsupported type: %1").arg(QVariant::typeToName(prop.type())));
            break;
        }
#pragma GCC diagnostic pop
    }
}

bool IDeserializable::deserialize(const QJsonObject &object)
{
    // Initialize all properties, if we are deserializing into a freshly created object
    if(fresh) {
        reset();
    }

    const QMetaObject *meta = this->metaObject();
    // For each property, find the corresponding JSON object and deserialize
    for (int i = meta->propertyOffset(); i < meta->propertyCount(); ++i) {
        QMetaProperty prop = meta->property(i);
        QJsonValue value = object.value(prop.name());

        if(QString(prop.name()).startsWith("__internal_"))
            continue;

        if(value.isUndefined()) {
            // JSON data is incomplete
            Log::error(QString("Key '%1' does not exist in the JSON object for '%2'").arg(prop.name()).arg(meta->className()));
        }
        else if(value.isObject()) {
            // Nested object, create a new class instance and deserialize recursively
            // Log::debug(QString("%1 = [OBJECT]").arg(prop.name()));

            IDeserializable* currentValue = prop.read(this).value<IDeserializable*>();
            if(currentValue == nullptr) {
                const QMetaObject* subMeta = QMetaType::metaObjectForType(QMetaType::type(prop.typeName()));
                if(!subMeta) {
                    Log::critical(QString("No meta type object for property %1 of type %2 found").arg(prop.name()).arg(prop.typeName()));
                }

                QObject* obj = subMeta->newInstance(Q_ARG(QObject*, this));
                currentValue = qobject_cast<IDeserializable*>(obj);
            }
            currentValue->deserialize(value.toObject());
            prop.write(this, QVariant::fromValue(currentValue));
        }
        else if(value.isArray()) {
            // Handle array, create a list
            QJsonArray array = value.toArray();

            // Log::debug(QString("%1 = [ARRAY]{%2 items}").arg(prop.name()).arg(array.count()));

            QVariantList list = prop.read(this).toList();
            for(int i = 0; i < list.count(); i++) {
                delete list.at(i).value<IDeserializable*>();
            }
            list.clear();

            for(int i = 0; i < array.count(); i++) {
                QJsonValue element = array.at(i);
                if(element.isObject()) {
                    int typeInfoPropertyIndex = meta->indexOfProperty(QString("__internal_%1_ItemType").arg(prop.name()).toLocal8Bit().constData());
                    QString itemTypeName = meta->property(typeInfoPropertyIndex).read(this).toString();

                    const QMetaObject* subMeta = QMetaType::metaObjectForType(QMetaType::type(itemTypeName.toLocal8Bit().constData()));
                    if(!subMeta) {
                        Log::critical(QString("No meta type object for property %1 of type %2 found").arg(prop.name()).arg(prop.typeName()));
                    }

                    QObject* obj = subMeta->newInstance(Q_ARG(QObject*, this));
                    IDeserializable *objectPtr = qobject_cast<IDeserializable*>(obj);
                    objectPtr->deserialize(element.toObject());
                    list.append(QVariant::fromValue(objectPtr));
                }
                else {
                    Log::error(QString("Primitive array types not implemented (%1)").arg(prop.name()));
                }
            }

            prop.write(this, QVariant::fromValue(list));
        }
        else {
            // Handle regular types
            QString serialization;
            QDebug(&serialization) << value.toVariant();
            prop.write(this, value.toVariant());
        }
    }

    return true;
}

bool IDeserializable::deserialize(const QString &json)
{
    return deserialize(QJsonDocument::fromJson(json.toUtf8()).object());
}

void IDeserializable::dump(QString &output, int indentLevel)
{
    QString indent = QString("\t").repeated(indentLevel);
    const QMetaObject *meta = this->metaObject();
    // For each property, find the corresponding JSON object and deserialize
    for (int i = meta->propertyOffset(); i < meta->propertyCount(); ++i) {
        QMetaProperty prop = meta->property(i);

        if(QString(prop.name()).startsWith("__internal_"))
            continue;

        if(prop.type() == QVariant::List) {
            QVariantList list = prop.read(this).value<QVariantList>();

            QString entryIndent = QString("\t").repeated(indentLevel + 1);
            output += indent + QString("%1 = [ARRAY](%2) [\n").arg(prop.name()).arg(list.count());

            for (int i = 0; i < list.count(); i++) {
                IDeserializable* object = list.at(i).value<IDeserializable*>();
                output += entryIndent + QString("[ENTRY %1] {\n").arg(i);
                if(object != nullptr) {
                    object->dump(output, indentLevel + 2);
                }
                output += entryIndent + "}\n";
            }
            output += indent + "]\n";
        }
        else if(prop.type() == QVariant::UserType) {
            output += indent + QString("%1 = [OBJECT] {\n").arg(prop.name());
            IDeserializable* object = prop.read(this).value<IDeserializable*>();
            if(object != nullptr) {
                object->dump(output, indentLevel + 1);
            }
            output += indent + "}\n";
        }
        else {
            QString serialization;
            QDebug(&serialization) << prop.read(this);
            output += indent + QString("%1 = %2\n").arg(prop.name()).arg(serialization);
        }
    }
}

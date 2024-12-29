//
// Generated file, do not edit! Created by opp_msgtool 6.1 from packets/PubSubMessage.msg.
//

// Disable warnings about unused variables, empty switch stmts, etc:
#ifdef _MSC_VER
#  pragma warning(disable:4101)
#  pragma warning(disable:4065)
#endif

#if defined(__clang__)
#  pragma clang diagnostic ignored "-Wshadow"
#  pragma clang diagnostic ignored "-Wconversion"
#  pragma clang diagnostic ignored "-Wunused-parameter"
#  pragma clang diagnostic ignored "-Wc++98-compat"
#  pragma clang diagnostic ignored "-Wunreachable-code-break"
#  pragma clang diagnostic ignored "-Wold-style-cast"
#elif defined(__GNUC__)
#  pragma GCC diagnostic ignored "-Wshadow"
#  pragma GCC diagnostic ignored "-Wconversion"
#  pragma GCC diagnostic ignored "-Wunused-parameter"
#  pragma GCC diagnostic ignored "-Wold-style-cast"
#  pragma GCC diagnostic ignored "-Wsuggest-attribute=noreturn"
#  pragma GCC diagnostic ignored "-Wfloat-conversion"
#endif

#include <iostream>
#include <sstream>
#include <memory>
#include <type_traits>
#include "PubSubMessage_m.h"

namespace omnetpp {

// Template pack/unpack rules. They are declared *after* a1l type-specific pack functions for multiple reasons.
// They are in the omnetpp namespace, to allow them to be found by argument-dependent lookup via the cCommBuffer argument

// Packing/unpacking an std::vector
template<typename T, typename A>
void doParsimPacking(omnetpp::cCommBuffer *buffer, const std::vector<T,A>& v)
{
    int n = v.size();
    doParsimPacking(buffer, n);
    for (int i = 0; i < n; i++)
        doParsimPacking(buffer, v[i]);
}

template<typename T, typename A>
void doParsimUnpacking(omnetpp::cCommBuffer *buffer, std::vector<T,A>& v)
{
    int n;
    doParsimUnpacking(buffer, n);
    v.resize(n);
    for (int i = 0; i < n; i++)
        doParsimUnpacking(buffer, v[i]);
}

// Packing/unpacking an std::list
template<typename T, typename A>
void doParsimPacking(omnetpp::cCommBuffer *buffer, const std::list<T,A>& l)
{
    doParsimPacking(buffer, (int)l.size());
    for (typename std::list<T,A>::const_iterator it = l.begin(); it != l.end(); ++it)
        doParsimPacking(buffer, (T&)*it);
}

template<typename T, typename A>
void doParsimUnpacking(omnetpp::cCommBuffer *buffer, std::list<T,A>& l)
{
    int n;
    doParsimUnpacking(buffer, n);
    for (int i = 0; i < n; i++) {
        l.push_back(T());
        doParsimUnpacking(buffer, l.back());
    }
}

// Packing/unpacking an std::set
template<typename T, typename Tr, typename A>
void doParsimPacking(omnetpp::cCommBuffer *buffer, const std::set<T,Tr,A>& s)
{
    doParsimPacking(buffer, (int)s.size());
    for (typename std::set<T,Tr,A>::const_iterator it = s.begin(); it != s.end(); ++it)
        doParsimPacking(buffer, *it);
}

template<typename T, typename Tr, typename A>
void doParsimUnpacking(omnetpp::cCommBuffer *buffer, std::set<T,Tr,A>& s)
{
    int n;
    doParsimUnpacking(buffer, n);
    for (int i = 0; i < n; i++) {
        T x;
        doParsimUnpacking(buffer, x);
        s.insert(x);
    }
}

// Packing/unpacking an std::map
template<typename K, typename V, typename Tr, typename A>
void doParsimPacking(omnetpp::cCommBuffer *buffer, const std::map<K,V,Tr,A>& m)
{
    doParsimPacking(buffer, (int)m.size());
    for (typename std::map<K,V,Tr,A>::const_iterator it = m.begin(); it != m.end(); ++it) {
        doParsimPacking(buffer, it->first);
        doParsimPacking(buffer, it->second);
    }
}

template<typename K, typename V, typename Tr, typename A>
void doParsimUnpacking(omnetpp::cCommBuffer *buffer, std::map<K,V,Tr,A>& m)
{
    int n;
    doParsimUnpacking(buffer, n);
    for (int i = 0; i < n; i++) {
        K k; V v;
        doParsimUnpacking(buffer, k);
        doParsimUnpacking(buffer, v);
        m[k] = v;
    }
}

// Default pack/unpack function for arrays
template<typename T>
void doParsimArrayPacking(omnetpp::cCommBuffer *b, const T *t, int n)
{
    for (int i = 0; i < n; i++)
        doParsimPacking(b, t[i]);
}

template<typename T>
void doParsimArrayUnpacking(omnetpp::cCommBuffer *b, T *t, int n)
{
    for (int i = 0; i < n; i++)
        doParsimUnpacking(b, t[i]);
}

// Default rule to prevent compiler from choosing base class' doParsimPacking() function
template<typename T>
void doParsimPacking(omnetpp::cCommBuffer *, const T& t)
{
    throw omnetpp::cRuntimeError("Parsim error: No doParsimPacking() function for type %s", omnetpp::opp_typename(typeid(t)));
}

template<typename T>
void doParsimUnpacking(omnetpp::cCommBuffer *, T& t)
{
    throw omnetpp::cRuntimeError("Parsim error: No doParsimUnpacking() function for type %s", omnetpp::opp_typename(typeid(t)));
}

}  // namespace omnetpp

Register_Enum(PubSubMessageType, (PubSubMessageType::Subscription, PubSubMessageType::Publication));

Register_Class(PubSubMessage)

PubSubMessage::PubSubMessage() : ::inet::FieldsChunk()
{
    this->setChunkLength(inet::B(6));

}

PubSubMessage::PubSubMessage(const PubSubMessage& other) : ::inet::FieldsChunk(other)
{
    copy(other);
}

PubSubMessage::~PubSubMessage()
{
}

PubSubMessage& PubSubMessage::operator=(const PubSubMessage& other)
{
    if (this == &other) return *this;
    ::inet::FieldsChunk::operator=(other);
    copy(other);
    return *this;
}

void PubSubMessage::copy(const PubSubMessage& other)
{
    this->hopCount = other.hopCount;
    this->nonce = other.nonce;
    this->type = other.type;
    this->topic = other.topic;
    this->nodeName = other.nodeName;
}

void PubSubMessage::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::inet::FieldsChunk::parsimPack(b);
    doParsimPacking(b,this->hopCount);
    doParsimPacking(b,this->nonce);
    doParsimPacking(b,this->type);
    doParsimPacking(b,this->topic);
    doParsimPacking(b,this->nodeName);
}

void PubSubMessage::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::inet::FieldsChunk::parsimUnpack(b);
    doParsimUnpacking(b,this->hopCount);
    doParsimUnpacking(b,this->nonce);
    doParsimUnpacking(b,this->type);
    doParsimUnpacking(b,this->topic);
    doParsimUnpacking(b,this->nodeName);
}

uint8_t PubSubMessage::getHopCount() const
{
    return this->hopCount;
}

void PubSubMessage::setHopCount(uint8_t hopCount)
{
    handleChange();
    this->hopCount = hopCount;
}

uint32_t PubSubMessage::getNonce() const
{
    return this->nonce;
}

void PubSubMessage::setNonce(uint32_t nonce)
{
    handleChange();
    this->nonce = nonce;
}

PubSubMessageType PubSubMessage::getType() const
{
    return this->type;
}

void PubSubMessage::setType(PubSubMessageType type)
{
    handleChange();
    this->type = type;
}

const char * PubSubMessage::getTopic() const
{
    return this->topic.c_str();
}

void PubSubMessage::setTopic(const char * topic)
{
    handleChange();
    this->topic = topic;
}

const char * PubSubMessage::getNodeName() const
{
    return this->nodeName.c_str();
}

void PubSubMessage::setNodeName(const char * nodeName)
{
    handleChange();
    this->nodeName = nodeName;
}

class PubSubMessageDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
        FIELD_hopCount,
        FIELD_nonce,
        FIELD_type,
        FIELD_topic,
        FIELD_nodeName,
    };
  public:
    PubSubMessageDescriptor();
    virtual ~PubSubMessageDescriptor();

    virtual bool doesSupport(omnetpp::cObject *obj) const override;
    virtual const char **getPropertyNames() const override;
    virtual const char *getProperty(const char *propertyName) const override;
    virtual int getFieldCount() const override;
    virtual const char *getFieldName(int field) const override;
    virtual int findField(const char *fieldName) const override;
    virtual unsigned int getFieldTypeFlags(int field) const override;
    virtual const char *getFieldTypeString(int field) const override;
    virtual const char **getFieldPropertyNames(int field) const override;
    virtual const char *getFieldProperty(int field, const char *propertyName) const override;
    virtual int getFieldArraySize(omnetpp::any_ptr object, int field) const override;
    virtual void setFieldArraySize(omnetpp::any_ptr object, int field, int size) const override;

    virtual const char *getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const override;
    virtual std::string getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const override;
    virtual void setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const override;
    virtual omnetpp::cValue getFieldValue(omnetpp::any_ptr object, int field, int i) const override;
    virtual void setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const override;

    virtual const char *getFieldStructName(int field) const override;
    virtual omnetpp::any_ptr getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const override;
    virtual void setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const override;
};

Register_ClassDescriptor(PubSubMessageDescriptor)

PubSubMessageDescriptor::PubSubMessageDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(PubSubMessage)), "inet::FieldsChunk")
{
    propertyNames = nullptr;
}

PubSubMessageDescriptor::~PubSubMessageDescriptor()
{
    delete[] propertyNames;
}

bool PubSubMessageDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<PubSubMessage *>(obj)!=nullptr;
}

const char **PubSubMessageDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *PubSubMessageDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int PubSubMessageDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 5+base->getFieldCount() : 5;
}

unsigned int PubSubMessageDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,    // FIELD_hopCount
        FD_ISEDITABLE,    // FIELD_nonce
        0,    // FIELD_type
        FD_ISEDITABLE,    // FIELD_topic
        FD_ISEDITABLE,    // FIELD_nodeName
    };
    return (field >= 0 && field < 5) ? fieldTypeFlags[field] : 0;
}

const char *PubSubMessageDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    static const char *fieldNames[] = {
        "hopCount",
        "nonce",
        "type",
        "topic",
        "nodeName",
    };
    return (field >= 0 && field < 5) ? fieldNames[field] : nullptr;
}

int PubSubMessageDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    int baseIndex = base ? base->getFieldCount() : 0;
    if (strcmp(fieldName, "hopCount") == 0) return baseIndex + 0;
    if (strcmp(fieldName, "nonce") == 0) return baseIndex + 1;
    if (strcmp(fieldName, "type") == 0) return baseIndex + 2;
    if (strcmp(fieldName, "topic") == 0) return baseIndex + 3;
    if (strcmp(fieldName, "nodeName") == 0) return baseIndex + 4;
    return base ? base->findField(fieldName) : -1;
}

const char *PubSubMessageDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "uint8_t",    // FIELD_hopCount
        "uint32_t",    // FIELD_nonce
        "PubSubMessageType",    // FIELD_type
        "string",    // FIELD_topic
        "string",    // FIELD_nodeName
    };
    return (field >= 0 && field < 5) ? fieldTypeStrings[field] : nullptr;
}

const char **PubSubMessageDescriptor::getFieldPropertyNames(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldPropertyNames(field);
        field -= base->getFieldCount();
    }
    switch (field) {
        case FIELD_type: {
            static const char *names[] = { "enum",  nullptr };
            return names;
        }
        default: return nullptr;
    }
}

const char *PubSubMessageDescriptor::getFieldProperty(int field, const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldProperty(field, propertyName);
        field -= base->getFieldCount();
    }
    switch (field) {
        case FIELD_type:
            if (!strcmp(propertyName, "enum")) return "PubSubMessageType";
            return nullptr;
        default: return nullptr;
    }
}

int PubSubMessageDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    PubSubMessage *pp = omnetpp::fromAnyPtr<PubSubMessage>(object); (void)pp;
    switch (field) {
        default: return 0;
    }
}

void PubSubMessageDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    PubSubMessage *pp = omnetpp::fromAnyPtr<PubSubMessage>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'PubSubMessage'", field);
    }
}

const char *PubSubMessageDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    PubSubMessage *pp = omnetpp::fromAnyPtr<PubSubMessage>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string PubSubMessageDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    PubSubMessage *pp = omnetpp::fromAnyPtr<PubSubMessage>(object); (void)pp;
    switch (field) {
        case FIELD_hopCount: return ulong2string(pp->getHopCount());
        case FIELD_nonce: return ulong2string(pp->getNonce());
        case FIELD_type: return enum2string(pp->getType(), "PubSubMessageType");
        case FIELD_topic: return oppstring2string(pp->getTopic());
        case FIELD_nodeName: return oppstring2string(pp->getNodeName());
        default: return "";
    }
}

void PubSubMessageDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    PubSubMessage *pp = omnetpp::fromAnyPtr<PubSubMessage>(object); (void)pp;
    switch (field) {
        case FIELD_hopCount: pp->setHopCount(string2ulong(value)); break;
        case FIELD_nonce: pp->setNonce(string2ulong(value)); break;
        case FIELD_topic: pp->setTopic((value)); break;
        case FIELD_nodeName: pp->setNodeName((value)); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'PubSubMessage'", field);
    }
}

omnetpp::cValue PubSubMessageDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    PubSubMessage *pp = omnetpp::fromAnyPtr<PubSubMessage>(object); (void)pp;
    switch (field) {
        case FIELD_hopCount: return (omnetpp::intval_t)(pp->getHopCount());
        case FIELD_nonce: return (omnetpp::intval_t)(pp->getNonce());
        case FIELD_type: return static_cast<int>(pp->getType());
        case FIELD_topic: return pp->getTopic();
        case FIELD_nodeName: return pp->getNodeName();
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'PubSubMessage' as cValue -- field index out of range?", field);
    }
}

void PubSubMessageDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    PubSubMessage *pp = omnetpp::fromAnyPtr<PubSubMessage>(object); (void)pp;
    switch (field) {
        case FIELD_hopCount: pp->setHopCount(omnetpp::checked_int_cast<uint8_t>(value.intValue())); break;
        case FIELD_nonce: pp->setNonce(omnetpp::checked_int_cast<uint32_t>(value.intValue())); break;
        case FIELD_topic: pp->setTopic(value.stringValue()); break;
        case FIELD_nodeName: pp->setNodeName(value.stringValue()); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'PubSubMessage'", field);
    }
}

const char *PubSubMessageDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructName(field);
        field -= base->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    };
}

omnetpp::any_ptr PubSubMessageDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    PubSubMessage *pp = omnetpp::fromAnyPtr<PubSubMessage>(object); (void)pp;
    switch (field) {
        default: return omnetpp::any_ptr(nullptr);
    }
}

void PubSubMessageDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    PubSubMessage *pp = omnetpp::fromAnyPtr<PubSubMessage>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'PubSubMessage'", field);
    }
}

namespace omnetpp {

}  // namespace omnetpp


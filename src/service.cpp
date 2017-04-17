#include "service.h"

namespace xzc {

using std::string;

Service::Service(const string& name, const string& type)
        : name_(name),
          type_(type),
          interface_(0),
          protocol_(Protocol::kNoSpec) {
}

Service::~Service() {
}

inline void Service::SetName(const string& name) {
    name_ = name;
}

inline const string& Service::GetName() const {
    return name_;
}

inline void Service::SetType(const string& type) {
    type_ = type;
}

inline const string& Service::GetType() const {
    return type_;
}

inline void Service::SetDomain(const string& domain) {
    domain_ = domain;
}

inline const string& Service::GetDomain() const {
    return domain_;
}

inline void Service::SetSubType(const string& subtype) {
    subtype_ = subtype;
}

inline const string& Service::GetSubType() const {
    return subtype_;
}

inline void Service::SetInterface(int interface) {
    interface_ = interface;
}

inline int Service::GetInterface() const {
    return interface_;
}

inline void Service::SetProtocol(Protocol protocol) {
    protocol_ = protocol;
}

inline Protocol Service::GetProtocol() const {
    return protocol_;
}

inline void Service::SetTXTRecord(const string& key, const string& value) {
    txt_[key] = value;
}

inline string Service::GetTXTRecord(const string& key) const {
    auto it = txt_.find(key);
    return it != txt_.end() ? it->second : "";
}

inline const TXT& Service::GetTXT() const {
    return txt_;
}

inline bool Service::operator==(const Service& rhs) const {
    return GetName() == rhs.GetName();
}
}  // xzc

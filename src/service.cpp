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

void Service::SetName(const string& name) {
    name_ = name;
}

const string& Service::GetName() const {
    return name_;
}

void Service::SetType(const string& type) {
    type_ = type;
}

const string& Service::GetType() const {
    return type_;
}

void Service::SetDomain(const string& domain) {
    domain_ = domain;
}

const string& Service::GetDomain() const {
    return domain_;
}

void Service::SetSubType(const string& subtype) {
    subtype_ = subtype;
}

const string& Service::GetSubType() const {
    return subtype_;
}

void Service::SetInterface(int interface) {
    interface_ = interface;
}

int Service::GetInterface() const {
    return interface_;
}

void Service::SetProtocol(Protocol protocol) {
    protocol_ = protocol;
}

Protocol Service::GetProtocol() const {
    return protocol_;
}

void Service::SetTXTRecord(const string& key, const string& value) {
    txt_[key] = value;
}

string Service::GetTXTRecord(const string& key) const {
    auto it = txt_.find(key);
    return it != txt_.end() ? it->second : "";
}

const TXT& Service::GetTXT() const {
    return txt_;
}

}  // xzc

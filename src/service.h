#ifndef SERVICE_H_
#define SERVICE_H_

#include "xzeroconf_define.h"

#include <string>

namespace xzc {

class Service {
public:
    Service();

    Service(const std::string& name, const std::string& type);

    ~Service();

    void SetName(const std::string& name);

    const std::string& GetName() const;

    void SetType(const std::string& type);

    const std::string& GetType() const;

    void SetDomain(const std::string& domain);

    const std::string& GetDomain() const;

    void SetHost(const std::string& host);

    const std::string& GetHost() const;

    void SetSubType(const std::string& subtype);

    const std::string& GetSubType() const;

    void SetPort(int port);

    int GetPort() const;

    void SetInterface(int interface);

    int GetInterface() const;

    void SetProtocol(Protocol protocol);

    Protocol GetProtocol() const;

    void SetTXTRecord(const std::string& key, const std::string& value);

    std::string GetTXTRecord(const std::string& key) const;

    const TXT& GetTXT() const;

    bool operator==(const Service& rhs) const;

private:
    std::string name_;
    std::string type_;
    std::string domain_;
    std::string host_;
    std::string subtype_;
	int port_;
    int interface_;
    Protocol protocol_;
    TXT txt_;
};

}  // xzc
#endif  // SERVICE_H_

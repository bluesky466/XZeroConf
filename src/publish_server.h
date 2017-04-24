#ifndef PUBLISH_SERVER_H_
#define PUBLISH_SERVER_H_

#include <memory>

#include "service.h"

namespace xzc {

class PublishServerEntry;
class PublishServiceEntry;

class PublishServer {
public:
    PublishServer(std::shared_ptr<PublishServerEntry> entry);

    void PublishService(const Service& service,
                        const PublishCallback& on_success,
                        const PublishCallback& on_error);

	bool StopPublished(const Service& service);

    std::map<std::string, Service> GetServices() const;

private:
    void OnPublishFinish(PublishServiceEntry* entry);

private:
    std::shared_ptr<PublishServerEntry> entry_;
    std::function<void(PublishServiceEntry*)> publish_callback_;
    std::map<std::string, Service> services_;
    std::map<std::string, PublishServiceEntry*> service_entrys_;
};
}  // xzc

#endif  // PUBLISH_SERVER_H_

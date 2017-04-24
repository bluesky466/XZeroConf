#include "publish_server.h"

#include "publish_server_entry.h"

using std::shared_ptr;
using std::map;
using std::string;
using std::placeholders::_1;

namespace xzc {

PublishServer::PublishServer(shared_ptr<PublishServerEntry> entry)
        : entry_(entry),
          publish_callback_(bind(&PublishServer::OnPublishFinish, this, _1)) {
}

void PublishServer::Start() {
    entry_->Start();
}

void PublishServer::Stop() {
    entry_->Stop();
}

void PublishServer::PublishService(const Service& service,
                                   const PublishCallback& on_success,
                                   const PublishCallback& on_error) {
    entry_->PublishService(service, publish_callback_, on_success, on_error);
}

bool PublishServer::StopPublished(const Service& service) {
    auto it = service_entrys_.find(service.GetName());
    if (it == service_entrys_.end()) {
        return false;
    }

    if (!it->second->StopPublished()) {
        return false;
    }

    services_.erase(service.GetName());
    service_entrys_.erase(it);
    return true;
}

map<string, Service> PublishServer::GetServices() const {
    return services_;
}

void PublishServer::OnPublishFinish(PublishServiceEntry* entry) {
    do {
        if (!entry->IsPublished()) {
            break;
        }

        auto& service = entry->GetService();
        auto& name = service.GetName();

        auto r1 = services_.insert(make_pair(name, service));
        if (!r1.second) {
            break;
        }

        auto r2 = service_entrys_.insert(make_pair(name, entry));
        if (!r2.second) {
            services_.erase(r1.first);
            break;
        }

        entry->OnSuccess();
        return;

    } while (0);
    entry->OnError();
}

}  // xzc

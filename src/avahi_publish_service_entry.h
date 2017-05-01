#ifndef AVAHI_PUBLISH_SERVICE_ENTRY_H_
#define AVAHI_PUBLISH_SERVICE_ENTRY_H_

#include "publish_service_entry.h"

namespace xzc
{

class AvahiPublishServiceEntry : public PublishServiceEntry {
public:
    AvahiPublishServiceEntry(const Service& service, const Callback& callback,
                        const PublishCallback& on_success,
                        const PublishCallback& on_error);


    virtual bool StopPublished();
private:
};

} // xzc
#endif  // AVAHI_PUBLISH_SERVICE_ENTRY_H_

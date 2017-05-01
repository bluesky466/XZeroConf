#ifndef AVAHI_PUBLISH_SERVER_ENTRY_H_
#define AVAHI_PUBLISH_SERVER_ENTRY_H_

#include <list>
#include <mutex>
#include <thread>

#include <avahi-client/client.h>

#include "avahi_publish_service_entry.h"
#include "publish_server_entry.h"

class AvahiEntryGroup;
class AvahiSimplePoll;
class AvahiStringList;

namespace xzc {
class AvahiPublishServerEntry : public PublishServerEntry {
public:
    AvahiPublishServerEntry();
    ~AvahiPublishServerEntry();

    virtual void PublishService(const Service& service,
                                const PublishServiceEntry::Callback& callback,
                                const PublishCallback& on_success,
                                const PublishCallback& on_error);

    virtual void Start();

    virtual void Stop();

private:
	void StartPollLoop();

    void PollLoopThread();

    bool AddService(AvahiPublishServiceEntry* entry);

	AvahiStringList* GetTXT(const Service& service)const;

	void PublishWaitedServices();

    static void ClientCallback(AvahiClient* client, AvahiClientState state,
                               void* userdata);

    static void GroupCallback(AvahiEntryGroup* group,
                              AvahiEntryGroupState state, void* userdata);

private:
    AvahiSimplePoll* poll_;
    AvahiClient* client_;
    std::thread poll_loop_thread_;
    std::mutex mutex_;
	std::list<AvahiPublishServiceEntry*> wait_list_;
};
}  // xzc

#endif  // AVAHI_PUBLISH_SERVER_ENTRY_H_

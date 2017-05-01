#include "avahi_publish_server_entry.h"

#include <cassert>

#include <avahi-client/publish.h>
#include <avahi-common/simple-watch.h>
#include <avahi-common/timeval.h>

using std::move;
using std::mutex;
using std::thread;
using std::lock_guard;
using std::this_thread::sleep_for;

namespace xzc {
AvahiPublishServerEntry::AvahiPublishServerEntry()
        : poll_(nullptr),
          client_(nullptr),
          poll_loop_thread_(),
          mutex_(),
          wait_list_() {
}

AvahiPublishServerEntry::~AvahiPublishServerEntry() {
    Stop();
}

void AvahiPublishServerEntry::PublishService(
    const Service& service, const PublishServiceEntry::Callback& callback,
    const PublishCallback& on_success, const PublishCallback& on_error) {
    lock_guard<mutex> lock(mutex_);

    auto entry =
        new AvahiPublishServiceEntry(service, callback, on_success, on_error);

    if (avahi_client_get_state(client_) == AVAHI_CLIENT_S_RUNNING) {
        AddService(entry);
    } else {
        wait_list_.push_back(entry);
    }
}

void AvahiPublishServerEntry::Start() {
    poll_ = avahi_simple_poll_new();

    int error;
    client_ = avahi_client_new(
        avahi_simple_poll_get(poll_), AVAHI_CLIENT_IGNORE_USER_CONFIG,
        AvahiPublishServerEntry::ClientCallback, this, &error);

    poll_loop_thread_ =
        move(thread(&AvahiPublishServerEntry::PollLoopThread, this));
}

void AvahiPublishServerEntry::Stop() {
    if (poll_) {
        avahi_simple_poll_quit(poll_);
    }

    if (client_) {
        avahi_client_free(client_);
        client_ = nullptr;
    }
    if (poll_) {
        avahi_simple_poll_free(poll_);
        poll_ = nullptr;
    }

    if (poll_loop_thread_.joinable()) {
        poll_loop_thread_.join();
    }
}

void AvahiPublishServerEntry::StartPollLoop() {
}

void AvahiPublishServerEntry::PollLoopThread() {
    if (poll_) {
        avahi_simple_poll_loop(poll_);
    }
}

bool AvahiPublishServerEntry::AddService(AvahiPublishServiceEntry* entry) {
    AvahiEntryGroup* group = avahi_entry_group_new(
        client_, &AvahiPublishServerEntry::GroupCallback, this);

    if (!avahi_entry_group_is_empty(group)) {
        entry->SetPublishFinished(false);
        entry->OnPublished();
        return false;
    }

    auto& service = entry->GetService();
    int ret = avahi_entry_group_add_service_strlst(
        group, AVAHI_IF_UNSPEC, AVAHI_PROTO_UNSPEC, AVAHI_PUBLISH_UNIQUE,
        service.GetName().c_str(), service.GetType().c_str(),
        service.GetDomain().c_str(), service.GetHost().c_str(),
        service.GetPort(), GetTXT(service));

    entry->SetPublishFinished(true);
    entry->OnPublished();
    return true;
}

AvahiStringList* AvahiPublishServerEntry::GetTXT(const Service& service) const {
    auto& txt = service.GetTXT();

    AvahiStringList* list = nullptr;
    for (auto i : txt) {
        const char* key = i.first.c_str();
        const char* value = i.second.c_str();
        list = avahi_string_list_add_pair(list, key, value);
    }
    return list;
}

void AvahiPublishServerEntry::PublishWaitedServices() {
    for (auto i : wait_list_) {
        AddService(i);
    }
}

void AvahiPublishServerEntry::ClientCallback(AvahiClient* client,
                                             AvahiClientState state,
                                             void* userdata) {
    assert(client && "AvahiPublisher::ClientCallback client is null!");
    printf("ClientCallback 1\n");

    AvahiPublishServerEntry* instance =
        static_cast<AvahiPublishServerEntry*>(userdata);

    lock_guard<mutex> lock(instance->mutex_);

    switch (state) {
        case AVAHI_CLIENT_S_RUNNING:
            break;
        case AVAHI_CLIENT_FAILURE:
            break;
        default:
            break;
    }
    printf("ClientCallback 2\n");
}

void AvahiPublishServerEntry::GroupCallback(AvahiEntryGroup* group,
                                            AvahiEntryGroupState state,
                                            void* userdata) {
}

}  // xzc

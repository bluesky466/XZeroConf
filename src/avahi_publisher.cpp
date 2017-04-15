#include "avahi_publisher.h"

using std::move;
using std::thread;

namespace xzc {

AvahiPublisher::AvahiPublisher()
        : is_running_(false),
          is_poll_loopping_(false),
          poll_(avahi_simple_poll_new()),
          poll_loop_thread_() {
    logger_ = spdlog::stdout_color_mt("AvahiPublisher");
    StartPoolLoop();
}

AvahiPublisher::~AvahiPublisher() {
    StopPollLoop();
    poll_loop_thread_.join();
}

void AvahiPublisher::Start() {
    int error = 0;
    avahi_client_new(avahi_simple_poll_get(poll_),
                     AVAHI_CLIENT_IGNORE_USER_CONFIG,
                     AvahiPublisher::ClientCallback, this, &error);
}

void AvahiPublisher::Stop() {
    is_running_ = false;
}

bool AvahiPublisher::IsRunning() const {
    return is_running_;
}

bool AvahiPublisher::IsPollLoop() const {
    return is_poll_loopping_;
}

void AvahiPublisher::StartPoolLoop() {
    assert(!is_poll_loopping_ && "poll is looping");

    if (poll_loop_thread_.joinable()) {
        poll_loop_thread_.join();
    }
    poll_loop_thread_ = move(thread(&AvahiPublisher::PollLoopThread, this));
}

void AvahiPublisher::StopPollLoop() {
    assert(is_poll_loopping_ && "poll is not looping");
    Stop();
    avahi_simple_poll_quit(poll_);
}

void AvahiPublisher::PollLoopThread() {
    is_poll_loopping_ = true;
    avahi_simple_poll_loop(poll_);
    is_poll_loopping_ = false;
}

void AvahiPublisher::ClientCallback(AvahiClient* client, AvahiClientState state,
                                    void* userdata) {
    assert(client && "AvahiPublisher::ClientCallback client is null!");

    AvahiPublisher* instance = static_cast<AvahiPublisher*>(userdata);

    switch (state) {
        case AVAHI_CLIENT_S_RUNNING:
            instance->is_running_ = true;
            break;
        case AVAHI_CLIENT_FAILURE:
            instance->logger_->info("AVAHI_CLIENT_FAILURE");
            instance->StopPollLoop();
            break;
        default:
            break;
    }
}

}  // xzc

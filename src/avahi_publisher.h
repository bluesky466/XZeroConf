#ifndef AVAHI_PUBLISHER_H_
#define AVAHI_PUBLISHER_H_

#include <cassert>
#include <thread>

#include <avahi-client/client.h>
#include <avahi-common/simple-watch.h>

#include "spdlog/spdlog.h"

namespace xzc {

class AvahiPublisher {
public:
    AvahiPublisher();

    ~AvahiPublisher();

    void Start();

    void Stop();

    bool IsRunning() const;

    bool IsPollLoop() const;

    void StartPoolLoop();

    void StopPollLoop();

private:
    void PollLoopThread();

    static void ClientCallback(AvahiClient* client, AvahiClientState state,
                               void* userdata);

private:
    std::shared_ptr<spdlog::logger> logger_;
    bool is_running_;
    bool is_poll_loopping_;
    AvahiSimplePoll* poll_;
    std::thread poll_loop_thread_;
    AvahiClient* client_;
};

}  // xzc
#endif  // AVAHI_PUBLISHER_H_

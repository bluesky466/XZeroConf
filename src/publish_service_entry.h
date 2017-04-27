#ifndef PUBLISH_SERVICE_ENTRY_H_
#define PUBLISH_SERVICE_ENTRY_H_

#include <functional>

#include "service.h"

namespace xzc {

class PublishServiceEntry {
public:
    typedef std::function<void(PublishServiceEntry*)> Callback;

public:
    PublishServiceEntry(const Service& service, const Callback& callback,
                        const PublishCallback& on_success,
                        const PublishCallback& on_error);

	virtual ~PublishServiceEntry();

    bool IsPublished() const;

    void SetPublishFinished(bool is_published);

    void OnPublished();

    void OnSuccess() const;

    void OnError() const;

    const Service& GetService() const;

    virtual bool StopPublished() = 0;

private:
    bool is_published_;
    Service service_;
    Callback callback_;
    PublishCallback on_success_;
    PublishCallback on_error_;
};

}  // xzc

#endif  // PUBLISH_SERVICE_ENTRY_H_

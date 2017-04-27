#include "publish_service_entry.h"

namespace xzc {
PublishServiceEntry::PublishServiceEntry(const Service& service,
                                         const Callback& callback,
                                         const PublishCallback& on_success,
                                         const PublishCallback& on_error)
        : is_published_(false),
          service_(service),
          callback_(callback),
          on_success_(on_success),
          on_error_(on_error) {
}

PublishServiceEntry::~PublishServiceEntry() {
}

bool PublishServiceEntry::IsPublished() const {
    return is_published_;
}

void PublishServiceEntry::SetPublishFinished(bool is_published) {
    is_published_ = is_published;
}

void PublishServiceEntry::OnPublished() {
    if (callback_) {
        callback_(this);
    }
}

void PublishServiceEntry::OnSuccess() const {
    if (on_success_) {
        on_success_(service_);
    }
}

void PublishServiceEntry::OnError() const {
    if (on_error_) {
        on_error_(service_);
    }
}

const Service& PublishServiceEntry::GetService() const {
    return service_;
}
}  // xzc

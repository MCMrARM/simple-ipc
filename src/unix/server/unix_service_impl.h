#pragma once

#include <simpleipc/server/service_impl.h>

namespace simpleipc {
namespace server {

class unix_service_impl : public service_impl {

private:
    callback_interface* cb;
    int fd = -1;
    std::string path;

public:
    void set_callback_interface(callback_interface* cb) override {
        this->cb = cb;
    }

    void bind(std::string const& path) override;

    void close() override;

};

}
}
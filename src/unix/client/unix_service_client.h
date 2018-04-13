#pragma once

#include <simpleipc/client/service_client_impl.h>

namespace simpleipc {
namespace client {

class unix_service_client_impl : public service_client_impl {

private:
    callback_interface* cb;
    int fd = -1;
    std::string path;

public:
    void set_callback_interface(callback_interface* cb) override {
        this->cb = cb;
    }

    void open(std::string const& path) override;

    void send_message(const char* data, size_t datalen) override {
        //
    }

    void close() override;

};

}
}
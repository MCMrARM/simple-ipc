#pragma once

#include <string>
#include "../common/connection.h"
#include "service_client_impl.h"

namespace simpleipc {
namespace client {

class service_client : public connection, private service_client_impl::callback_interface {

private:
    std::unique_ptr<service_client_impl> impl;

    void handle(char* data, size_t datalen) override {}

public:
    service_client(std::unique_ptr<service_client_impl> impl) : impl(std::move(impl)) {
        impl->set_callback_interface(this);
    }
    service_client(std::string const& path) : impl(service_client_impl_factory::create_platform_service()) {
        impl->set_callback_interface(this);
        impl->open(path);
    }

    void send_message(nlohmann::json const& data) override {
        impl->send_message(data);
    }

};

}
}
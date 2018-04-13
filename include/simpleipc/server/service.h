#pragma once

#include <nlohmann/json.hpp>
#include "../common/connection.h"
#include "service_impl.h"

namespace simpleipc {
namespace server {

class service : public service_impl::callback_interface {

private:
    std::unique_ptr<service_impl> impl;

public:
    service(std::unique_ptr<service_impl> impl) : impl(std::move(impl)) {
        impl->set_callback_interface(this);
    }

    service(std::string const& path) : impl(service_impl_factory::create_platform_service()) {
        impl->set_callback_interface(this);
        impl->bind(path);
    }

    ~service() {
        impl->close();
    }

    virtual bool connect(connection const& client, nlohmann::json const& req) { return true; }

    virtual void disconnect(connection const& client) {}

    virtual void handle(connection const& client, nlohmann::json const& req) = 0;

};

}
}
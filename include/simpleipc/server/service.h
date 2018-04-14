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
        this->impl->set_callback_interface(this);
    }

    service(std::string const& path) : service(service_impl_factory::create_platform_service()) {
        impl->bind(path);
    }

    ~service() {
        impl->close();
    }

};

}
}
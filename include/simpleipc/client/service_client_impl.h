#pragma once

#include <string>
#include <nlohmann/json.hpp>
#include "../common/connection.h"

namespace simpleipc {
namespace client {

class service_client_impl {

public:
    class callback_interface {

    public:
        virtual void handle(char* data, size_t datalen) = 0;

    };

    virtual void set_callback_interface(callback_interface* cb) = 0;

    virtual void open(std::string const& path) = 0;

    virtual void send_message(rpc_message const& msg) = 0;

    virtual void close() = 0;

};

class service_client_impl_factory {

public:
    static std::unique_ptr<service_client_impl> create_platform_service();

};

}
}
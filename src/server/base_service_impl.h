#pragma once

#include <simpleipc/server/service_impl.h>

namespace simpleipc {
namespace server {

class base_service_impl : public service_impl {

protected:
    callback_interface* cb;

public:
    void set_callback_interface(callback_interface* cb) override {
        this->cb = cb;
    }

    void handle_message(connection& conn, rpc_message const& msg) override {
        cb->handle_message(conn, msg);
    }

};

}
}
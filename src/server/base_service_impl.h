#pragma once

#include <simpleipc/server/service_impl.h>
#include "default_rpc_handler.h"

namespace simpleipc {
namespace server {

class base_service_impl : public service_impl {

protected:
    callback_interface* cb;
    default_rpc_handler default_handler;

public:
    void set_callback_interface(callback_interface* cb) override {
        this->cb = cb;
    }

    void handle_message(connection& conn, rpc_message const& msg) override {
        if (msg.method().size() > 0 && msg.method()[0] == '.') {
            default_handler.invoke(conn.shared_from_this(), msg);
            return;
        }
        cb->handle_message(conn, msg);
    }

};

}
}
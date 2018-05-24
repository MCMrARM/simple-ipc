#pragma once

#include <simpleipc/client/service_client_impl.h>

namespace simpleipc {
namespace client {

class base_service_client_impl : public service_client_impl {

protected:
    callback_interface* cb = nullptr;

public:
    void set_callback_interface(callback_interface* cb) override {
        this->cb = cb;
    }

    void connection_closed(connection&) override {
        close();
        if (cb)
            cb->connection_closed();
    }

    void handle_message(connection&, response_message const& msg) override {
        if (cb)
            cb->handle_message(msg);
    }

    void handle_message(connection&, error_message const& msg) override {
        if (cb)
            cb->handle_message(msg);
    }

};

}
}
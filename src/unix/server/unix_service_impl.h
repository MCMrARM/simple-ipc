#pragma once

#include <simpleipc/server/service_impl.h>
#include <unordered_set>
#include <memory>
#include "../common/unix_connection.h"

namespace simpleipc {
namespace server {

class unix_service_impl : public service_impl {

private:
    callback_interface* cb;
    int fd = -1;
    std::string path;
    std::unordered_set<unix_connection*> connections;

    void handle_incoming();

    void on_connection_closed(unix_connection* conn);

public:
    ~unix_service_impl();

    void set_callback_interface(callback_interface* cb) override {
        this->cb = cb;
    }

    void bind(std::string const& path) override;

    void close() override;

};

}
}
#pragma once

#include <simpleipc/client/service_client_impl.h>
#include "../common/unix_connection.h"

namespace simpleipc {
namespace client {

class unix_service_client_impl : public service_client_impl {

private:
    callback_interface* cb;
    int fd = -1;
    std::string path;
    std::unique_ptr<unix_connection> connection;

public:
    void set_callback_interface(callback_interface* cb) override {
        this->cb = cb;
    }

    void open(std::string const& path) override;

    void send_message(std::string const& method, nlohmann::json const& data) override;

    void close() override;

};

}
}
#pragma once

#include <string>
#include <unordered_map>
#include <mutex>
#include <atomic>
#include "../common/connection.h"
#include "../common/message/message_id.h"
#include "service_client_impl.h"
#include "rpc_call.h"

namespace simpleipc {
namespace client {

class service_client : private service_client_impl::callback_interface {

private:
    friend class rpc_call;

    std::unique_ptr<service_client_impl> impl;
    std::atomic<message_id> next_message_id;
    std::recursive_mutex cb_mutex;
    std::unordered_map<message_id, rpc_result_callback> cbs;

    void handle_message(response_message const& msg) override;

    void handle_message(error_message const& msg) override;


    void send_message(rpc_message const& msg);

    void add_rpc_cb(message_id msg, rpc_result_callback cb);

    rpc_result_callback get_rpc_cb(message_id msg);

public:
    service_client(std::unique_ptr<service_client_impl> impl) : impl(std::move(impl)), next_message_id(0) {
        this->impl->set_callback_interface(this);
    }
    service_client(std::string const& path) : service_client(service_client_impl_factory::create_platform_service()) {
        impl->open(path);
    }

    rpc_call rpc(std::string method, nlohmann::json data) {
        return rpc_call(*this, std::move(method), std::move(data));
    }

    void connection_closed() override {}


};

}
}
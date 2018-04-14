#include <simpleipc/client/service_client.h>

using namespace simpleipc::client;

void service_client::add_rpc_cb(message_id msg, rpc_result_callback cb) {
    std::lock_guard<std::recursive_mutex> lock(cb_mutex);
    cbs[msg] = cb;
}

void service_client::send_message(rpc_message const& msg) {
    impl->send_message(msg);
}
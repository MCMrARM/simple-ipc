#include <simpleipc/client/service_client.h>
#include <simpleipc/common/message/response_message.h>
#include <simpleipc/common/message/error_message.h>

using namespace simpleipc::client;

void service_client::add_rpc_cb(message_id msg, rpc_result_callback cb) {
    std::lock_guard<std::recursive_mutex> lock(cb_mutex);
    cbs[msg] = cb;
}

void service_client::send_message(rpc_message const& msg) {
    impl->send_message(msg);
}

rpc_result_callback service_client::get_rpc_cb(message_id msg) {
    std::lock_guard<std::recursive_mutex> lock(cb_mutex);
    auto it = cbs.find(msg);
    if (it != cbs.end()) {
        auto val = it->second;
        cbs.erase(it);
        return std::move(val);
    }
    return nullptr;
}

void service_client::handle_message(response_message const& msg) {
    if (!msg.has_id())
        return;
    auto cb = get_rpc_cb(msg.id());
    if (cb)
        cb(rpc_result::response(msg.data()));
}

void service_client::handle_message(error_message const& msg) {
    if (!msg.has_id())
        return;
    auto cb = get_rpc_cb(msg.id());
    if (cb)
        cb(rpc_result::error(msg.error_code(), msg.error_text(), msg.data()));
}
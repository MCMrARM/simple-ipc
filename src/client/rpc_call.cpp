#include <simpleipc/client/rpc_call.h>
#include <simpleipc/client/service_client.h>
#include <simpleipc/common/message/rpc_message.h>
#include <condition_variable>
#include <future>

using namespace simpleipc;
using namespace simpleipc::client;

void rpc_call::run() {
    client.send_message(rpc_message(method, data));
}

void rpc_call::call(rpc_result_callback cb) {
    auto msg_id = client.next_message_id.fetch_add(1);
    client.add_rpc_cb(msg_id, cb);
    client.send_message(rpc_message(msg_id, method, data));
}

rpc_result rpc_call::call() {
    std::promise<rpc_result> result;
    auto future = result.get_future();
    call([&result](rpc_result new_result) {
        result.set_value(std::move(new_result));
    });
    return future.get();
}
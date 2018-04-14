#include <simpleipc/client/rpc_call.h>
#include <simpleipc/client/service_client.h>
#include <simpleipc/common/message/rpc_message.h>
#include <condition_variable>

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
    std::condition_variable cv;
    std::mutex mutex;
    rpc_result result;
    bool has_result = false;
    call([&result, &has_result, &mutex, &cv](rpc_result new_result) {
        std::lock_guard<std::mutex> lock (mutex);
        result = std::move(new_result);
        has_result = true;
        cv.notify_all();
    });
    std::unique_lock<std::mutex> lock (mutex);
    cv.wait(lock, [&has_result] { return has_result; });
    return result;
}
#include <simpleipc/server/rpc_handler.h>
#include <simpleipc/common/connection.h>
#include <simpleipc/common/message/rpc_message.h>
#include <simpleipc/common/message/response_message.h>
#include <simpleipc/common/message/error_message.h>

using namespace simpleipc::server;

void rpc_handler::add_handler_async(std::string const& method, call_handler_async handler) {
    if (handlers.count(method) > 0)
        throw std::runtime_error("A handler for this method already exists");
    handlers[method] = std::move(handler);
}

void rpc_handler::invoke(connection& conn, std::string const& method, nlohmann::json const& data,
                         result_handler const& handler) {
    auto h = handlers.find(method);
    if (h == handlers.end())
        throw std::runtime_error("No handler available for this method");
    h->second(conn, method, data, std::move(handler));
}

void rpc_handler::invoke(connection& conn, rpc_message const& msg) {
    if (msg.has_id()) {
        message_id id = msg.id();
        connection* conn_ptr = &conn;
        invoke(conn, msg.method(), msg.data(), [conn_ptr, id](rpc_result result) { // TODO: the connection may be destroyed before, change to shared_ptr
            if (result.success())
                conn_ptr->send_message(response_message(id, std::move(result._data)));
            else
                conn_ptr->send_message(error_message(id, result._error_code, std::move(result._error_text),
                                                      std::move(result._data)));
        });
    } else {
        invoke(conn, msg.method(), msg.data(), [](rpc_result) {});
    }
}
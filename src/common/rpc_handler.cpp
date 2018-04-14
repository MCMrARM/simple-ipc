#include <simpleipc/common/rpc_handler.h>

using namespace simpleipc;

void rpc_handler::add_handler(std::string const& method, call_handler_async handler) {
    if (handlers.count(method) > 0)
        throw std::runtime_error("A handler for this method already exists");
    handlers[method] = std::move(handler);
}

void rpc_handler::invoke(std::string const& method, nlohmann::json const& data, result_handler handler) {
    if (handlers.count(method) < 0)
        throw std::runtime_error("No handler available for this method");
    handlers.at(method)(method, data, std::move(handler));
}
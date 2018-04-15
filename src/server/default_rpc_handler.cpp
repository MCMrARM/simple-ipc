#include "default_rpc_handler.h"
#include <simpleipc/common/version.h>

using namespace simpleipc::server;

default_rpc_handler::default_rpc_handler() {
    using namespace std::placeholders;
    add_handler(".hello", [this](nlohmann::json const& data) { return handle_hello(data); });
}

simpleipc::rpc_result default_rpc_handler::handle_hello(nlohmann::json const& data) {
    return rpc_result::response({
            {"version", version::current_version}
    });
}
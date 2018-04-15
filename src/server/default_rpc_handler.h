#pragma once

#include <simpleipc/common/rpc_handler.h>

namespace simpleipc {
namespace server {

class default_rpc_handler : public rpc_handler {

public:
    default_rpc_handler();

private:
    rpc_result handle_hello(nlohmann::json const& data);

};

}
}
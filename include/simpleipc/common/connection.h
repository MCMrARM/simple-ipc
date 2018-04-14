#pragma once

#include <nlohmann/json.hpp>

namespace simpleipc {

class rpc_message;
class response_message;
class error_message;

class connection {

public:
    virtual void send_message(rpc_message const& msg) = 0;

    virtual void send_message(response_message const& msg) = 0;

    virtual void send_message(error_message const& msg) = 0;

};

}
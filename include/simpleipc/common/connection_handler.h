#pragma once

#include <stdexcept>
#include <nlohmann/json.hpp>

namespace simpleipc {

class rpc_message;
class response_message;
class error_message;

class connection_handler {

public:
    virtual void connection_closed(connection& connection) {}

    virtual void handle_message(connection& connection, rpc_message const& msg) {
        throw std::runtime_error("Unsupported message");
    }

    virtual void handle_message(connection& connection, response_message const& msg) {
        throw std::runtime_error("Unsupported message");
    }

    virtual void handle_message(connection& connection, error_message const& msg) {
        throw std::runtime_error("Unsupported message");
    }

};

}
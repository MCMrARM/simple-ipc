#pragma once

#include <functional>
#include <nlohmann/json.hpp>

namespace simpleipc {

class rpc_handler {

public:
    using call_handler = std::function<void (std::string const& method, nlohmann::json const& data)>;
    using call_handler_data_only = std::function<void (nlohmann::json const& data)>;

private:
    std::map<std::string, call_handler> handlers;

public:
    void add_handler(std::string const& method, call_handler handler);

    void add_handler(std::string const& method, call_handler_data_only handler) {
        add_handler(method, std::bind(handler, std::placeholders::_2));
    }

    void invoke(std::string const& method, nlohmann::json const& data);

};

}
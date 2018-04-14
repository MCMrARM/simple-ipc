#pragma once

#include <functional>
#include <nlohmann/json.hpp>
#include "rpc_result.h"

namespace simpleipc {

class rpc_handler {

public:
    using result_handler = std::function<void (rpc_result const&)>;

    using call_handler_async = std::function<void (std::string const& method, nlohmann::json const& data, result_handler)>;
    using call_handler_async_data_only = std::function<void (nlohmann::json const& data, result_handler)>;

    using call_handler_sync = std::function<rpc_result (std::string const& method, nlohmann::json const& data)>;
    using call_handler_sync_data_only = std::function<rpc_result (nlohmann::json const& data)>;

private:
    std::map<std::string, call_handler_async> handlers;

public:
    void add_handler(std::string const& method, call_handler_async handler);

    void add_handler(std::string const& method, call_handler_async_data_only handler) {
        add_handler(method, std::bind(handler, std::placeholders::_2, std::placeholders::_3));
    }

    void add_handler(std::string const& method, call_handler_sync handler) {
        add_handler(method, [handler](std::string const& method, nlohmann::json const& data, result_handler result) {
            result(handler(method, data));
        });
    }

    void add_handler(std::string const& method, call_handler_sync_data_only handler) {
        add_handler(method, [handler](std::string const& method, nlohmann::json const& data, result_handler result) {
            result(handler(data));
        });
    }


    void invoke(std::string const& method, nlohmann::json const& data, result_handler handler);

};

}
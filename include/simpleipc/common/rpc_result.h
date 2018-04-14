#pragma once

#include <string>
#include "message/error_code.h"
#include <nlohmann/json.hpp>

namespace simpleipc {

class rpc_handler;

struct rpc_result {

private:
    friend class rpc_handler;

    rpc_error_code _error_code;
    std::string _error_text;
    nlohmann::json _data;

public:
    rpc_result() {}

    rpc_result(rpc_error_code error_code, std::string error_text, nlohmann::json data) :
            _error_code(error_code), _error_text(std::move(error_text)), _data(std::move(data)) {}

    static rpc_result response(nlohmann::json data) {
        return rpc_result(rpc_error_codes::success, std::string(), std::move(data));
    }
    static rpc_result error(rpc_error_code error_code, std::string error_text, nlohmann::json data) {
        return rpc_result(error_code, std::move(error_text), std::move(data));
    }
    static rpc_result error(rpc_error_code error_code, rpc_error_string_translator tr, nlohmann::json data) {
        return rpc_result(error_code, tr(error_code), std::move(data));
    }

    constexpr rpc_error_code error_code() const { return _error_code; }

    constexpr std::string const& error_text() const { return _error_text; }

    constexpr nlohmann::json const& data() const { return _data; }

    constexpr bool success() const { return error_code() == rpc_error_codes::success; }


};

}
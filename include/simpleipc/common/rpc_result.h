#pragma once

#include <string>
#include "message/error_code.h"
#include <nlohmann/json.hpp>

namespace simpleipc {

namespace server {
class rpc_handler;
}

template <typename T>
struct rpc_result {

private:
    friend class server::rpc_handler;

    rpc_error_code _error_code;
    std::string _error_text;
    T _data;

public:
    rpc_result() {}

    rpc_result(rpc_error_code error_code, std::string error_text, T data) :
            _error_code(error_code), _error_text(std::move(error_text)), _data(std::move(data)) {}

    static rpc_result response(T data) {
        return rpc_result(rpc_error_codes::success, std::string(), std::move(data));
    }
    static rpc_result error(rpc_error_code error_code, std::string error_text, nlohmann::json data = nullptr) {
        return rpc_result(error_code, std::move(error_text), std::move(data));
    }
    static rpc_result error(rpc_error_code error_code, rpc_error_string_translator const& tr,
                            nlohmann::json data = nullptr) {
        return rpc_result(error_code, tr(error_code), std::move(data));
    }

    constexpr rpc_error_code error_code() const { return _error_code; }

    constexpr std::string const& error_text() const { return _error_text; }

    constexpr T const& data() const { return _data; }

    constexpr bool success() const { return error_code() == rpc_error_codes::success; }


};

using rpc_json_result = rpc_result<nlohmann::json>;

}
#pragma once

#include <string>
#include "message/error_code.h"
#include <nlohmann/json.hpp>

namespace simpleipc {

struct rpc_result {

    rpc_error_code error_code;
    std::string error_text;
    nlohmann::json data;

    static rpc_result response(nlohmann::json data) {
        return {rpc_error_codes::success, std::string(), std::move(data)};
    }
    static rpc_result error(rpc_error_code error_code, std::string error_text, nlohmann::json data) {
        return {error_code, std::move(error_text), std::move(data)};
    }
    static rpc_result error(rpc_error_code error_code, rpc_error_string_translator tr, nlohmann::json data) {
        return {error_code, tr(error_code), std::move(data)};
    }

};

}
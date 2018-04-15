#pragma once

#include <nlohmann/json.hpp>
#include "message/error_code.h"

namespace simpleipc {

class rpc_call_exception_interface : public std::exception {

public:
    virtual rpc_error_code code() const = 0;
    virtual nlohmann::json const& data() const = 0;

};

class rpc_call_exception : public rpc_call_exception_interface {

private:
    rpc_error_code _code;
    nlohmann::json _data;

public:
    rpc_call_exception(rpc_error_code code, nlohmann::json data) : _code(code), _data(std::move(data)) {
    }

    virtual rpc_error_code code() const {
        return _code;
    }
    virtual nlohmann::json const& data() const {
        return _data;
    }

};

}
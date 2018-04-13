#pragma once

#include <nlohmann/json.hpp>

namespace simpleipc {

class connection_internal;

namespace encoding {

class encoding {

public:
    virtual void send_message(connection_internal& conn, nlohmann::json const& data) = 0;

};

}

}
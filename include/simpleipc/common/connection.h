#pragma once

#include <nlohmann/json.hpp>

namespace simpleipc {

class connection {

public:
    virtual void send_message(nlohmann::json const& data) = 0;

};

}
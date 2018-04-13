#pragma once

#include <nlohmann/json.hpp>

namespace simpleipc {
class connection {

public:
    virtual void send_message(const char* data, size_t datalen) = 0;

    void send_message(nlohmann::json const& data) {
        std::string str = data.dump();
        send_message(str.data(), str.length());
    }

};
}
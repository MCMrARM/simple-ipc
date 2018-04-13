#pragma once

#include <nlohmann/json.hpp>

namespace simpleipc {

class connection_internal;

namespace encoding {

struct decoded_message {
    std::string method;
    nlohmann::json data;
};

class encoding {

public:
    virtual void send_message(connection_internal& conn, std::string const& method, nlohmann::json const& data) = 0;

    // negative if not complete (-1), otherwise the byte offset of the end
    virtual ssize_t check_read_message_complete(const char* buf, size_t buf_size, size_t last_read_off) = 0;

    virtual decoded_message read_message(const char* buf, size_t buf_size) = 0;

};

}

}
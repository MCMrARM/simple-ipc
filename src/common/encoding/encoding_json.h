#pragma once

#include "encoding.h"

namespace simpleipc {
namespace encoding {

class json : public encoding {

public:
    void send_message(connection_internal& conn, std::string const& method, nlohmann::json const& data) override;

    ssize_t check_read_message_complete(const char* buf, size_t buf_size, size_t last_read_off) override;

    decoded_message read_message(const char* buf, size_t buf_size) override;

};
}
}
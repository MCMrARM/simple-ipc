#include "encoding_json.h"

#include "../connection_internal.h"

using namespace simpleipc;

void encoding::json::send_message(connection_internal& conn, std::string const& method, nlohmann::json const& data) {
    nlohmann::json full_data;
    full_data["m"] = method;
    full_data["d"] = data;

    std::string buf = full_data.dump();
    if (buf.length() + 1 > conn.get_max_out_msg_size())
        throw std::runtime_error("Message is too big");
    conn.send_data(buf.c_str(), buf.size() + 1);
}

ssize_t encoding::json::check_read_message_complete(const char* buf, size_t buf_size, size_t last_read_off) {
    for (size_t i = last_read_off; i < buf_size; i++) {
        if (buf[i] == '\n' || buf[i] == '\0')
            return i;
    }
    return -1;
}

encoding::decoded_message encoding::json::read_message(const char* buf, size_t buf_size) {
    nlohmann::json full_data = nlohmann::json::parse(nlohmann::detail::input_adapter(buf, buf_size));

    decoded_message msg;
    msg.method = full_data["m"];
    msg.data = full_data["d"];
    return msg;
}
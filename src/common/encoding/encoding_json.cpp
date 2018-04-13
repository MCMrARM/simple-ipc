#include "encoding_json.h"

#include "../connection_internal.h"

using namespace simpleipc;

void encoding::json::send_message(connection_internal& conn, nlohmann::json const& data) {
    std::string buf = data.dump();
    if (buf.length() + 1 > conn.get_max_out_msg_size())
        throw std::runtime_error("Message is too big");
    conn.send_data(buf.c_str(), buf.size() + 1); // zero terminated
}
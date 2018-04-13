#include "encoding_json_cbor.h"
#include "varint.h"

#include "../connection_internal.h"

using namespace simpleipc;

void encoding::json_cbor::send_message(connection_internal& conn, std::string const& method,
                                       nlohmann::json const& data) {
    nlohmann::json full_json = {method, data};
    auto buf = nlohmann::json::to_cbor(full_json);

    char vbuf[10];
    size_t vbufs;
    varint::encode_unsigned(buf.size(), vbuf, vbufs);
    conn.send_data(vbuf, vbufs);
    conn.send_data((char*) buf.data(), buf.size());
}

ssize_t encoding::json_cbor::check_read_message_complete(const char* buf, size_t buf_size, size_t last_read_off) {
    size_t varint_size = buf_size;
    auto size = varint::decode_unsigned(buf, buf_size, &varint_size);
    return buf_size >= size + varint_size;
}

encoding::decoded_message encoding::json_cbor::read_message(const char* buf, size_t buf_size) {
    size_t varint_size = buf_size;
    auto size = varint::decode_unsigned(buf, buf_size, &varint_size);
    nlohmann::json full_json =
            nlohmann::json::from_cbor(nlohmann::detail::input_adapter(&buf[varint_size], buf_size - varint_size));

    decoded_message msg;
    msg.method = full_json[0];
    msg.data = full_json[1];
    return msg;
}
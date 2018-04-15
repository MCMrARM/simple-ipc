#pragma once

#include <simpleipc/common/connection.h>
#include <simpleipc/common/connection_handler.h>
#include <mutex>
#include "encoding/encoding.h"
#include "encoding/encodings.h"

namespace simpleipc {

class connection_internal : public connection {

public:
    using message_callback = std::function<void (std::string const& method, nlohmann::json const& data)>;
    using close_callback = std::function<void ()>;

private:
    static const size_t BUFFER_SIZE = 1024 * 16;
    static const size_t MAX_BUFFER_SIZE = 1024 * 512;

    connection_handler* handler;
    std::vector<char> buffer;
    size_t buffer_start_off = 0;
    size_t buffer_off = 0;
    encoding::encoding* current_encoding = encoding::encodings::get_default_encoding();
    size_t max_out_msg_size = MAX_BUFFER_SIZE;
    message_container current_message;

public:
    connection_internal() : buffer(BUFFER_SIZE) {
    }

    inline size_t get_max_out_msg_size() const {
        return max_out_msg_size;
    }

    void set_handler(connection_handler* handler) {
        this->handler = handler;
    }

    void set_encoding(encoding::encoding* enc) {
        current_encoding = enc;
    }

    virtual void register_io_handler() = 0;

    virtual void unregister_io_handler() = 0;

    virtual void send_data(const char* data, size_t datalen) = 0;

    virtual ssize_t read_data(char* data, size_t datalen) = 0;


    virtual void send_message(rpc_message const& msg) {
        current_encoding->send_message(*this, msg);
    }

    virtual void send_message(response_message const& msg) {
        current_encoding->send_message(*this, msg);
    }

    virtual void send_message(error_message const& msg) {
        current_encoding->send_message(*this, msg);
    }

protected:
    void on_message(message_container const& msg);

    void on_close() {
        handler->connection_closed(*this);
    }


    void handle_data_available();

};

}
#pragma once

#include <simpleipc/common/connection.h>
#include <mutex>
#include "encoding/encoding.h"
#include "encoding/encodings.h"

namespace simpleipc {

class connection_internal : public connection {

public:
    using message_callback = std::function<void (const char*, size_t)>;
    using close_callback = std::function<void ()>;

private:
    static const size_t BUFFER_SIZE = 1024 * 16;
    static const size_t MAX_BUFFER_SIZE = 1024 * 512;

    std::mutex callback_mutex;
    message_callback callback_message;
    close_callback callback_close;
    std::vector<char> buffer;
    encoding::encoding* current_encoding = encoding::encodings::get_default_encoding();
    size_t max_out_msg_size = MAX_BUFFER_SIZE;

public:
    connection_internal() : buffer(BUFFER_SIZE) {
    }

    inline size_t get_max_out_msg_size() const {
        return max_out_msg_size;
    }

    void set_message_callback(message_callback callback) {
        std::lock_guard<std::mutex> guard(callback_mutex);
        callback_message = callback;
    }

    void set_close_callback(close_callback callback) {
        std::lock_guard<std::mutex> guard(callback_mutex);
        callback_close = callback;
    }

    virtual void register_io_handler() = 0;

    virtual void unregister_io_handler() = 0;

    virtual void send_data(const char* data, size_t datalen) = 0;

    virtual ssize_t read_data(char* data, size_t datalen) = 0;


    void send_message(std::string const& method, nlohmann::json const& data) override;

protected:
    void on_message(const char* data, size_t datalen) {
        std::lock_guard<std::mutex> guard(callback_mutex);
        if (callback_message)
            callback_message(data, datalen);
    }

    void on_close() {
        std::lock_guard<std::mutex> guard(callback_mutex);
        if (callback_close)
            callback_close();
    }


    void handle_data_available();

};

}
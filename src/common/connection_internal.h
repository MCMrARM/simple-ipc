#pragma once

#include <simpleipc/common/connection.h>
#include <mutex>

namespace simpleipc {

class connection_internal : public connection {

public:
    using message_callback = std::function<void (const char*, size_t)>;
    using close_callback = std::function<void ()>;

private:
    std::mutex callback_mutex;
    message_callback callback_message;
    close_callback callback_close;

public:
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


    virtual void send_message(const char* data, size_t datalen) {
        send_data(data, datalen);
    }

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
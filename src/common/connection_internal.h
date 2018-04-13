#pragma once

#include <simpleipc/common/connection.h>

namespace simpleipc {

class connection_internal : public connection {

public:
    virtual void send_data(const char* data, size_t datalen) = 0;

    virtual ssize_t read_data(char* data, size_t datalen) = 0;


    virtual void send_message(const char* data, size_t datalen) {
        send_data(data, datalen);
    }

};

}
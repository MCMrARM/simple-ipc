#pragma once

#include "../../common/connection_internal.h"

namespace simpleipc {

class unix_connection : public connection_internal {

private:
    int fd;

public:
    unix_connection(int fd) : fd(fd) {}

    void send_data(const char* data, size_t datalen) override;

    ssize_t read_data(char* data, size_t datalen) override;

};

}
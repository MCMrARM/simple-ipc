#include "unix_connection.h"

#include <unistd.h>

using namespace simpleipc;

void unix_connection::send_data(const char* data, size_t datalen) {
    if (write(fd, data, datalen) != datalen)
        throw std::runtime_error("write() failed");
}

ssize_t unix_connection::read_data(char* data, size_t datalen) {
    return read(fd, data, datalen);
}

#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>
#include <simpleipc/common/io_handler.h>
#include "unix_service_impl.h"

using namespace simpleipc::server;

void unix_service_impl::bind(std::string const& path) {
    if (fd != -1)
        throw std::runtime_error("Socket already created (invalid program state)");
    fd = socket(AF_UNIX, SOCK_STREAM, 0);
    if (fd < 0)
        throw std::runtime_error("Failed to open socket: socket() returned " + std::to_string(fd));
    sockaddr_un addr;
    addr.sun_family = AF_UNIX;
    if (path.length() >= sizeof(addr.sun_path))
        throw std::runtime_error("Path is too long");
    this->path = path;
    strcpy(addr.sun_path, path.c_str());
    unlink(path.c_str());
    if (::bind(fd, (const sockaddr*) &addr, sizeof(addr)) < 0) {
        try {
            close();
        } catch (std::exception&) {}
        throw std::runtime_error("Failed to bind socket");
    }
    io_handler::get_instance().add_socket(fd, [](int) {
        printf("data!\n");
    });
}

void unix_service_impl::close() {
    if (fd == -1)
        return;
    io_handler::get_instance().remove_socket(fd);
    shutdown(fd, SHUT_RDWR);
    if (::close(fd) < 0) {
        fd = -1;
        throw std::runtime_error("Failed to close socket");
    }
    fd = -1;
    unlink(path.c_str());
    path = std::string();
}


std::unique_ptr<service_impl> service_impl_factory::create_platform_service() {
    return std::unique_ptr<service_impl>(new unix_service_impl());
}
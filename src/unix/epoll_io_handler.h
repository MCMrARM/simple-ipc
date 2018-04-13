#pragma once

#include <simpleipc/common/io_handler.h>
#include <unordered_map>
#include <mutex>
#include <thread>

namespace simpleipc {

class epoll_io_handler : public io_handler {

private:
    int fd, efd;
    std::unordered_map<int, data_callback> cbs;
    bool running = true;
    std::mutex cbm;
    std::thread thread;

    void run();

public:
    epoll_io_handler();

    ~epoll_io_handler();


    void add_socket(int fd, data_callback cb) override;

    void remove_socket(int fd) override;

};

}
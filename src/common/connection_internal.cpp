#include "connection_internal.h"

using namespace simpleipc;

void connection_internal::send_message(std::string const& method, nlohmann::json const& data) {
    current_encoding->send_message(*this, method, data);
}

void connection_internal::handle_data_available() {
    printf("data available!\n");
}
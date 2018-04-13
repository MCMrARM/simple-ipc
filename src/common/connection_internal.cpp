#include "connection_internal.h"

using namespace simpleipc;

void connection_internal::send_message(nlohmann::json const& data) {
    current_encoding->send_message(*this, data);
}

void connection_internal::handle_data_available() {
    //
}
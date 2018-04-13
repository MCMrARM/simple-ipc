#pragma once

#include "encoding.h"

namespace simpleipc {
namespace encoding {

class json : public encoding {

public:
    void send_message(connection_internal& conn, nlohmann::json const& data) override;

};
}
}
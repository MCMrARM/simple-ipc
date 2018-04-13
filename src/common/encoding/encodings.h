#pragma once

#include <string>
#include <map>
#include <memory>

namespace simpleipc {
namespace encoding {

class encoding;

class encodings {

private:
    std::map<std::string, std::unique_ptr<encoding>> encodings_map;
    encoding* default_encoding;

    static encodings instance;

public:
    encodings();

    static encoding* get_encoding_by_name(std::string const& name);

    static encoding* get_default_encoding();

};

}
}
#include "encodings.h"
#include "encoding_json.h"
#include "encoding_json_cbor.h"

using namespace simpleipc::encoding;

encodings encodings::instance;

encodings::encodings() {
    encodings_map["json"] = std::unique_ptr<encoding>(new json());
    encodings_map["cbor"] = std::unique_ptr<encoding>(new json());

    default_encoding = encodings_map["json"].get();
}

encoding* encodings::get_default_encoding() {
    return instance.default_encoding;
}

encoding* encodings::get_encoding_by_name(std::string const& name) {
    auto it = instance.encodings_map.find(name);
    if (it == instance.encodings_map.end())
        return nullptr;
    return it->second.get();
}
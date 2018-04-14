#include <simpleipc/common/message/error_code.h>

using namespace simpleipc;

const char* rpc_error_codes::to_string(rpc_error_code code) {
    switch (code) {
        case success:
            return "";
        case parse_error:
            return "Parse error";
        case invalid_request:
            return "Invalid request";
        case method_not_found:
            return "Method not found";
        case invalid_params:
            return "Invalid method parameters";
        case internal_error:
            return "Internal server error";
        default:
            return "Unknown error";
    }
}

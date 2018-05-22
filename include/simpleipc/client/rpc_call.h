#pragma once

#include "rpc_json_call.h"

namespace simpleipc {
namespace client {

template <typename T>
using rpc_result_callback = std::function<void (rpc_result<T>)>;

template <typename T>
using rpc_call_conversion_func = T (*)(nlohmann::json const&);

template <typename T>
class rpc_call {

private:
    rpc_json_call& c;
    rpc_call_conversion_func<T> cf;

    rpc_result<T> convert(rpc_json_result const& r) {
        if (r.success()) {
            try {
                return rpc_result<T>::response(cf(r.data()));
            } catch (rpc_call_exception_interface& e) {
                return rpc_result<T>::error(e.code(), e.what());
            } catch (std::exception& e) {
                return rpc_result<T>::error(rpc_error_codes::internal_error, e.what());
            }
        }
        return rpc_result<T>::error(r.error_code(), r.error_text(), r.error_data());
    }

public:
    rpc_call(rpc_json_call& c, rpc_call_conversion_func<T> cf) : c(c), cf(cf) {}

    /**
     * Executes this call synchronically, returning the result.
     */
    rpc_result<T> call() {
        return convert(c.call());
    }

    /**
     * Executes this call asynchronically, returning the result.
     */
    void call(rpc_result_callback<T> cb) {
        c.call([this, cb](rpc_json_result r) {
            cb(convert(r));
        });
    }

    /**
     * Executes this call asynchronically, ignoring the result.
     */
    void run() {
        c.run();
    }

};

}
}
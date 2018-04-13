#include "varint.h"

#include <stdexcept>

using namespace simpleipc::encoding;

void varint::encode_unsigned(unsigned long long i, char* out, size_t& outs) {
    outs = 0;
    while (i > 0) {
        out[outs++] = (char) ((unsigned char) (i << 1) | (1 << 7));
        i >>= 7;
    }
    out[outs] &= 0b01111111;
}

unsigned long long varint::decode_unsigned(const char* in, size_t ins, size_t* len) {
    unsigned long long ret = 0;
    unsigned char b;
    in += ins;
    ssize_t o = -ins;
    while (o < 0) {
        b = (unsigned char) in[o];
        ret = ret << 7 | b;
        if (!(b >> 7)) {
            if (len)
                *len = ins + o;
            return ret;
        }
        o++;
    }
    throw std::runtime_error("Out of bounds");
}
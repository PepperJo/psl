#ifndef LOCALE_H
#define LOCALE_H

#include <cstdint>
#include <locale>

namespace psl {

template <class charT>
class basic_ctype : public std::ctype_base {};

using ctype = basic_ctype<char>;

template <>
class basic_ctype<char> : public std::ctype_base {
   public:
    using char_type = char;
    constexpr bool is(mask m, char_type c) const {
        return classify[static_cast<size_t>(c)] & m;
    }

   private:
    static constexpr mask classify[] = {
        /* 0x00 = */ ctype::cntrl,
        /* 0x01 = */ ctype::cntrl,
        /* 0x02 = */ ctype::cntrl,
        /* 0x03 = */ ctype::cntrl,
        /* 0x04 = */ ctype::cntrl,
        /* 0x05 = */ ctype::cntrl,
        /* 0x06 = */ ctype::cntrl,
        /* 0x07 = */ ctype::cntrl,
        /* 0x08 = */ ctype::cntrl,

        /* 0x09 = */ ctype::cntrl | ctype::space,

        /* 0x0A = */ ctype::cntrl | ctype::space,
        /* 0x0B = */ ctype::cntrl | ctype::space,
        /* 0x0C = */ ctype::cntrl | ctype::space,
        /* 0x0D = */ ctype::cntrl | ctype::space,

        /* 0x0E = */ ctype::cntrl,
        /* 0x0F = */ ctype::cntrl,
        /* 0x10 = */ ctype::cntrl,
        /* 0x11 = */ ctype::cntrl,
        /* 0x12 = */ ctype::cntrl,
        /* 0x13 = */ ctype::cntrl,
        /* 0x14 = */ ctype::cntrl,
        /* 0x15 = */ ctype::cntrl,
        /* 0x16 = */ ctype::cntrl,
        /* 0x17 = */ ctype::cntrl,
        /* 0x18 = */ ctype::cntrl,
        /* 0x19 = */ ctype::cntrl,
        /* 0x1A = */ ctype::cntrl,
        /* 0x1B = */ ctype::cntrl,
        /* 0x1C = */ ctype::cntrl,
        /* 0x1D = */ ctype::cntrl,
        /* 0x1E = */ ctype::cntrl,
        /* 0x1F = */ ctype::cntrl,

        /* 0x20 = */ ctype::space | ctype::print,

        /* 0x21 = */ ctype::punct | ctype::print,
        /* 0x22 = */ ctype::punct | ctype::print,
        /* 0x23 = */ ctype::punct | ctype::print,
        /* 0x24 = */ ctype::punct | ctype::print,
        /* 0x25 = */ ctype::punct | ctype::print,
        /* 0x26 = */ ctype::punct | ctype::print,
        /* 0x27 = */ ctype::punct | ctype::print,
        /* 0x28 = */ ctype::punct | ctype::print,
        /* 0x29 = */ ctype::punct | ctype::print,
        /* 0x2A = */ ctype::punct | ctype::print,
        /* 0x2B = */ ctype::punct | ctype::print,
        /* 0x2C = */ ctype::punct | ctype::print,
        /* 0x2D = */ ctype::punct | ctype::print,
        /* 0x2E = */ ctype::punct | ctype::print,
        /* 0x2F = */ ctype::punct | ctype::print,

        /* 0x30 = */ ctype::digit | ctype::xdigit | ctype::print,
        /* 0x31 = */ ctype::digit | ctype::xdigit | ctype::print,
        /* 0x32 = */ ctype::digit | ctype::xdigit | ctype::print,
        /* 0x33 = */ ctype::digit | ctype::xdigit | ctype::print,
        /* 0x34 = */ ctype::digit | ctype::xdigit | ctype::print,
        /* 0x35 = */ ctype::digit | ctype::xdigit | ctype::print,
        /* 0x36 = */ ctype::digit | ctype::xdigit | ctype::print,
        /* 0x37 = */ ctype::digit | ctype::xdigit | ctype::print,
        /* 0x38 = */ ctype::digit | ctype::xdigit | ctype::print,
        /* 0x39 = */ ctype::digit | ctype::xdigit | ctype::print,

        /* 0x3A = */ ctype::punct | ctype::print,
        /* 0x3B = */ ctype::punct | ctype::print,
        /* 0x3C = */ ctype::punct | ctype::print,
        /* 0x3D = */ ctype::punct | ctype::print,
        /* 0x3E = */ ctype::punct | ctype::print,
        /* 0x3F = */ ctype::punct | ctype::print,
        /* 0x40 = */ ctype::punct | ctype::print,

        /* 0x41 = */ ctype::upper | ctype::alpha | ctype::xdigit | ctype::print,
        /* 0x42 = */ ctype::upper | ctype::alpha | ctype::xdigit | ctype::print,
        /* 0x43 = */ ctype::upper | ctype::alpha | ctype::xdigit | ctype::print,
        /* 0x44 = */ ctype::upper | ctype::alpha | ctype::xdigit | ctype::print,
        /* 0x45 = */ ctype::upper | ctype::alpha | ctype::xdigit | ctype::print,
        /* 0x46 = */ ctype::upper | ctype::alpha | ctype::xdigit | ctype::print,

        /* 0x47 = */ ctype::upper | ctype::alpha | ctype::print,
        /* 0x48 = */ ctype::upper | ctype::alpha | ctype::print,
        /* 0x49 = */ ctype::upper | ctype::alpha | ctype::print,
        /* 0x50 = */ ctype::upper | ctype::alpha | ctype::print,
        /* 0x51 = */ ctype::upper | ctype::alpha | ctype::print,
        /* 0x52 = */ ctype::upper | ctype::alpha | ctype::print,
        /* 0x53 = */ ctype::upper | ctype::alpha | ctype::print,
        /* 0x54 = */ ctype::upper | ctype::alpha | ctype::print,
        /* 0x55 = */ ctype::upper | ctype::alpha | ctype::print,
        /* 0x56 = */ ctype::upper | ctype::alpha | ctype::print,
        /* 0x57 = */ ctype::upper | ctype::alpha | ctype::print,
        /* 0x58 = */ ctype::upper | ctype::alpha | ctype::print,
        /* 0x59 = */ ctype::upper | ctype::alpha | ctype::print,
        /* 0x5A = */ ctype::upper | ctype::alpha | ctype::print,

        /* 0x5B = */ ctype::punct | ctype::print,
        /* 0x5C = */ ctype::punct | ctype::print,
        /* 0x5D = */ ctype::punct | ctype::print,
        /* 0x5E = */ ctype::punct | ctype::print,
        /* 0x5F = */ ctype::punct | ctype::print,
        /* 0x60 = */ ctype::punct | ctype::print,

        /* 0x61 = */ ctype::lower | ctype::alpha | ctype::xdigit | ctype::print,
        /* 0x62 = */ ctype::lower | ctype::alpha | ctype::xdigit | ctype::print,
        /* 0x63 = */ ctype::lower | ctype::alpha | ctype::xdigit | ctype::print,
        /* 0x64 = */ ctype::lower | ctype::alpha | ctype::xdigit | ctype::print,
        /* 0x65 = */ ctype::lower | ctype::alpha | ctype::xdigit | ctype::print,
        /* 0x66 = */ ctype::lower | ctype::alpha | ctype::xdigit | ctype::print,

        /* 0x67 = */ ctype::lower | ctype::alpha | ctype::print,
        /* 0x68 = */ ctype::lower | ctype::alpha | ctype::print,
        /* 0x69 = */ ctype::lower | ctype::alpha | ctype::print,
        /* 0x70 = */ ctype::lower | ctype::alpha | ctype::print,
        /* 0x71 = */ ctype::lower | ctype::alpha | ctype::print,
        /* 0x72 = */ ctype::lower | ctype::alpha | ctype::print,
        /* 0x73 = */ ctype::lower | ctype::alpha | ctype::print,
        /* 0x74 = */ ctype::lower | ctype::alpha | ctype::print,
        /* 0x75 = */ ctype::lower | ctype::alpha | ctype::print,
        /* 0x76 = */ ctype::lower | ctype::alpha | ctype::print,
        /* 0x77 = */ ctype::lower | ctype::alpha | ctype::print,
        /* 0x78 = */ ctype::lower | ctype::alpha | ctype::print,
        /* 0x79 = */ ctype::lower | ctype::alpha | ctype::print,
        /* 0x7A = */ ctype::lower | ctype::alpha | ctype::print,

        /* 0x7B = */ ctype::punct | ctype::print,
        /* 0x7C = */ ctype::punct | ctype::print,
        /* 0x7D = */ ctype::punct | ctype::print,
        /* 0x7E = */ ctype::punct | ctype::print,

        /* 0x7F = */ ctype::cntrl, };
};
}
#endif /* LOCALE_H */

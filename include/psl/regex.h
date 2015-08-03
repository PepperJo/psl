#ifndef REGEX_H
#define REGEX_H

#include <regex>

#include <psl/locale.h>

namespace psl {

template <class charT>
class match {
   public:
    using ctype = basic_ctype<charT>;

   private:
    const ctype ct_;
    const typename ctype::mask m_;

   public:
    constexpr match(typename ctype::mask m) : ct_{}, m_{m} {}
    constexpr bool operator()(charT c) {
        return ct_.is(m_, c);
    }
};


template <class charT>
class basic_regex {
   public:
    using value_type = charT;
    using flag_type = std::regex_constants::syntax_option_type;

   private:
   public:
    constexpr basic_regex(const charT* str,
                          flag_type = std::regex::ECMAScript) {}
};

using regex = basic_regex<char>;
}

#endif /* REGEX_H */

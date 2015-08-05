#ifndef REGEX_H
#define REGEX_H

#include <regex>
#include <iterator>
#include <limits>

#include <iostream>

#include <psl/locale.h>

namespace psl {

enum class match_type {
    ANY,
    TIMES_0_N,
    TIMES_1_N,
    OPTIONAL,
    REPEAT,
    GROUP,
    CHAR,
    CHAR_CLASS,
    END
};

struct sub_regex {
    using idx_type = std::ptrdiff_t;
    match_type type;
    idx_type first;
    idx_type last;

    constexpr sub_regex(const match_type& mt, idx_type idx)
        : type{mt}, first{idx}, last{idx + 1} {}

    constexpr sub_regex(const match_type& mt, idx_type first, idx_type last)
        : type{mt}, first{first}, last{last} {}
};

template <class charT>
class basic_regex {
   public:
    using idx_type = std::ptrdiff_t;
    using value_type = charT;
    using flag_type = std::regex_constants::syntax_option_type;

   private:
    const charT* str_;

    constexpr idx_type delim_next(size_t i, bool nested) const {
        uint32_t depth = 0;
        char open = str_[i];
        char close{};

        if (open == '{') {
            close = '}';
        } else if (open == '(') {
            close = ')';
        } else if (open == '[') {
            close = ']';
        }

        while (true) {
            char c = str_[i++];
            if (c == '\0') {
                break;
            } else if (c == open) {
                if (nested) {
                    depth++;
                } else {
                    break;
                }
            } else if (c == close) {
                if (depth == 0) {
                    return i + 1;
                }
                depth--;
            }
        }

        return -1;
    }

    constexpr sub_regex next(idx_type i) const {
        auto j = i + 1;
        switch (str_[j]) {
            case '\0':
                return {match_type::END, j};
            /* special characters */
            case '\\':
                /* todo */
                return {match_type::END, j, -1};
            case '.':
                return {match_type::ANY, j};
            /* quantifiers  */
            case '+':
                return {match_type::TIMES_0_N, j};
            case '*':
                return {match_type::TIMES_1_N, j};
            case '?':
                return {match_type::OPTIONAL, j};
            case '{':
                return {match_type::REPEAT, j, delim_next(j, false)};
            /* groups */
            case '(':
                return {match_type::GROUP, j, delim_next(j, true)};
            /* character class  */
            case '[':
                return {match_type::CHAR_CLASS, j, delim_next(j, false)};
            default:
                return {match_type::CHAR, j};
        }
    }

    constexpr std::pair<int, int> ntimes(const sub_regex& sre) const {
        switch (sre.type) {
            case match_type::OPTIONAL:
                return {0, 1};
            case match_type::TIMES_0_N:
                return {0, -1};
            case match_type::TIMES_1_N:
                return {1, -1};
            case match_type::REPEAT:
                /* todo */
                break;
            default:
                break;
        }

        return {-1, -1};
    }

   public:
    constexpr basic_regex(const charT* str,
                          flag_type flag = std::regex::ECMAScript)
        : str_{str} {}

    template <class BidirIt, class charG>
    friend constexpr match_type regex_match(BidirIt first, BidirIt last,
                                      const basic_regex<charG>& e);
};

template <class BidirIt, class charT>
constexpr match_type regex_match(BidirIt first, BidirIt last,
                           const basic_regex<charT>& e) {
    auto sre = e.next(-1);
    // for (; first != last; first++) {
    //
    // }
    return sre.type;
}

using regex = basic_regex<char>;
}

#endif /* REGEX_H */

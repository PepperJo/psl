#ifndef REGEX_H
#define REGEX_H

#include <regex>
#include <iterator>
#include <limits>

#include <iostream>

#include <psl/locale.h>

namespace psl {

namespace regex_constants {
enum class error_type {
    ERROR_COLLATE,
    ERROR_CTYPE,
    ERROR_ESCAPE,
    ERROR_BACKREF,
    ERROR_BRACK,
    ERROR_PAREN,
    ERROR_BRACE,
    ERROR_BADBRACE,
    ERROR_RANGE,
    ERROR_SPACE,
    ERROR_BADREPEAT,
    ERROR_COMPLEXITY,
    ERROR_STACK,
    ERROR_LAST
};

constexpr error_type error_collate = error_type::ERROR_COLLATE;
constexpr error_type error_ctype = error_type::ERROR_CTYPE;
constexpr error_type error_escape = error_type::ERROR_ESCAPE;
constexpr error_type error_backref = error_type::ERROR_BACKREF;
constexpr error_type error_brack = error_type::ERROR_BRACK;
constexpr error_type error_paren = error_type::ERROR_PAREN;
constexpr error_type error_brace = error_type::ERROR_BRACE;
constexpr error_type error_badbrace = error_type::ERROR_BADBRACE;
constexpr error_type error_range = error_type::ERROR_RANGE;
constexpr error_type error_space = error_type::ERROR_SPACE;
constexpr error_type error_badrepeat = error_type::ERROR_BADREPEAT;
constexpr error_type error_complexity = error_type::ERROR_COMPLEXITY;
constexpr error_type error_stack = error_type::ERROR_STACK;
}

class regex_error {
   private:
    regex_constants::error_type code_;

   public:
    constexpr regex_error(regex_constants::error_type ecode) : code_{ecode} {}
    constexpr regex_constants::error_type code() { return code_; }
};

enum class match_type {
    ANY,
    REPEAT_0_N,
    REPEAT_1_N,
    OPTIONAL,
    REPEAT,
    GROUP,
    CHAR,
    CHAR_CLASS,
    END
};

enum class char_class_type {
    CHAR,
    CHAR_RANGE,
    MASK
};

struct sub_regex {
    using idx_type = std::size_t;
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
    using idx_type = size_t;
    using value_type = charT;
    // using flag_type = regex_constants::syntax_option_type;

   private:
    const charT* str_;

    constexpr idx_type delim_next(char open, size_t i) const {
        uint32_t depth = 0;
        char close{};
        bool nested{};
        regex_error err{regex_constants::error_type::ERROR_LAST};

        if (open == '{') {
            close = '}';
            nested = false;
            err = regex_constants::error_brace;
        } else if (open == '(') {
            close = ')';
            nested = true;
            err = regex_constants::error_paren;
        } else if (open == '[') {
            close = ']';
            nested = true;
            err = regex_constants::error_brack;
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

        throw regex_error(err);
    }

    constexpr sub_regex parse(idx_type i) const {
        char c = str_[i];
        switch (c) {
            case '\0':
                return {match_type::END, i, i};
            /* special characters */
            case '\\':
                /* todo */
                throw regex_error{regex_constants::error_escape};
            case '.':
                return {match_type::ANY, i};
            /* quantifiers  */
            case '+':
                return {match_type::REPEAT_1_N, i};
            case '*':
                return {match_type::REPEAT_0_N, i};
            case '?':
                return {match_type::OPTIONAL, i};
            case '{':
                return {match_type::REPEAT, i, delim_next(c, i)};
            /* groups */
            case '(':
                return {match_type::GROUP, i, delim_next(c, i)};
            /* character class  */
            case '[':
                return {match_type::CHAR_CLASS, i, delim_next(c, i)};
            default:
                return {match_type::CHAR, i};
        }
    }

    // constexpr char_class_type parse_char_class(idx_type i, idx_type end) const {
    //     char c = str_[i];
    //     char c_next = '\0';
    //     if (i + 1 != end) {
    //         #<{(| look ahead |)}>#
    //         c_next = str_[i + 1];
    //     }
    //
    //     switch(c_next) {
    //         case ':':
    //             if (c == '[') {
    //                 #<{(| todo |)}>#
    //                 throw regex_error{regex_constants::error_ctype};
    //             }
    //             break;
    //         case '-':
    //         {
    //             char b = str_[i + 2];
    //         }
    //     }
    // }

    constexpr std::pair<int, int> parse_repeat(const sub_regex& sre) const {
        switch (sre.type) {
            case match_type::OPTIONAL:
                return {0, 1};
            case match_type::REPEAT_0_N:
                return {0, -1};
            case match_type::REPEAT_1_N:
                return {1, -1};
            case match_type::REPEAT:
                /* todo */
                break;
            default:
                break;
        }

        throw regex_error{regex_constants::error_badbrace};
    }

   public:
    constexpr basic_regex(const charT* str) : str_{str} {}

    template <class BidirIt, class charG>
    friend constexpr bool regex_match(BidirIt first, BidirIt last,
                                      const basic_regex<charG>& e);
};

template <class BidirIt, class charT>
constexpr bool regex_match(BidirIt first, BidirIt last,
                           const basic_regex<charT>& e) {
    sub_regex prev_sre = {match_type::END, 0, 0};
    auto sre = e.parse(0);

    bool prev_match = true;
    int repeat = 0;

    while (first != last) {
        if (sre.type == match_type::CHAR) {
            if (!prev_match) {
                break;
            }
            prev_match = *first == e.str_[sre.first];
            if (prev_match) {
                first++;
            }
            prev_sre = sre;
            sre = e.parse(sre.last);
        } else if (sre.type == match_type::REPEAT ||
                   sre.type == match_type::TIMES_0_N ||
                   sre.type == match_type::TIMES_1_N ||
                   sre.type == match_type::OPTIONAL) {
            if (prev_sre.type != match_type::CHAR) {
                throw regex_error{regex_constants::error_badrepeat};
            }
            auto times = e.parse_repeat(sre);
            if (!prev_match) {
                if (repeat < times.first) {
                    break;
                }
                /* we could not match it but this is fine since we reached
                 * min repeat */
                prev_match = true;
                /* we still need to match prev but with the next sub-regex */
                repeat = 0;
                prev_sre = sre;
                sre = e.parse(sre.last);
            } else {
                repeat++;
                if (repeat == times.second) {
                    repeat = 0;
                    prev_sre = sre;
                    sre = e.parse(sre.last);
                } else {
                    sre = prev_sre;
                }
            }
        } else if (sre.type == match_type::CHAR_CLASS) {
            /* TODO */
        } else {
            break;
        }
    }
    // if (first != last) throw 1;
    // if (!prev_match) throw 2;
    return first == last && prev_match && sre.type == match_type::END;
}

using regex = basic_regex<char>;
}

#endif /* REGEX_H */

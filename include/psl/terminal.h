#ifndef TERMINAL_H
#define TERMINAL_H

#include <array>
#include <cstdint>
#include <ostream>

namespace psl {
namespace terminal {

enum class graphic_format : uint8_t {
    RESET = 0,
    BOLD = 1,
    FAINT = 2,
    RED = 31,
    WHITE = 37,
};

/* control sequence introducer */
constexpr auto CSI = "\033[";
/* select graphic rendering mode */
constexpr auto SGR = "m";

template <typename E>
constexpr auto to_underlying(E e) -> typename std::underlying_type<E>::type {
    return static_cast<typename std::underlying_type<E>::type>(e);
}

inline std::ostream& operator<<(std::ostream& out, const graphic_format f) {
    out << CSI << std::to_string(to_underlying(f)) << "m";
    return out;
}

template <typename container>
inline typename std::enable_if<
    std::is_same<typename std::remove_cv<typename container::value_type>::type,
                 graphic_format>::value,
    std::ostream&>::type
operator<<(std::ostream& out, const container vf) {
    out << CSI;
    bool first = true;
    for (auto f : vf) {
        first ? first = false : out << ";";
        out << std::to_string(to_underlying(f));
    }
    out << SGR;
    return out;
}
}
}

#endif /* TERMINAL_H */

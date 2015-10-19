#ifndef LOG_H
#define LOG_H

#include <iostream>
#include <system_error>

#include <psl/terminal.h>

namespace psl {

template <typename format>
inline std::ostream& log_err(std::ostream& out, const char* file, uint32_t line,
                             int ev) {
    std::system_error error(ev < 0 ? -ev : ev, std::system_category());
    out << format::BOLD << file << ':' << line << ": " << format::RED
        << "error: " << format::WHITE << error.code().message() << format::RESET
        << " (" << error.code() << ")" << format::RESET;
    return out;
}

#define TERM_LOG_ERR(ev)                                                       \
    psl::log_err<psl::terminal::graphic_format>(std::cerr, __FILE__, __LINE__, \
                                                ev)
#define CHECK_ERR(condition, ev)                                               \
    if (condition)                                                             \
    TERM_LOG_ERR(ev) << "\n\t" << #condition << '\n'

#define LOG_ERR_EXIT(condition, ev)                                            \
    do {                                                                       \
        CHECK_ERR(condition, ev), std::exit(ev < 0 ? ev : -ev);                \
    } while (0)
}

#endif /* LOG_H */

#ifndef CHRONO_H
#define CHRONO_H

#include <chrono>

/* unfortunatly older c++ standard libraries do use unprecise realtime clocks
 * so we need this to do the right job */

namespace psl {
namespace chrono {

struct high_resolution_clock {
    typedef std::chrono::nanoseconds duration;
    typedef duration::rep rep;
    typedef duration::period period;
    typedef std::chrono::time_point<high_resolution_clock, duration> time_point;

    static_assert(high_resolution_clock::duration::min() <
                      high_resolution_clock::duration::zero(),
                  "a clock's minimum duration cannot be less than its epoch");

    static constexpr bool is_steady = true;

    static time_point now() noexcept;
};
}
}

#endif /* CHRONO_H */

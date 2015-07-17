
#include <psl/chrono.h>

#include <unistd.h>
#include <sys/time.h>

namespace psl {
namespace chrono {

high_resolution_clock::time_point high_resolution_clock::now() noexcept
{
    using namespace std::chrono;
    timespec tp;
    clock_gettime(CLOCK_MONOTONIC, &tp);
    return time_point(duration(seconds(tp.tv_sec)
                + nanoseconds(tp.tv_nsec)));
}

}
}


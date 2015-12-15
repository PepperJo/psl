#ifndef ALIGN_H
#define ALIGN_H

#include <cassert>

namespace psl {

template <typename T> inline T align(T t, T alignment) {
    assert(alignment % 2 == 0);
    T mask = alignment - 1;
    return (t + mask) & ~mask;
}

}

#endif /* ALIGN_H */

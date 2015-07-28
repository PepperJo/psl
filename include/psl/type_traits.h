#ifndef TYPE_TRAITS_H
#define TYPE_TRAITS_H

#include <utility>
#include <cstddef>

namespace psl {

template <typename T, std::size_t Align>
struct aligned_type {
   private:
    alignas(Align) T t;

   public:
    template <class... Args>
    aligned_type(Args&&... args)
        : t(std::forward<Args>(args)...) {}

    T* operator->() { return &t; }

    T& operator*() { return t; }
};

template <typename T>
using plus_result_type = decltype(std::declval<T>() + std::declval<T>());
}

#endif /* TYPE_TRAITS_H */

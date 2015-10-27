#ifndef TYPE_TRAITS_H
#define TYPE_TRAITS_H

#include <utility>
#include <cstddef>

namespace psl {

template <typename T, std::size_t Align> struct aligned_type {
  private:
    alignas(Align) T t;

  public:
    template <class... Args>
    aligned_type(Args&&... args)
        : t(std::forward<Args>(args)...) {}

    T* operator->() { return &t; }

    T& operator*() { return t; }
};

template <typename T1, typename T2 = T1>
using plus_result_type = decltype(std::declval<T1>() + std::declval<T2>());

template <typename E>
constexpr auto to_underlying(E e) -> typename std::underlying_type<E>::type {
    return static_cast<typename std::underlying_type<E>::type>(e);
}
}

#endif /* TYPE_TRAITS_H */

#ifndef STATS_H
#define STATS_H

#include <algorithm>
#include <cmath>
#include <iterator>

#include <psl/type_traits.h>

namespace psl {
namespace stats {

template <class InputIterator,
          class Sum = plus_result_type<typename InputIterator::value_type>>
double mean(InputIterator first, InputIterator last) {
    size_t count = 0;
    Sum sum = 0;
    /* we could use std::accumulate here but if the iterator
     * is not a RandomAccessIterator we would need to compute the size again
     * (can be a O(n) operation, e.g. for lists) */
    std::for_each(first, last, [&](decltype(*first) & e) {
        count++;
        sum = sum + e;
    });

    return sum / static_cast<double>(count);
}

template <class InputIterator,
          class Sum = plus_result_type<typename InputIterator::value_type>>
double variance_m(InputIterator first, InputIterator last, double mu) {
    size_t count = 0;
    Sum sum = 0;

    std::for_each(first, last, [&](decltype(*first) & e) {
        count++;
        sum = sum + (e - mu) * (e - mu);
    });
    return sum / static_cast<double>(count - 1);
}

template <class InputIterator,
          class Sum = plus_result_type<typename InputIterator::value_type>>
double variance(InputIterator first, InputIterator last) {
    return variance_m<InputIterator, Sum>(
        first, last, mean<InputIterator, Sum>(first, last));
}

template <class InputIterator,
          class Sum = plus_result_type<typename InputIterator::value_type>>
double stddev_m(InputIterator first, InputIterator last, double mu) {
    return std::sqrt(variance_m<InputIterator, Sum>(first, last, mu));
}

template <class InputIterator,
          class Sum = plus_result_type<typename InputIterator::value_type>>
double stddev(InputIterator first, InputIterator last, double mu) {
    return stddev<InputIterator, Sum>(first, last,
                                      mean<InputIterator, Sum>(first, last));
}

template <class InputIterator>
double quantile(InputIterator first, InputIterator last, double f) {
    auto count = std::distance(first, last);
    double delta = (count - 1) * f;
    size_t i = delta;
    delta -= i;
    std::advance(first, i);
    return (1 - delta) * *first + delta * *std::next(first);
}

template <class InputIterator>
double median(InputIterator first, InputIterator last) {
    return quantile(first, last, 0.5);
}
}
}

#endif /* STATS_H */

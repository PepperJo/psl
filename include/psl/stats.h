#ifndef STATS_H
#define STATS_H

#include <algorithm>
#include <cmath>
#include <iterator>

#include <psl/type_traits.h>

namespace psl {
namespace stats {

template <class InputIterator,
          class Sum = plus_result_type<
              typename std::iterator_traits<InputIterator>::value_type>>
constexpr double mean(InputIterator first, InputIterator last) {
    size_t count = 0;
    Sum sum = 0;
    /* 1. we could use std::accumulate here but if the iterator
     * is not a RandomAccessIterator we need another O(n) to compute the size
     * 2. we do not use std::for_each because of constexpr
     */
    for (; first != last; first++) {
        count++;
        sum = sum + *first;
    }

    return sum / static_cast<double>(count);
}

constexpr size_t BesselCorrection(const size_t count) {
    /* corrected/unbiased */
    return count - 1;
}

constexpr size_t ShrinkageEstimator(const size_t count) {
    /* Minimize mean squared error (biased) */
    return count + 1;
}

template <class InputIterator,
          class Sum = plus_result_type<
              typename std::iterator_traits<InputIterator>::value_type>,
          class CorrectionFunction>
constexpr double variance(InputIterator first, InputIterator last, double mu,
                CorrectionFunction cf) {
    size_t count = 0;
    Sum sum = 0;

    for(; first != last; first++) {
        count++;
        sum = sum + (*first - mu) * (*first - mu);
    }

    return sum / static_cast<double>(cf(count));
}

template <class InputIterator,
          class Sum = plus_result_type<
              typename std::iterator_traits<InputIterator>::value_type>,
          class CorrectionFunction = decltype(BesselCorrection)>
constexpr double variance(InputIterator first, InputIterator last,
                CorrectionFunction cf = BesselCorrection) {
    return variance<InputIterator, Sum, CorrectionFunction>(
        first, last, mean<InputIterator, Sum>(first, last), cf);
}

template <class InputIterator,
          class Sum = plus_result_type<
              typename std::iterator_traits<InputIterator>::value_type>,
          class CorrectionFunction>
double stddev(InputIterator first, InputIterator last, double mu,
              CorrectionFunction cf) {
    return std::sqrt(
        variance<InputIterator, Sum, CorrectionFunction>(first, last, mu, cf));
}

template <class InputIterator,
          class Sum = plus_result_type<
              typename std::iterator_traits<InputIterator>::value_type>,
          class CorrectionFunction = decltype(BesselCorrection)>
double stddev(InputIterator first, InputIterator last,
              CorrectionFunction cf = BesselCorrection) {
    return stddev<InputIterator, Sum, CorrectionFunction>(
        first, last, mean<InputIterator, Sum>(first, last), cf);
}

template <class InputIterator>
double quantile(InputIterator first, InputIterator last, double f) {
    auto count = std::distance(first, last);
    double delta = (count - 1) * f;
    size_t i = /* floor */ delta;
    delta -= i;
    std::advance(first, i);
    return (1 - delta) * *first + delta * *std::next(first);
}

template <class InputIterator>
double interquartile_range(InputIterator first, InputIterator last) {
    return quantile<InputIterator>(first, last, 0.75) -
           quantile<InputIterator>(first, last, 0.25);
}

template <class InputIterator>
double median(InputIterator first, InputIterator last) {
    return quantile(first, last, 0.5);
}
}
}

#endif /* STATS_H */

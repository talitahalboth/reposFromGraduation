#include <stdio.h>
 extern "C"
{
#include <immintrin.h>
}

int main(int argc, char const *argv[])
{
    __m256d values = _mm256_set_pd(23211.24, -123.421, 1224.123, 413.231);

    // assuming _mm256_hadd_pd(a, b) == a0 + a1, b0 + b1, a2 + a3, b2 + b3 (5 cycles) ...
    values = _mm256_hadd_pd(values, _mm256_permute2f128_pd(values, values, 1));
    // ^^^^^^^^^^^^^^^^^^^^ a0 + a1, a2 + a3, a2 + a3, a0 + a1

    values = _mm256_hadd_pd(values, values);
    // ^^^^^^^^^^^^^^^^^^^^ (a0 + a1 + a2 + a3), (a0 + a1 + a2 + a3), (a2 + a3 + a0 + a1), (a2 + a3 + a0 + a1)

    // Being that addition is associative then each component of values contains the sum of all its initial components (11 cycles) to calculate, (1-2 cycles) to extract, total (12-13 cycles)
    double got = _mm_cvtsd_f64(_mm256_castpd256_pd128(values)), exp = (23211.24 + -123.421 + 1224.123 + 413.231);

    if (got != exp || _mm256_movemask_pd(_mm256_cmp_pd(values, _mm256_set1_pd(exp), _CMP_EQ_OS)) != 0b1111)
        printf("Failed to sum double components, exp: %f, got %f\n", exp, got);
    else
        printf("ok\n");
    return 0;
}
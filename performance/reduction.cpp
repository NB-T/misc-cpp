#include "NBTlog.hpp"
#include <functional>
#include <immintrin.h>
#include <iomanip>
#include <map>
#include <random>

typedef int v8si __attribute__((vector_size(32)));

int sum(int* a, int n)
{
    int s = 0;
    for (int i = 0; i < n; ++i)
    {
        s += a[i];
    }
    return s;
}

int sum_simd_1(v8si* a, int n)
{
    v8si s = {0};
    for (int i = 0; i < n / 8; ++i)
    {
        s += a[i];
    }
    int res = 0;
    for (int i = 0; i < 8; ++i)
    {
        res += s[i];
    }
    int* tail = (int*)a;
    for (int i = n / 8 * 8; i < n; ++i)
    {
        res += tail[i];
    }
    return res;
}

const int B = 2;

int sum_simd_2(v8si* a, int n)
{
    v8si b[B] = {0};
    for (int i = 0; i + (B - 1) < n / 8; i += B)
    {
        for (int j = 0; j < B; ++j)
        {
            b[j] += a[i + j];
        }
    }

    for (int i = 1; i < B; ++i)
    {
        b[0] += b[i];
    }
    int s = 0;
    for (int i = 0; i < 8; ++i)
    {
        s += b[0][i];
    }

    int* tail = (int*)a;
    for (int i = n / (8 * B) * (8 * B); i < n; ++i)
    {
        s += tail[i];
    }

    return s;
}

int hsum(__m256i x)
{
    __m128i l = _mm256_extracti128_si256(x, 0);
    __m128i h = _mm256_extracti128_si256(x, 1);
    l = _mm_add_epi32(l, h);
    l = _mm_hadd_epi32(l, l);
    return _mm_extract_epi32(l, 0) + _mm_extract_epi32(l, 1);
}

int sum_simd_3(v8si* a, int n)
{
    int s = 0;
    for (int i = 0; i < n / 8; ++i)
    {
        s += hsum((__m256i)a[i]);
    }
    return s;
}

int main()
{
    int n = 1 << 20;
    int* a = (int*)std::aligned_alloc(32, n * sizeof(int));
    for (int i = 0; i < n; ++i)
    {
        a[i] = std::rand() % 100;
    }
    v8si* a_simd = (v8si*)a;
    nano log;
    log.start();

    std::map<std::string, std::pair<double, long>> times;
    auto bench = [&](const std::string& name, auto fn)
    {
        for (int i = 0; i < 5; ++i)
        {
            log.stamp();
            times[name].second = fn();
            times[name].first += log._duration_();
        }
    };

    bench(
        "sum",
        [&]
        {
            return sum(a, n);
        }
    );
    bench(
        "sum_simd_1",
        [&]
        {
            return sum_simd_1(a_simd, n);
        }
    );
    bench(
        "sum_simd_2",
        [&]
        {
            return sum_simd_2(a_simd, n);
        }
    );
    bench(
        "sum_simd_3",
        [&]
        {
            return sum_simd_3(a_simd, n);
        }
    );
    for (const auto& [name, val] : times)
    {
        std::cout << name << std::fixed << std::setprecision(2) << std::setw(15) << val.first / 5
                  << "ns  result=" << val.second << std::endl;
    }

    std::free(a);
}

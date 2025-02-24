#include <iostream>
#include <vector>

#include "nbtlog.hpp"

const int n = 1200;

int main()
{
    std::vector<std::vector<int>> mul1(n, std::vector<int>(n, 0));
    std::vector<std::vector<int>> mul2(n, std::vector<int>(n, 0));

    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < n; ++j)
        {
            mul1[i][j] = i + j;
            mul2[i][j] = i + j;
        }
    }

    std::vector<std::vector<int>> r1(n, std::vector<int>(n));
    auto start = nbtlog::timestamp();
    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < n; ++j)
        {
            for (int k = 0; k < n; ++k)
            {
                r1[i][j] += mul1[i][k] * mul2[k][j];
            }
        }
    }
    nbtlog::log("IJK", nbtlog::timestamp() - start);

    // transpose A
    start = nbtlog::timestamp();
    std::vector<std::vector<int>> tmp_a(n, std::vector<int>(n));
    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < n; ++j)
        {
            tmp_a[i][j] = mul1[j][i];
        }
    }

    nbtlog::log("out-of-place transpose A", nbtlog::timestamp() - start);

    tmp_a = mul1;
    start = nbtlog::timestamp();
    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < i; ++j)
        {
            std::swap(tmp_a[i][j], tmp_a[j][i]);
        }
    }

    nbtlog::log("in-place transpose A", nbtlog::timestamp() - start);

    std::vector<std::vector<int>> r2(n, std::vector<int>(n));
    start = nbtlog::timestamp();
    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < n; ++j)
        {
            for (int k = 0; k < n; ++k)
            {
                r2[i][j] += tmp_a[i][k] * mul2[k][j];
            }
        }
    }

    nbtlog::log("TRANSPOSED A", nbtlog::timestamp() - start);

    std::vector<std::vector<int>> tmp_b = mul2;
    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < i; ++j)
        {
            std::swap(tmp_b[i][j], tmp_b[j][i]);
        }
    }

    r2 = std::vector(n, std::vector(n, 0));
    start = nbtlog::timestamp();
    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < n; ++j)
        {
            for (int k = 0; k < n; ++k)
            {
                r2[i][j] += mul1[i][k] * tmp_b[j][k];
            }
        }
    }
    nbtlog::log("TRANSPOSED B", nbtlog::timestamp() - start);

    std::vector<std::vector<int>> r3(n, std::vector<int>(n));
    start = nbtlog::timestamp();
    for (int j = 0; j < n; ++j)
    {
        for (int k = 0; k < n; ++k)
        {
            for (int i = 0; i < n; ++i)
            {
                r3[i][j] = mul1[i][k] * mul2[k][j];
            }
        }
    }
    nbtlog::log("JKI", nbtlog::timestamp() - start);

    std::vector<std::vector<int>> r4(n, std::vector<int>(n));
    start = nbtlog::timestamp();
    for (int k = 0; k < n; ++k)
    {
        for (int j = 0; j < n; ++j)
        {
            for (int i = 0; i < n; ++i)
            {
                r4[i][j] = mul1[i][k] * mul2[k][j];
            }
        }
    }
    nbtlog::log("KJI", nbtlog::timestamp() - start);

    std::vector<std::vector<int>> r5(n, std::vector<int>(n));
    start = nbtlog::timestamp();
    for (int k = 0; k < n; ++k)
    {
        for (int i = 0; i < n; ++i)
        {
            for (int j = 0; j < n; ++j)
            {
                r5[i][j] = mul1[i][k] * mul2[k][j];
            }
        }
    }
    nbtlog::log("KIJ", nbtlog::timestamp() - start);

    std::vector<std::vector<int>> r6(n, std::vector<int>(n));
    start = nbtlog::timestamp();
    for (int i = 0; i < n; ++i)
    {
        for (int k = 0; k < n; ++k)
        {
            for (int j = 0; j < n; ++j)
            {
                r6[i][j] = mul1[i][k] * mul2[k][j];
            }
        }
    }
    nbtlog::log("IKJ", nbtlog::timestamp() - start);

    std::vector<std::vector<int>> r7(n, std::vector<int>(n));
    start = nbtlog::timestamp();
    for (int i = 0; i < n; ++i)
    {
        for (int k = 0; k < n; ++k)
        {
            for (int j = 0; j < n; ++j)
            {
                r7[i][j] = mul1[i][k] * mul2[k][j];
            }
        }
    }
    nbtlog::log("IKJ", nbtlog::timestamp() - start);

    std::vector<std::vector<int>> r8(n, std::vector<int>(n));
    start = nbtlog::timestamp();
    for (int j = 0; j < n; ++j)
    {
        for (int i = 0; i < n; ++i)
        {
            for (int k = 0; k < n; ++k)
            {
                r8[i][j] = mul1[i][k] * mul2[k][j];
            }
        }
    }
    nbtlog::log("JIK", nbtlog::timestamp() - start);
    return EXIT_SUCCESS;
}

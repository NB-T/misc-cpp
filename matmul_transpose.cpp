#include <iostream>
#include <vector>

#include "nbtlog.hpp"

const int n = 1000;

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

    start = nbtlog::timestamp();
    std::vector<std::vector<int>> tmp(n, std::vector<int>(n));
    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < n; ++j)
        {
            tmp[i][j] = mul2[j][i];
        }
    }
    nbtlog::log("out-of-place transpose", nbtlog::timestamp() - start);

    tmp = mul2;
    start = nbtlog::timestamp();
    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < i; ++j)
        {
            std::swap(tmp[i][j], tmp[j][i]);
        }
    }
    nbtlog::log("in-place transpose", nbtlog::timestamp() - start);

    std::vector<std::vector<int>> r2(n, std::vector<int>(n));
    start = nbtlog::timestamp();
    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < n; ++j)
        {
            for (int k = 0; k < n; ++k)
            {
                r2[i][j] += mul1[i][k] * tmp[j][k];
            }
        }
    }
    nbtlog::log("TRANSPOSED", nbtlog::timestamp() - start);

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

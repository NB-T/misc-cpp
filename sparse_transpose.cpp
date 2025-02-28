#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <numeric>
#include <random>
#include <tuple>
#include <unordered_set>
#include <vector>

#include "nbtlog.hpp"

using _NT = int8_t;
using _IT = int64_t;

template <typename NT, typename IT>
using CSR = std::tuple<std::vector<NT>, std::vector<IT>, std::vector<IT>>;

template <typename NT>
bool isTranspose(const std::vector<std::vector<NT>> &A, const std::vector<std::vector<NT>> &B)
{
    auto m = A.size();
    auto n = A[0].size();

    if (B.size() != n || B[0].size() != m)
    {
        return false;
    }

    for (int i = 0; i < m; ++i)
    {
        for (int j = 0; j < n; ++j)
        {
            if (A[i][j] != B[j][i])
            {
                return false;
            }
        }
    }

    return true;
}

template <typename NT, typename IT>
CSR<NT, IT> gen_rand_csr(IT m, IT n, IT nnz)
{
    std::vector<NT> nums(nnz);
    std::vector<IT> colidxs(nnz);
    std::vector<IT> rowptrs(m + 1);

    std::srand(std::time(0));

    std::random_device rd;
    std::mt19937 gen(rd());

    std::uniform_int_distribution<IT> dist_row(0, nnz - 1);

    for (int row = 1; row < m; ++row)
    {
        rowptrs[row] = dist_row(gen);
    }

    rowptrs[0] = 0;
    rowptrs[m] = nnz;

    std::sort(std::begin(rowptrs), std::end(rowptrs));

    // remove all but one leading zero
    while (rowptrs[0] == 0 && rowptrs[1] == 0)
    {
        rowptrs.erase(rowptrs.begin());
    }

    // remove trailing duplicates
    while (rowptrs[rowptrs.size() - 1] == rowptrs[rowptrs.size() - 2])
    {
        rowptrs.pop_back();
    }

    auto start = nbtlog::timestamp();

    for (IT i = 0; i < nnz; ++i)
    {
        nums[i] = std::rand() % 100 + 1;
        colidxs[i] = std::rand() % n;
    }

    nbtlog::log("gen_rand_csr", nbtlog::timestamp() - start);

    return std::make_tuple(nums, colidxs, rowptrs);
}

template <typename NT, typename IT>
CSR<NT, IT> transpose_csr(const CSR<NT, IT> &csr)
{
    auto nums = std::get<0>(csr);
    auto colidxs = std::get<1>(csr);
    auto rowptrs = std::get<2>(csr);

    std::vector<NT> tnums(nums.size());
    std::vector<IT> tcolidxs(colidxs.size());

    auto tm = *std::max_element(std::begin(colidxs), std::end(colidxs)) + 1;
    std::vector<IT> trowptrs(tm + 1, 0);

    // histogramming
    std::vector<IT> nnz_per_col(tm, 0);
    for (int i = 0; i < tm; ++i)
    {
        for (int j = 0; j < rowptrs.size() - 1; ++j)
        {
            for (int jp = rowptrs[j]; jp < rowptrs[j + 1]; ++jp)
            {
                if (colidxs[jp] == i)
                {
                    nnz_per_col[i]++;
                }
            }
        }
    }

    // prefix sum from second element, using first element (zero) as offset
    // std::partial_sum(std::begin(nnz_per_col), std::end(nnz_per_col), std::begin(trowptrs) + 1);
    for (int i = 1; i < tm; ++i)
    {
        trowptrs[i] = trowptrs[i - 1] + nnz_per_col[i - 1];
    }

    // fill in tnums and tcolidxs
    for (int i = 0; i < rowptrs.size() - 1; ++i)
    {
        for (int j = rowptrs[i]; j < rowptrs[i + 1]; ++j)
        {
            auto col = colidxs[j];
            auto idx = trowptrs[col];
            tnums[idx] = nums[j];
            tcolidxs[idx] = i;
            trowptrs[col]++;
        }
    }

    // shift right by one
    std::rotate(std::rbegin(trowptrs), std::rbegin(trowptrs) + 1, std::rend(trowptrs));

    return std::make_tuple(tnums, tcolidxs, trowptrs);
}

template <typename NT, typename IT>
std::vector<std::vector<NT>> densify(const CSR<NT, IT> &csr)
{
    auto nums = std::get<0>(csr);
    auto colidxs = std::get<1>(csr);
    auto rowptrs = std::get<2>(csr);

    auto m = rowptrs.size() - 1;
    auto n = *std::max_element(std::begin(colidxs), std::end(colidxs)) + 1;

    std::vector<std::vector<NT>> dense(m, std::vector<NT>(n, 0));

    for (int row = 0; row < m; ++row)
    {
        for (int j = rowptrs[row]; j < rowptrs[row + 1]; ++j)
        {
            auto col = colidxs[j];
            dense[row][col] = nums[j];
        }
    }

    return dense;
}

template <typename NT>
void print_matrix(const std::vector<std::vector<NT>> &dense)
{
    for (auto &row : dense)
    {
        for (auto &elem : row)
        {
            std::cout << static_cast<int>(elem) << '\t';
        }
        std::cout << std::endl;
    }
}

int main(int argc, char *argv[])
{
    if (argc != 4)
    {
        std::cerr << "Usage: " << argv[0] << " <m> <n> <nnz>" << std::endl;
        return EXIT_FAILURE;
    }

    auto m = std::atoi(argv[1]);
    auto n = std::atoi(argv[2]);
    auto nnz = std::atoi(argv[3]);
    if (m <= 0 || n <= 0 || nnz <= 0)
    {
        std::cerr << "Error: m, n, and nnz must be positive integers." << std::endl;
        return EXIT_FAILURE;
    }

    std::cout << std::endl;

    std::cout << "Generating random CSR matrix with <m> = " + std::to_string(m) + ", <n> = " + std::to_string(n) + ", and <nnz> = " + std::to_string(nnz) << std::endl;
    std::cout << "Note --- <nnz> upper bounds number of non-zero elements. PRNG is hard :(" << std::endl;

    auto csr = gen_rand_csr<_NT, _IT>(m, n, nnz);
    auto [nums, colidxs, rowptrs] = csr;

    std::cout << "NUMS" << std::endl;

    for (auto &num : nums)
    {
        std::cout << static_cast<int>(num) << " ";
    }
    std::cout << std::endl;

    std::cout << "COLIDXS" << std::endl;

    for (auto &colidx : colidxs)
    {
        std::cout << colidx << " ";
    }
    std::cout << std::endl;

    std::cout << "ROWPTRS" << std::endl;

    for (auto &rowptr : rowptrs)
    {
        std::cout << rowptr << " ";
    }
    std::cout << std::endl;

    std::cout << "DENSIFY" << std::endl;

    // print_densify(std::make_tuple(nums, colidxs, rowptrs));
    auto matrix1 = densify(csr);
    print_matrix(matrix1);

    std::cout << std::endl;

    auto tcsr = transpose_csr(csr);
    auto [tnums, tcolidxs, trowptrs] = tcsr;

    std::cout << "TNUMS" << std::endl;

    for (auto &tnum : tnums)
    {
        std::cout << static_cast<int>(tnum) << " ";
    }
    std::cout << std::endl;

    std::cout << "TCOLIDXS" << std::endl;

    for (auto &tcolidx : tcolidxs)
    {
        std::cout << tcolidx << " ";
    }
    std::cout << std::endl;

    std::cout << "TROWPTRS" << std::endl;

    for (auto &trowptr : trowptrs)
    {
        std::cout << trowptr << " ";
    }
    std::cout << std::endl;

    std::cout << "DENSIFY" << std::endl;

    auto matrix2 = densify(tcsr);
    print_matrix(matrix2);

    std::cout << std::boolalpha << isTranspose(matrix1, matrix2) << std::endl;

    return EXIT_SUCCESS;
}

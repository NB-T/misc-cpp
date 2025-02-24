#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <tuple>
#include <vector>

#include "nbtlog.hpp"

using _NT = int8_t;
using _IT = int64_t;

template <typename NT, typename IT>
using CSR = std::tuple<std::vector<NT>, std::vector<IT>, std::vector<IT>>;

template <typename NT, typename IT>
CSR<NT, IT> gen_rand_csr(IT m, IT n, IT nnz)
{
    std::vector<NT> nums(nnz);
    std::vector<IT> colidxs(nnz);
    std::vector<IT> rowptrs(m + 1);

    std::srand(std::time(0));
    rowptrs[0] = 0;
    for (IT i = 0; i < m; i++)
    {
        rowptrs[i + 1] = rowptrs[i] + (std::rand() % (n / 2));
    }

    for (IT i = 0; i < nnz; i++)
    {
        colidxs[i] = std::rand() % n;
        nums[i] = std::rand() % 100 + 1;
    }

    return std::make_tuple(nums, colidxs, rowptrs);
}

template <typename NT, typename IT>
void print_densify(const CSR<NT, IT> &csr)
{
    auto nums = std::get<0>(csr);
    auto colidxs = std::get<1>(csr);
    auto rowptrs = std::get<2>(csr);

    auto n = *std::max_element(std::begin(colidxs), std::end(colidxs));

    for (IT row = 0; row < rowptrs.size() - 1; row++)
    {
        std::vector<NT> dense_row(n, 0);
        for (IT j = rowptrs[row]; j < rowptrs[row + 1]; ++j)
        {
            dense_row[colidxs[j]] = nums[j];
        }
        for (auto &num : dense_row)
        {
            std::cout << static_cast<int>(num) << '\t';
        }

        std::cout << '\n';
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

    auto [nums, colidxs, rowptrs] = gen_rand_csr<_NT, _IT>(m, n, nnz);

    std::cout << "NUMS" << std::endl;

    for (auto &num : nums)
    {
        std::cout << (int)num << " ";
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

    print_densify(std::make_tuple(nums, colidxs, rowptrs));

    return EXIT_SUCCESS;
}

#include <iostream>
#include <numeric>
#include <vector>

int main()
{
    // identity matrix
    std::vector<std::vector<int>> matrix = {
        {1, 0, 0},
        {0, 1, 0},
        {0, 0, 1}};

    // vector of twos
    std::vector<int> twos(3, 2);

    // dot product using accumulate
    std::vector<int> result(3);
    for (size_t i = 0; i < matrix.size(); ++i)
    {
        result[i] = std::inner_product(matrix[i].begin(), matrix[i].end(), twos.begin(), 0);
    }

    // output the result
    for (const auto &elem : result)
    {
        std::cout << elem << ' ';
    }
    std::cout << '\n';

    // now do it just using std::accumulate
    std::vector<int> result2(3);
    for (size_t i = 0; i < matrix.size(); ++i)
    {
        result2[i] = std::accumulate(matrix[i].begin(), matrix[i].end(), 0,
                                     [](int sum, int val)
                                     { return sum + val * 2; });
    }

    // output the result
    for (const auto &elem : result2)
    {
        std::cout << elem << ' ';
    }
    std::cout << '\n';

    return EXIT_SUCCESS;
}
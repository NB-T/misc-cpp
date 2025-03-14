#include <filesystem>
#include <fstream>
#include <iostream>
#include <vector>

#include "nbtlog.hpp"

void writeTimeToFile(std::ostream& file, int i, int num_iterations, double time)
{
    file << time;
    if (i < num_iterations - 1)
    {
        file << ",";
    }
}

std::string factorfactorfactor(int n, int num_iterations, std::string approach)
{
    // return std::to_string(n) + "/" + std::to_string(num_iterations) + "_" + approach + ".csv";
    return "out/" + std::to_string(n) + "/" + std::to_string(num_iterations) + "/" + approach + ".csv";
}

int main(int argc, char* argv[])
{
    if (argc != 3)
    {
        std::cerr << "Usage: " << argv[0] << " <n> <num_iterations>" << std::endl;
        return EXIT_FAILURE;
    }

    const int n = std::stoi(argv[1]);
    const int num_iterations = std::stoi(argv[2]);

    if (num_iterations <= 3)
    {
        std::cerr << "Usage: num_iterations must be greater than 3" << std::endl;
        return EXIT_FAILURE;
    }

    // ensure necessary directories exist using std::filesystem
    std::string out_dir = "out";
    std::filesystem::create_directories(out_dir);

    // create subdirs for different values of n
    std::string n_dir = out_dir + "/" + std::to_string(n);
    std::filesystem::create_directories(n_dir);

    // create subdirs for different values of num_iterations
    std::string num_iterations_dir = n_dir + "/" + std::to_string(num_iterations);
    std::filesystem::create_directories(num_iterations_dir);

    std::ofstream file1(factorfactorfactor(n, num_iterations, "ijk"));
    std::ofstream file2(factorfactorfactor(n, num_iterations, "transposed_a"));
    std::ofstream file3(factorfactorfactor(n, num_iterations, "transposed_b"));
    std::ofstream file4(factorfactorfactor(n, num_iterations, "jki"));
    std::ofstream file5(factorfactorfactor(n, num_iterations, "kji"));
    std::ofstream file6(factorfactorfactor(n, num_iterations, "kij"));
    std::ofstream file7(factorfactorfactor(n, num_iterations, "ikj"));
    std::ofstream file8(factorfactorfactor(n, num_iterations, "jik"));

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
    for (int i = 0; i < num_iterations; ++i)
    {
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
        // nbtlog::log("IJK", nbtlog::timestamp() - start);
        writeTimeToFile(file1, i, num_iterations, nbtlog::timestamp() - start);
    }

    // transpose A
    auto start = nbtlog::timestamp();
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
    for (int i = 0; i < num_iterations; ++i)
    {
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
        // nbtlog::log("TRANSPOSED A", nbtlog::timestamp() - start);
        writeTimeToFile(file2, i, num_iterations, nbtlog::timestamp() - start);
    }

    std::vector<std::vector<int>> tmp_b = mul2;
    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < i; ++j)
        {
            std::swap(tmp_b[i][j], tmp_b[j][i]);
        }
    }

    r2 = std::vector(n, std::vector(n, 0));
    for (int i = 0; i < num_iterations; ++i)
    {
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
        // nbtlog::log("TRANSPOSED B", nbtlog::timestamp() - start);
        writeTimeToFile(file3, i, num_iterations, nbtlog::timestamp() - start);
    }

    std::vector<std::vector<int>> r3(n, std::vector<int>(n));
    for (int i = 0; i < num_iterations; ++i)
    {
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
        // nbtlog::log("JKI", nbtlog::timestamp() - start);
        writeTimeToFile(file4, i, num_iterations, nbtlog::timestamp() - start);
    }

    std::vector<std::vector<int>> r4(n, std::vector<int>(n));
    for (int i = 0; i < num_iterations; ++i)
    {
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
        // nbtlog::log("KJI", nbtlog::timestamp() - start);
        writeTimeToFile(file5, i, num_iterations, nbtlog::timestamp() - start);
    }

    std::vector<std::vector<int>> r5(n, std::vector<int>(n));
    for (int i = 0; i < num_iterations; ++i)
    {
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
        // nbtlog::log("KIJ", nbtlog::timestamp() - start);
        writeTimeToFile(file6, i, num_iterations, nbtlog::timestamp() - start);
    }

    std::vector<std::vector<int>> r6(n, std::vector<int>(n));
    for (int i = 0; i < num_iterations; ++i)
    {
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
        //    nbtlog::log("IKJ", nbtlog::timestamp() - start);
        writeTimeToFile(file7, i, num_iterations, nbtlog::timestamp() - start);
    }

    std::vector<std::vector<int>> r7(n, std::vector<int>(n));
    for (int i = 0; i < num_iterations; ++i)
    {
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
        // nbtlog::log("IKJ", nbtlog::timestamp() - start);
        writeTimeToFile(file8, i, num_iterations, nbtlog::timestamp() - start);
    }

    file1.close();
    file2.close();
    file3.close();
    file4.close();
    file5.close();
    file6.close();
    file7.close();
    file8.close();

    return EXIT_SUCCESS;
}

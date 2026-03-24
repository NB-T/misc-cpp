#include <atomic>
#include <omp.h>
#include <set>
#include <vector>

using Graph = ? ? ? ? ? ;

void BFS(const Graph& g, int source, std::vector<int>& depth)
{
    std::set<int> frontier_in;
    std::set<int> frontier_out;
    depth[source] = 0;
    int d = 1;

    while (!frontier_in.empty())
    {
#pragma omp parallel for
        for (auto it = frontier_in.begin(); it != frontier_in.end(); ++it)
        {
            int v = *it;
            for (int n : g.neighbors(v))
            {
                /*
if (depth[n] == -1)
{
    depth[n] = d;
    frontier_out.insert(n);
}
                */
                if (std::compare_exchange_strong(depth[n], -1, d))
                {
                    frontier_out.insert(n);
                }
            }
        }
        frontier_in = frontier_out;
        frontier_out.clear();
        ++d;
    }
}

struct GraphCSR
{
    int n;
    std::vector<int> row_ptr;
    std::vector<int> val;
};

void BFS(const GraphCSR& g, int source, std::vector<std::atomic<int>>& depth)
{
    std::set<int> frontier_in;
    std::set<int> frontier_out;

    frontier_in.insert(source);
    depth[source].store(0, std::memory_order_relaxed);

    int d = 1;

    while (!frontier_in.empty())
    {
#pragma omp parallel for
        for (auto it = frontier_in.begin(); it != frontier_in.end(); ++it)
        {
            int v = *it;
            for (int idx = g.row_ptr[v]; idx < row_ptr[v + 1]; ++idx)
            {
                int n = g.val[idx];
                if (depth[n].compare_exchange_strong(-1, d))
                {
                    frontier_out.insert(n);
                }
            }
        }

        frontier_in = frontier_out;
        frontier_out.clear();
        ++d;
    }
}

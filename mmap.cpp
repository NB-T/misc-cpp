#include <algorithm>
#include <chrono>
#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <fcntl.h>
#include <iostream>
#include <random>
#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>
#include <vector>

using clk = std::chrono::steady_clock;

static double ms_since(clk::time_point t0)
{
    auto dt = clk::now() - t0;
    return std::chrono::duration<double, std::milli>(dt).count();
}

// Drop the page cache so each benchmark starts from a cold disk read.
// Requires root (sudo); silently skipped otherwise.
static void drop_caches()
{
    sync();
    int fd = open("/proc/sys/vm/drop_caches", O_WRONLY);
    if (fd == -1) return;
    const char* three = "3\n";
    [[maybe_unused]] auto _ = write(fd, three, 2);
    close(fd);
}

static void create_file(const char* filename, size_t file_size)
{
    int fd = open(filename, O_RDWR | O_CREAT | O_TRUNC, 0644);
    if (fd == -1) { std::perror("open"); std::exit(1); }
    if (ftruncate(fd, file_size) == -1) { std::perror("ftruncate"); std::exit(1); }

    std::mt19937 rng(42);
    const size_t chunk_ints = 1 << 20; // 4 MiB chunks
    std::vector<int> buf(chunk_ints);
    size_t remaining = file_size / sizeof(int);
    while (remaining > 0) {
        size_t n = std::min(chunk_ints, remaining);
        for (size_t i = 0; i < n; ++i) buf[i] = static_cast<int>(rng());
        if (write(fd, buf.data(), n * sizeof(int)) == -1) {
            std::perror("write"); std::exit(1);
        }
        remaining -= n;
    }
    close(fd);
}

// ---------- Sequential sum: read() vs mmap ----------

static int64_t sum_with_read(const char* filename, size_t file_size)
{
    int fd = open(filename, O_RDONLY);
    if (fd == -1) { std::perror("open"); std::exit(1); }

    const size_t buf_bytes = 1 << 20; // 1 MiB
    std::vector<int> buf(buf_bytes / sizeof(int));
    int64_t sum = 0;
    size_t remaining = file_size;
    while (remaining > 0) {
        size_t want = std::min(buf_bytes, remaining);
        ssize_t got = read(fd, buf.data(), want);
        if (got <= 0) { std::perror("read"); std::exit(1); }
        size_t n = static_cast<size_t>(got) / sizeof(int);
        for (size_t i = 0; i < n; ++i) sum += buf[i];
        remaining -= got;
    }
    close(fd);
    return sum;
}

static int64_t sum_with_mmap(const char* filename, size_t file_size)
{
    int fd = open(filename, O_RDONLY);
    if (fd == -1) { std::perror("open"); std::exit(1); }

    void* p = mmap(nullptr, file_size, PROT_READ, MAP_PRIVATE, fd, 0);
    if (p == MAP_FAILED) { std::perror("mmap"); std::exit(1); }
    // Hint that we'll stream through it; lets the kernel prefetch aggressively.
    madvise(p, file_size, MADV_SEQUENTIAL);

    const int* data = static_cast<const int*>(p);
    size_t n = file_size / sizeof(int);
    int64_t sum = 0;
    for (size_t i = 0; i < n; ++i) sum += data[i];

    munmap(p, file_size);
    close(fd);
    return sum;
}

// ---------- Random access: pread() vs mmap ----------
//
// Touch N random 4-byte ints scattered across the file. mmap wins here
// because each access is a memory load (page-faulted on first touch),
// not a syscall.

static int64_t random_access_pread(const char* filename, size_t file_size,
                                   size_t num_accesses, uint64_t seed)
{
    int fd = open(filename, O_RDONLY);
    if (fd == -1) { std::perror("open"); std::exit(1); }

    std::mt19937_64 rng(seed);
    size_t num_ints = file_size / sizeof(int);
    int64_t sum = 0;
    for (size_t i = 0; i < num_accesses; ++i) {
        size_t idx = rng() % num_ints;
        int val;
        ssize_t got = pread(fd, &val, sizeof(int), idx * sizeof(int));
        if (got != sizeof(int)) { std::perror("pread"); std::exit(1); }
        sum += val;
    }
    close(fd);
    return sum;
}

static int64_t random_access_mmap(const char* filename, size_t file_size,
                                  size_t num_accesses, uint64_t seed)
{
    int fd = open(filename, O_RDONLY);
    if (fd == -1) { std::perror("open"); std::exit(1); }

    void* p = mmap(nullptr, file_size, PROT_READ, MAP_PRIVATE, fd, 0);
    if (p == MAP_FAILED) { std::perror("mmap"); std::exit(1); }
    madvise(p, file_size, MADV_RANDOM);

    const int* data = static_cast<const int*>(p);
    std::mt19937_64 rng(seed);
    size_t num_ints = file_size / sizeof(int);
    int64_t sum = 0;
    for (size_t i = 0; i < num_accesses; ++i) {
        size_t idx = rng() % num_ints;
        sum += data[idx];
    }

    munmap(p, file_size);
    close(fd);
    return sum;
}

int main(int argc, char** argv)
{
    const char* filename = "input.bin";
    // 256 MiB by default — big enough that page-cache effects matter,
    // small enough to fit in RAM on a laptop.
    size_t file_size = (argc > 1) ? std::strtoull(argv[1], nullptr, 10)
                                  : (size_t(256) << 20);
    size_t num_random = (argc > 2) ? std::strtoull(argv[2], nullptr, 10)
                                   : 200000;

    std::cout << "file size: " << (file_size >> 20) << " MiB\n";
    std::cout << "random accesses: " << num_random << "\n\n";

    create_file(filename, file_size);

    // --- Sequential sum ---
    std::cout << "[sequential sum, warm cache]\n";
    int64_t s_read_warm = sum_with_read(filename, file_size); // prime cache
    auto t0 = clk::now();
    int64_t s_read = sum_with_read(filename, file_size);
    double t_read = ms_since(t0);

    t0 = clk::now();
    int64_t s_mmap = sum_with_mmap(filename, file_size);
    double t_mmap = ms_since(t0);

    std::cout << "  read():  " << t_read << " ms  (sum=" << s_read << ")\n";
    std::cout << "  mmap():  " << t_mmap << " ms  (sum=" << s_mmap << ")\n";
    std::cout << "  speedup: " << (t_read / t_mmap) << "x\n";
    if (s_read != s_mmap || s_read != s_read_warm) {
        std::cerr << "  !! sum mismatch\n"; return 1;
    }

    // --- Random access (this is where mmap really wins) ---
    std::cout << "\n[random access, warm cache]\n";
    uint64_t seed = 0xC0FFEEULL;
    // prime cache
    (void)random_access_pread(filename, file_size, num_random, seed);

    t0 = clk::now();
    int64_t r_pread = random_access_pread(filename, file_size, num_random, seed);
    double t_pread = ms_since(t0);

    t0 = clk::now();
    int64_t r_mmap = random_access_mmap(filename, file_size, num_random, seed);
    double t_mmap_r = ms_since(t0);

    std::cout << "  pread(): " << t_pread << " ms  (sum=" << r_pread << ")\n";
    std::cout << "  mmap():  " << t_mmap_r << " ms  (sum=" << r_mmap << ")\n";
    std::cout << "  speedup: " << (t_pread / t_mmap_r) << "x\n";
    if (r_pread != r_mmap) { std::cerr << "  !! sum mismatch\n"; return 1; }

    // --- Optional cold-cache run (needs root for drop_caches) ---
    if (geteuid() == 0) {
        std::cout << "\n[sequential sum, cold cache]\n";
        drop_caches();
        t0 = clk::now();
        (void)sum_with_read(filename, file_size);
        double c_read = ms_since(t0);

        drop_caches();
        t0 = clk::now();
        (void)sum_with_mmap(filename, file_size);
        double c_mmap = ms_since(t0);

        std::cout << "  read(): " << c_read << " ms\n";
        std::cout << "  mmap(): " << c_mmap << " ms\n";
    } else {
        std::cout << "\n(run as root to also see cold-cache numbers)\n";
    }

    return 0;
}

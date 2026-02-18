if [ "$#" -lt 1 ]; then
    echo "Usage: $0 <source{.cpp}> [source2.cpp] ..."
    exit 1
fi

for arg in "$@"; do
    EXEC="${arg%.cpp}"
    clang++ -std=c++23 "$EXEC.cpp" -g -o "$(basename "$EXEC")" -fopenmp -O0 -fsanitize=address
done

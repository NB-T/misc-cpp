if [ "$#" -ne 1 ]; then
    echo "Usage: $0 <>[.cpp]"
    exit 1
fi

EXEC="${1%.cpp}"

clang++ -std=c++23 $EXEC.cpp -g -o $(basename "$EXEC") -fopenmp -O0 -fsanitize=address
# g++ -std=c++2b $EXEC.cpp -o $(basename "$EXEC")

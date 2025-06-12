g++ -std=c++2a $1 -Iinclude -Llib -lnbtlog -g -o $(basename "$1" .cpp) -fopenmp -O3 -fsanitize=address

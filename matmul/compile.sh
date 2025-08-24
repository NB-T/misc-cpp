if [ $# -ne 1 ]; then
  echo "Usage: $0 <.cpp>"
  exit 1
fi

g++ -std=c++2a $1 -Iinclude -Llib -lnbtlog -g -o $(basename "$1" .cpp) -fopenmp -O0 -fsanitize=address

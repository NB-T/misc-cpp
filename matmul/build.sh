#!/usr/bin/env bash
set -euo pipefail

BUILD_DIR="${BUILD_DIR:-build}"
BUILD_TYPE="${BUILD_TYPE:-Release}"

cmake -S . -B "${BUILD_DIR}" -DCMAKE_BUILD_TYPE="${BUILD_TYPE}"
cmake --build "${BUILD_DIR}" --parallel "$(nproc)"

if [[ $# -gt 0 ]]; then
  "./${BUILD_DIR}/matmul" "$@"
else
  echo "Built ./${BUILD_DIR}/matmul"
  echo "Run: ./${BUILD_DIR}/matmul <n> <num_iterations>"
fi



#!/usr/bin/env bash

set -e # Exit on first error

# Remove the build directory if it exists
if [[ -d "build" ]]; then
  echo "Removing existing build directory..."
  rm -rf build
fi

# Configure the project with CMake
echo "Configuring project with CMake..."
cmake -S . -B build

# Build the project
echo "Building project..."
cmake --build build

# Run the resulting binary if it exists
if [[ -x "build/bin/infcalc" ]]; then
  echo "Running program..."
  ./build/bin/infcalc
else
  echo "Error: Binary 'build/bin/infcalc' not found or not executable."
  exit 1
fi

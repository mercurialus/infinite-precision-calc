│── src/                            # Source code
│   ├── bigint.hpp                   # BigInt class (header)
│   ├── bigint.cpp                   # BigInt class (implementation)
│   ├── bigfloat.hpp                 # BigFloat class (header)
│   ├── bigfloat.cpp                 # BigFloat class (implementation)
│   ├── bigint_karatsuba.hpp         # Optimized BigInt with Karatsuba (header)
│   ├── bigint_karatsuba.cpp         # Optimized BigInt with Karatsuba (implementation)
│   ├── bigint_fft.hpp               # Optimized BigInt with FFT (header) (Optional, if added)
│   ├── bigint_fft.cpp               # Optimized BigInt with FFT (implementation) (Optional, if added)
│   ├── benchmark.hpp                # Benchmarking utility (header)
│   ├── benchmark.cpp                # Benchmarking utility (implementation)
│   ├── cli.hpp                      # Command-line interface (header)
│   ├── cli.cpp                      # Command-line interface (implementation)
│   ├── utils.hpp                    # Helper functions (header)
│   ├── utils.cpp                    # Helper functions (implementation)
│   ├── main.cpp                     # Entry point (CLI-based calculator)
│
│── tests/                           # Unit & performance tests
│   ├── unit/  
│   │   ├── test_bigint.cpp          # Tests for BigInt class
│   │   ├── test_bigfloat.cpp        # Tests for BigFloat class
│   ├── utils/  
│   │   ├── test_performance.cpp     # Benchmark & performance tests
│
│── docs/                            # Documentation
│   ├── README.md                    # Project overview
│   ├── DESIGN.md                    # Design decisions & architecture
│   ├── USAGE.md                      # How to use the calculator
│   ├── PROJECT_STRUCTURE.md         # Directory structure & purpose of each file
│   ├── CONTRIBUTING.md              # Guidelines for contributors (optional)
│
│── config/                          # Configuration files (Optional, if CLI has settings)
│   ├── default_settings.json        # Default configuration settings (Optional)
│   ├── cli_config.ini               # CLI configurations (Optional)
│
│── build/                           # Compiled binaries (Auto-generated, ignored in Git)
│── CMakeLists.txt                    # Build system configuration
│── .gitignore                        # Ignore build files, binaries, and unnecessary files
│── LICENSE                           # License (MIT, Apache, or chosen license)

This is the expected final structure of the project for submission. I will try to add as many features as possible.
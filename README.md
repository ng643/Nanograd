# NANOGRAD

Small C++ autodiff playground built while following Andrej Karpathy’s micrograd walkthrough. All credit for the idea and original Python implementation goes to Andrej; see <https://github.com/karpathy/micrograd>.

## Build and run

- Windows (MSVC): `cl /EHsc src\\Main.cpp src\\Value.cpp`
- GCC/Clang: `g++ -std=c++17 -O2 -o nanograd src/Main.cpp src/Value.cpp`

Then run `nanograd` (or `nanograd.exe` on Windows).

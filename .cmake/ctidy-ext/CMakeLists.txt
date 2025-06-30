# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.
cmake_minimum_required(VERSION 3.13)
project(MchpVelocitySPClangTidyModule C CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(LLVM_DIR /usr/lib/cmake/clang-14/)
set(CMAKE_EXPORT_COMPILE_COMMANDS on)

set(Clang_DIR /usr/lib/llvm-14/lib/cmake/clang)

find_package(Clang REQUIRED
             #PATH /usr/lib/llvm-14/lib/cmake/clang
             #NO_DEFAULT_PATH
)

add_subdirectory(src)


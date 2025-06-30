# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

include_directories(.)
add_library(mchp-velocitysp-clang-tidy-module MODULE
  Module.cxx

  ImplicitBoolConversionCheck.cpp
  ImplicitBoolConversionCheck.h

  IntegerLiteralConversion.cpp
  IntegerLiteralConversion.h
)

target_include_directories(mchp-velocitysp-clang-tidy-module PRIVATE ${CLANG_INCLUDE_DIRS})
target_link_libraries(mchp-velocitysp-clang-tidy-module PRIVATE clang-tidy)


# Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
# SPDX-License-Identifier: MIT

include(./.cmake/flags.cmake)

# Only include the following if we are the top level project
if (${PROJECT_NAME} STREQUAL ${CMAKE_PROJECT_NAME})
  include(./.cmake/mkid.cmake)
  include(./.cmake/tags.cmake)
endif()


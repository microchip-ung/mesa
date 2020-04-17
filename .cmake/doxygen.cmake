# Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
# SPDX-License-Identifier: MIT

if (${BUILD_DOXYGEN})
    message(STATUS "Build doxygen as part of the default target")
    add_custom_target(doxygen ALL)
else()
    add_custom_target(doxygen)
endif()

macro(doxygen_target)
  set(options HTML PDF)
  set(oneValueArgs TARGET NAME)
  set(multiValueArgs FILES DEFINES INCLUDES)
  cmake_parse_arguments(A "${options}" "${oneValueArgs}" "${multiValueArgs}" ${ARGN})

  add_custom_command(
      OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/doxygen/${A_TARGET}.pdf
      COMMAND ${CMAKE_SOURCE_DIR}/.cmake/doxygen.rb
              --name ${A_NAME}
              --target ${A_TARGET}
              --output-dir ${CMAKE_CURRENT_BINARY_DIR}/doxygen
              ${A_DEFINES}
              ${A_INCLUDES}
              ${A_FILES}

      WORKING_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}"
      COMMENT "Doxygen config"
  )
  add_custom_target(doxygen_${A_TARGET} DEPENDS ${CMAKE_CURRENT_BINARY_DIR}/doxygen/${A_TARGET}.pdf)
  add_dependencies(doxygen doxygen_${A_TARGET})
endmacro()


# Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
# SPDX-License-Identifier: MIT

include(./.cmake/flags.cmake)

# Only include the following if we are the top level project
if (${PROJECT_NAME} STREQUAL ${CMAKE_PROJECT_NAME})
  include(./.cmake/mkid.cmake)
  include(./.cmake/tags.cmake)
endif()

macro(mesa_export_compile_commands_recursive)
    set(libs ${ARGV})
    set(libs_next ${ARGV})

    while (TRUE)
        foreach(l ${libs})
            set_property(TARGET ${l} PROPERTY EXPORT_COMPILE_COMMANDS ON)

            get_target_property(DEPS ${l} LINK_LIBRARIES)
            if (DEPS)
                foreach(dep ${DEPS})
                    list(FIND libs ${dep} found)
                    if (${found} EQUAL -1)
                        #message(STATUS "DEP: ${l} -> ${dep} - NOT FOUND")
                        list(APPEND libs_next ${dep})
                    else ()
                        #message(STATUS "DEP: ${l} -> ${dep} - FOUND")
                    endif()
                endforeach()
            endif()

            get_target_property(DEPS ${l} MANUALLY_ADDED_DEPENDENCIES)
            if (DEPS)
                foreach(dep ${DEPS})
                    list(FIND libs ${dep} found)
                    if (${found} EQUAL -1)
                        #message(STATUS "MDEP: ${l} -> ${dep} - NOT FOUND")
                        list(APPEND libs_next ${dep})
                    else ()
                        #message(STATUS "DEP: ${l} -> ${dep} - FOUND")
                    endif()
                endforeach()
            endif()
        endforeach()

        list(LENGTH libs libs_length)
        list(LENGTH libs_next libs_next_length)
        #message(STATUS "${libs_length} ${libs_next_length}")
        if (${libs_length} EQUAL ${libs_next_length})
            break()
        else()
            set(libs ${libs_next})
        endif()
    endwhile()
endmacro()

macro(mesa_export_targets_recursive)
    set(a ${ARGV})
    list(POP_FRONT a FILENAME)
    set(libs ${a})
    set(libs_next ${a})
    set(visited )

    set(obj_target "EXECUTABLE"
                   "SHARED"
                   "MODULE"
                   "OBJECT_LIBRARY"
                   "STATIC_LIBRARY")

    set(props "BINARY_DIR"
              "COMPILE_DEFINITIONS"
              "C_STANDARD"
              "EXCLUDE_FROM_ALL"
              "EXPORT_COMPILE_COMMANDS"
              "IMPORTED"
              "IMPORTED_GLOBAL"
              "INCLUDE_DIRECTORIES"
              "INTERFACE_LINK_LIBRARIES"
              "INTERFACE_LINK_OPTIONS"
              "LINK_DEPENDS"
              "LINK_LIBRARIES"
              "LINK_OPTIONS"
              "MANUALLY_ADDED_DEPENDENCIES"
              "NAME"
              "SOURCES"
              "SOURCE_DIR"
              "TYPE"
              "INTERFACE_COMPILE_DEFINITIONS"
              "COMPILE_OPTIONS"
              "INTERFACE_COMPILE_OPTIONS"
              "OUTPUT_NAME"
              "INTERFACE_INCLUDE_DIRECTORIES")

    file(WRITE ${FILENAME} "")

    # Dump properties to file
    set(t "")

    while (TRUE)
        foreach(l ${libs})
            list(FIND visited ${l} found)
            if (NOT(${found} EQUAL -1))
                continue()
            endif()
            list(APPEND visited ${l})

            #TODO, we need to get directory properties as well!
            #get_directory_property(DIRECTORY_DEFS COMPILE_DEFINITIONS)

            foreach(p ${props})
                get_property(was_set TARGET ${l} PROPERTY ${p} SET)
                if(was_set)
                    get_target_property(value ${l} ${p})
                    if (${p} STREQUAL "INTERFACE_LINK_LIBRARIES")
                        list(FILTER value EXCLUDE REGEX "LINK_ONLY:")
                    endif()

                    string(APPEND t "${l} ${p} = ${value}\n")
                endif()

            endforeach()

            get_property(type TARGET ${l} PROPERTY "TYPE")
            list(FIND obj_target ${type} found)
            if (NOT ${found} EQUAL -1)
                if (NOT type STREQUAL "OBJECT_LIBRARY")
                    string(APPEND t "${l} TARGET_FILE = $<TARGET_FILE:${l}>\n")
                endif()
                string(APPEND t "${l} TARGET_OBJECTS = $<TARGET_OBJECTS:${l}>\n")
            endif()

            # Go through direct dependencies
            get_target_property(DEPS ${l} LINK_LIBRARIES)
            if (DEPS)
                foreach(dep ${DEPS})
                    list(FIND libs ${dep} found)
                    if (${found} EQUAL -1)
                        #message(STATUS "DEP: ${l} -> ${dep} - NOT FOUND")
                        list(FIND libs_next ${dep} found)
                        if (${found} EQUAL -1)
                            list(APPEND libs_next ${dep})
                        endif()
                    else ()
                        #message(STATUS "DEP: ${l} -> ${dep} - FOUND")
                    endif()
                endforeach()
            endif()

            # Go through dependencies of imported targets (partial-linked-static
            # libs)
            get_target_property(DEPS ${l} MANUALLY_ADDED_DEPENDENCIES)
            if (DEPS)
                foreach(dep ${DEPS})
                    list(FIND libs ${dep} found)
                    if (${found} EQUAL -1)
                        #message(STATUS "MDEP: ${l} -> ${dep} - NOT FOUND")
                        list(FIND libs_next ${dep} found)
                        if (${found} EQUAL -1)
                            list(APPEND libs_next ${dep})
                        endif()
                    else ()
                        #message(STATUS "DEP: ${l} -> ${dep} - FOUND")
                    endif()
                endforeach()
            endif()
        endforeach()

        list(LENGTH libs libs_length)
        list(LENGTH libs_next libs_next_length)
        #message(STATUS "${libs_length} ${libs_next_length}")
        if (${libs_length} EQUAL ${libs_next_length})
            break()
        else()
            set(libs ${libs_next})
        endif()
    endwhile()

    #file(APPEND ${FILENAME} CONTENT "${t}")
    file(GENERATE OUTPUT ${FILENAME} CONTENT "${t}")


endmacro()

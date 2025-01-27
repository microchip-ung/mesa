# Copyright (c) 2021-2022 Microchip Technology Inc. and its subsidiaries.
# SPDX-License-Identifier: MIT

include_directories(${acutest_SOURCE_DIR})
message(STATUS "utils/acutest: ${acutest_SOURCE_DIR}")

lm_test_add_executable(lm_ut_utils lm_ut_utils.c)
lm_test_target_link_libraries(lm_ut_utils lm_utils lmd_mup1 lms_stub)

lm_test_add_executable(lm_ut_utils_trace_conf lm_ut_utils_trace_conf.c)
lm_test_target_link_libraries(lm_ut_utils_trace_conf lm_utils)

lm_test_add_executable(lm_ut_utils_strchr lm_ut_strchr.c)
lm_test_target_link_libraries(lm_ut_utils_strchr lm_utils lms_stub)

lm_test_add_executable(lm_ut_utils_strcspn lm_ut_strcspn.c)
lm_test_target_link_libraries(lm_ut_utils_strcspn lm_utils lms_stub)

lm_test_add_executable(lm_ut_utils_strspn lm_ut_strspn.c)
lm_test_target_link_libraries(lm_ut_utils_strspn lm_utils lms_stub)

// Copyright (c) 2021-2022 Microchip Technology Inc. and its subsidiaries.
// SPDX-License-Identifier: MIT

#ifndef LM_UTILS_PP_H
#define LM_UTILS_PP_H

#define LMU_PP_DUMMY_ARG 0

#define LMU_PP_STRINGIFY_IMPL(X) #X
#define LMU_PP_STRINGIFY(X)      LMU_PP_STRINGIFY_IMPL(X)

#define LMU_PP_CONCAT_IMPL4(x, y) x##y
#define LMU_PP_CONCAT_IMPL3(x, y) LMU_PP_CONCAT_IMPL4(x, y)
#define LMU_PP_CONCAT_IMPL2(x, y) LMU_PP_CONCAT_IMPL3(x, y)
#define LMU_PP_CONCAT_IMPL1(x, y) LMU_PP_CONCAT_IMPL2(x, y)
#define LMU_PP_CONCAT_IMPL(x, y)  LMU_PP_CONCAT_IMPL1(x, y)
#define LMU_PP_CONCAT(x, y)       LMU_PP_CONCAT_IMPL(x, y)

#define LMU_PP_RSEQ_N() 15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0
#define LMU_PP_ONE_OR_MORE_RSEQ_N()                                            \
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0
#define LMU_PP_TWO_OR_MORE_RSEQ_N()                                            \
    2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 1, 0

#define LMU_PP_ARG_N(_1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13,   \
                     _14, _15, N, ...)                                         \
    N

#if defined(__GNUC__)
#if __GNUC__ == 13
// Not sure when it is best to use __VA_OPT__(,) instead of ##__VA_ARGS__, but
// we see that gcc 13 does not shallow the comma in the MACROs below.
// But we cannot change to always __VA_OPT__(,) as this is not supported in
// GCC10
#define LMU_PP_USE___VA_OPT__
#endif
#endif

#if defined(LMU_PP_USE___VA_OPT__)
#define LMU_PP_VA_ARGS_NARG_(DUMMY, ...) LMU_PP_ARG_N(__VA_ARGS__)
#define LMU_PP_VA_ARGS_NARG(...)                                               \
    LMU_PP_VA_ARGS_NARG_(LMU_PP_DUMMY_ARG __VA_OPT__(, ) __VA_ARGS__,          \
                         LMU_PP_RSEQ_N())

#define LMU_PP_VA_ARGS_ONE_OR_MORE_(DUMMY, ...) LMU_PP_ARG_N(__VA_ARGS__)
#define LMU_PP_VA_ARGS_ONE_OR_MORE(...)                                        \
    LMU_PP_VA_ARGS_ONE_OR_MORE_(LMU_PP_DUMMY_ARG __VA_OPT__(, ) __VA_ARGS__,   \
                                LMU_PP_ONE_OR_MORE_RSEQ_N())

#define LMU_PP_VA_ARGS_TWO_OR_MORE_(DUMMY, ...) LMU_PP_ARG_N(__VA_ARGS__)
#define LMU_PP_VA_ARGS_TWO_OR_MORE(...)                                        \
    LMU_PP_VA_ARGS_TWO_OR_MORE_(LMU_PP_DUMMY_ARG __VA_OPT__(, ) __VA_ARGS__,   \
                                LMU_PP_TWO_OR_MORE_RSEQ_N())
#else // LMU_PP_USE___VA_OPT__

#define LMU_PP_VA_ARGS_NARG_(DUMMY, ...) LMU_PP_ARG_N(__VA_ARGS__)
#define LMU_PP_VA_ARGS_NARG(...)                                               \
    LMU_PP_VA_ARGS_NARG_(LMU_PP_DUMMY_ARG, ##__VA_ARGS__, LMU_PP_RSEQ_N())

#define LMU_PP_VA_ARGS_ONE_OR_MORE_(DUMMY, ...) LMU_PP_ARG_N(__VA_ARGS__)
#define LMU_PP_VA_ARGS_ONE_OR_MORE(...)                                        \
    LMU_PP_VA_ARGS_ONE_OR_MORE_(LMU_PP_DUMMY_ARG, ##__VA_ARGS__,               \
                                LMU_PP_ONE_OR_MORE_RSEQ_N())

#define LMU_PP_VA_ARGS_TWO_OR_MORE_(DUMMY, ...) LMU_PP_ARG_N(__VA_ARGS__)
#define LMU_PP_VA_ARGS_TWO_OR_MORE(...)                                        \
    LMU_PP_VA_ARGS_TWO_OR_MORE_(LMU_PP_DUMMY_ARG, ##__VA_ARGS__,               \
                                LMU_PP_TWO_OR_MORE_RSEQ_N())

#endif // LMU_PP_USE___VA_OPT__

#define LMU_PP_VA_ARGS_OVERLOAD(M, ...)                                        \
    LMU_PP_CONCAT_IMPL(M, LMU_PP_VA_ARGS_NARG(__VA_ARGS__))

#define LMU_PP_VA_ARGS_OVERLOAD_ONE_OR_MORE(M, ...)                            \
    LMU_PP_CONCAT_IMPL(M, LMU_PP_VA_ARGS_ONE_OR_MORE(__VA_ARGS__))

#define LMU_PP_VA_ARGS_OVERLOAD_TWO_OR_MORE(M, ...)                            \
    LMU_PP_CONCAT_IMPL(M, LMU_PP_VA_ARGS_TWO_OR_MORE(__VA_ARGS__))

#define LMU_PP_FOREACH_0(ACTION)
#define LMU_PP_FOREACH_1(ACTION, X) ACTION(X)
#define LMU_PP_FOREACH_2(ACTION, X, ...)                                       \
    ACTION(X) LMU_PP_FOREACH_1(ACTION, __VA_ARGS__)
#define LMU_PP_FOREACH_3(ACTION, X, ...)                                       \
    ACTION(X) LMU_PP_FOREACH_2(ACTION, __VA_ARGS__)
#define LMU_PP_FOREACH_4(ACTION, X, ...)                                       \
    ACTION(X) LMU_PP_FOREACH_3(ACTION, __VA_ARGS__)
#define LMU_PP_FOREACH_5(ACTION, X, ...)                                       \
    ACTION(X) LMU_PP_FOREACH_4(ACTION, __VA_ARGS__)
#define LMU_PP_FOREACH_6(ACTION, X, ...)                                       \
    ACTION(X) LMU_PP_FOREACH_5(ACTION, __VA_ARGS__)
#define LMU_PP_FOREACH_7(ACTION, X, ...)                                       \
    ACTION(X) LMU_PP_FOREACH_6(ACTION, __VA_ARGS__)
#define LMU_PP_FOREACH_8(ACTION, X, ...)                                       \
    ACTION(X) LMU_PP_FOREACH_7(ACTION, __VA_ARGS__)
#define LMU_PP_FOREACH_9(ACTION, X, ...)                                       \
    ACTION(X) LMU_PP_FOREACH_8(ACTION, __VA_ARGS__)
#define LMU_PP_FOREACH_10(ACTION, X, ...)                                       \
    ACTION(X) LMU_PP_FOREACH_9(ACTION, __VA_ARGS__)
#define LMU_PP_FOREACH_11(ACTION, X, ...)                                       \
    ACTION(X) LMU_PP_FOREACH_10(ACTION, __VA_ARGS__)
#define LMU_PP_FOREACH_12(ACTION, X, ...)                                       \
    ACTION(X) LMU_PP_FOREACH_11(ACTION, __VA_ARGS__)
#define LMU_PP_FOREACH_13(ACTION, X, ...)                                       \
    ACTION(X) LMU_PP_FOREACH_12(ACTION, __VA_ARGS__)
#define LMU_PP_FOREACH_14(ACTION, X, ...)                                       \
    ACTION(X) LMU_PP_FOREACH_13(ACTION, __VA_ARGS__)
#define LMU_PP_FOREACH_15(ACTION, X, ...)                                       \
    ACTION(X) LMU_PP_FOREACH_14(ACTION, __VA_ARGS__)
#define LMU_PP_FOREACH(ACTION, ...)                                            \
    LMU_PP_VA_ARGS_OVERLOAD(LMU_PP_FOREACH_, ##__VA_ARGS__)                    \
    (ACTION, ##__VA_ARGS__)

#define LMU_PP_FOREACH_1ARG_0(ACTION, A0)
#define LMU_PP_FOREACH_1ARG_1(ACTION, A0, X) ACTION(A0, X)
#define LMU_PP_FOREACH_1ARG_2(ACTION, A0, X, ...)                              \
    ACTION(A0, X) LMU_PP_FOREACH_1ARG_1(ACTION, A0, __VA_ARGS__)
#define LMU_PP_FOREACH_1ARG_3(ACTION, A0, X, ...)                              \
    ACTION(A0, X) LMU_PP_FOREACH_1ARG_2(ACTION, A0, __VA_ARGS__)
#define LMU_PP_FOREACH_1ARG_4(ACTION, A0, X, ...)                              \
    ACTION(A0, X) LMU_PP_FOREACH_1ARG_3(ACTION, A0, __VA_ARGS__)
#define LMU_PP_FOREACH_1ARG_5(ACTION, A0, X, ...)                              \
    ACTION(A0, X) LMU_PP_FOREACH_1ARG_4(ACTION, A0, __VA_ARGS__)
#define LMU_PP_FOREACH_1ARG_6(ACTION, A0, X, ...)                              \
    ACTION(A0, X) LMU_PP_FOREACH_1ARG_5(ACTION, A0, __VA_ARGS__)
#define LMU_PP_FOREACH_1ARG_7(ACTION, A0, X, ...)                              \
    ACTION(A0, X) LMU_PP_FOREACH_1ARG_6(ACTION, A0, __VA_ARGS__)
#define LMU_PP_FOREACH_1ARG_8(ACTION, A0, X, ...)                              \
    ACTION(A0, X) LMU_PP_FOREACH_1ARG_7(ACTION, A0, __VA_ARGS__)
#define LMU_PP_FOREACH_1ARG_9(ACTION, A0, X, ...)                              \
    ACTION(A0, X) LMU_PP_FOREACH_1ARG_8(ACTION, A0, __VA_ARGS__)
#define LMU_PP_FOREACH_1ARG_10(ACTION, A0, X, ...)                              \
    ACTION(A0, X) LMU_PP_FOREACH_1ARG_9(ACTION, A0, __VA_ARGS__)
#define LMU_PP_FOREACH_1ARG_11(ACTION, A0, X, ...)                              \
    ACTION(A0, X) LMU_PP_FOREACH_1ARG_10(ACTION, A0, __VA_ARGS__)
#define LMU_PP_FOREACH_1ARG_12(ACTION, A0, X, ...)                              \
    ACTION(A0, X) LMU_PP_FOREACH_1ARG_11(ACTION, A0, __VA_ARGS__)
#define LMU_PP_FOREACH_1ARG_13(ACTION, A0, X, ...)                              \
    ACTION(A0, X) LMU_PP_FOREACH_1ARG_12(ACTION, A0, __VA_ARGS__)
#define LMU_PP_FOREACH_1ARG_14(ACTION, A0, X, ...)                              \
    ACTION(A0, X) LMU_PP_FOREACH_1ARG_13(ACTION, A0, __VA_ARGS__)
#define LMU_PP_FOREACH_1ARG_15(ACTION, A0, X, ...)                              \
    ACTION(A0, X) LMU_PP_FOREACH_1ARG_14(ACTION, A0, __VA_ARGS__)
#define LMU_PP_FOREACH_1ARG(ACTION, A0, ...)                                   \
    LMU_PP_VA_ARGS_OVERLOAD(LMU_PP_FOREACH_1ARG_, ##__VA_ARGS__)               \
    (ACTION, A0, ##__VA_ARGS__)

#endif

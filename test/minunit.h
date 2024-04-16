/*
 * MinUnit simple unit test framework
 * Based of John Brewer implementation https://jera.com/techinfo/jtns/jtn002
 */

#ifndef MINUNIT_MINUNIT_H
#define MINUNIT_MINUNIT_H

#include <stdio.h>
#include <string.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Color printing escapecharecters */
#define COLOR_RED "\x1b[31m"
#define COLOR_GREEN "\x1b[32m"
#define COLOR_RESET "\x1b[0m"

#define MU_MESSAGE_LENGTH 256
static char error_message[MU_MESSAGE_LENGTH];

static int tests_run = 0;
static int tests_failed = 0;

/* Run test and print result, inc failed test on failure */
#define MU_RUN_TEST(test)                                                      \
  do {                                                                         \
    char *message = test();                                                    \
    tests_run++;                                                               \
    if (message) {                                                             \
      printf(COLOR_RED "FAILED " #test "\n\t%s\n" COLOR_RESET, message);       \
      tests_failed++;                                                          \
    } else {                                                                   \
      printf(COLOR_GREEN "PASSED " COLOR_RESET #test "\n");                    \
    }                                                                          \
  } while (0)

/* Define test to run by MU_RUN_TEST */
#define MU_TEST(name) static char *name(void)

/* Stop test and return message if test fail */
#define MU_ASSERT(test, message)                                               \
  do {                                                                         \
    if (!(test)) {                                                             \
      (void)snprintf(error_message, MU_MESSAGE_LENGTH, "%s:%d: %s\n",          \
                     __FILE__, __LINE__, message);                             \
      return error_message;                                                    \
    }                                                                          \
  } while (0)

/* Stops test and return message if not equal */
#define MU_ASSERT_EQ(expected, result)                                         \
  do {                                                                         \
    if (expected != result) {                                                  \
      (void)snprintf(error_message, MU_MESSAGE_LENGTH,                         \
                     "%s:%d: expected %d but was %d\n", __FILE__, __LINE__,    \
                     expected, result);                                        \
      return error_message;                                                    \
    }                                                                          \
  } while (0)

/* Stops test and return message if strings not match */
#define MU_ASSERT_MATCH(expected, result)                                      \
  do {                                                                         \
    if (strcmp(expected, result) != 0) {                                       \
      (void)snprintf(error_message, MU_MESSAGE_LENGTH,                         \
                     "%s:%d\nExpected:\n%s\nBut was:\n%s\n", __FILE__,         \
                     __LINE__, expected, result);                              \
      return error_message;                                                    \
    }                                                                          \
  } while (0)

/* Report macro, print stats */
#define MU_REPORT()                                                            \
  do {                                                                         \
    printf("+-------------------------------------+\n");                       \
    printf("| Tests run:    %3d                   |\n", tests_run);            \
    printf("| Tests failed: %3d                   |\n", tests_failed);         \
    printf("| Result: ");                                                      \
    if (0 == tests_failed) {                                                   \
      printf(COLOR_GREEN "%14s" COLOR_RESET, "PASSED");                        \
    } else {                                                                   \
      printf(COLOR_RED "%14s" COLOR_RESET, "FAILED");                          \
    }                                                                          \
    printf("%14s|\n", "");                                                     \
    printf("+-------------------------------------+\n");                       \
  } while (0)

#define MU_RESULT tests_failed

#ifdef __cplusplus
}
#endif

#endif /* MINUNIT_MINUNIT_H */

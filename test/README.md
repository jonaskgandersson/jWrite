# Simple testing for jWrite
jWrite is meant to be simple in both implementation and usage. Testing should/must
not be more complex than the project it serves. MinUnit is used to create an
self contained testing framework for jWrite.

## Usage
Define test by using MU_TEST(test_name)

- MU_ASSERT(test, message) If condition in test fails message is returned
- MU_ASSERT_EQ(expected, result) If expected != result both are returned
- MU_ASSERT_MATCH(expected, result) String comparison if exp != res both are returned

Run test by using MU_RUN_TEST(test_name)

Use assertion macro for test.
This will set failed count and print result of test, assertions will end current.
test but not all tests.


MU_REPORT(); Will print stats to stdout.

MU_RESULT will hold number of failed tests, if > 0 exit code is 1.

Example
``` C
/* Include whats needed */
#include "../jWrite.h"
#include "minunit.h"

/* TEST jwOpen object in compact format */
MU_TEST(test_obj_open_compact) {
  /* Setup buffer for test */
  unsigned int length = 128;
  char json[length];

  jwOpen(json, length, JW_OBJECT, JW_COMPACT);

  /* Assert if created json not match */
  MU_ASSERT_MATCH("{", json);
  /* If all pass return no error message */
  return 0;
}

/* Collect all test to run in one function */
static void all_tests() { 
  MU_RUN_TEST(test_obj_open_compact);
}

int main() {
  /* Run all test */
  all_tests();
  /* Print report to console */
  MU_REPORT();
  /* Return true if any failures */
  return MU_RESULT != 0;
}
```

## Makefile
There is an simple Makefile to run tests with gcc, you can of course use your
own toolchain to run the test on a specific platform.
```sh
make test
PASSED test_obj_open_compact
+-------------------------------------+
| Tests run:      1                   |
| Tests failed:   0                   |
| Result:         PASSED              |
+-------------------------------------+
echo $?
0
```
To create test coverage files with gcc and gcov run make test_cov
``` sh
make test_cov
File '.../jWrite.c'
Lines executed:93.95% of 248
Creating 'jWrite.c.gcov'
```
This will output .c.gcov, .gcda, .gcno files in the test directory.
Tools like gcovr can be used to visualize and analyze coverage.


## MinUnit
MinUnit is based on John Brewer implementation, https://jera.com/techinfo/jtns/jtn002.

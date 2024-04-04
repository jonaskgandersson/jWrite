/*
 * Tests for jWrite, uses MinUnit
 *
 */

#include "../jWrite.h"
#include "minunit.h"

#include <string.h>

/* TEST jwOpen */
MU_TEST(test_obj_open_compact) {
  unsigned int length = 128;
  char json[length];

  jwOpen(json, length, JW_OBJECT, JW_COMPACT);

  MU_ASSERT_MATCH("{", json);
  return 0;
}

MU_TEST(test_obj_open_pretty) {
  unsigned int length = 128;
  char json[length];

  jwOpen(json, length, JW_OBJECT, JW_PRETTY);

  MU_ASSERT_MATCH("{", json);
  return 0;
}

MU_TEST(test_array_open_compact) {
  unsigned int length = 128;
  char json[length];

  jwOpen(json, length, JW_ARRAY, JW_COMPACT);

  MU_ASSERT_MATCH("[", json);
  return 0;
}

MU_TEST(test_array_open_pretty) {
  unsigned int length = 128;
  char json[length];

  jwOpen(json, length, JW_ARRAY, JW_PRETTY);

  MU_ASSERT_MATCH("[", json);
  return 0;
}

MU_TEST(test_obj_open_length) {
  char json[64];

  jwOpen(json, 32, JW_OBJECT, JW_COMPACT);
  MU_ASSERT_EQ(1, (int)strlen(json));

  jwObj_string("key1", "string");
  MU_ASSERT_EQ(16, (int)strlen(json));

  jwObj_string("key2", "to long string");
  MU_ASSERT_EQ(31, (int)strlen(json));
  int err = jwClose();
  MU_ASSERT_EQ(31, (int)strlen(json));
  MU_ASSERT_EQ(JWRITE_BUF_FULL, err);
  return 0;
}

/* TEST jwObj_string */
MU_TEST(test_obj_string_compact) {
  unsigned int length = 128;
  char json[length];

  jwOpen(json, length, JW_OBJECT, JW_COMPACT);
  jwObj_string("key", "string");
  int err = jwClose();

  MU_ASSERT_MATCH("{\"key\":\"string\"}", json);
  MU_ASSERT_EQ(JWRITE_OK, err);
  return 0;
}

MU_TEST(test_obj_string_pretty) {
  unsigned int length = 128;
  char json[length];

  jwOpen(json, length, JW_OBJECT, JW_PRETTY);
  jwObj_string("key", "string");
  int err = jwClose();

  MU_ASSERT_MATCH("{\n    \"key\": \"string\"\n}", json);
  MU_ASSERT_EQ(JWRITE_OK, err);
  return 0;
}

/* TEST jwClose */
MU_TEST(test_close_ok) {
  unsigned int length = 128;
  char json[length];

  jwOpen(json, length, JW_OBJECT, JW_PRETTY);
  jwObj_string("key", "string");
  int err = jwClose();

  MU_ASSERT_MATCH("{\n    \"key\": \"string\"\n}", json);
  MU_ASSERT_EQ(JWRITE_OK, err);
  return 0;
}

MU_TEST(test_close_array_not_closed) {
  unsigned int length = 128;
  char json[length];

  jwOpen(json, length, JW_OBJECT, JW_COMPACT);
  jwObj_array("array");
  int err = jwClose();

  MU_ASSERT_MATCH("{\"array\":[", json);
  MU_ASSERT_EQ(JWRITE_NEST_ERROR, err);
  return 0;
}

/* TEST Stack full */
MU_TEST(test_close_stack_full) {
  unsigned int length = 128;
  char json[length];

  jwOpen(json, length, JW_ARRAY, JW_COMPACT);
  int i = 0;
  /* Add nested arrays to max depth */
  for (i = 0; i < JWRITE_STACK_DEPTH; i++) {
    jwArr_array();
  }
  int err = jwClose();
  MU_ASSERT_EQ(JWRITE_STACK_FULL, err);
  return 0;
}

/* Run all tests */
static void all_tests() {
  MU_RUN_TEST(test_obj_open_compact);
  MU_RUN_TEST(test_obj_open_pretty);
  MU_RUN_TEST(test_array_open_compact);
  MU_RUN_TEST(test_array_open_pretty);
  MU_RUN_TEST(test_obj_open_length);
  MU_RUN_TEST(test_obj_string_compact);
  MU_RUN_TEST(test_obj_string_pretty);
  MU_RUN_TEST(test_close_ok);
  MU_RUN_TEST(test_close_array_not_closed);
  MU_RUN_TEST(test_close_stack_full);
}

int main() {
  all_tests();
  MU_REPORT();
  return MU_RESULT != 0;
}

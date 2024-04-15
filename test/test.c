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
  /* Missing jwEnd() here */
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

MU_TEST(test_end_object) {
  unsigned int length = 128;
  char json[length];

  jwOpen(json, length, JW_OBJECT, JW_COMPACT);
  jwObj_object("obj1");
  jwObj_int("int1", 1);
  jwEnd();
  int err = jwClose();
  MU_ASSERT_EQ(JWRITE_OK, err);
  MU_ASSERT_MATCH("{\"obj1\":{\"int1\":1}}", json);
  return 0;
}

MU_TEST(test_end_array) {
  unsigned int length = 128;
  char json[length];

  jwOpen(json, length, JW_OBJECT, JW_COMPACT);
  jwObj_array("array1");
  jwArr_int(1);
  jwEnd();
  int err = jwClose();
  MU_ASSERT_EQ(JWRITE_OK, err);
  MU_ASSERT_MATCH("{\"array1\":[1]}", json);
  return 0;
}

MU_TEST(test_end_missing) {
  unsigned int length = 128;
  char json[length];

  jwOpen(json, length, JW_OBJECT, JW_COMPACT);
  jwObj_array("array1");
  jwArr_int(1);
  /* Missing jwEnd(); here to close array */
  int err = jwClose();
  MU_ASSERT_EQ(JWRITE_NEST_ERROR, err);
  MU_ASSERT_MATCH("{\"array1\":[1", json);
  return 0;
}

MU_TEST(test_end_to_many) {
  unsigned int length = 128;
  char json[length];

  jwOpen(json, length, JW_OBJECT, JW_COMPACT);
  jwObj_array("array1");
  jwArr_int(1);
  jwEnd();
  jwEnd(); /* This end is one to much */
  int err = jwClose();
  MU_ASSERT_EQ(JWRITE_STACK_EMPTY, err);
  MU_ASSERT_MATCH("{\"array1\":[1]}", json);
  return 0;
}

MU_TEST(test_obj_int_basic) {
  unsigned int length = 128;
  char json[length];

  jwOpen(json, length, JW_OBJECT, JW_COMPACT);
  jwObj_int("int1", 1);
  int err = jwClose();

  MU_ASSERT_MATCH("{\"int1\":1}", json);
  MU_ASSERT_EQ(JWRITE_OK, err);
  return 0;
}

MU_TEST(test_obj_double_basic) {
  unsigned int length = 128;
  char json[length];

  jwOpen(json, length, JW_OBJECT, JW_COMPACT);
  jwObj_double("double1", 1);
  int err = jwClose();

  MU_ASSERT_MATCH("{\"double1\":1}", json);
  MU_ASSERT_EQ(JWRITE_OK, err);
  return 0;
}

MU_TEST(test_obj_bool) {
  unsigned int length = 128;
  char json[length];

  jwOpen(json, length, JW_OBJECT, JW_COMPACT);
  jwObj_bool("bool_true", 1);
  jwObj_bool("bool_false", 0);
  int err = jwClose();

  MU_ASSERT_MATCH("{\"bool_true\":true,\"bool_false\":false}", json);
  MU_ASSERT_EQ(JWRITE_OK, err);
  return 0;
}

MU_TEST(test_obj_null) {
  unsigned int length = 128;
  char json[length];

  jwOpen(json, length, JW_OBJECT, JW_COMPACT);
  jwObj_null("null");
  int err = jwClose();

  MU_ASSERT_MATCH("{\"null\":null}", json);
  MU_ASSERT_EQ(JWRITE_OK, err);
  return 0;
}

MU_TEST(test_obj_object) {
  unsigned int length = 128;
  char json[length];

  jwOpen(json, length, JW_OBJECT, JW_COMPACT);
  jwObj_object("object");
  jwEnd();
  int err = jwClose();

  MU_ASSERT_MATCH("{\"object\":{}}", json);
  MU_ASSERT_EQ(JWRITE_OK, err);
  return 0;
}

MU_TEST(test_obj_array) {
  unsigned int length = 128;
  char json[length];

  jwOpen(json, length, JW_OBJECT, JW_COMPACT);
  jwObj_array("array");
  jwEnd();
  int err = jwClose();

  MU_ASSERT_MATCH("{\"array\":[]}", json);
  MU_ASSERT_EQ(JWRITE_OK, err);
  return 0;
}

MU_TEST(test_obj_raw) {
  unsigned int length = 128;
  char json[length];

  jwOpen(json, length, JW_OBJECT, JW_COMPACT);
  jwObj_raw("raw", "abc");
  int err = jwClose();

  MU_ASSERT_MATCH("{\"raw\":abc}", json);
  MU_ASSERT_EQ(JWRITE_OK, err);
  return 0;
}

/* ARRAY TESTS */

MU_TEST(test_arr_raw) {
  unsigned int length = 128;
  char json[length];

  jwOpen(json, length, JW_ARRAY, JW_COMPACT);
  jwArr_raw("abc");
  int err = jwClose();

  MU_ASSERT_MATCH("[abc]", json);
  MU_ASSERT_EQ(JWRITE_OK, err);
  return 0;
}

MU_TEST(test_arr_string) {
  unsigned int length = 128;
  char json[length];

  jwOpen(json, length, JW_ARRAY, JW_COMPACT);
  jwArr_string("abc");
  int err = jwClose();

  MU_ASSERT_MATCH("[\"abc\"]", json);
  MU_ASSERT_EQ(JWRITE_OK, err);
  return 0;
}

MU_TEST(test_arr_int_basic) {
  unsigned int length = 128;
  char json[length];

  jwOpen(json, length, JW_ARRAY, JW_COMPACT);
  jwArr_int(42);
  int err = jwClose();

  MU_ASSERT_MATCH("[42]", json);
  MU_ASSERT_EQ(JWRITE_OK, err);
  return 0;
}

MU_TEST(test_arr_double_basic) {
  unsigned int length = 128;
  char json[length];

  jwOpen(json, length, JW_ARRAY, JW_COMPACT);
  jwArr_double(3.14);
  int err = jwClose();

  MU_ASSERT_MATCH("[3.14]", json);
  MU_ASSERT_EQ(JWRITE_OK, err);
  return 0;
}

MU_TEST(test_arr_bool) {
  unsigned int length = 128;
  char json[length];

  jwOpen(json, length, JW_ARRAY, JW_COMPACT);
  jwArr_bool(1);
  jwArr_bool(0);
  int err = jwClose();

  MU_ASSERT_MATCH("[true,false]", json);
  MU_ASSERT_EQ(JWRITE_OK, err);
  return 0;
}

MU_TEST(test_arr_null) {
  unsigned int length = 128;
  char json[length];

  jwOpen(json, length, JW_ARRAY, JW_COMPACT);
  jwArr_null();
  int err = jwClose();

  MU_ASSERT_MATCH("[null]", json);
  MU_ASSERT_EQ(JWRITE_OK, err);
  return 0;
}

MU_TEST(test_arr_object) {
  unsigned int length = 128;
  char json[length];

  jwOpen(json, length, JW_ARRAY, JW_COMPACT);
  jwArr_object();
  jwEnd();
  jwArr_object();
  jwEnd();
  int err = jwClose();

  MU_ASSERT_MATCH("[{},{}]", json);
  MU_ASSERT_EQ(JWRITE_OK, err);
  return 0;
}

MU_TEST(test_arr_array) {
  unsigned int length = 128;
  char json[length];

  jwOpen(json, length, JW_ARRAY, JW_COMPACT);
  jwArr_array();
  jwEnd();
  jwArr_array();
  jwEnd();
  int err = jwClose();

  MU_ASSERT_MATCH("[[],[]]", json);
  MU_ASSERT_EQ(JWRITE_OK, err);
  return 0;
}

/* ERROR TEST */
MU_TEST(test_arr_key_value_insert) {
  unsigned int length = 128;
  char json[length];

  jwOpen(json, length, JW_ARRAY, JW_COMPACT);
  jwArr_array();
  jwObj_int("Int", 42); /* Error insert key value to array */
  jwEnd();
  int err = jwClose();

  MU_ASSERT_EQ(JWRITE_NOT_OBJECT, err);

  int err_pos = jwErrorPos();
  MU_ASSERT_EQ(3, err_pos);

  return 0;
}

MU_TEST(test_obj_array_insert) {
  unsigned int length = 128;
  char json[length];

  jwOpen(json, length, JW_OBJECT, JW_COMPACT);
  jwArr_int(42); /* Error insert array value to object, missing key */
  jwEnd();
  int err = jwClose();

  MU_ASSERT_EQ(JWRITE_NOT_ARRAY, err);

  int err_pos = jwErrorPos();
  MU_ASSERT_EQ(2, err_pos);

  return 0;
}

MU_TEST(test_obj_write_not_ok) {
  unsigned int length = 128;
  char json[length];

  jwOpen(json, length, JW_OBJECT, JW_COMPACT);
  jwEnd();
  /* This calls will return direct as json already closed */
  jwObj_raw("raw", "Not written");
  jwObj_string("string", "Not written");
  jwObj_int("int", 42);
  jwObj_double("double", 3.14);
  jwObj_bool("bool", 1);
  jwObj_null("null");
  jwObj_object("object");
  jwObj_array("array");
  int err = jwClose();

  MU_ASSERT_EQ(JWRITE_STACK_EMPTY, err);

  int err_pos = jwErrorPos();
  MU_ASSERT_EQ(1, err_pos);

  return 0;
}

MU_TEST(test_arr_write_not_ok) {
  unsigned int length = 128;
  char json[length];

  jwOpen(json, length, JW_ARRAY, JW_COMPACT);
  jwEnd();
  /* This calls will return direct as json already closed */
  jwArr_raw("Not written");
  jwArr_string("Not written");
  jwArr_int(42);
  jwArr_double(3.14);
  jwArr_bool(1);
  jwArr_null();
  jwArr_object();
  jwArr_array();
  int err = jwClose();

  MU_ASSERT_EQ(JWRITE_STACK_EMPTY, err);

  int err_pos = jwErrorPos();
  MU_ASSERT_EQ(1, err_pos);

  return 0;
}

MU_TEST(test_error_to_string) {

  MU_ASSERT_MATCH("OK", jwErrorToString(JWRITE_OK));

  MU_ASSERT_MATCH("output buffer full", jwErrorToString(JWRITE_BUF_FULL));

  MU_ASSERT_MATCH("tried to write Array value into Object",
                  jwErrorToString(JWRITE_NOT_ARRAY));

  MU_ASSERT_MATCH("tried to write Object key/value into Array",
                  jwErrorToString(JWRITE_NOT_OBJECT));

  MU_ASSERT_MATCH("array/object nesting > JWRITE_STACK_DEPTH",
                  jwErrorToString(JWRITE_STACK_FULL));

  MU_ASSERT_MATCH("stack underflow error (too many 'end's)",
                  jwErrorToString(JWRITE_STACK_EMPTY));

  MU_ASSERT_MATCH("nesting error, not all objects closed when jwClose() called",
                  jwErrorToString(JWRITE_NEST_ERROR));

  MU_ASSERT_MATCH("Unknown error", jwErrorToString(999));

  return 0;
}

/* Edge test */
MU_TEST(test_nan) {
  unsigned int length = 128;
  char json[length];

  jwOpen(json, length, JW_OBJECT, JW_COMPACT);

  double nan = 0.0 / 0.0; /* Create nan from devision by 0 */
  jwObj_double("Nan", nan);
  int err = jwClose();

  MU_ASSERT_EQ(JWRITE_OK, err);
  MU_ASSERT_MATCH("{\"Nan\":nan}", json);

  return 0;
}

MU_TEST(test_double_max_decimals) {
  unsigned int length = 128;
  char json[length];

  jwOpen(json, length, JW_OBJECT, JW_COMPACT);

  jwObj_double("decimal", 0.123456789);
  jwObj_double("decimal_neg", -0.123456789);
  int err = jwClose();

  MU_ASSERT_EQ(JWRITE_OK, err);

  /* jWrite only convert 6 decimal places, will round up */
  MU_ASSERT_MATCH("{\"decimal\":0.123457,\"decimal_neg\":-0.123457}", json);
  return 0;
}

MU_TEST(test_double_max_normal) {
  unsigned int length = 128;
  char json[length];

  jwOpen(json, length, JW_OBJECT, JW_COMPACT);

  /* jWrite  converts to scientific notation above this value */
  jwObj_double("max_normal", 0x7FFFFFFF);
  jwObj_double("max_normal_neg", -0x7FFFFFFF);
  int err = jwClose();

  MU_ASSERT_EQ(JWRITE_OK, err);

  MU_ASSERT_MATCH("{\"max_normal\":2147483647,\"max_normal_neg\":-2147483647}",
                  json);
  return 0;
}

MU_TEST(test_double_first_scientific) {
  unsigned int length = 128;
  char json[length];

  jwOpen(json, length, JW_OBJECT, JW_COMPACT);

  /* jWrite  converts to scientific */
  jwObj_double("first_scientific", 2147483648);
  jwObj_double("first_scientific_neg", -2147483648);
  int err = jwClose();

  MU_ASSERT_EQ(JWRITE_OK, err);
  /* jWrite will round to 6 decimal places */
  MU_ASSERT_MATCH("{\"first_scientific\":2.147484e+09,\"first_scientific_"
                  "neg\":-2.147484e+09}",
                  json);
  return 0;
}

MU_TEST(test_int_max) {
  unsigned int length = 128;
  char json[length];

  jwOpen(json, length, JW_OBJECT, JW_COMPACT);
  jwObj_int("int_max", 2147483647);
  jwObj_int("int_max_neg", -2147483648);
  int err = jwClose();

  MU_ASSERT_EQ(JWRITE_OK, err);
  MU_ASSERT_MATCH("{\"int_max\":2147483647,\"int_max_neg\":-2147483648}", json);

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

  MU_RUN_TEST(test_end_object);
  MU_RUN_TEST(test_end_array);
  MU_RUN_TEST(test_end_missing);
  MU_RUN_TEST(test_end_to_many);

  MU_RUN_TEST(test_obj_int_basic);
  MU_RUN_TEST(test_obj_double_basic);
  MU_RUN_TEST(test_obj_bool);
  MU_RUN_TEST(test_obj_null);
  MU_RUN_TEST(test_obj_object);
  MU_RUN_TEST(test_obj_array);
  MU_RUN_TEST(test_obj_raw);

  /* ARRAY TESTS */
  MU_RUN_TEST(test_arr_raw);
  MU_RUN_TEST(test_arr_string);
  MU_RUN_TEST(test_arr_int_basic);
  MU_RUN_TEST(test_arr_double_basic);
  MU_RUN_TEST(test_arr_bool);
  MU_RUN_TEST(test_arr_null);
  MU_RUN_TEST(test_arr_object);
  MU_RUN_TEST(test_arr_array);

  /* ERROR Test */
  MU_RUN_TEST(test_arr_key_value_insert);
  MU_RUN_TEST(test_obj_array_insert);
  MU_RUN_TEST(test_obj_write_not_ok);
  MU_RUN_TEST(test_arr_write_not_ok);
  MU_RUN_TEST(test_error_to_string);

  /* Edge test */
  MU_RUN_TEST(test_nan);
  MU_RUN_TEST(test_double_max_decimals);
  MU_RUN_TEST(test_double_max_normal);
  MU_RUN_TEST(test_double_first_scientific);
  MU_RUN_TEST(test_int_max);
}

int main() {
  all_tests();
  MU_REPORT();
  return MU_RESULT != 0;
}

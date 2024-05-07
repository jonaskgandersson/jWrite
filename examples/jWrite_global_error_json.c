#include <stdio.h>

#include "../jWrite.h"

/* Use same buffer for all examples */
char json[1024];
unsigned int maxJsonLen = 1024;
int err;

/* Basic root object
 * {
 *     "key": "value",
 *     "int": 1,
 *
 * Error: tried to write Array value into Object at function call 4
 */
void basic_root_object() {

  printf("JSON root object:\n\n");

  /* Clear json buffer, create root as object and set format to pretty */
  jwOpen(json, maxJsonLen, JW_OBJECT, JW_PRETTY);

  /* Add key:value pairs of different types to object */
  jw_key("key");
  jw_string("value");
  jw_key("int");
  jw_int(1);
  jw_double(1.234); /* Wrong function, value to object, no key */
  jw_key("nullThing");
  jw_null();
  jw_key("bool");
  jw_bool(1);

  err = jwClose(); /* close and get error code */

  printf("%s\n\n", json);
  if (err != JWRITE_OK)
    printf("Error: %s at function call %d\n", jwErrorToString(err),
           jwErrorPos());
  return;
}

/* Basic root array
 * [
 *     "value",
 *     1,
 *     "double":
 *
 * Error: tried to write Object key/value into Array at function call 4
 */
void basic_root_array() {

  printf("JSON root array:\n\n");

  /* Clear json buffer, create root as array and set format to pretty */
  jwOpen(json, maxJsonLen, JW_ARRAY, JW_PRETTY);

  /* Add value of different types to array */
  jw_string("value");
  jw_int(1);
  jw_key("double"); /* Wrong function, key to array */
  jw_double(1.234);
  jw_null();
  jw_bool(1);

  err = jwClose(); /* close and get error code */

  printf("%s\n\n", json);
  if (err != JWRITE_OK)
    printf("Error: %s at function call %d\n", jwErrorToString(err),
           jwErrorPos());
  return;
}

/* Array in object
 * {
 *     "array_empty": [, // Missing closing ]
 *       "array_basic":
 *
 * Error: tried to write Object key/value into Array at function call 3
 */
void array_in_object() {

  printf("JSON arrays in object:\n\n");

  /* Clear json buffer, create root as object and set format to pretty */
  jwOpen(json, maxJsonLen, JW_OBJECT, JW_PRETTY);

  /* Add empty to object */
  jw_key("array_empty");
  jw_array(); /* Create and open array */
  /*  jwEnd();                    Missing close array */

  /* Create array and insert basic types */
  jw_key("array_basic");
  jw_array();
  jw_string("value");
  jw_int(1);
  jw_double(1.234);
  jw_null();
  jw_bool(1);
  jwEnd();

  err = jwClose(); /* close and get error code */

  printf("%s\n\n", json);
  if (err != JWRITE_OK)
    printf("Error: %s at function call %d\n", jwErrorToString(err),
           jwErrorPos());
  return;
}

/* Object in object
 * {
 *     "object_empty": {
 *       "object_basic": {
 *           "key": "value",
 *           "int": 1,
 *           "double": 1.234,
 *           "nullThing": null,
 *           "bool": true
 *       }
 *
 * Error: nesting error, not all objects closed when jwClose() called at
 * function call 8
 */
void object_in_object() {

  printf("JSON object in object:\n\n");

  /* Clear json buffer, create root as object and set format to pretty */
  jwOpen(json, maxJsonLen, JW_OBJECT, JW_PRETTY);

  /* Add empty to object */
  jw_key("object_empty");
  jw_object(); /* Create and open object */
  /* jwEnd();                      Missing end close object */

  /* Create object and insert basic types */
  jw_key("object_basic");
  jw_object();
  jw_key("key");
  jw_string("value");
  jw_key("int");
  jw_int(1);
  jw_key("double");
  jw_double(1.234);
  jw_key("nullThing");
  jw_null();
  jw_key("bool");
  jw_bool(1);
  jwEnd();

  err = jwClose(); /* close and get error code */

  printf("%s\n\n", json);
  if (err != JWRITE_OK)
    printf("Error: %s at function call %d\n", jwErrorToString(err),
           jwErrorPos());
  return;
}

/* Run examples */
int main() {
  basic_root_object();

  basic_root_array();

  array_in_object();
  object_in_object();

  return 0;
}

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
 *     "double": 1.234,
 *     "nullThing": null,
 *     "bool": true
 * }
 */
void basic_root_object() {

  printf("JSON root object:\n\n");

  /* Clear json buffer, create root as object and set format to pretty */
  jwOpen(json, maxJsonLen, JW_OBJECT, JW_PRETTY);

  /* Add key:value pairs of different types to object */
  jwObj_string("key", "value");
  jwObj_int("int", 1);
  jwObj_double("double", 1.234);
  jwObj_null("nullThing");
  jwObj_bool("bool", 1);

  err = jwClose(); /* close and get error code */

  printf("%s\n\n", json);
  if (err != JWRITE_OK)
    printf("Error: %s at function call %d\n", jwErrorToString(err),
           jwErrorPos());
  return;
}

/* Basic root object in compact format, no space and newlines
 *
 * {"key":"value","int":1,"double":1.234,"nullThing":null,"bool":true}
 */
void basic_root_object_compact() {

  printf("JSON root object:\n\n");

  /* Clear json buffer, create root as object and set format to compact */
  jwOpen(json, maxJsonLen, JW_OBJECT, JW_COMPACT);

  /* Add key:value pairs of different types to object */
  jwObj_string("key", "value");
  jwObj_int("int", 1);
  jwObj_double("double", 1.234);
  jwObj_null("nullThing");
  jwObj_bool("bool", 1);

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
 *     1.234,
 *     null,
 *     true
 * ]
 */
void basic_root_array() {

  printf("JSON root array:\n\n");

  /* Clear json buffer, create root as array and set format to pretty */
  jwOpen(json, maxJsonLen, JW_ARRAY, JW_PRETTY);

  /* Add value of different types to array */
  jwArr_string("value");
  jwArr_int(1);
  jwArr_double(1.234);
  jwArr_null();
  jwArr_bool(1);

  err = jwClose(); /* close and get error code */

  printf("%s\n\n", json);
  if (err != JWRITE_OK)
    printf("Error: %s at function call %d\n", jwErrorToString(err),
           jwErrorPos());
  return;
}

/* Array in object
 * {
 *     "array_empty": [],
 *     "array_basic": [
 *         "value",
 *         1,
 *         1.234,
 *         null,
 *         true
 *     ]
 * }
 */
void array_in_object() {

  printf("JSON arrays in object:\n\n");

  /* Clear json buffer, create root as object and set format to pretty */
  jwOpen(json, maxJsonLen, JW_OBJECT, JW_PRETTY);

  /* Add empty to object */
  jwObj_array("array_empty"); /* Create and open array */
  jwEnd();                    /* Close array */

  /* Create array and insert basic types */
  jwObj_array("array_basic");
  jwArr_string("value");
  jwArr_int(1);
  jwArr_double(1.234);
  jwArr_null();
  jwArr_bool(1);
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
 *     "object_empty": {},
 *     "object_basic": {
 *         "key": "value",
 *         "int": 1,
 *         "double": 1.234,
 *         "nullThing": null,
 *         "bool": true
 *     }
 * }
 */
void object_in_object() {

  printf("JSON object in object:\n\n");

  /* Clear json buffer, create root as object and set format to pretty */
  jwOpen(json, maxJsonLen, JW_OBJECT, JW_PRETTY);

  /* Add empty to object */
  jwObj_object("object_empty"); /* Create and open object */
  jwEnd();                      /* Close object */

  /* Create object and insert basic types */
  jwObj_object("object_basic");
  jwObj_string("key", "value");
  jwObj_int("int", 1);
  jwObj_double("double", 1.234);
  jwObj_null("nullThing");
  jwObj_bool("bool", 1);
  jwEnd();

  err = jwClose(); /* close and get error code */

  printf("%s\n\n", json);
  if (err != JWRITE_OK)
    printf("Error: %s at function call %d\n", jwErrorToString(err),
           jwErrorPos());
  return;
}

/* Objects in array
 * {
 *     "array_of_objects": [
 *         {
 *             "key": "value",
 *             "int": 1,
 *             "double": 1.234,
 *             "nullThing": null,
 *             "bool": true
 *         },
 *         {
 *             "key": "value",
 *             "int": 1,
 *             "double": 1.234,
 *             "nullThing": null,
 *             "bool": true
 *         },
 *         {
 *             "key": "value",
 *             "int": 1,
 *             "double": 1.234,
 *             "nullThing": null,
 *             "bool": true
 *         }
 *     ]
 * }
 */
void object_in_array() {

  printf("JSON object in array:\n\n");

  /* Clear json buffer, create root as object and set format to pretty */
  jwOpen(json, maxJsonLen, JW_OBJECT, JW_PRETTY);

  /* Add array to hold objects */
  jwObj_array("array_of_objects"); /* Create and open array */

  /* Add object 0 to array */
  jwArr_object(); /* Create object in array */
  jwObj_string("key", "value");
  jwObj_int("int", 1);
  jwObj_double("double", 1.234);
  jwObj_null("nullThing");
  jwObj_bool("bool", 1);
  jwEnd(); /* Close object in array */

  /* Add object 1 to array */
  jwArr_object(); /* Create object in array */
  jwObj_string("key", "value");
  jwObj_int("int", 1);
  jwObj_double("double", 1.234);
  jwObj_null("nullThing");
  jwObj_bool("bool", 1);
  jwEnd(); /* Close object in array */

  /* Add object 2 to array */
  jwArr_object(); /* Create object in array */
  jwObj_string("key", "value");
  jwObj_int("int", 1);
  jwObj_double("double", 1.234);
  jwObj_null("nullThing");
  jwObj_bool("bool", 1);
  jwEnd(); /* Close object in array */

  jwEnd(); /* Close array */

  err = jwClose(); /* Close json and get error code */
  printf("%s\n\n", json);
  if (err != JWRITE_OK)
    printf("Error: %s at function call %d\n", jwErrorToString(err),
           jwErrorPos());
  return;
}

/* Array in array
 * {
 *     "array_of_arrays": [
 *         [
 *             "value",
 *             1,
 *             1.234,
 *             null,
 *             true
 *         ],
 *         [
 *             "value",
 *             1,
 *             1.234,
 *             null,
 *             true
 *         ],
 *         [
 *             "value",
 *             1,
 *             1.234,
 *             null,
 *             true
 *         ]
 *     ]
 * }
 */
void array_in_array() {

  printf("JSON arrays in array:\n\n");

  /* Clear json buffer, create root as object and set format to pretty */
  jwOpen(json, maxJsonLen, JW_OBJECT, JW_PRETTY);

  /* Add empty to object */
  jwObj_array("array_of_arrays"); /* Create and open array */

  /* Create array 0 and insert basic types */
  jwArr_array();
  jwArr_string("value");
  jwArr_int(1);
  jwArr_double(1.234);
  jwArr_null();
  jwArr_bool(1);
  jwEnd();

  /* Create array 1 and insert basic types */
  jwArr_array();
  jwArr_string("value");
  jwArr_int(1);
  jwArr_double(1.234);
  jwArr_null();
  jwArr_bool(1);
  jwEnd();

  /* Create array 2 and insert basic types */
  jwArr_array();
  jwArr_string("value");
  jwArr_int(1);
  jwArr_double(1.234);
  jwArr_null();
  jwArr_bool(1);
  jwEnd();

  jwEnd();         /* Close array */
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
  basic_root_object_compact();

  basic_root_array();

  array_in_object();
  object_in_object();

  object_in_array();
  array_in_array();

  return 0;
}

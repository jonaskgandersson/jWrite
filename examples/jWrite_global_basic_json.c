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
  jw_key("key");
  jw_string("value");
  jw_key("int");
  jw_int(1);
  jw_key("dobule");
  jw_double(1.234);
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

/* Basic root object in compact format, no space and newlines
 *
 * {"key":"value","int":1,"double":1.234,"nullThing":null,"bool":true}
 */
void basic_root_object_compact() {

  printf("JSON root object:\n\n");

  /* Clear json buffer, create root as object and set format to compact */
  jwOpen(json, maxJsonLen, JW_OBJECT, JW_COMPACT);

  /* Add key:value pairs of different types to object */
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
  jw_string("value");
  jw_int(1);
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
  jw_key("array_empty");
  jw_array(); /* Create and open array */
  jwEnd();    /* Close array */

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
  jw_key("object_empty");
  jw_object(); /* Create and open object */
  jwEnd();     /* Close object */

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
  jw_key("array_of_objects");
  jw_array(); /* Create and open array */

  /* Add object 0 to array */
  jw_object(); /* Create object in array */
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
  jwEnd(); /* Close object in array */

  /* Add object 1 to array */
  jw_object(); /* Create object in array */
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
  jwEnd(); /* Close object in array */

  /* Add object 2 to array */
  jw_object(); /* Create object in array */
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
  jw_key("array_ofarrays");
  jw_array(); /* Create and open array */

  /* Create array 0 and insert basic types */
  jw_array();
  jw_string("value");
  jw_int(1);
  jw_double(1.234);
  jw_null();
  jw_bool(1);
  jwEnd();

  /* Create array 1 and insert basic types */
  jw_array();
  jw_string("value");
  jw_int(1);
  jw_double(1.234);
  jw_null();
  jw_bool(1);
  jwEnd();

  /* Create array 2 and insert basic types */
  jw_array();
  jw_string("value");
  jw_int(1);
  jw_double(1.234);
  jw_null();
  jw_bool(1);
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

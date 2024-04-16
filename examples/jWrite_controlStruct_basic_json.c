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

  /* Create structure to use for json state */
  struct jWriteControl jwc;
  /* Clear json buffer, create root as object and set format to pretty */
  jwOpen(&jwc, json, maxJsonLen, JW_OBJECT, JW_PRETTY);

  /* Add key:value pairs of different types to object */
  jwObj_string(&jwc, "key", "value");
  jwObj_int(&jwc, "int", 1);
  jwObj_double(&jwc, "double", 1.234);
  jwObj_null(&jwc, "nullThing");
  jwObj_bool(&jwc, "bool", 1);

  err = jwClose(&jwc); /* close and get error code */

  printf("%s\n\n", json);
  if (err != JWRITE_OK)
    printf("Error: %s at function call %d\n", jwErrorToString(err),
           jwErrorPos(&jwc));
  return;
}

/* Basic root object in compact format, no space and newlines
 *
 * {"key":"value","int":1,"double":1.234,"nullThing":null,"bool":true}
 */
void basic_root_object_compact() {

  printf("JSON root object:\n\n");

  /* Create structure to use for json state */
  struct jWriteControl jwc;
  /* Clear json buffer, create root as object and set format to compact */
  jwOpen(&jwc, json, maxJsonLen, JW_OBJECT, JW_COMPACT);

  /* Add key:value pairs of different types to object */
  jwObj_string(&jwc, "key", "value");
  jwObj_int(&jwc, "int", 1);
  jwObj_double(&jwc, "double", 1.234);
  jwObj_null(&jwc, "nullThing");
  jwObj_bool(&jwc, "bool", 1);

  err = jwClose(&jwc); /* close and get error code */

  printf("%s\n\n", json);
  if (err != JWRITE_OK)
    printf("Error: %s at function call %d\n", jwErrorToString(err),
           jwErrorPos(&jwc));
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

  /* Create structure to use for json state */
  struct jWriteControl jwc;
  /* Clear json buffer, create root as array and set format to pretty */
  jwOpen(&jwc, json, maxJsonLen, JW_ARRAY, JW_PRETTY);

  /* Add value of different types to array */
  jwArr_string(&jwc, "value");
  jwArr_int(&jwc, 1);
  jwArr_double(&jwc, 1.234);
  jwArr_null(&jwc);
  jwArr_bool(&jwc, 1);

  err = jwClose(&jwc); /* close and get error code */

  printf("%s\n\n", json);
  if (err != JWRITE_OK)
    printf("Error: %s at function call %d\n", jwErrorToString(err),
           jwErrorPos(&jwc));
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

  /* Create structure to use for json state */
  struct jWriteControl jwc;
  /* Clear json buffer, create root as object and set format to pretty */
  jwOpen(&jwc, json, maxJsonLen, JW_OBJECT, JW_PRETTY);

  /* Add empty to object */
  jwObj_array(&jwc, "array_empty"); /* Create and open array */
  jwEnd(&jwc);                      /* Close array */

  /* Create array and insert basic types */
  jwObj_array(&jwc, "array_basic");
  jwArr_string(&jwc, "value");
  jwArr_int(&jwc, 1);
  jwArr_double(&jwc, 1.234);
  jwArr_null(&jwc);
  jwArr_bool(&jwc, 1);
  jwEnd(&jwc);

  err = jwClose(&jwc); /* close and get error code */

  printf("%s\n\n", json);
  if (err != JWRITE_OK)
    printf("Error: %s at function call %d\n", jwErrorToString(err),
           jwErrorPos(&jwc));
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

  /* Create structure to use for json state */
  struct jWriteControl jwc;
  /* Clear json buffer, create root as object and set format to pretty */
  jwOpen(&jwc, json, maxJsonLen, JW_OBJECT, JW_PRETTY);

  /* Add empty to object */
  jwObj_object(&jwc, "object_empty"); /* Create and open object */
  jwEnd(&jwc);                        /* Close object */

  /* Create object and insert basic types */
  jwObj_object(&jwc, "object_basic");
  jwObj_string(&jwc, "key", "value");
  jwObj_int(&jwc, "int", 1);
  jwObj_double(&jwc, "double", 1.234);
  jwObj_null(&jwc, "nullThing");
  jwObj_bool(&jwc, "bool", 1);
  jwEnd(&jwc);

  err = jwClose(&jwc); /* close and get error code */

  printf("%s\n\n", json);
  if (err != JWRITE_OK)
    printf("Error: %s at function call %d\n", jwErrorToString(err),
           jwErrorPos(&jwc));
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

  /* Create structure to use for json state */
  struct jWriteControl jwc;
  /* Clear json buffer, create root as object and set format to pretty */
  jwOpen(&jwc, json, maxJsonLen, JW_OBJECT, JW_PRETTY);

  /* Add array to hold objects */
  jwObj_array(&jwc, "array_of_objects"); /* Create and open array */

  /* Add object 0 to array */
  jwArr_object(&jwc); /* Create object in array */
  jwObj_string(&jwc, "key", "value");
  jwObj_int(&jwc, "int", 1);
  jwObj_double(&jwc, "double", 1.234);
  jwObj_null(&jwc, "nullThing");
  jwObj_bool(&jwc, "bool", 1);
  jwEnd(&jwc); /* Close object in array */

  /* Add object 1 to array */
  jwArr_object(&jwc); /* Create object in array */
  jwObj_string(&jwc, "key", "value");
  jwObj_int(&jwc, "int", 1);
  jwObj_double(&jwc, "double", 1.234);
  jwObj_null(&jwc, "nullThing");
  jwObj_bool(&jwc, "bool", 1);
  jwEnd(&jwc); /* Close object in array */

  /* Add object 2 to array */
  jwArr_object(&jwc); /* Create object in array */
  jwObj_string(&jwc, "key", "value");
  jwObj_int(&jwc, "int", 1);
  jwObj_double(&jwc, "double", 1.234);
  jwObj_null(&jwc, "nullThing");
  jwObj_bool(&jwc, "bool", 1);
  jwEnd(&jwc); /* Close object in array */

  jwEnd(&jwc); /* Close array */

  err = jwClose(&jwc); /* Close json and get error code */
  printf("%s\n\n", json);
  if (err != JWRITE_OK)
    printf("Error: %s at function call %d\n", jwErrorToString(err),
           jwErrorPos(&jwc));
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

  /* Create structure to use for json state */
  struct jWriteControl jwc;
  /* Clear json buffer, create root as object and set format to pretty */
  jwOpen(&jwc, json, maxJsonLen, JW_OBJECT, JW_PRETTY);

  /* Add empty to object */
  jwObj_array(&jwc, "array_of_arrays"); /* Create and open array */

  /* Create array 0 and insert basic types */
  jwArr_array(&jwc);
  jwArr_string(&jwc, "value");
  jwArr_int(&jwc, 1);
  jwArr_double(&jwc, 1.234);
  jwArr_null(&jwc);
  jwArr_bool(&jwc, 1);
  jwEnd(&jwc);

  /* Create array 1 and insert basic types */
  jwArr_array(&jwc);
  jwArr_string(&jwc, "value");
  jwArr_int(&jwc, 1);
  jwArr_double(&jwc, 1.234);
  jwArr_null(&jwc);
  jwArr_bool(&jwc, 1);
  jwEnd(&jwc);

  /* Create array 2 and insert basic types */
  jwArr_array(&jwc);
  jwArr_string(&jwc, "value");
  jwArr_int(&jwc, 1);
  jwArr_double(&jwc, 1.234);
  jwArr_null(&jwc);
  jwArr_bool(&jwc, 1);
  jwEnd(&jwc);

  jwEnd(&jwc);         /* Close array */
  err = jwClose(&jwc); /* close and get error code */

  printf("%s\n\n", json);
  if (err != JWRITE_OK)
    printf("Error: %s at function call %d\n", jwErrorToString(err),
           jwErrorPos(&jwc));
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

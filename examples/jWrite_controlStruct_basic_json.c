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
  jw_key(&jwc, "key");
  jw_string(&jwc, "value");
  jw_key(&jwc, "int");
  jw_int(&jwc, 1);
  jw_key(&jwc, "double");
  jw_double(&jwc, 1.234);
  jw_key(&jwc, "nullThing");
  jw_null(&jwc);
  jw_key(&jwc, "bool");
  jw_bool(&jwc, 1);

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
  jw_key(&jwc, "key");
  jw_string(&jwc, "value");
  jw_key(&jwc, "int");
  jw_int(&jwc, 1);
  jw_key(&jwc, "double");
  jw_double(&jwc, 1.234);
  jw_key(&jwc, "nullThing");
  jw_null(&jwc);
  jw_key(&jwc, "bool");
  jw_bool(&jwc, 1);

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
  jw_string(&jwc, "value");
  jw_int(&jwc, 1);
  jw_double(&jwc, 1.234);
  jw_null(&jwc);
  jw_bool(&jwc, 1);

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
  jw_key(&jwc, "array_empty");
  jw_array(&jwc); /* Create and open array */
  jwEnd(&jwc);    /* Close array */

  /* Create array and insert basic types */
  jw_key(&jwc, "array_basic");
  jw_array(&jwc);
  jw_string(&jwc, "value");
  jw_int(&jwc, 1);
  jw_double(&jwc, 1.234);
  jw_null(&jwc);
  jw_bool(&jwc, 1);
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
  jw_key(&jwc, "object_empty");
  jw_object(&jwc); /* Create and open object */
  jwEnd(&jwc);     /* Close object */

  /* Create object and insert basic types */
  jw_key(&jwc, "object_basic");
  jw_object(&jwc);
  jw_key(&jwc, "key");
  jw_string(&jwc, "value");
  jw_key(&jwc, "int");
  jw_int(&jwc, 1);
  jw_key(&jwc, "double");
  jw_double(&jwc, 1.234);
  jw_key(&jwc, "nullThing");
  jw_null(&jwc);
  jw_key(&jwc, "bool");
  jw_bool(&jwc, 1);
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
  jw_key(&jwc, "array_of_objects");
  jw_array(&jwc); /* Create and open array */

  /* Add object 0 to array */
  jw_object(&jwc); /* Create object in array */
  jw_key(&jwc, "key");
  jw_string(&jwc, "value");
  jw_key(&jwc, "int");
  jw_int(&jwc, 1);
  jw_key(&jwc, "double");
  jw_double(&jwc, 1.234);
  jw_key(&jwc, "nullThing");
  jw_null(&jwc);
  jw_key(&jwc, "bool");
  jw_bool(&jwc, 1);
  jwEnd(&jwc); /* Close object in array */

  /* Add object 1 to array */
  jw_object(&jwc); /* Create object in array */
  jw_key(&jwc, "key");
  jw_string(&jwc, "value");
  jw_key(&jwc, "int");
  jw_int(&jwc, 1);
  jw_key(&jwc, "double");
  jw_double(&jwc, 1.234);
  jw_key(&jwc, "nullThing");
  jw_null(&jwc);
  jw_key(&jwc, "bool");
  jw_bool(&jwc, 1);
  jwEnd(&jwc); /* Close object in array */

  /* Add object 2 to array */
  jw_object(&jwc); /* Create object in array */
  jw_key(&jwc, "key");
  jw_string(&jwc, "value");
  jw_key(&jwc, "int");
  jw_int(&jwc, 1);
  jw_key(&jwc, "double");
  jw_double(&jwc, 1.234);
  jw_key(&jwc, "nullThing");
  jw_null(&jwc);
  jw_key(&jwc, "bool");
  jw_bool(&jwc, 1);
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
  jw_key(&jwc, "array_of_arrays");
  jw_array(&jwc); /* Create and open array */

  /* Create array 0 and insert basic types */
  jw_array(&jwc);
  jw_string(&jwc, "value");
  jw_int(&jwc, 1);
  jw_double(&jwc, 1.234);
  jw_null(&jwc);
  jw_bool(&jwc, 1);
  jwEnd(&jwc);

  /* Create array 1 and insert basic types */
  jw_array(&jwc);
  jw_string(&jwc, "value");
  jw_int(&jwc, 1);
  jw_double(&jwc, 1.234);
  jw_null(&jwc);
  jw_bool(&jwc, 1);
  jwEnd(&jwc);

  /* Create array 2 and insert basic types */
  jw_array(&jwc);
  jw_string(&jwc, "value");
  jw_int(&jwc, 1);
  jw_double(&jwc, 1.234);
  jw_null(&jwc);
  jw_bool(&jwc, 1);
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

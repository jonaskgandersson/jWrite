#include <stdio.h>

#include "../jWrite.h"

/* Use same buffer for all examples */
char json[1024];
unsigned int maxJsonLen = 1024;
int err;

/* Some custom struct/type */
struct Person {
  char name[10];
  int age;
};

/* Person to json object
 * Create custom helper function to write custom data.
 * This implementation is only for using global control struct.
 */
void jwObj_person(struct jWriteControl *jwc, char *key, struct Person person) {
  jwObj_object(jwc, key);
  jwObj_string(jwc, "Name", person.name);
  jwObj_int(jwc, "Age", person.age);
  jwEnd(jwc);

  return;
}

/* Person to json array
 * Create custom helper function to write custom data.
 * This implementation is only for using global control struct.
 */
void jwArr_person(struct jWriteControl *jwc, struct Person person) {
  jwArr_object(jwc);
  jwObj_string(jwc, "Name", person.name);
  jwObj_int(jwc, "Age", person.age);
  jwEnd(jwc);

  return;
}

/* Struct to object
 * {
 *     "Alice": {
 *         "Name": "Alice",
 *         "Age": 31
 *     },
 *     "Bob": {
 *         "Name": "Bob",
 *         "Age": 42
 *     }
 * }
 *
 */
void person_root_object() {

  /* Create some example data to write to json */
  struct Person bob = {"Bob", 42};
  struct Person alice = {"Alice", 31};

  printf("JSON root object:\n\n");

  struct jWriteControl json_state;

  /* Clear json buffer, create root as object and set format to pretty */
  jwOpen(&json_state, json, maxJsonLen, JW_OBJECT, JW_PRETTY);

  /* Add persons to object as key:Person */
  jwObj_person(&json_state, alice.name, alice);
  jwObj_person(&json_state, bob.name, bob);

  err = jwClose(&json_state); /* close and get error code */

  printf("%s\n\n", json);
  if (err != JWRITE_OK)
    printf("Error: %s at function call %d\n", jwErrorToString(err),
           jwErrorPos(&json_state));
  return;
}

/* Struct to array object
 *
 * [
 *     {
 *         "Name": "Bob",
 *         "Age": 42
 *     },
 *     {
 *         "Name": "Alice",
 *         "Age": 31
 *     }
 * ]
 *
 */
void person_root_array() {

  /* Create some example data to write to json */
  struct Person catalog[] = {{"Bob", 42}, {"Alice", 31}};
  int catalog_length = sizeof(catalog) / sizeof(catalog[0]);

  printf("JSON root array:\n\n");

  struct jWriteControl json_state;

  /* Clear json buffer, create root as object and set format to pretty */
  jwOpen(&json_state, json, maxJsonLen, JW_ARRAY, JW_PRETTY);

  /* Add all persons in catalog to json array */
  int i = 0;
  for (i = 0; i < catalog_length; i++) {
    jwArr_person(&json_state, catalog[i]);
  }

  err = jwClose(&json_state); /* close and get error code */

  printf("%s\n\n", json);
  if (err != JWRITE_OK)
    printf("Error: %s at function call %d\n", jwErrorToString(err),
           jwErrorPos(&json_state));
  return;
}
/* Run examples */
int main() {

  person_root_object();

  person_root_array();
  return 0;
}

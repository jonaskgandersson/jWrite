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

/* Person to json object value
 * Create custom helper function to write custom data.
 * This implementation is only for using global control struct.
 */
void jw_person(struct Person person) {
  jw_object();
  jw_key("Name");
  jw_string(person.name);
  jw_key("Age");
  jw_int(person.age);
  jwEnd();

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

  /* Clear json buffer, create root as object and set format to pretty */
  jwOpen(json, maxJsonLen, JW_OBJECT, JW_PRETTY);

  /* Add persons to object as key:Person */
  jw_key(alice.name);
  jw_person(alice);
  jw_key(bob.name);
  jw_person(bob);

  err = jwClose(); /* close and get error code */

  printf("%s\n\n", json);
  if (err != JWRITE_OK)
    printf("Error: %s at function call %d\n", jwErrorToString(err),
           jwErrorPos());
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

  /* Clear json buffer, create root as object and set format to pretty */
  jwOpen(json, maxJsonLen, JW_ARRAY, JW_PRETTY);

  /* Add all persons in catalog to json array */
  int i = 0;
  for (i = 0; i < catalog_length; i++) {
    jw_person(catalog[i]);
  }

  err = jwClose(); /* close and get error code */

  printf("%s\n\n", json);
  if (err != JWRITE_OK)
    printf("Error: %s at function call %d\n", jwErrorToString(err),
           jwErrorPos());
  return;
}
/* Run examples */
int main() {

  person_root_object();

  person_root_array();
  return 0;
}

/*
 * jWrite.h
 *
 * A *really* simple JSON writer in C  (C89)
 * - a collection of functions to generate JSON semi-automatically
 *
 * The idea is to simplify writing native C values into a JSON string and
 * to provide some error trapping to ensure that the result is valid JSON.
 *
 */

/* Comment this out to use applic-supplied jWriteControl */
#define JW_GLOBAL_CONTROL_STRUCT

#define JWRITE_STACK_DEPTH 32 /* max nesting depth of objects/arrays */

#define JW_COMPACT 0 /* output string control for jwOpen() */
#define JW_PRETTY 1  /* pretty adds \n and indentation */

enum jwNodeType { JW_OBJECT = 1, JW_ARRAY, JW_VALUE };

struct jwNodeStack {
  enum jwNodeType nodeType;
  int elementNo;
};

struct jWriteControl {
  char *buffer;        /* pointer to application's buffer */
  unsigned int buflen; /* length of buffer */
  char *bufp;          /* current write position in buffer */
  char tmpbuf[32];     /* local buffer for int/double convertions */
  int error;           /* error code */
  int callNo;          /* API call on which error occurred */
  struct jwNodeStack
      nodeStack[JWRITE_STACK_DEPTH]; /* stack of array/object nodes */
  int stackpos;
  int isPretty; /* 1= pretty output (inserts \n and spaces) */
};

/* Error Codes */
#define JWRITE_OK 0
#define JWRITE_BUF_FULL 1      /* output buffer full */
#define JWRITE_NOT_ARRAY 2     /* tried to write Array value into Object */
#define JWRITE_NOT_OBJECT 3    /* tried to write Object key/value into Array */
#define JWRITE_STACK_FULL 4    /* array/object nesting > JWRITE_STACK_DEPTH */
#define JWRITE_STACK_EMPTY 5   /* stack underflow error (too many 'end's) */
#define JWRITE_NEST_ERROR 6    /* not all objects closed at jwClose()*/
#define JWRITE_NOT_VALUE 7     /* tried to write value without key */
#define JWRITE_MISSING_VALUE 8 /* object missing value */

/**
 * Get error description from error code
 *
 * @param err error code
 * @return '\0'-terminated string
 */
char *jwErrorToString(int err);

#ifdef JW_GLOBAL_CONTROL_STRUCT /* USING GLOBAL g_jWriteControl */

/**
 * @brief Initialises jWrite buffer and global control struct
 *
 * @param buffer char array for holding json
 * @param buflen length of json buffer
 * @param rootType JW_OBJECT or JW_ARRAY
 * @param isPretty JW_PRETTY to add space and newlines, or JW_COMPACT
 */
void jwOpen(char *buffer, unsigned int buflen, enum jwNodeType rootType,
            int isPretty);

/**
 * Closes the element opened by jwOpen()
 *
 * @return error code for the first error detected
 */
int jwClose();

/*
 * Get jWrite function call which caused the first error
 *
 * @return number of the last function call before error
 */
int jwErrorPos();

/**
 * Insert key: to object
 *
 * @param key name of key
 */
int jw_key(char *key);

/**
 * Insert quoted string as "value".
 *
 * @param value as string
 */
void jw_string(char *value);

/**
 * Insert number as value.
 *
 * @param value as int
 */
void jw_int(int value);

/**
 * Insert number as value.
 * Number will be rounded, big values will be converted to scientific notation
 *
 * @param value as double
 */
void jw_double(double value);

/**
 * Insert boolen as false|true.
 *
 * @param value as int, 0 = false, >0 = true
 */
void jw_bool(int oneOrZero);

/**
 * Insert null.
 */
void jw_null();

/**
 * Insert object as {.
 * Add key:value with other function calls.
 * Close object with jwEnd()
 */
void jw_object();

/**
 * Insert array as [.
 * Add value with other function calls.
 * Close array with jwEnd()
 */
void jw_array();

/**
 * Defines the end of an Object or Array definition.
 * Will insert ending } or ].
 * Root element is closed by jwClose().
 */
int jwEnd();

/**
 * Insert raw text to JSON as rawtext.
 * Enclosing quotes are not added.
 * Use with custom value->string function.
 *
 * @param rawtext as string
 */
void jw_raw(char *rawtext);

#else /* JW_GLOBAL_CONTROL_STRUCT not defined */
/* Same API functions with app-supplied control struct option */

/**
 * Initialises jWrite buffer and control struct
 *
 * @param jwc control struct to hold json state
 * @param buffer char array for holding json
 * @param buflen length of json buffer
 * @param rootType JW_OBJECT or JW_ARRAY
 * @param isPretty JW_PRETTY to add space and newlines, or JW_COMPACT
 */
void jwOpen(struct jWriteControl *jwc, char *buffer, unsigned int buflen,
            enum jwNodeType rootType, int isPretty);

/**
 * Closes the element opened by jwOpen()
 *
 * @param jwc control struct for json state
 * @return error code for the first error detected
 */
int jwClose(struct jWriteControl *jwc);

/*
 * Get jWrite function call which caused the first error
 *
 * @param jwc control struct for json state
 * @return number of the last function call before error
 */
int jwErrorPos(struct jWriteControl *jwc);

/**
 * Insert key: to object
 *
 * @param jwc control struct for json state
 * @param key name of key
 */
int jw_key(struct jWriteControl *jwc, char *key);

/**
 * Insert quoted string as "value".
 *
 * @param jwc control struct for json state
 * @param value as string
 */
void jw_string(struct jWriteControl *jwc, char *value);

/**
 * Insert number as value.
 *
 * @param jwc control struct for json state
 * @param value as int
 */
void jw_int(struct jWriteControl *jwc, int value);

/**
 * Insert number as value.
 * Number will be rounded, big values will be converted to scientific notation
 *
 * @param jwc control struct for json state
 * @param value as double
 */
void jw_double(struct jWriteControl *jwc, double value);

/**
 * Insert boolen as false|true.
 *
 * @param jwc control struct for json state
 * @param value as int, 0 = false, >0 = true
 */
void jw_bool(struct jWriteControl *jwc, int oneOrZero);

/**
 * Insert null as null.
 *
 * @param jwc control struct for json state
 */
void jw_null(struct jWriteControl *jwc);

/**
 * Insert object as {.
 * Add key:value with other function calls.
 * Close object with jwEnd()
 *
 * @param jwc control struct for json state
 */
void jw_object(struct jWriteControl *jwc);

/**
 * Insert array as [.
 * Add value with other function calls.
 * Close array with jwEnd()
 *
 * @param jwc control struct for json state
 */
void jw_array(struct jWriteControl *jwc);

/**
 * Defines the end of an Object or Array definition.
 * Will insert ending } or ].
 * Root element is closed by jwClose().
 *
 * @param jwc control struct for json state
 */
int jwEnd(struct jWriteControl *jwc);

/**
 * Insert raw text to JSON as rawtext.
 * Enclosing quotes are not added.
 * Use with custom value->string function.
 *
 * @param jwc control struct for json state
 * @param rawtext as string
 */
void jw_raw(struct jWriteControl *jwc, char *rawtext);

#endif /* JW_GLOBAL_CONTROL_STRUCT */

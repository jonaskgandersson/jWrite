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

/* <--- comment this out to use applic-supplied jWriteControl */
#define JW_GLOBAL_CONTROL_STRUCT

#define JWRITE_STACK_DEPTH 32 /* max nesting depth of objects/arrays */

#define JW_COMPACT 0 /* output string control for jwOpen() */
#define JW_PRETTY 1  /* pretty adds \n and indentation */

enum jwNodeType { JW_OBJECT = 1, JW_ARRAY };

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
#define JWRITE_BUF_FULL 1    /* output buffer full */
#define JWRITE_NOT_ARRAY 2   /* tried to write Array value into Object */
#define JWRITE_NOT_OBJECT 3  /* tried to write Object key/value into Array */
#define JWRITE_STACK_FULL 4  /* array/object nesting > JWRITE_STACK_DEPTH */
#define JWRITE_STACK_EMPTY 5 /* stack underflow error (too many 'end's) */
#define JWRITE_NEST_ERROR                                                      \
  6 /* nesting error, not all objects closed when jwClose() called */

/* API functions
 * -------------
 *
 * Returns '\0'-termianted string describing the error (as returned by
 * jwClose())
 */
char *jwErrorToString(int err);

#ifdef JW_GLOBAL_CONTROL_STRUCT /* USING GLOBAL g_jWriteControl */

/* jwOpen
 * - initialises jWrite with the application supplied 'buffer' of length
 * 'buflen'
 *   in operation, the buffer will always contain a valid '\0'-terminated string
 * - jWrite will not overrun the buffer (it returns an "output buffer full"
 * error)
 * - rootType is the base JSON type: JW_OBJECT or JW_ARRAY
 * - isPretty controls 'prettifying' the output: JW_PRETTY or JW_COMPACT
 */
void jwOpen(char *buffer, unsigned int buflen, enum jwNodeType rootType,
            int isPretty);

/* jwClose
 * - closes the element opened by jwOpen()
 * - returns error code (0 = JWRITE_OK)
 * - after an error, all following jWrite calls are skipped internally
 *   so the error code is for the first error detected
 */
int jwClose();

/* jwErrorPos
 * - if jwClose returned an error, this function returns the number of the
 * jWrite function call
 *   which caused that error.
 */
int jwErrorPos();

/* Object insertion functions
 * - used to insert "key":"value" pairs into an object
 */
void jwObj_string(char *key, char *value);
void jwObj_int(char *key, int value);
void jwObj_double(char *key, double value);
void jwObj_bool(char *key, int oneOrZero);
void jwObj_null(char *key);
void jwObj_object(char *key);
void jwObj_array(char *key);

/* Array insertion functions
 * - used to insert "value" elements into an array
 */
void jwArr_string(char *value);
void jwArr_int(int value);
void jwArr_double(double value);
void jwArr_bool(int oneOrZero);
void jwArr_null();
void jwArr_object();
void jwArr_array();

/* jwEnd
 * - defines the end of an Object or Array definition
 */
int jwEnd();

/* these 'raw' routines write the JSON value as the contents of rawtext
 * i.e. enclosing quotes are not added
 * - use if your app. supplies its own value->string functions
 */
void jwObj_raw(char *key, char *rawtext);
void jwArr_raw(char *rawtext);

#else /* JW_GLOBAL_CONTROL_STRUCT not defined */
/* Same API functions with app-supplied control struct option
 */
void jwOpen(struct jWriteControl *jwc, char *buffer, unsigned int buflen,
            enum jwNodeType rootType, int isPretty);
int jwClose(struct jWriteControl *jwc);
int jwErrorPos(struct jWriteControl *jwc);
void jwObj_string(struct jWriteControl *jwc, char *key, char *value);
void jwObj_int(struct jWriteControl *jwc, char *key, int value);
void jwObj_double(struct jWriteControl *jwc, char *key, double value);
void jwObj_bool(struct jWriteControl *jwc, char *key, int oneOrZero);
void jwObj_null(struct jWriteControl *jwc, char *key);
void jwObj_object(struct jWriteControl *jwc, char *key);
void jwObj_array(struct jWriteControl *jwc, char *key);
void jwArr_string(struct jWriteControl *jwc, char *value);
void jwArr_int(struct jWriteControl *jwc, int value);
void jwArr_double(struct jWriteControl *jwc, double value);
void jwArr_bool(struct jWriteControl *jwc, int oneOrZero);
void jwArr_null(struct jWriteControl *jwc);
void jwArr_object(struct jWriteControl *jwc);
void jwArr_array(struct jWriteControl *jwc);
int jwEnd(struct jWriteControl *jwc);
void jwObj_raw(struct jWriteControl *jwc, char *key, char *rawtext);
void jwArr_raw(struct jWriteControl *jwc, char *rawtext);

#endif /* JW_GLOBAL_CONTROL_STRUCT */

/* end of jWrite.h */

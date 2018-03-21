// main.c
//
// Test harness command-line for jWrite 
//
// TonyWilk
// 17mar2015
//
#define _CRT_SECURE_NO_WARNINGS			// stop complaining about deprecated functions

#include <stdio.h>

#include "jWrite.h"

//-------------------------------------------------
// Command-line interface
// usage:
//  jWrite			prints example tests
//
void jWriteTest();

int main(int argc, char * argv[])
{
	jWriteTest();
	return 0;
}


//------------------------------------------------------------

#ifdef JW_GLOBAL_CONTROL_STRUCT

// Examples of jWrite
// - using global control structure
//
void jWriteTest()
{
	char buffer[1024];
	unsigned int buflen= 1024;
	int err;

	printf("A JSON object example:\n\n" );

	jwOpen( buffer, buflen, JW_OBJECT, JW_PRETTY );		// start root object

	jwObj_string( "key", "value" );				// add object key:value pairs
	jwObj_int( "int", 1 );
	jwObj_double( "double", 1.234 );
	jwObj_null( "nullThing" );
	jwObj_bool( "bool", 1 );
	jwObj_array( "EmptyArray" );
		// empty array
	jwEnd();
	jwObj_array( "anArray" );					// array with elements
		jwArr_string("array one" );
		jwArr_int( -2 );
		jwArr_double( 1234.567 );
		jwArr_null();
		jwArr_bool( 0 );
		jwArr_object();							// object in array
			jwObj_string( "obj3_one", "one");
			jwObj_string( "obj3_two", "two");
		jwEnd();
		jwArr_array();							// array in array
			jwArr_int( 0 );
			jwArr_int( 1 );
			jwArr_int( 2 );
		jwEnd();
	jwEnd();									// end of "anArray" , back to root object

	jwObj_object( "EmptyObject" );
	jwEnd();

	jwObj_object( "anObject" );					// object in the root object
		jwObj_string("msg","object in object");
		jwObj_string("msg2","object in object 2nd entry");
	jwEnd();
	jwObj_string( "ObjEntry", "This is the last one" );

	err= jwClose();								// close and get error code

	printf( buffer );
	if( err != JWRITE_OK )
		printf( "Error: %s at function call %d\n", jwErrorToString(err), jwErrorPos() );

	printf("\n\nA JSON array example:\n\n" );

	jwOpen( buffer, buflen, JW_ARRAY, JW_PRETTY );
	jwArr_string( "String value" );
	jwArr_int( 1234 );
	jwArr_double( 567.89012 );
	jwArr_bool( 1 );
	jwArr_null();
	jwArr_object();		
		// empty object
	jwEnd();
	jwArr_object();
		jwObj_string( "key", "value" );
		jwObj_string( "key2", "value2" );
	jwEnd();
	jwArr_array();		// array in array
		jwArr_string("Array in array");
		jwArr_string("the end");
	jwEnd();
	jwArr_string("Empty array next...");
	jwArr_array();
		// empty array
	jwEnd();
	err= jwClose();

	printf( buffer );
	if( err != JWRITE_OK )
		printf( "Error: %s at function call %d\n", jwErrorToString(err), jwErrorPos() );

	printf("\n\nExample error:\n\n" );
	// this is a copy of the above array example with an error introduced...
	//
	jwOpen( buffer, buflen, JW_ARRAY, JW_PRETTY );	// 1
	jwArr_string( "String value" );					// 2
	jwArr_int( 1234 );								// 3
	jwArr_double( 567.89012 );						// 4
	jwArr_bool( 1 );								// 5
	jwArr_null();									// 6
	jwArr_object();									// 7
		// empty object
	//jwEnd();
	jwArr_object();									// 8  <-- this is where the error is
		jwObj_string( "key", "value" );				// 9
		jwObj_string( "key2", "value2" );			// 10
	jwEnd();										// 11 
	jwArr_array();		// array in array			// 12
		jwArr_string("Array in array");				// 13
		jwArr_string("the end");					// 14
	jwEnd();										// 15
	jwArr_string("Empty array next...");			// 16
	jwArr_array();									// 17
		// empty array
	jwEnd();										// 18
	err= jwClose();									

	printf( buffer );
	if( err != JWRITE_OK )
		printf( "Error: %s at function call %d\n", jwErrorToString(err), jwErrorPos() );

	return;
}

#else /* JW_GLOBAL_CONTROL_STRUCT */

// Same examples using user-defined control structure
// - to compile in this mode, comment out the JW_GLOBAL_CONTROL_STRUCT definition
//
void jWriteTest()
{
	char buffer[1024];
	unsigned int buflen= 1024;
	int err;
	struct jWriteControl jwc;

	printf("jWrite - a JSON object example:\n\n" );
	//
	// Example JSON object
	//
	jwOpen( &jwc, buffer, buflen, JW_OBJECT, 1 );

	jwObj_string( &jwc, "key", "value" );
	jwObj_int( &jwc, "int", 1 );
	jwObj_double( &jwc, "double", 1.234 );
	jwObj_null( &jwc, "nullThing" );
	jwObj_bool( &jwc, "bool", 1 );
	jwObj_array( &jwc, "EmptyArray" );		// empty array
	jwEnd( &jwc );
	jwObj_array( &jwc, "anArray" );
		jwArr_string(&jwc, "array one" );
		jwArr_int( &jwc, 2 );
		jwArr_double( &jwc, 1234.567 );
		jwArr_null(&jwc);
		jwArr_bool( &jwc, 0 );
		jwArr_object( &jwc );
			jwObj_string( &jwc, "obj3_one", "one");
			jwObj_string( &jwc, "obj3_two", "two");
		jwEnd(&jwc);
		jwArr_array(&jwc);
			jwArr_int( &jwc, 0 );
			jwArr_int( &jwc, 1 );
			jwArr_int( &jwc, 2 );
		jwEnd(&jwc );
	jwEnd(&jwc);

	jwObj_object( &jwc, "EmptyObject" );
	jwEnd(&jwc);

	jwObj_object( &jwc, "anObject" );
		jwObj_string(&jwc, "msg","object in object");
		jwObj_string(&jwc, "msg2","object in object 2nd entry");
	jwEnd( &jwc );
	jwObj_string( &jwc, "ObjEntry", "This is the last one" );

	err= jwClose(&jwc);

	printf( buffer );
	if( err != JWRITE_OK )
		printf( "Error: %s at function call %d\n", jwErrorToString(err), jwErrorPos(&jwc) );


	printf("\n\nA JSON array example:\n\n" );

	jwOpen( &jwc, buffer, buflen, JW_ARRAY, 1 );
	jwArr_string( &jwc, "String value" );
	jwArr_int( &jwc, 1234 );
	jwArr_double( &jwc, 567.89012 );
	jwArr_bool( &jwc, 1 );
	jwArr_null( &jwc );
	jwArr_object( &jwc );		
		// empty object
	jwEnd( &jwc );
	jwArr_object( &jwc );
		jwObj_string( &jwc, "key", "value" );
		jwObj_string( &jwc, "key2", "value2" );
	jwEnd( &jwc );
	jwArr_array( &jwc );		// array in array
		jwArr_string(&jwc, "Array in array");
		jwArr_string(&jwc, "the end");
	jwEnd( &jwc );
	err= jwClose( &jwc );

	printf( buffer );
	if( err != JWRITE_OK )
		printf( "Error: %s at function call %d\n", jwErrorToString(err), jwErrorPos( &jwc ) );

	printf("\n\nExample error:\n\n" );
	jwOpen( &jwc, buffer, buflen, JW_ARRAY, 1 );		// 1
	jwArr_string( &jwc, "String value" );				// 2
	jwArr_int( &jwc, 1234 );							// 3
	jwArr_double( &jwc, 567.89012 );					// 4
	jwArr_bool( &jwc, 1 );								// 5
	jwArr_null( &jwc );									// 6
	jwArr_object( &jwc );								// 7
		// empty object
	//jwEnd( &jwc );
	jwArr_object( &jwc );								// 8  <-- this is where the error is
		jwObj_string( &jwc, "key", "value" );			// 9
		jwObj_string( &jwc, "key2", "value2" );			// 10
	jwEnd( &jwc );										// 11 
	jwArr_array( &jwc );		// array in array		// 12
		jwArr_string(&jwc, "Array in array");			// 13
		jwArr_string(&jwc, "the end");					// 14
	jwEnd( &jwc );										// 15
	err= jwClose( &jwc );								// 16

	printf( buffer );
	if( err != JWRITE_OK )
		printf( "Error: %s at function call %d\n", jwErrorToString(err), jwErrorPos( &jwc ) );

	return;
}

#endif /* JW_GLOBAL_CONTROL_STRUCT */

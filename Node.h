
/**************************************************************************/
/* def.h                                                                  */
/* This file contains GENERAL definitions used in several data structures */
/**************************************************************************/

#ifndef _Node_
#define _Node_


// new types
typedef void* DATA;					// a type for data (easy to change)
typedef enum { False, True } BOOL;	// a boolean type

// Node
typedef struct node
{
	DATA key;
	struct node* next;
}NODE;

#endif

/*
* headers.h
* Copyright (c) 2023
* GNU GPLv3
*/

#ifndef FIDO_HEADERS_H
#define FIDO_HEADERS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// ==== Data Structures  ====
//FIDO HEADER Creates a Header object to be used in HTTP Calls
typedef struct FIDO_HEADER {
    char* key;
    char* value;
} FIDO_HEADER;

//FIDER HEADERLIST is a list of Fido headers
typedef struct FIDO_HEADERLIST {
    int length;
    FIDO_HEADER** headers;
} FIDO_HEADERLIST;

// ==== Data Structure Interfaces ====
#ifndef HEADER
  typedef struct FIDO_HEADER HEADER;
#endif

#ifndef HEADERLIST
  typedef struct FIDO_HEADERLIST HEADERLIST;
#endif

// ==== Public Functions ====
//Create a New FIDO Header
FIDO_HEADER* FIDO_CREATE_HEADER(char* key, char* value);

//Frees Header Object
void FIDO_FREE_HEADER(FIDO_HEADER* h);

//Sets the Key of a FIDO Header
void FIDO_SET_KEY(FIDO_HEADER *h, char* key);

//Sets the value of a FIDO Header
void FIDO_SET_VALUE(FIDO_HEADER *h, char* value);

//Creates a new Header List
FIDO_HEADERLIST* FIDO_CREATE_HEADER_LIST();

//Adds a new header to the passed list
void FIDO_ADD_HEADER(FIDO_HEADERLIST *list, FIDO_HEADER *header);

//Returns a Header from the passed headerlist at index
FIDO_HEADER* FIDO_GET_HEADER(FIDO_HEADERLIST *list, int index);

//Returns a header by a key value from the passed headerlist
FIDO_HEADER* FIDO_GET_HEADER_BY_KEY(FIDO_HEADERLIST *list, char* key);

//Removes a header from the passed list at index. DOES NOT FREE
void FIDO_REMOVE_HEADER(FIDO_HEADERLIST *list, int index);

//Removes a header from a passed list at index by key, DOES NOT FREE
void FIDO_REMOVE_HEADER_BY_KEY(FIDO_HEADERLIST *list, char* key);

//Returns a header by key from a list.
int FIDO_GET_HEADER_INDEX(FIDO_HEADERLIST *list, char* key);

//Prints the list to stdout
void FIDO_PRINT_HEADER_LIST(FIDO_HEADERLIST *list);

//Frees the list memory. DOES NOT FREE EACH HEADER
void FIDO_FREE_HEADER_LIST(FIDO_HEADERLIST *list);

// ==== Function Interfaces ====
#ifndef CREATE_HEADER
  #define CREATE_HEADER(key, value) FIDO_CREATE_HEADER(key, value)
#endif

#ifndef FREE_HEADER
  #define FREE_HEADER(h) FIDO_FREE_HEADER(h)
#endif

#ifndef SET_KEY
  #define SET_KEY(h, key) FIDO_SET_KEY(h, key)
#endif

#ifndef SET_VALUE
  #define SET_VALUE(h, value) FIDO_SET_VALUE(h, value)
#endif

#ifndef CREATE_HEADER_LIST
  #define CREATE_HEADER_LIST() FIDO_CREATE_HEADER_LIST()
#endif

#ifndef ADD_HEADER
  #define ADD_HEADER(list, header) FIDO_ADD_HEADER(list,header)
#endif

#ifndef GET_HEADER
  #define GET_HEADER(list, index) FIDO_GET_HEADER(list, index)
#endif

#ifndef GET_HEADER_BY_KEY
  #define GET_HEADER_BY_KEY(list, key) FIDO_GET_HEADER_BY_KEY(list, key)
#endif

#ifndef REMOVE_HEADER
  #define REMOVE_HEADER(list, index) FIDO_REMOVE_HEADER(list, index)
#endif

#ifndef REMOVE_HEADER_BY_KEY
  #define REMOVE_HEADER_BY_KEY(list, key) FIDO_REMOVE_HEADER_BY_KEY
#endif

#ifndef GET_HEADER_INDEX
  #define GET_HEADER_INDEX(list, key) FIDO_GET_HEADER_INDEX(list,key)
#endif

#ifndef PRINT_HEADER_LIST
  #define PRINT_HEADER_LIST(list) FIDO_PRINT_HEADER_LIST(list)
#endif

#ifndef FREE_HEADER_LIST
  #define FREE_HEADER_LIST(list) FIDO_FREE_HEADER_LIST(list)
#endif

#endif

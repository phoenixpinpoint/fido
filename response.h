/*
* response.h
* Copyright (c) 2023
* GNU GPLv3
*/

#ifndef FIDO_RESPONSE_H
#define FIDO_RESPONSE_H

#ifndef FIDO_HEADERS_H
  #include "headers.h"
#endif

// ==== Data Structures  ====
//Fido HTTP Response Object
typedef struct FIDO_HTTP_RESPONSE {
    int response_code;  // Response Code
    char* body;         // Raw body as char array TODO: build JSON body
    FIDO_HEADERLIST* headers;       // String representation of header.
} FIDO_HTTP_RESPONSE;

// ==== Data Structure Interfaces ====
#ifndef HTTP_RESPONSE
  typedef struct FIDO_HTTP_RESPONSE HTTP_RESPONSE;
#endif

// ====Public Functions ====
//Create a HTTP Response Object
FIDO_HTTP_RESPONSE* FIDO_CREATE_HTTP_RESPONSE(int response_code, char* body, FIDO_HEADERLIST* list);

//Free the HTTP Response Memory
void FIDO_FREE_HTTP_RESPONSE(FIDO_HTTP_RESPONSE* res);

//Set the HTTP Response body
void FIDO_SET_HTTP_RESPONSE_BODY(FIDO_HTTP_RESPONSE* res, char* body);

#endif

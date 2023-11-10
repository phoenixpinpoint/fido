/*
* request.h
* Copyright (c) 2023
* GNU GPLv3
*/

#ifndef FIDO_REQUEST_H
#define FIDO_REQUEST_H

#ifndef FIDO_HEADERS_H
  #include "headers.h"
#endif

// ==== Data Structures  ====
//Fido HTTP Request Object
typedef struct FIDO_HTTP_REQUEST {
    char* url;          // URL of the endpoint
    char* body;         // Raw body as char array TODO: build JSON body
    FIDO_HEADERLIST* headers;  // Request headers
} FIDO_HTTP_REQUEST;

// ==== Data Structure Interfaces ====
#ifndef HTTP_REQUEST
  typedef struct FIDO_HTTP_REQUEST HTTP_REQUEST;
#endif

// ====Public Functions ====
//Create a new HTTP Request Structure
FIDO_HTTP_REQUEST* FIDO_CREATE_HTTP_REQUEST(char* url, char* body, FIDO_HEADERLIST* list);

//Free the request memory
void FIDO_FREE_HTTP_REQUEST(FIDO_HTTP_REQUEST* req);

//Set request body of the FIDO HTTP request
void FIDO_SET_HTTP_REQUEST_BODY(FIDO_HTTP_REQUEST* req, char* body);

//Set the URL of the HTTP Request
void FIDO_SET_HTTP_URL(FIDO_HTTP_REQUEST* req, char* url);

// ==== Function Interfaces ====
#ifndef CREATE_HTTP_REQUEST
  #define CREATE_HTTP_REQUEST(url, body, headerlist) FIDO_CREATE_HTTP_REQUEST(url, body, headerlist)
#endif

#ifndef FREE_HTTP_REQUEST
  #define FREE_HTTP_REQUEST(req) FIDO_FREE_HTTP_REQUEST(req)
#endif

#ifndef SET_HTTP_REQUEST_BODY
  #define FIDO_SET_HTTP_REQUEST_BODY(req, body) SET_HTTP_REQUEST_BODY(req, body)
#endif

#ifndef SET_HTTP_URL
  #define FIDO_SET_HTTP_URL(req, url) SET_HTTP_URL(req, url)
#endif

#endif

/*
* fido.h
* Copyright (c) 2023
* GNU GPLv3
*/

#ifndef FIDO_H
#define FIDO_H

#include <buffer/buffer.h>
#include <parson/parson.h>

#include "headers.h"
#include "request.h"
#include "response.h"

// ==== Public Functions ===
//Calls the JS Fetch with params, which returns a JSON object as string.
char* FIDO_FETCH(char *httpMethod, char *url, char* headers, char* body);

void FIDO_CLEAN();

//HTTP Get for JS Fetch API
FIDO_HTTP_RESPONSE* FIDO_GET(FIDO_HTTP_REQUEST* req);

//HTTP POST for JS Fetch API
FIDO_HTTP_RESPONSE* FIDO_POST(FIDO_HTTP_REQUEST* req);

//HTTP PATCH for JS Fetch API
FIDO_HTTP_RESPONSE* FIDO_PATCH(FIDO_HTTP_REQUEST* req);

//HTTP PATCH for JS Fetch API
FIDO_HTTP_RESPONSE* FIDO_PATCH(FIDO_HTTP_REQUEST* req);

//HTTP DELETE for JS Fetch API
FIDO_HTTP_RESPONSE* FIDO_DELETE(FIDO_HTTP_REQUEST* req);


#ifdef USE_LIBCURL
//char* CGET();
//FIDO_HEADERLIST* FIDO_PARSE_CURL_HEADERS(char* rawHeaders);
#endif


// ==== Function Interfaces ====
#ifndef HTTP_GET
  #define HTTP_GET(req) FIDO_GET(req)
#endif

#ifndef HTTP_POST
  #define HTTP_POST(req) FIDO_POST(req)
#endif

#ifndef HTTP_PATCH
  #define HTTP_PATCH(req) FIDO_PATCH(req)
#endif

#ifndef HTTP_DELETE
  #define HTTP_DELETE(req) FIDO_DELETE(req)
#endif

#endif

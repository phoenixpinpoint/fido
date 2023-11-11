/*
* fido.h
* Copyright (c) 2023
* GNU GPLv3
*/

#ifndef FIDO_H
#define FIDO_H

#include <emscripten.h>
#include <parson/parson.h>

#include "headers.h"
#include "request.h"
#include "response.h"

//Calls the JS Fetch with params, which returns a JSON object as string.
char* FIDO_FETCH(char *httpMethod, char *url, char* headers, char* body);

//HTTP Get for JS Fetch API
FIDO_HTTP_RESPONSE* FIDO_GET(FIDO_HTTP_REQUEST* req);

#endif

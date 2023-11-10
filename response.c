/*
* response.c
* Copyright (c) 2023
* GNU GPLv3
*/

#include "response.h"

//Create a HTTP Response Object
FIDO_HTTP_RESPONSE* FIDO_CREATE_HTTP_RESPONSE(long response_code, char* body, FIDO_HEADERLIST* list)
{
  FIDO_HTTP_RESPONSE *instance = (FIDO_HTTP_RESPONSE*)malloc(sizeof(FIDO_HTTP_RESPONSE));

	instance->response_code = 0;

	instance->body = (char*)malloc(strlen(body)+1*sizeof(char));
	strncpy(instance->body, body, strlen(body)+1);
    instance->body[strlen(body)] = '\0';

	instance->headers = list;
	return instance;
}

//Free the HTTP Response Memory
void FIDO_FREE_HTTP_RESPONSE(FIDO_HTTP_RESPONSE* res)
{
    if (res->body)
    {
        free(res->body);
    }

    if(res)
    {
        free(res);
    }
}

//Set the HTTP Response body
void FIDO_SET_HTTP_RESPONSE_BODY(FIDO_HTTP_RESPONSE* res, char* body)
{
    	//Free Old Memory
	if (res->body)
	{
		free(res->body);
		res->body = 0;
	}

	if(body)
    {
        res->body = (char*)malloc(strlen(body)+1*sizeof(char));
        strncpy(res->body, body, strlen(body)+1);
		    res->body[strlen(res->body)] = '\0';
    }
}

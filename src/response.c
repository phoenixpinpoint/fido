/*
* response.c
* Copyright (c) 2023
* GNU GPLv3
*/

#include "response.h"

#include <parson/parson.h>

//Create a HTTP Response Object
FIDO_HTTP_RESPONSE* FIDO_CREATE_HTTP_RESPONSE(int response_code, char* body, FIDO_HEADERLIST* list)
{
  FIDO_HTTP_RESPONSE *instance = (FIDO_HTTP_RESPONSE*)malloc(sizeof(FIDO_HTTP_RESPONSE));

	instance->response_code = response_code;

	instance->body = (char*)malloc(strlen(body)+1*sizeof(char));
	strncpy(instance->body, body, strlen(body)+1);
    instance->body[strlen(body)] = '\0';

	instance->headers = list;
	return instance;
}

//Create an HTTP Response Object from a JSON string
FIDO_HTTP_RESPONSE* FIDO_CREATE_HTTP_RESPONSE_FROM_JSON(char* json)
{
    JSON_Value* jsonValue = json_parse_string(json);
    JSON_Object* jsonObject = json_value_get_object(jsonValue);

    int response_code = json_object_get_number(jsonObject, "code");
    char* body = json_object_get_string(jsonObject, "body");
    FIDO_HEADERLIST* headers = FIDO_CREATE_HEADER_LIST();

    JSON_Object* headerObject = json_object_get_object(jsonObject, "headers");
    int headerCount = json_object_get_count(headerObject);

    for(int i = 0; i < headerCount; i++)
    {
        char* key = json_object_get_name(headerObject, i);
        char* value = json_object_get_string(headerObject, key);
        FIDO_ADD_HEADER(headers, FIDO_CREATE_HEADER(key, value));
    }

    json_value_free(jsonValue);
    return FIDO_CREATE_HTTP_RESPONSE(response_code, body, headers);
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

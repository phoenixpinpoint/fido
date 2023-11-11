/*
* request.c
* Copyright (c) 2023
* GNU GPLv3
*/

#include "request.h"

//Create a new HTTP Request Structure
FIDO_HTTP_REQUEST* FIDO_CREATE_HTTP_REQUEST(char* url, FIDO_HEADERLIST* list, char* body)
{
	FIDO_HTTP_REQUEST *instance = (FIDO_HTTP_REQUEST*)malloc(sizeof(FIDO_HTTP_REQUEST));

	instance->url = (char*)malloc(strlen(url)+1*sizeof(char));
	strncpy(instance->url, url, strlen(url)+1);
	instance->url[strlen(instance->url)] = '\0';

	if(body)
	{
		instance->body = (char*)malloc(strlen(body)+1*sizeof(char));
		strncpy(instance->body, body, strlen(body)+1);
		instance->body[strlen(instance->body)] = '\0';
	}
	else
	{
		instance->body = NULL;
	}

	if(list)
	{
		instance->headers = list;
	}
	else
	{
		instance->headers = NULL;
	}


	return instance;
}

//Free the request memory
void FIDO_FREE_HTTP_REQUEST(FIDO_HTTP_REQUEST* req)
{
	if(req->url)
	{
		free(req->url);
	}

	if(req->body)
	{
		free(req->body);
	}

	if(req)
	{
		free(req);
	}

	return;
}

//Set request body of the FIDO HTTP request
void FIDO_SET_HTTP_REQUEST_BODY(FIDO_HTTP_REQUEST* req, char* body)
{
	//Free Old Memory
	if (req->body)
	{
		free(req->body);
		req->body = 0;
	}

	if(body)
  {
		req->body = (char*)malloc(strlen(body)+1*sizeof(char));
		strncpy(req->body, body, strlen(body)+1);
		req->body[strlen(req->body)] = '\0';
  }
}

//Set the URL of the HTTP Request
void FIDO_SET_HTTP_URL(FIDO_HTTP_REQUEST* req, char* url)
{
	//Free Old Memory
	if(req->url)
	{
		free(req->url);
		req->url = 0;
	}

	if(url)
  {
    req->url = (char*)malloc(strlen(url)+1*sizeof(char));
    strncpy(req->url, url, strlen(url)+1);
    req->url[strlen(req->url)] = '\0';
  }
}

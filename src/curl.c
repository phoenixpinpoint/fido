#include "fido.h"

#include <stdlib.h>
#include <stdio.h>

#include <curl/curl.h>

//Libcurl implementation of FIDO_FETCH;
char* FIDO_FETCH(char *httpMethod, char *url, char* headers, char* body)
{
	//Check if Method is empty
	if(!httpMethod)
	{
		return "HTTP_REQ_ERROR: Invalid or No method specified.";	
	}

	//If there are headers
	if(headers)
	{
		JSON_Value *root = json_parse_string(headers);
		if(json_value_get_type(root) != JSONObject)
		{
			return "HTTP_REQ_ERROR: failed to parse header json.";
		}
	}

	if(httpMethod && strcmp(httpMethod, "GET") == 0)
	{
		printf("GET\n");
	}
	else if(httpMethod && strcmp(httpMethod, "POST") == 0)
	{
		printf("POST\n");
	}
	else if(httpMethod && strcmp(httpMethod, "PATCH") == 0)
	{
		printf("PATCH\n");
	}
	else if(httpMethod && strcmp(httpMethod, "DELETE") ==0)
	{
		printf("DELETE\n");
	}
	else { 
		return "HTTP_REQ_ERROR: Invalid or No method specified.";		
	}
	
	char* testResult = malloc(8*sizeof(char));
	//test = "SUCCESS\0;"
	strncpy(testResult, "SUCCESS\0", 8);
	return testResult;
}


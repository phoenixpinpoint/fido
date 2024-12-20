#include "fido.h"

//#include <stdlib.h>
//#include <stdio.h>

#include <curl/curl.h>
#include <string.h>

#define KEY 0
#define VALUE 1
#define LF 10
#define CR 13
#define SPACE 32
#define QUOTE 34
#define COLON 58

char* responseBody;
char* rawHeaders;

void FIDO_CLEAN()
{
	if((void*)responseBody)
	{
		free(responseBody);
		responseBody = 0;
	}
	if((void*)rawHeaders)
	{
		free(rawHeaders);
		rawHeaders = 0;
	}
}

size_t writeFunction(void *ptr, size_t size, size_t nmemb, void *stream) {
    size_t memNeeded = size*nmemb;
	size_t previousSize;
	//printf(ptr);
	if (!(void*)responseBody)
	{
		//printf("CREATING BUFFER\n");
		previousSize = 0;
		responseBody = malloc(memNeeded+1*sizeof(char));
		if(!responseBody)
		{
			return -1;
		}
		strncpy(responseBody, ptr, nmemb+1);//+1 to include the null terminator
	}
	else {
		//printf("RESIZING BUFFER\n");
		previousSize = strlen(responseBody);
		char* reallocBuffer = realloc(responseBody, (previousSize+nmemb+1)*sizeof(char));
		if(!reallocBuffer)
		{
			return -1;
		}
		responseBody = reallocBuffer;
		strncat(responseBody, ptr, nmemb);
	}
    return strlen(responseBody)-previousSize;
}

size_t writeHeadersFunction(void *ptr, size_t size, size_t nmemb, void *stream) {
	size_t memNeeded = size*nmemb;
	size_t previousSize;
	if (!(void*)rawHeaders)
	{
		//printf("Creating Headers Buffer\n");
		//printf("Headers: *%s*\n", ptr);
		previousSize = 0;
		rawHeaders = malloc(memNeeded+1*sizeof(char));
		if(!rawHeaders)
		{
			return -1;
		}
		strncpy(rawHeaders, ptr, nmemb+1);//+1 to include the null terminator
		//printf("**%s\n**", rawHeaders);
	}
	else {
		//printf("Resizing Headers Buffer\n");
		previousSize = strlen(rawHeaders);
		char* reallocBuffer = realloc(rawHeaders, (previousSize+nmemb+1)*sizeof(char));
		if(!reallocBuffer)
		{
			return -1;
		}
		rawHeaders = reallocBuffer;
		strncat(rawHeaders, ptr, nmemb);
	}
    return strlen(rawHeaders)-previousSize;
}


//Libcurl implementation of FIDO_FETCH;
char* FIDO_FETCH(char *httpMethod, char *url, char* headers, char* body)
{
	//printf("Setting Up cURL\n");
	//Setup our CURL prereqs
	CURL *curl;
  	CURLcode res;
	responseBody = 0;
	struct curl_slist *hs=NULL;

	//printf("Checking for HTTP METOD\n");
	//Do preemptive checks before doing cURL init.
	//Check if Method is empty
	if(!httpMethod)
	{
		return "HTTP_REQ_ERROR: Invalid or No method specified.";	
	}

	//printf("Checking for Headers\n");
	//printf("HEADERS: %s\n", headers);
	//If there are headers
	if(headers)
	{
		if (strcmp(headers, "{}") != 0 && strcmp(headers, "") != 0)
		{
			//printf("Parsing Headers\n");
			JSON_Value *root = json_parse_string(headers);
			if(json_value_get_type(root) != JSONObject)
			{
				return "HTTP_REQ_ERROR: failed to parse header json.";
			}
			JSON_Array *root_object = json_value_get_object(root);
			char* headerString = json_serialize_to_string(root);
			char *key;
			char *value;
			size_t count = json_object_get_count(root_object);
			for (size_t i = 0; i < count; i++)
			{
				key = json_object_get_name(root_object, i);
				value = json_object_get_string(root_object, key);

				buffer_t* headerBuffer = buffer_new();
				buffer_append(headerBuffer, key);
				buffer_append(headerBuffer, ": ");
				buffer_append(headerBuffer, value);
				hs = curl_slist_append(hs, headerBuffer->data);
				buffer_free(headerBuffer);
			}
			json_value_free(root);
		}
		else{
			// /printf("Empty Headers\n");
		}

	}
	
	//printf("Initializeing cURL\n");
	curl = curl_easy_init();
  	if(!curl) {
		return "HTTP_REQ_ERROR: failed to init libcurl.";
	}
    curl_easy_setopt(curl, CURLOPT_URL, url);
	curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writeFunction);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, responseBody);
	curl_easy_setopt(curl, CURLOPT_HEADERFUNCTION, writeHeadersFunction);
	curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
	
	//curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L);
	
	if(hs)
	{
		curl_easy_setopt(curl, CURLOPT_HTTPHEADER, hs);
	}

	if(httpMethod && strcmp(httpMethod, "GET") == 0)
	{
		//printf("GET\n");
	}
	else if(httpMethod && strcmp(httpMethod, "POST") == 0)//
	{
		//printf("POST\n");
		curl_easy_setopt(curl, CURLOPT_POST, 1L);
		
		//Debugging Options
		//curl_easy_setopt(curl, CURLOPT_FAILONERROR, 1L);
		//curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L);
		
		//HTTP makes a POST request with a body go to HTTP 100 CONTINUE, This allows us to skip that.
		if (!body)
		{
			curl_easy_setopt(curl, CURLOPT_POSTFIELDS, "");
		}
		else {
			//printf(body);
			curl_easy_setopt(curl, CURLOPT_POSTFIELDS, body);
		}	
	}
	else if(httpMethod && strcmp(httpMethod, "PATCH") == 0)
	{
		//printf("PATCH\n");
		curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "PATCH");
		//TODO Added Body Handling
	}
	else if(httpMethod && strcmp(httpMethod, "DELETE") == 0)
	{
		//printf("DELETE\n");
		curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "DELETE");
	}
	else {
		curl_easy_cleanup(curl);
		return "HTTP_REQ_ERROR: Invalid or No method specified.";		
	}

    // Perform the request, res gets the return code 
    res = curl_easy_perform(curl);

	//printf("End of cURL Request\n");

    //Check for errors
    if(res != CURLE_OK)
	{
      	fprintf(stderr, "curl_easy_perform() failed: %s\n",curl_easy_strerror(res));
	}

	//printf("Setting up Code and Header Processing.\n");
	//Process the cURL response
 	FIDO_HEADERLIST* headerList = FIDO_CREATE_HEADER_LIST();
	int mode = KEY;
	buffer_t* keyBuff = buffer_new();
	buffer_t* valueBuff = buffer_new();
	FIDO_HEADER* tempHeader = 0;
	buffer_t* responseCodeAsString;
	char* tempBuffer;

	//printf("RAW HEADERS: %s\n", rawHeaders);

	//Handling for Redirect Headers
	//Split the Headers on \n\n and take the last one.
	char* lastSubstring = "\0";
	char* subString = strstr(rawHeaders, "\r\n\r\n");
	//If there are multiple headers, we want the last one.
	//printf("SUBSTRING: %s\n", subString);
	//printf("LEN: %d\n", strlen(subString));
	if (subString == NULL || strlen(subString) <= 4)
	{
		//DO NOTHING FOR NOW
		//printf("SINGLE HEADER DETECTED\n");
	}
	else {
		subString += 4; // Move past the \r\n\r\n
		lastSubstring = subString;
		while (subString != NULL && strlen(subString) > 4)
		{
			subString = strstr(subString, "\r\n\r\n");
			subString += 4; // Move past the \r\n\r\n
			if(subString && strlen(subString) > 0)
			{
				lastSubstring = subString;
			}
		}	
	}

	//printf("RAW HEADERS: %s\n", rawHeaders);
	if (lastSubstring != NULL && strlen(lastSubstring) > 0)
	{
		char* originalRawHeaders = rawHeaders;
		rawHeaders = strdup(lastSubstring);
		free(originalRawHeaders);
	}

	//printf("RAW HEADERS: %s\n", rawHeaders);

	//Process The Headers
	for(int i = 0; i < strlen(rawHeaders); i++)
	{	
		if(i == 0)
		{
			//printf("Processing Status Code\n");
			//printf("RAW HEADERS: %s\n", rawHeaders);
			if(strncmp(rawHeaders, "HTTP/1.0", 8) == 0)
			{
				//printf("HTTP 1.0\n");
				tempBuffer = (char*)calloc(3, sizeof(char));
				char* modifiedHeaders = &rawHeaders[9];
			   	strncpy(tempBuffer, modifiedHeaders, 3);
				responseCodeAsString = buffer_new_with_string(tempBuffer);
			}
			else if(strncmp(rawHeaders, "HTTP/1.1", 8) == 0)
			{
				//printf("HTTP 1.1\n");
				tempBuffer = (char*)calloc(3, sizeof(char));
				char* modifiedHeaders = &rawHeaders[9];
			   	strncpy(tempBuffer, modifiedHeaders, 3);
				responseCodeAsString = buffer_new_with_string(tempBuffer);
			}
			else if(strncmp(rawHeaders, "HTTP/2", 6) ==0)
			{
				//printf("HTTP 2\n");
				tempBuffer = (char*)calloc(3, sizeof(char));
				char* modifiedHeaders = &rawHeaders[7];
			   	strncpy(tempBuffer, modifiedHeaders, 3);
				responseCodeAsString = buffer_new_with_string(tempBuffer);
			}
			else 
			{
				return("HTTP_REQ_ERROR: Unable to determine HTTP type.");
			}
			//printf("Status:%s\n", responseCodeAsString->data);
		}

		if((int)rawHeaders[i] == COLON)
		{
			if(mode == KEY)//If we are reading the KEY property
			{
				mode = VALUE;//Set our mode to VALUE
				i++;//There is a space after the colon on headers;
			} 
			else if(mode == VALUE)
			{
				buffer_append_n(valueBuff, &rawHeaders[i], 1);
			}
			else {
				//KEY and VALUE are the only two modes, this is undefined behavour. 
			}

		}
		else if((int)rawHeaders[i] == CR)
		{
			//printf("CR DETECTED! MODE: %d\n", mode);
			if(mode == VALUE)
			{
				buffer_trim_right(keyBuff);
				buffer_trim_right(valueBuff);
				FIDO_HEADER* tempHeader = FIDO_CREATE_HEADER(keyBuff->data, valueBuff->data);
				FIDO_ADD_HEADER(headerList, tempHeader);
				buffer_clear(keyBuff);
				buffer_clear(valueBuff);
				mode = KEY;
			} 
			else if(mode == KEY)
			{
				//printf("Buffer LEN %d\n", buffer_length(keyBuff));
				buffer_clear(keyBuff);
			} 
			else 
			{
				//
			}
		}
		else if((int)rawHeaders[i] == LF)
		{
			//printf("LN DETECTED!\n");
			//Do Nothing as this is a LINE
		}
		else if((int)rawHeaders[i] == QUOTE)
		{
			buffer_append(valueBuff, "\\\"");
		}
		else {
			if(mode == KEY)
			{
				//printf("KEY\n");res
				buffer_append_n(keyBuff, &rawHeaders[i], 1);
			} 
			else if (mode == VALUE)
			{
				//printf("VALUE\n");
				buffer_append_n(valueBuff, &rawHeaders[i], 1);
			}
			else 
			{
			
			}
		}
	}

	//FIDO_PRINT_HEADER_LIST(headerList);
	buffer_t* headersAsJSONString = FIDO_JSONIFY_HEADERS(headerList);
	JSON_Value *responseJSON  = json_value_init_object();
	JSON_Object *root_object = json_value_get_object(responseJSON);
	double responseCode = atof(responseCodeAsString->data);
	//printf("RESPONSE CODE: %f\n", responseCode);
	json_object_set_number(root_object, "code", responseCode);
	json_object_set_value(root_object, "headers", json_parse_string(headersAsJSONString->data));
	json_object_set_string(root_object, "body", responseBody);

	char *serialized_string = NULL;
	serialized_string = json_serialize_to_string(responseJSON);
	json_value_free(responseJSON);

   	curl_easy_cleanup(curl);
	buffer_free(keyBuff);
	buffer_free(valueBuff);
	buffer_free(headersAsJSONString);
	free(rawHeaders);
	rawHeaders = 0;
	free(responseBody);
	responseBody = 0;
	for(int h = 0; h < headerList->length; h++)
	{
		FIDO_FREE_HEADER(headerList->headers[h]);
	}
	FIDO_FREE_HEADER_LIST(headerList);
	free(tempBuffer);

	return serialized_string;
}

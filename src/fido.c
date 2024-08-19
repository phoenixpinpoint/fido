#include "fido.h"

//The default is to load the emscripten/wasm fetch.c.
//If at compile time -D USE_LIBCURL is defined then it will use the curl.c
#ifndef USE_LIBCURL
#include "fetch.c"
#else
#include "curl.c"
#endif

//HTTP Get for JS Fetch 
FIDO_HTTP_RESPONSE* FIDO_GET(FIDO_HTTP_REQUEST* req)
{
  //Create our initial res object
  FIDO_HTTP_RESPONSE *res;

  //Create an array for header conversion to string
  char* headersAsString = NULL;

  //If there is a header passed
  if(req->headers != 0)
  {
    //Stringify it.
    headersAsString = FIDO_JSONIFY_HEADERS(req->headers)->data;
  }

  //FIDO_FETCH always returns a string which is a stringified response from JS.
  char* rawResponse = FIDO_FETCH("GET", req->url, headersAsString, req->body);

  //Create a Parson Root
  JSON_Value *responseRoot = json_parse_string(rawResponse);

  if(json_value_get_type(responseRoot) == JSONObject)
  {
    //Convert Parson Value to JSON Object
    JSON_Object *responseObject = json_value_get_object(responseRoot);

    //Get the status code from the JSON.
    int statusCode = (int)json_object_get_number(responseObject, "code");

    //Get the Headers Array
    JSON_Array *headersArray = json_object_get_array(responseObject, "headers");
    FIDO_HEADERLIST *headers = FIDO_CREATE_HEADER_LIST();
    //For each header
    for (int i = 0; i< json_array_get_count(headersArray); i++)
    {
      //Get the raw header
      JSON_Object *rawHeader = json_array_get_object(headersArray, i);

      //Get the Key from the header
      buffer_t* keyBuffer = buffer_new();
      buffer_append(keyBuffer, json_object_get_name(rawHeader, 0));

      //Get the value from the header
      buffer_t* valueBuffer = buffer_new();
      buffer_append(valueBuffer, json_object_get_string(rawHeader, keyBuffer->data));

      //Create the FIDO Header Object
      FIDO_HEADER *h = FIDO_CREATE_HEADER(keyBuffer->data, valueBuffer->data);

      //Add the header to the list
      FIDO_ADD_HEADER(headers, h);

      //Clean Up
      buffer_free(keyBuffer);
      buffer_free(valueBuffer);
    }

    //Get the body as a sring.
    char* body = json_object_get_string(responseObject, "body");

    //Create the HTTP Response
    res = FIDO_CREATE_HTTP_RESPONSE(statusCode, body, headers);
  }

  //Will either return an empty res or a created res
  return res;
}


//HTTP POST for JS Fetch API
FIDO_HTTP_RESPONSE* FIDO_POST(FIDO_HTTP_REQUEST* req)
{
  //Create our initial res object
  FIDO_HTTP_RESPONSE *res;

  //Create an array for header conversion to string
  char* headersAsString = NULL;

  //If there is a header passed
  if(req->headers != 0)
  {
    //Stringify it.
    headersAsString = FIDO_JSONIFY_HEADERS(req->headers)->data;
  }

  //FIDO_FETCH always returns a string which is a stringified response from JS.
  char* rawResponse = FIDO_FETCH("POST", req->url, headersAsString, req->body);


  //Create a Parson Root
  JSON_Value *responseRoot = json_parse_string(rawResponse);

  if(json_value_get_type(responseRoot) == JSONObject)
  {
    //Convert Parson Value to JSON Object
    JSON_Object *responseObject = json_value_get_object(responseRoot);

    //Get the status code from the JSON.
    int statusCode = (int)json_object_get_number(responseObject, "code");

    //Get the Headers Array
    JSON_Array *headersArray = json_object_get_array(responseObject, "headers");
    FIDO_HEADERLIST *headers = FIDO_CREATE_HEADER_LIST();
    //For each header
    for (int i = 0; i< json_array_get_count(headersArray); i++)
    {
      //Get the raw header
	  JSON_Object *rawHeader = json_array_get_object(headersArray, i);

      //Get the Key from the header
      buffer_t* keyBuffer = buffer_new();
      buffer_append(keyBuffer, json_object_get_name(rawHeader, 0));

      //Get the value from the header
      buffer_t* valueBuffer = buffer_new();
      buffer_append(valueBuffer, json_object_get_string(rawHeader, keyBuffer->data));

      //Create the FIDO Header Object
      FIDO_HEADER *h = FIDO_CREATE_HEADER(keyBuffer->data, valueBuffer->data);

      //Add the header to the list
      FIDO_ADD_HEADER(headers, h);

      //Clean Up
      buffer_free(keyBuffer);
      buffer_free(valueBuffer);
    }

    //Get the body as a sring.
    char* body = json_object_get_string(responseObject, "body");

    //Create the HTTP Response
    res = FIDO_CREATE_HTTP_RESPONSE(statusCode, body, headers);
  }

  //Will either return an empty res or a created res
  return res;
}

//HTTP PATCH for JS Fetch API
FIDO_HTTP_RESPONSE* FIDO_PATCH(FIDO_HTTP_REQUEST* req)
{
  //Create our initial res object
  FIDO_HTTP_RESPONSE *res;

  //Create an array for header conversion to string
  char* headersAsString = NULL;

  //If there is a header passed
  if(req->headers != 0)
  {
    //Stringify it.
    headersAsString = FIDO_JSONIFY_HEADERS(req->headers)->data;
  }

  //FIDO_FETCH always returns a string which is a stringified response from JS.
  char* rawResponse = FIDO_FETCH("PATCH", req->url, headersAsString, req->body);


  //Create a Parson Root
  JSON_Value *responseRoot = json_parse_string(rawResponse);

  if(json_value_get_type(responseRoot) == JSONObject)
  {
    //Convert Parson Value to JSON Object
    JSON_Object *responseObject = json_value_get_object(responseRoot);

    //Get the status code from the JSON.
    int statusCode = (int)json_object_get_number(responseObject, "code");

    //Get the Headers Array
    JSON_Array *headersArray = json_object_get_array(responseObject, "headers");
    FIDO_HEADERLIST *headers = FIDO_CREATE_HEADER_LIST();
    //For each header
    for (int i = 0; i< json_array_get_count(headersArray); i++)
    {
      //Get the raw header
      JSON_Object *rawHeader = json_array_get_object(headersArray, i);

      //Get the Key from the header
      buffer_t* keyBuffer = buffer_new();
      buffer_append(keyBuffer, json_object_get_name(rawHeader, 0));

      //Get the value from the header
      buffer_t* valueBuffer = buffer_new();
      buffer_append(valueBuffer, json_object_get_string(rawHeader, keyBuffer->data));

      //Create the FIDO Header Object
      FIDO_HEADER *h = FIDO_CREATE_HEADER(keyBuffer->data, valueBuffer->data);

      //Add the header to the list
      FIDO_ADD_HEADER(headers, h);

      //Clean Up
      buffer_free(keyBuffer);
      buffer_free(valueBuffer);
    }

    //Get the body as a sring.
    char* body = json_object_get_string(responseObject, "body");

    //Create the HTTP Response
    res = FIDO_CREATE_HTTP_RESPONSE(statusCode, body, headers);
  }

  //Will either return an empty res or a created res
  return res;
}

//HTTP DELETE for JS Fetch API
FIDO_HTTP_RESPONSE* FIDO_DELETE(FIDO_HTTP_REQUEST* req)
{
  //Create our initial res object
  FIDO_HTTP_RESPONSE *res;

  //Create an array for header conversion to string
  char* headersAsString = NULL;

  //If there is a header passed
  if(req->headers != 0)
  {
    //Stringify it.
    headersAsString = FIDO_JSONIFY_HEADERS(req->headers)->data;
  }

  //FIDO_FETCH always returns a string which is a stringified response from JS.
  char* rawResponse = FIDO_FETCH("DELETE", req->url, headersAsString, req->body);

  //Create a Parson Root
  JSON_Value *responseRoot = json_parse_string(rawResponse);

  if(json_value_get_type(responseRoot) == JSONObject)
  {
    //Convert Parson Value to JSON Object
    JSON_Object *responseObject = json_value_get_object(responseRoot);

    //Get the status code from the JSON.
    int statusCode = (int)json_object_get_number(responseObject, "code");

    //Get the Headers Array
    JSON_Array *headersArray = json_object_get_array(responseObject, "headers");
    FIDO_HEADERLIST *headers = FIDO_CREATE_HEADER_LIST();
    //For each header
    for (int i = 0; i< json_array_get_count(headersArray); i++)
    {
      //Get the raw header
      JSON_Object *rawHeader = json_array_get_object(headersArray, i);

      //Get the Key from the header
      buffer_t* keyBuffer = buffer_new();
      buffer_append(keyBuffer, json_object_get_name(rawHeader, 0));

      //Get the value from the header
      buffer_t* valueBuffer = buffer_new();
      buffer_append(valueBuffer, json_object_get_string(rawHeader, keyBuffer->data));

      //Create the FIDO Header Object
      FIDO_HEADER *h = FIDO_CREATE_HEADER(keyBuffer->data, valueBuffer->data);

      //Add the header to the list
      FIDO_ADD_HEADER(headers, h);

      //Clean Up
      buffer_free(keyBuffer);
      buffer_free(valueBuffer);
    }

    //Get the body as a sring.
    char* body = json_object_get_string(responseObject, "body");

    //Create the HTTP Response
    res = FIDO_CREATE_HTTP_RESPONSE(statusCode, body, headers);
  }

  //Will either return an empty res or a created res
  return res;
}

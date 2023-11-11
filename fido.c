#include "fido.h"

#include <buffer/buffer.c>
#include <parson/parson.c>

#include "headers.c"
#include "request.c"
#include "response.c"

EM_ASYNC_JS(char*, FIDO_FETCH, (char *httpMethod, char *url, char *headers, char* body), {
  let init = {};//HTTP Init Object

  //If a method is supplied
  if (httpMethod)
  {
    init["method"] = UTF8ToString(httpMethod);//Set the method
  }
  else//if not return an error.
  {
    return allocate(intArrayFromString("HTTP_REQ_ERROR: No method specified."),ALLOC_NORMAL);
  }

  //If headers are supplied
  if (headers)
  {
    try {//Try to parse them into a json object.
      init["headers"] = JSON.parse(UTF8ToString(headers));
    }
    catch {
      //If parsing fails send an error
      return allocate(intArrayFromString("HTTP_REQ_ERROR: failed to parse header json."),ALLOC_NORMAL);
    }
  }

  //If a body is supplied
  if (body)
  {
    init["body"] = UTF8ToString(body);
  }

  //Call fetch
  let rawResponse = await fetch(UTF8ToString(url), init);

  //Iterate through the Headers and create a clean headers object
  let resHeaders = [];
  rawResponse.headers.forEach((value, key) => {
    let header = {};
    header[key] = value;
    resHeaders.push(header);
  });

  //Set the responseCode to the status which is a number. IE 200
  let responseCode = rawResponse.status;

  //Store the body as text
  let responseBody = await rawResponse.text();

  //Build our response object
  let responseObject = {};
  responseObject["code"] = responseCode;
  responseObject["headers"] = resHeaders;
  responseObject["body"] = responseBody;

  //Stringify it to send it back the FIDO_FETCH function.
  let responseString = JSON.stringify(responseObject);

  //Allocate the Memory in the LLVM stack and set it to the responseString
  return allocate(intArrayFromString(responseString),ALLOC_NORMAL);
});

//HTTP Get for JS Fetch API
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

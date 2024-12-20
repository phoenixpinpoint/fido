#include "fido.h"

#include <emscripten.h>

void FIDO_CLEAN()
{
	return;
}

EM_ASYNC_JS(char*, FIDO_FETCH, (char *httpMethod, char *url, char *headers, char* body), {
  let init = {};//HTTP Init Object
  init["headers"] = {};//HTTP Headers Object

  let buffer;

  //If a method is supplied
  if (httpMethod)
  {
    init["method"] = UTF8ToString(httpMethod);//Set the method
  }
  else//if not return an error.
  {  
  	let messageBuffer = intArrayFromString("HTTP_REQ_ERROR: Invalid or No method specified.");
	  let returnMessage = Module._malloc(2*messageBuffer.length);
	  Module.HEAPU8.set(messageBuffer, returnMessage);
   	return returnMessage;	
  }

  //If headers are supplied
  let castedHeaders = UTF8ToString(headers);
  if (castedHeaders && castedHeaders != "" && castedHeaders != "{}")
  {
    //let rawHeaders = await UTF8ToString(headers);
    let parsedHeaders = JSON.parse(castedHeaders);
    try {//Try to parse them into a json object.
        if(Array.isArray(parsedHeaders))
        {
          parsedHeaders.forEach((header) => {
            //console.log("JS Header: " + JSON.stringify(header));
            let key = Object.keys(header)[0];
            let value = header[key];
            let headerObject = {};
            headerObject[key] = value;
            //console.log("Key " + key + " Value: " + value);
            Object.assign(init["headers"], headerObject);
          });
        }
        else
        {
          init["headers"] = parsedHeaders;
        }
        
    }
    catch (e) {
      //If parsing fails send an error
      //This block should be a helper function in JS
      //console.log("JS: Error Parsing Headers: " + e); 
	    let messageBuffer = intArrayFromString("HTTP_REQ_ERROR: failed to parse header json.");
	    let returnMessage = Module._malloc(2*messageBuffer.length);
	    Module.HEAPU8.set(messageBuffer, returnMessage);
	    return returnMessage;
    }
  }

  //If a body is supplied
  if (body)
  {
    init["body"] = UTF8ToString(body);
  }

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
  //console.log(responseBody);

  //Build our response object
  let responseObject = {};
  responseObject["code"] = responseCode;
  responseObject["headers"] = resHeaders;
  responseObject["body"] = responseBody;

  //Stringify it to send it back the FIDO_FETCH function.
  let responseString = JSON.stringify(responseObject);

  //console.log(responseString);

  //Allocate the Memory in the LLVM stack and set it to the responseString
  responseString = intArrayFromString(responseString);
  let responseBuffer = Module._malloc(2*responseString.length);
  Module.HEAPU8.set(responseString, responseBuffer);
  return responseBuffer;
});

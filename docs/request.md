# requests
Fido requests symbolize a standard HTTP Request. It is composed of a url string, a body string and a Fido Headerlist.

## Data Structures
### FIDO_HTTP_REQUEST
```c
typedef struct FIDO_HTTP_REQUEST {
    char* url;          // URL of the endpoint
    char* body;         // Raw body as char array
    FIDO_HEADERLIST* headers;  // Request headers
} FIDO_HTTP_REQUEST;
```  
Just as with the Header structure we have a macro mapping.
```c
#ifndef HTTP_REQUEST
  typedef struct FIDO_HTTP_REQUEST HTTP_REQUEST;
#endif
```
You can remove this alias by either commenting out interfaces or adding the following to any file in the build path of Fido.
```c
#define HTTP_REQUEST
```

## Fido HTTP Request API
Request objects are created and managed through the following.
```c
//Create a new HTTP Request note: Assumes headers is a valid header list
FIDO_HTTP_REQUEST *req = FIDO_CREATE_HTTP_REQUEST("http://example.com", headers, NULL);

//You can set the body by
FIDO_HTTP_REQUEST_BODY(req, "SOME NEW BODY VALUE");

//You can change the url by
FIDO_HTTP_REQUEST_URL(req, "http://newexample.com");

//Clean up by
FIDO_FREE_HTTP_REQUEST(req);
```

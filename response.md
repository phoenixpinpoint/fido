# response
Fido responses symbolize a standard HTTP Response. It is composed of a response code, a body string and a Fido Headerlist.

## Data Structures
### FIDO_HTTP_RESPONSE
```c
typedef struct FIDO_HTTP_RESPONSE {
    int response_code;  // Response Code
    char* body;         // Raw body as char array
    FIDO_HEADERLIST* headers;       // String representation of header.
} FIDO_HTTP_RESPONSE;
```  
Just as with the Header structure we have a macro mapping.
```c
#ifndef HTTP_RESPONSE
  typedef struct FIDO_HTTP_RESPONSE HTTP_RESPONSE;
#endif
```
You can remove this alias by either commenting out interfaces or adding the following to any file in the build path of Fido.
```c
#define HTTP_RESPONSE
```
## Fido HTTP Response API
Response Objects are create using the following. This is typically done by the FETCH interfaces.
```c
//Create a new HTTP Response
FIDO_HTTP_RESPONSE *res = FIDO_CREATE_HTTP_RESPONSE(200, "RESPONSE SUCCESS.", headers);

//You can set the body by
FIDO_HTTP_RESPONSE_BODY(res, "SOME NEW BODY VALUE");

//Clean up by
FIDO_FREE_HTTP_RESPONSE(res);
```

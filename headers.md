
# headers
Fido Headers represent HTTP headers, simply a key value pair.
There are two structures that matter. One is the header itself and the other is a list

## Data Structures
### FIDO_HEADER
Fido Header is as single header object that stores a key string and value string.
```c
typedef struct FIDO_HEADER {
    char* key;
    char* value;
} FIDO_HEADER;
```  
Left to defaults there is also a mapping to HEADER
```c
#ifndef HEADER
  typedef struct FIDO_HEADER HEADER;
#endif
```
You can remove this alias by either commenting out interfaces or adding the following to any file in the build path of Fido.
```c
#define HEADER
```
### FIDO_HEADERLIST
Fido Headerlist is a simple list object of Fido Headers
```c
typedef struct FIDO_HEADERLIST {
    int length;
    FIDO_HEADER** headers;
} FIDO_HEADERLIST;
```
As with Fido Headers there is also a mapping to HEADERLIST
```c
#ifndef HEADERLIST
  typedef struct FIDO_HEADERLIST HEADERLIST;
#endif
```
And just like with HEADER if you want to ignore the alias add the following to any file in the Fido build path.
```c
#define HEADERLIST
```
## Fido Header API
All APIs have interfaces that remove FIDO from the front. Example: FIDO_CREATE_HEADER becomes CREATE_HEADER.
These interfaces can be negated by adding the same style define as the data structures.
```c
//Create A Header
FIDO_HEADER *header = FIDO_CREATE_HEADER("key", "value");

//Print A Header prints 'key:value'
printf("%s:%s\n", header->key, header->value);

//Update Key => newKey:value
FIDO_SET_KEY(header, "newKey");
//Update Value => newKey:newValue
FIDO_SET_VALUE(header, "newValue");

//Delete Header
FIDO_FREE_HEADER(header);
```
## Fido Headerlist API
Headrlists are an index array (list) of Header structures.
```c
//Create a new Header List
FIDO_HEADERLIST *list = FIDO_CREATE_HEADER_LIST();

//Add Header to List
FIDO_ADD_HEADER(list, header);

//Get Header by index
FIDO_HEADER *foundHeader = FIDO_GET_HEADER(list, 0);

//Get Header by Key
FIDO_HEADER *foundByKey = FIDO_GET_HEADER_BY_KEY(list, "newKey");

//Delete Header by index note: Does NOT Free the memory of the removed header
FIDO_REMOVE_HEADER(list, 0);

//Delete Header by key note: Does not Free the memory of the removed header
FIDO_REMOVE_HEADER_KEY(list, "newKey");
```

# Fido
Fido provides JS Fetch API bindings in C for use in WASM. Additionally Fido provides a simple Header, Request and, Response API.

## Installation & Running
### clibs Installation
Installing Fido is simple with clibs. This section assumes you have the deps folder added to your includ path.
```bash
clib install phoenixpinpoint/fido
```
Somewhere in your GCC Makefile/Buildpath:
```bash
-Ideps
```
In your C files:
```c
#include <fido/fido.h>
```
### manual Installation
Although not recommended it is possible to install Fido without clibs. The general idea is below but mileage may vary.
```bash
#Create Deps Folder
mkdir deps
cd deps
#Add Deps and Fido
git clone https://github.com/clibs/buffer.git
git clone https://github.com/phoenixpinpoint/fido.git
#Update compiler
gcc ..-Ideps..-Ideps/fido/src
```
### compilation and testing
This section only applies for the project as a standalone. Compiling Fido as a standalone project with emscripten.
```bash
make fido
```
Running with Node.js (Mostly for testing)
```bash
node fido
```
## Use
### Simple GET
In this example we make a simple GET to a Web Page.
```c
#include <fido/fido.h>

int main()
{
	//Note if all macros are left intact you can remove FIDO_
	FIDO_HTTP_REQUEST *req = FIDO_CREATE_HTTP_REQUEST("https://google.com", NULL, NULL);
	FIDO_HTTP_RESPONSE *res = FIDO_GET(req);

	//If the server response with 200 OK
	if(res->response_code == 200)
	{
		printf("BODY: %s\n", res->body);
	}
	else {
		printf("Some Error Occured.\n");
	}
	return 0;
}
```
### Simple POST
In this example we make a simple POST to a Web Page.
```c
#include <fido/fido.h>

int main()
{
	//Note if all macros are left intact you can remove FIDO_
	FIDO_HEADER *contentType = FIDO_CREATE_HEADER("Content-Type", "application/json");
	FIDO_HEADERLIST *headers = FIDO_CREATE_HEADER_LIST();
	FIDO_ADD_HEADER(headers, contentType);
	FIDO_HTTP_REQUEST *req = FIDO_CREATE_HTTP_REQUEST("https://example.com", headers, "{\"TEST\":\"VALUE\"}");
	FIDO_HTTP_RESPONSE *res = FIDO_POST(req);

	//If the server response with 200 OK
	if(res->response_code == 200)
	{
		printf("BODY: %s\n", res->body);
	}
	else {
		printf("Some Error Occured.\n");
	}
	return 0;
}
```
## Additional Docs
https://github.com/phoenixpinpoint/fido/tree/main/docs

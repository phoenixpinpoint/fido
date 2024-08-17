#include <fido.h>

int test_fido_no_method_check()
{
	char* result = FIDO_FETCH(NULL, "https://google.com", NULL, NULL);
	if (strcmp("HTTP_REQ_ERROR: Invalid or No method specified.", result) == 0)
	{
		return 0;
	}
	else {
		return -1;
	}
	free(result);
}

int test_fido_empty_string_header_object()
{
	char* result = FIDO_FETCH("GET", "https://google.com", "", NULL);
	if (strcmp("HTTP_REQ_ERROR: failed to parse header json.", result) == 0)
	{
		return 0;
	}
	else {
		return -1;
	}

	free(result);
}

int test_fido_empty_header_object()
{
	char* result = FIDO_FETCH("GET", "https://google.com", "{}", NULL);
	if(strcmp("HTTP_REQ_ERROR: failed to parse header json.", result) == 0)
	{
		return -1;
	}
	else {
		return 0;
	}
	free(result);
}

//Fetch needed for this test
int test_fido_get_check()
{
	char* result = FIDO_FETCH("GET", "https://google.com", NULL, NULL);
	if(strlen(result) > 100)//100 as picked based on most status codes in fido are less than 100 characters.
	{
		return 0;
	} else {
		return -1;
	}
}

int main(void)
{
	printf("FIDO WASM TESTS\n");
	printf("====================\n");
	printf("No Method Detection: %d\n", test_fido_no_method_check());
	printf("Empty String Header Test: %d\n", test_fido_empty_string_header_object());
	printf("Empty Header Test: %d\n", test_fido_empty_header_object());
	//printf("Fetch GET Check: %d\n", test_fido_get_check());

	return 0;
}

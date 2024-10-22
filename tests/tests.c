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
	FIDO_CLEAN();
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
	FIDO_CLEAN();
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
	FIDO_CLEAN();
}

//Fetch needed for this test
int test_fido_get_check()
{
	char* result = FIDO_FETCH("GET", "http://localhost:3000", NULL, NULL);
	JSON_Value* json = json_parse_string(result);
	JSON_Object* obj = json_value_get_object(json);
	char* status = json_object_get_string(obj, "code");
	if(strcmp(json_object_get_string(obj, "code"), "200") == 0)
	{
		return 0;
	} else {
		//printf("Returned Status Code: %s\n", status);
		return -1;
	}
	free(result);
	FIDO_CLEAN();
}

int test_fido_post_check()
{
	char* result = FIDO_FETCH("POST", "http://localhost:3000/simple", NULL, NULL);
	printf("Result: %s\n", result);
	if(strlen(result) > 1)//100 as picked based on most status codes in fido are less than 100 characters.
	{
		return 0;
	} else {
		return -1;
	}
	free(result);
	FIDO_CLEAN();
}


int main(void)
{
	printf("FIDO TESTS\n");
	printf("====================\n");
	printf("No Method Detection: %d\n", test_fido_no_method_check());
	printf("Empty String Header Test: %d\n", test_fido_empty_string_header_object());
	printf("Empty Header Test: %d\n", test_fido_empty_header_object());
	printf("GET Check: %d\n", test_fido_get_check());
	printf("POST Check: %d\n", test_fido_post_check());
	printf("GET Check 2: %d\n", test_fido_get_check());
	FIDO_CLEAN();	

	return 0;
}

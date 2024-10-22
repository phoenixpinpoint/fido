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
	printf("RES: %s\n", result);
	JSON_Value* json = json_parse_string(result);
	JSON_Object* obj = json_value_get_object(json);
	if(json_object_get_number(obj, "code") ==  200)
	{
		return 0;
	} else {
		return -1;
	}
	free(result);
	FIDO_CLEAN();
}

int test_fido_post_check()
{
	char* result = FIDO_FETCH("POST", "http://localhost:3000/simple", NULL, NULL);
	printf(result);
	JSON_Value* json = json_parse_string(result);
	JSON_Object* obj = json_value_get_object(json);
	if(json_object_get_number(obj, "code") ==  200)
	{
		return 0;
	} else {
		return -1;
	}
	free(result);
	FIDO_CLEAN();
}

int test_fido_post_400_check()
{
	char* result = FIDO_FETCH("POST", "http://localhost:3000/complex", NULL, NULL);
	printf("Result: %s\n", result);
	JSON_Value* json = json_parse_string(result);
	JSON_Object* obj = json_value_get_object(json);
	if(json_object_get_number(obj, "code") ==  400)
	{
		return 0;
	} else {
		return -1;
	}
	free(result);
	FIDO_CLEAN();
}

int test_fido_post_body()
{
	char* result = FIDO_FETCH("POST", "http://localhost:3000/complex", "{\"Content-Type\": \"application/json\"}", "{\"name\":\"John\"}");
	//printf("Result: %s\n", result);
	JSON_Value* json = json_parse_string(result);
	JSON_Object* obj = json_value_get_object(json);
	if(json_object_get_number(obj, "code") ==  200)
	{
		return 0;
	} else {
		return -1;
	}
	free(result);
	FIDO_CLEAN();
}

int test_fido_patch()
{
	char* result = FIDO_FETCH("PATCH", "http://localhost:3000/14", "{\"Content-Type\": \"application/json\"}", "{\"name\":\"John\"}");
	//printf("Result: %s\n", result);
	JSON_Value* json = json_parse_string(result);
	JSON_Object* obj = json_value_get_object(json);
	if(json_object_get_number(obj, "code") ==  200)
	{
		return 0;
	} else {
		return -1;
	}
	free(result);
	FIDO_CLEAN();
}

int test_fido_delete()
{
	char* result = FIDO_FETCH("DELETE", "http://localhost:3000/14", NULL, NULL);
	JSON_Value* json = json_parse_string(result);
	JSON_Object* obj = json_value_get_object(json);
	if(json_object_get_number(obj, "code") ==  200)
	{
		return 0;
	} else {
		return -1;
	}
	free(result);
	FIDO_CLEAN();
}

int test_fido_post_with_f_headers()
{
	FIDO_HEADER* header = FIDO_CREATE_HEADER("Content-Type", "application/json");
	FIDO_HEADERLIST* list = FIDO_CREATE_HEADER_LIST();
	FIDO_ADD_HEADER(list, header);
	char* result = FIDO_FETCH("POST", "http://localhost:3000/complex", FIDO_JSONIFY_HEADERS(list)->data, "{\"name\":\"John\"}");
	//printf("Result: %s\n", result);
	JSON_Value* json = json_parse_string(result);
	JSON_Object* obj = json_value_get_object(json);
	if(json_object_get_number(obj, "code") ==  200)
	{
		return 0;
	} else {
		return -1;
	}
}

int main(void)
{
	printf("FIDO TESTS\n");
	printf("====================\n");
	// printf("No Method Detection: %d\n", test_fido_no_method_check());
	// printf("Empty String Header Test: %d\n", test_fido_empty_string_header_object());
	// printf("Empty Header Test: %d\n", test_fido_empty_header_object());
	printf("GET Check: %d\n", test_fido_get_check());
	//printf("POST Check: %d\n", test_fido_post_check());
	// printf("GET Check 2: %d\n", test_fido_get_check());
	// printf("POST 400 Check: %d\n", test_fido_post_400_check());
	// printf("POST Body Check: %d\n", test_fido_post_body());
	// printf("PATCH Check: %d\n", test_fido_patch());
	// printf("DELETE Check: %d\n", test_fido_delete());
	// printf("POST Fido Headers: %d\n", test_fido_post_with_f_headers());
	FIDO_CLEAN();	

	return 0;
}

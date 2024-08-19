/*
* headers.c
* Copyright (c) 2023
* GNU GPLv3
*/

#include "headers.h"

//Create a New FIDO Header
FIDO_HEADER* FIDO_CREATE_HEADER(char* key, char* value)
{
    //Create an instance pointer.
    FIDO_HEADER *instance = (FIDO_HEADER*)malloc(sizeof(HEADER));

    //If Key is a valid value
    if (strlen(key) > 0)
    {
        instance->key = (char*)malloc(strlen(key)+1*sizeof(char));
        strncpy(instance->key, key, strlen(key)+1);
        instance->key[strlen(instance->key)] = '\0';
    }
    else {
        return (FIDO_HEADER*)-1;
    }

    //If Value is a valid value.
    if(strlen(value) > 0)
    {
        instance->value = (char*)malloc(strlen(value)+1*sizeof(char));
        strncpy(instance->value, value, strlen(value)+1);
        instance->value[strlen(instance->value)] = '\0';
    }
    else {
        return (FIDO_HEADER*)-1;
    }

    //Return the Resulting Pointer
    return instance;
}

//Frees Header Object
void FIDO_FREE_HEADER(FIDO_HEADER* h)
{
    if(h->key)
    {
        free(h->key);
    }
    if(h->value)
    {
        free(h->value);
    }
    if(h)
    {
        free(h);
    }
    return;
}

//Sets the Key of a FIDO Header
void FIDO_SET_KEY(FIDO_HEADER *h, char* key)
{
    // If there is key value free it.
    if(h->key)
    {
        free(h->key);
        h->key = 0;
    }

    //If there is a key value
    if(key)
    {
        h->key = (char*)malloc(strlen(key)+1*sizeof(char));
        strncpy(h->key, key, strlen(key)+1);
        h->key[strlen(h->key)] = '\0';
    }
    return;
}

//Sets the value of a FIDO Header
void FIDO_SET_VALUE(FIDO_HEADER *h, char* value)
{
    //If there is a value string free it
    if(h->value)
    {
        free(h->value);
        h->value = 0;
    }

    //Value passed to the function
    if(value)
    {
        h->value = (char*)malloc(strlen(value)+1*sizeof(char));
        strncpy(h->value, value, strlen(value)+1);
        h->value[strlen(h->value)] = '\0';
    }
}

//Creates a new Header List
FIDO_HEADERLIST* FIDO_CREATE_HEADER_LIST()
{
    //Create a new listInstance Object
    FIDO_HEADERLIST* listInstance = (FIDO_HEADERLIST*)malloc(sizeof(FIDO_HEADERLIST));
    listInstance->length = 0;
    listInstance->headers = 0;

    // Return the created list.
    return listInstance;
}

//Adds a new header to the passed list
void FIDO_ADD_HEADER(FIDO_HEADERLIST *list, FIDO_HEADER *header)
{
    //If first header
    if(list->length == 0)
    {
        list->headers = (FIDO_HEADER**)malloc(sizeof(FIDO_HEADER*));
        list->headers[0] = header;
        list->length = 1;
    }
    //If additional header
    else{
        list->headers = (FIDO_HEADER**)realloc(list->headers, (list->length+1)*sizeof(FIDO_HEADER*));
        list->headers[list->length] = header;
        list->length = list->length + 1;
    }

    return;
}

//Returns a Header from the passed headerlist at index
FIDO_HEADER* FIDO_GET_HEADER(FIDO_HEADERLIST *list, int index)
{
    if (list->headers[index])
    {
        return list->headers[index];
    }
    else
    {
        return 0;
    }
}

//Returns a header by a key value from the passed headerlist
FIDO_HEADER* FIDO_GET_HEADER_BY_KEY(FIDO_HEADERLIST *list, char* key)
{
    //If there are keys and headers
    if(strlen(key) > 0 && list->headers)
    {
        for(int iteration = 0; iteration < list->length; iteration++)
        {
            if(strcmp(list->headers[iteration]->key, key) == 0)
            {
                return list->headers[iteration];
            }
        }
    }
    else {
        return 0;
    }
    return (FIDO_HEADER*)-1;
}

//Removes a header from the passed list at index. DOES NOT FREE
void FIDO_REMOVE_HEADER(FIDO_HEADERLIST *list, int index)
{
    //Handle Single Header Arrays
    if (index == 0 && list->length == 1)
    {
        free(list->headers);
        list->headers = 0;
        list->length = 0;
    }

    else {
        //For each entry after index, move up one and finally reallocate the array.
        for (int iteration = index; iteration < list->length-1; iteration++)
        {
            list->headers[index] = list->headers[index+1];
        }

        list->length = list->length - 1;
        list->headers = (FIDO_HEADER**)realloc(list->headers, list->length*sizeof(FIDO_HEADER*));
    }

    return;
}

//Removes a header from a passed list at index by key, DOES NOT FREE
void FIDO_REMOVE_HEADER_BY_KEY(FIDO_HEADERLIST *list, char* key)
{
    int indexToRemove = FIDO_GET_HEADER_INDEX(list ,key);
    if(indexToRemove >= 0)
    {
        FIDO_REMOVE_HEADER(list, indexToRemove);
    }
}

//Returns a header index by key from a list.
int FIDO_GET_HEADER_INDEX(FIDO_HEADERLIST *list, char* key)
{
    //If there are keys and headers
    if(key && list->headers)
    {
        for(int iteration = 0; iteration < list->length-1; iteration++)
        {
            if(strcmp(list->headers[iteration]->key, key) == 0)
            {
                return iteration;
            }
        }
    }
    else {
        return -1;
    }
    return -1;
}

//Returns a JSON string of the header list.
buffer_t* FIDO_JSONIFY_HEADERS(FIDO_HEADERLIST *list)
{
  //All headers should be a key value pair of strings

  //Create a buffer to store the new JSON String
  buffer_t* jsonString = buffer_new();
  //Add our json object open
  buffer_append(jsonString, "{");
  //For each header in the header list
  for (int iteration = 0; iteration < list->length; iteration++)
  {
      buffer_append(jsonString, "\"");//create our first quote
      buffer_append(jsonString, list->headers[iteration]->key);//add the key
      buffer_append(jsonString, "\":\"");//add the closing quote for the key, the colon, and the openeing quote for the value
      buffer_append(jsonString, list->headers[iteration]->value);//add the value
      if(iteration != list->length-1)//If it is not the last item
      {
        buffer_append(jsonString, "\",");//add the closing quote and comma
      } else {//if it is the last item
        buffer_append(jsonString, "\"");//add only the closing quote
      }
  }
  buffer_append(jsonString, "}");//Add the closing brace
  return jsonString;//return the string
}

//Prints the list to stdout
void FIDO_PRINT_HEADER_LIST(FIDO_HEADERLIST *list)
{
    printf("PRINT_HEADER_LIST\n====================\n");
    for (int iteration = 0; iteration < list->length-1; iteration++)
    {
        printf("Index:%d, Key:*%s*, Value:*%s*\n", iteration, list->headers[iteration]->key, list->headers[iteration]->value);
    }
    printf("====================\n");
}

//Frees the list memory. DOES NOT FREE EACH HEADER
void FIDO_FREE_HEADER_LIST(FIDO_HEADERLIST *list)
{
    if (list->headers)
    {
        free(list->headers);
    }

    if (list)
    {
        free(list);
    }
}

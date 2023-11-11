headers:
	gcc -c -Ideps ./src/headers.c -o headers.o

request:
	gcc -c -Ideps ./src/request.c -o request.o

response:
	gcc -c -Ideps ./src/response.c -o response.o

fido:
	emcc -s EXPORTED_RUNTIME_METHODS=ccall,cwrap -s LINKABLE=1 -s EXPORT_ALL=1 -s ASYNCIFY -s DEFAULT_LIBRARY_FUNCS_TO_INCLUDE='$$allocate','$$intArrayFromString' -Ideps ./src/fido.c -o fido

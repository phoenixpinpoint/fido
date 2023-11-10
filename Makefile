headers:
	gcc -c headers.c -o headers.o

request:
	gcc -c request.c -o request.o

response:
	gcc -c response.c -o response.o

fido:
	emcc -s EXPORTED_RUNTIME_METHODS=ccall,cwrap -s LINKABLE=1 -s EXPORT_ALL=1 -s ASYNCIFY -s DEFAULT_LIBRARY_FUNCS_TO_INCLUDE='$$allocate','$$intArrayFromString' -Ideps ./fido.c -o fido

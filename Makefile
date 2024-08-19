test:
	emcc -s EXPORTED_RUNTIME_METHODS=intArrayFromString -s EXPORTED_FUNCTIONS=_main,_malloc -s EXPORT_ALL=1 -s ASYNCIFY -Ideps -Isrc ./survey.c ./src/fido.c ./src/headers.c ./src/request.c ./src/response.c ./tests/tests.c -o ./tests/tests.js; node ./tests/tests.js

ctest: 
	gcc -D USE_LIBCURL -Ideps -Isrc ./survey.c src/fido.c src/headers.c src/request.c src/response.c ./tests/tests.c -o ./tests/tests -lcurl; ./tests/tests

cvalgrind: 
	gcc -D USE_LIBCURL -Ideps -Isrc ./survey.c src/fido.c src/headers.c src/request.c src/response.c ./tests/tests.c -o ./tests/tests -lcurl; valgrind --leak-check=full --show-leak-kinds=all ./tests/tests


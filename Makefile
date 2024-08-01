test:
	emcc -s EXPORTED_RUNTIME_METHODS=intArrayFromString -s EXPORTED_FUNCTIONS=_main,_malloc -s EXPORT_ALL=1 -s ASYNCIFY -Ideps -Isrc ./survey.c ./src/fido.c ./src/headers.c ./src/request.c ./src/response.c ./tests/wasm/tests.c -o ./tests/wasm/tests.js; node ./tests/wasm/tests.js

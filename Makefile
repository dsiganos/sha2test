sha2test: sha2test.c
	gcc -o sha2test sha2test.c -lcrypto

run: sha2test
	./sha2test sha224
	./sha2test sha256
	./sha2test sha384
	./sha2test sha512

.PHONY: run

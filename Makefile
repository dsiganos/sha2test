sha2test: sha2test.c
	gcc -o sha2test sha2test.c -lcrypto

run: sha2test
	./sha2test sha224 & sleep 1; ./client.py
	./sha2test sha256 & sleep 1; ./client.py
	./sha2test sha384 & sleep 1; ./client.py
	./sha2test sha512 & sleep 1; ./client.py

.PHONY: run

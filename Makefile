sha2test: sha2test.c
	gcc -o sha2test sha2test.c -lcrypto

run: sha2test
	./sha2test & sleep 1; echo -n hello | ./client.py sha224
	./sha2test & sleep 1; echo -n hello | ./client.py sha256
	./sha2test & sleep 1; echo -n hello | ./client.py sha384
	./sha2test & sleep 1; echo -n hello | ./client.py sha512

.PHONY: run

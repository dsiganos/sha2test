sha2test: sha2test.c
	gcc -o sha2test sha2test.c -lcrypto

random.file: FORCE
	dd if=/dev/urandom of=random.file bs=1024 count=10240

run: sha2test random.file
	./sha2test & sleep 1; ./client.py sha224 127.0.0.1 < random.file
	./sha2test & sleep 1; ./client.py sha256 127.0.0.1 < random.file
	./sha2test & sleep 1; ./client.py sha384 127.0.0.1 < random.file
	./sha2test & sleep 1; ./client.py sha512 127.0.0.1 < random.file

FORCE:

.PHONY: FORCE run

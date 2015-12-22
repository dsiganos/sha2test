sha2test: sha2test.c
	gcc -o sha2test sha2test.c -lcrypto

random.file: FORCE
	dd if=/dev/urandom of=random.file bs=1024 count=10240

run: sha2test random.file
	./sha2test & sleep 1; ./client.py sha224 < random.file
	./sha2test & sleep 1; ./client.py sha256 < random.file
	./sha2test & sleep 1; ./client.py sha384 < random.file
	./sha2test & sleep 1; ./client.py sha512 < random.file

FORCE:

.PHONY: FORCE run

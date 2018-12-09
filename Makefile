
enc:
	gcc -Wall -std=c99 key.c encrypt.c -o encrypt
	gcc -Wall -std=c99 key.c brute.c -o brute
	gcc -Wall -std=c99 key.c hash.c decrypt.c -o decrypt
	


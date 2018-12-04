
enc:
	gcc -Wall key.c brute.c -o brute
	gcc -Wall key.c hash.c decrypt.c -o decrypt


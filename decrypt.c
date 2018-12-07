#include <stdlib.h>
#include <stdio.h>
#include "hash.h"

int main(int argc, char *argv[]) {
    Key encrypted;                 // A senha criptografada.
    Key T[N];                      // A tabela T.

    if (argc != 2) {
        fprintf(stderr, "Usage: ./encrypt [encrypted] < [table.txt]\n");
        exit(EXIT_FAILURE);
    }

    encrypted = init_key((unsigned char *) argv[1]);

    // Lê a tabela T.
    unsigned char buffer[C+1];     // Buffer temporário.
    iniciarHash();
    
    printf("iniciou hash\n");
    for (int i = 0; i < N; i++) {
        scanf("%s", buffer);
        T[i] = init_key(buffer);
    }
    printf("iniciou tabela\n");
    //for (int i = 0; i < N; i++) {
    crackingDecrypt(encrypted,T);
        //insereHash(T[i], T);
    //}
    //printf("inseriu na hash\n");
    procuraHash(encrypted);
    
    //destroiHash();
    
    return 0;
}

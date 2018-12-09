#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "key.h"

void cracking(Key k, Key T[N]);

int main(int argc, char *argv[]) {
    Key encrypted;                 // A senha criptografada.
    Key T[N];                      // A tabela T.

    if (argc != 2) {
        fprintf(stderr, "Usage: ./brute [encrypted] < [table.txt]\n");
        exit(EXIT_FAILURE);
    }

    encrypted = init_key((unsigned char *) argv[1]);

    // Lê a tabela T.
    unsigned char buffer[C+1];     // Buffer temporário.
    for (int i = 0; i < N; i++) {
        scanf("%s", buffer);
        T[i] = init_key(buffer);
    }
    cracking(encrypted, T);

    return 0;
}

// Verifica cada combinação da tabela (R^C) para encontrar a senha
void cracking(Key k, Key T[N]) {
    Key const1;
    for(int i = 0; i < C-1; i++){
        const1.digit[i] = 0;
    }const1.digit[C-1] = 1;
    Key sum = {{0}};
    long long int limite = 1;
    
    limite = pow(R,C);
    for(long long j = 0; j < limite; j++){
        Key pass = subset_sum(sum, T);
              
        if(compare(pass, k))
            print_key_char(sum);
        sum = add(sum, const1);
   }
   
}

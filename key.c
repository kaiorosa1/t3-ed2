#include <stdio.h>
#include "key.h"

// Inicializa e retorna uma chave a partir do vetor de char dado.
// Exemplo: s = "abcdwxyz"  =>  k = 0 1 2 3 22 23 24 25
Key init_key(unsigned char s[]) {
    // Converte cada char em um int no intervalo 0-31.
    Key k;
    for (int i = 0; i < C; i++) {
        for (int j = 0; j < R; j++) {
            if (s[i] == ALPHABET[j]) {
                k.digit[i] = j;
            }
        }
    }
    // Note que não há problema de retornar uma variável local aqui porque
    // a semântica do C para variáveis do tipo struct (não struct*) é fazer
    // uma cópia da struct inteira. Isso pode parecer ineficiente mas lembre
    // que o vetor da struct de chave é muito pequeno.
    return k;
}

// Exibe a chave 'k' em stdout em três formatos: chars, ints (base R) e binário.
void print_key(Key k) {
    for (int i = 0; i < C; i++) {
        printf("%c", ALPHABET[k.digit[i]]);
    }
    printf("  ");
    for (int i = 0; i < C; i++) {
        printf("%2d ", k.digit[i]);
    }
    printf("  ");
    for (int i = 0; i < N; i++) {
        printf("%d", bit(k, i));
    }
    printf("\n");
}

// Exibe a chave 'k' em stdout somente no formato de chars.
void print_key_char(Key k) {
    for (int i = 0; i < C; i++) {
        printf("%c", ALPHABET[k.digit[i]]);
    }
    printf("\n");
}

// Retorna o i-ésimo bit de k.
int bit(Key k, int i) {
    return (k.digit[i/B] >> (B - 1 - i % B)) & 1;
}

// Retorna a + b (mod 2^N) .
Key add(Key a, Key b) {
    Key c = {{0}};
    int carry = 0;
    for (int i = C-1; i >= 0; i--) {
        int sum = a.digit[i] + b.digit[i] + carry;
        c.digit[i] = sum  % R;
        carry      = sum >= R;
    }
    return c;
}

// Soma (módulo 2^N) e retorna o subconjunto dos inteiros T[i] que
// são indexados pelos bits de k.
Key subset_sum(Key k, Key T[N]) {
    Key sum = {{0}};
    for (int i = 0; i < N; i++) {
        if (bit(k, i)) {
            sum = add(sum, T[i]);
            //printf("%2d ", i);           // Para teste.
            //print_key(T[i]);             // Para teste.
        }
    }
   return sum;
}

// Retorna 1 para a sendo igual a b e 0 se forem diferentes.
int compare(Key a, Key b){
    for(int i = 0;i < C; i++){
        if(a.digit[i] != b.digit[i])
            return 0;
    }
    return 1;
}

// Retorna a - b (mod 2^N) .
Key sub(Key a, Key b) {
    Key c = {{0}};
    int carry = 0;
    for (int i = C-1; i >= 0; i--) {
        int sub = a.digit[i] - b.digit[i] + carry;
        if(c.digit[i] < 0)
            c.digit[i] = 0;
        c.digit[i] = sub  % R;
        carry      = sub < 0;
    }
    return c;
}


// Verifica cada combinação da tabela (R^C) para encontrar a senha
void cracking(Key k, Key T[N]) {
    Key const1;
    for(int i = 0; i < C-1; i++){
        const1.digit[i] = 0;
    }const1.digit[C-1] = 1;
    Key sum = {{0}};
    long long int limite = 1;
    for(int i = 0; i < C; i++){
        limite = limite * R;
    }
    for(long long j = 0; j < limite; j++){
        Key pass = subset_sum(sum, T);
        //print_key_char(pass);
        //print_key_char(sum);        
        if(compare(pass, k))
            print_key_char(sum);
        sum = add(sum, const1);
   }
}

//Retorna o valor único da Key
long long int returnKeyValue(Key a){
    long long int valor = a.digit[C-1];
    for(int i = C-2; i >= 0; i--){
        valor = (valor*R)+a.digit[i];
    }return valor;
}

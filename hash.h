#ifndef HASH_H
#define HASH_H

#include "key.h"

// Inicializa e retorna uma chave a partir do vetor de char dado.
// Exemplo: s = "abcdwxyz"  =>  k = 0 1 2 3 22 23 24 25
Key init_key(unsigned char s[]);

// Inicializa uma tabela de celulas de tamanho passado
// pelo parâmetro.
void iniciarHash();

// Insere o Item na tabela.
void insereHash(Key obj, Key T[N]);

// Procura a lista de Key que possuem a mesma chave de obj
// e imprime cada uma delas
void procuraHash(Key obj);

// Destroi a memoria alocada da hash
void destroiHash();

#endif

#include "hash.h"
#include <stdlib.h>
#include <stdio.h>

typedef struct {
    Key encrypt;
    Key decrypt;
}Keys;

typedef struct celula Celula;

struct celula{
    Keys obj;
    Celula* next;
};

// Tabela de celulas, variavel global
Celula** tab;
long long int tabTam;

long long int hash(Key obj){
    return returnKeyValue(obj)%tabTam;
}

// Inicializa uma tabela de celulas de tamanho passado
// pelo parâmetro.
void iniciarHash() 
{ 
    tabTam = 1;
    for(int i = 0; i < C-1; i++){
        tabTam = tabTam * R;
    } 
    tab = (Celula**) malloc(tabTam * sizeof (Celula*));
    for (int h = 0; h < tabTam; h++) 
        tab[h] = NULL;
}

// Insere o Item na tabela.
void insereHash(Key obj, Key T[N])
{ 
    long long int h;
    Keys chave;
    chave.decrypt = obj;
    chave.encrypt = subset_sum(obj, T);
    h = hash(chave.encrypt);
    Celula* novo = malloc(sizeof (Celula));
    novo->obj = chave;
    novo->next = tab[h];
    tab[h] = novo;
}

// Procura a lista de Key que possuem a mesma chave de obj
// e imprime cada uma delas
void procuraHash(Key obj) 
{ 
    Celula* t;
    long long int h;
    h = hash(obj);
    for (t = tab[h]; t != NULL; t = t->next) 
      if (compare(t->obj.encrypt ,obj)) print_key_char(t->obj.decrypt);
}

// Destroi a memoria alocada da hash
void destroiHash(){
    free(tab);
}

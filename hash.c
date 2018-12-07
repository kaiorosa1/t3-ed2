#include "hash.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

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
    tabTam = 199; //numero primo para numero de buckets - no caso o maximo de possibilidades de senha
    //tabTam = pow(R,C);
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
  
    for (t = tab[h]; t != NULL; t = t->next){
        if (compare(t->obj.encrypt ,obj)){
             print_key_char(t->obj.decrypt);
        }
        
    }
      
}

void crackingDecrypt(Key k, Key T[N]) {
    Key const1;
    for(int i = 0; i < C-1; i++){
        const1.digit[i] = 0;
    }const1.digit[C-1] = 1;
    Key sum = {{0}};
    long long int limite = 1;
    limite = pow(R,C);
    //for(int i = 0; i < C; i++){
    //    limite = limite * R; //here
    //}
    for(long long j = 0; j < limite; j++){
        Key pass = subset_sum(sum, T);
        //print_key_char(pass);
        
        //print_key_char(sum);        
        if(compare(pass, k)){
            insereHash(sum,T);
            //print_key_char(sum);
        }
        sum = add(sum, const1); // anda para a proxima chave 
   }
   printf("Finsihed!!!\n");
}

// Destroi a memoria alocada da hash
void destroiHash(){
    free(tab);
}

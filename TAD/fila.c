#include "fila.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void inserirAtendimento(filaAtendimento **fila, const char *cpf) {
    filaAtendimento *novo = malloc(sizeof(filaAtendimento));
    if (novo) {
        strcpy(novo->cpf, cpf);
        novo->prox = NULL;
        if ((*fila) == NULL) {
            (*fila) = novo;
        }else {
            novo = *fila;
            while (novo->prox) {
                novo = novo->prox;
            }
            novo->prox = novo;
        }
    }
    else {
        printf("Erro ao alocar memoria\n");
    }


}

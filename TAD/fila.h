#ifndef FILA_ATENDIMENTO_H
#define FILA_ATENDIMENTO_H

#include "tabela.h"

typedef struct filaAtendimento {
    char cpf[12];
    struct filaAtendimento *prox;
}filaAtendimento;



void inserirAtendimento(filaAtendimento **fila, const char *cpf);
filaAtendimento *removerAtendimento(filaAtendimento **fila);
void imprimirFila(filaAtendimento *fila, struct Tabela *tabela);


#endif //FILA_ATENDIMENTO_H

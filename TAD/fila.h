#ifndef FILA_ATENDIMENTO_H
#define FILA_ATENDIMENTO_H

typedef struct filaAtendimento {
    char cpf[12];
    struct filaAtendimento *prox;
}filaAtendimento;

void inserirAtendimento(filaAtendimento **fila, const char *cpf);



#endif //FILA_ATENDIMENTO_H

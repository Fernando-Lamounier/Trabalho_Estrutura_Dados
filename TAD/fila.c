#include "fila.h"
#include "tabela.h"

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

filaAtendimento *removerAtendimento(filaAtendimento **fila) {
    filaAtendimento *remover = NULL;

    if (*fila) {
        remover = *fila;
        *fila = remover->prox;
    }
    else {
        printf("Fila vazia\n");
    }
    return remover;
}

void imprimirFila(filaAtendimento *fila, struct Tabela *tabela) {
    Cliente *cliente = malloc(sizeof(Cliente));
    printf("--------FILA--------\n");
    while (fila) {
        buscaCliente(tabela, fila->cpf, cliente, 1);
        printf("CPF: %s | Nome: %s | Telefone: %s | Endereço: %s\n\n",
                   cliente->cpf_cnpj, cliente->nome, cliente->telefone, cliente->endereco);
    }
}
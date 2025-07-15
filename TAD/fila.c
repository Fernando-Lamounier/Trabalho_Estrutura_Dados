#include "fila.h"
#include "tabela.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

void inserirAtendimento(filaAtendimento **fila, const char *cpf) {

    filaAtendimento *novo = malloc(sizeof(filaAtendimento));
    if (novo) {
        strncpy(novo->cpf, cpf, sizeof(novo->cpf) - 1);
        novo->cpf[sizeof(novo->cpf) - 1] = '\0'; // Garante terminação nula
        novo->prox = NULL;

        if (*fila == NULL) {
            *fila = novo;
        } else {
            filaAtendimento *atual = *fila;
            while (atual->prox != NULL) {
                atual = atual->prox;
            }
            atual->prox = novo;
        }
    } else {
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
        buscaCliente(tabela, fila->cpf, cliente, NULL, 1);
        printf("CPF: %s | Nome: %s | Telefone: %s | Endereço: %s\n\n",
                   cliente->cpf, cliente->nome, cliente->telefone, cliente->endereco);
        fila = fila->prox;
    }
}
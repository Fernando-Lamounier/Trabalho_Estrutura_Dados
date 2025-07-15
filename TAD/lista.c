#include "lista.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

int verificarConflito(Agendamento *lista, const char *data, const char *hora) {
    while (lista != NULL) {
        if (strcmp(lista->data, data) == 0 && strcmp(lista->hora, hora) == 0 && strcmp(lista->status, "Agendado") == 0) {
            return 1;  // Conflito encontrado
        }
        lista = lista->prox;
    }
    return 0;  // Nenhum conflito
}

Agendamento* criarLista() {
    return NULL;
}

Agendamento* agendar(Agendamento *lista, const char *cpf, const char *data, const char *hora, const char *tipoServico,
                     const char *status) {

    // Cria novo agendamento
    Agendamento *novo = (Agendamento *) malloc(sizeof(Agendamento));
    if (!novo) {
        printf("Erro ao alocar memória.\n");
        return lista;
    }

    strcpy(novo->cpf, cpf);
    strcpy(novo->data, data);
    strcpy(novo->hora, hora);
    strcpy(novo->tipoServico, tipoServico);
    strcpy(novo->status, status);
    novo->prox = NULL;

    // Insere no final da lista
    if (lista == NULL) {
        return novo;  // Lista estava vazia
    } else {
        Agendamento *temp = lista;
        while (temp->prox != NULL)
            temp = temp->prox;
        temp->prox = novo;

        return lista;
    }
}

void visualizarAgendamentos(Agendamento *lista, const char *cpf) {
    int encontrou = 0;

    clock_t inicio = clock();
    printf("Resultado da busca:\n");
    while (lista != NULL) {
        if (strcmp(lista->cpf, cpf) == 0) {
            printf("CPF: %s | Data: %s | Hora: %s | Serviço: %s | Status: %s\n",
                   lista->cpf, lista->data, lista->hora, lista->tipoServico, lista->status);
            encontrou = 1;
        }
        lista = lista->prox;
        clock_t final = clock();
        double tempo = (double) (final - inicio)/CLOCKS_PER_SEC;
        printf("\nTempo para visualização: %f\n",tempo);
    }

    if (!encontrou) {
        printf("Nenhum agendamento encontrado para o CPF %s.\n", cpf);
    }
}

Agendamento* atualizarStatus(Agendamento *lista, const char *cpf, const char *data, const char *hora, const char *novoStatus) {
    Agendamento *atual = lista;

    while (atual != NULL) {
        if (strcmp(atual->cpf, cpf) == 0 && strcmp(atual->data, data) == 0 && strcmp(atual->hora, hora) == 0 && strcmp(atual->status, "Agendado") == 0) {
            strcpy(atual->status, novoStatus);
            printf("Serviço %s com sucesso.\n", novoStatus);
            return lista;
        }
        atual = atual->prox;
    }

    printf("Agendamento não encontrado.\n");
    return lista;
}

void liberarLista(Agendamento *lista) {
    Agendamento *tmp;
    while (lista != NULL) {
        tmp = lista;
        lista = lista->prox;
        free(tmp);
    }
}

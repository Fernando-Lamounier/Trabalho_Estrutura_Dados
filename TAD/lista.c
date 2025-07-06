#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lista.h"

Agendamento* criarLista() {
    return NULL;
}

Agendamento* agendar(Agendamento *lista, const char *cpf, const char *data, const char *hora, const char *tipoServico) {
    Agendamento *novo = (Agendamento *) malloc(sizeof(Agendamento));
    if (!novo) {
        printf("Erro ao alocar memória.\n");
        return lista;
    }

    strcpy(novo->cpf, cpf);
    strcpy(novo->data, data);
    strcpy(novo->hora, hora);
    strcpy(novo->tipoServico, tipoServico);
    strcpy(novo->status, "Agendado");
    novo->prox = lista;

    return novo; // novo início da lista
}

void visualizarAgendamentos(Agendamento *lista, const char *cpf) {
    int encontrou = 0;
    while (lista != NULL) {
        if (strcmp(lista->cpf, cpf) == 0) {
            printf("CPF: %s | Data: %s | Hora: %s | Serviço: %s | Status: %s\n",
                   lista->cpf, lista->data, lista->hora, lista->tipoServico, lista->status);
            encontrou = 1;
        }
        lista = lista->prox;
    }

    if (!encontrou) {
        printf("Nenhum agendamento encontrado para o CPF %s.\n", cpf);
    }
}

Agendamento* cancelarAgendamento(Agendamento *lista, const char *cpf, const char *data, const char *hora) {
    Agendamento *atual = lista;

    while (atual != NULL) {
        if (strcmp(atual->cpf, cpf) == 0 && strcmp(atual->data, data) == 0 && strcmp(atual->hora, hora) == 0) {
            strcpy(atual->status, "Cancelado");
            printf("Agendamento cancelado com sucesso.\n");
            return lista;
        }
        atual = atual->prox;
    }

    printf("Agendamento não encontrado.\n");
    return lista;
}

Agendamento* atualizarStatus(Agendamento *lista, const char *cpf, const char *data, const char *hora, const char *novoStatus) {
    Agendamento *atual = lista;

    while (atual != NULL) {
        if (strcmp(atual->cpf, cpf) == 0 && strcmp(atual->data, data) == 0 && strcmp(atual->hora, hora) == 0) {
            strcpy(atual->status, novoStatus);
            printf("Status atualizado com sucesso.\n");
            return lista;
        }
        atual = atual->prox;
    }

    printf("Agendamento não encontrado para atualizar status.\n");
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

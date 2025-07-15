#include "pilha.h"
#include "tabela.h"
#include "agendamento.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>


void inicializarPilha(HistoricoAtendimento *pilha) {
    pilha->topo = NULL;
}

void pushAtendimento(HistoricoAtendimento *pilha, Historico *dado) {

    NoPilha *novo = malloc(sizeof(NoPilha));
    if (!novo) {
        fprintf(stderr, "Erro ao alocar memória para nó da pilha.\n");
        return;
    }
    Historico *copia = malloc(sizeof(Historico));
    if (!copia) {
        fprintf(stderr, "Erro ao alocar memória para histórico.\n");
        free(novo);
        return;
    }
    *copia = *dado;
    novo->dado = copia;
    novo->prox = pilha->topo;
    pilha->topo = novo;

}


void visualizarHistorico(struct Tabela *tabela) {
    clock_t inicio = clock();
    Cliente *busca = malloc(sizeof(Cliente));
    char cpf[12];

    while (getchar() != '\n');
    printf("Digite o CPF do Cliente (somente números): ");
    fgets(cpf, sizeof(cpf), stdin);
    cpf[strcspn(cpf, "\n")] = '\0';

    if (!validarCPF(cpf)) {
        printf("Erro: CPF inválido. (Ausência de números ou retire caracteres especiais [pontos e traços])\n");
        free(busca);
        return;
    }

    if (buscaCliente(tabela, cpf, busca, 1)) {
        if (busca->historico.topo == NULL) {
            printf("Sem atendimentos concluídos.\n");
            free(busca);
            return;
        }


        NoPilha *atual = busca->historico.topo;
        int count = 1;

        while (atual) {
            printf("\nAtendimento %d:\n", count++);
            printf("Data: %s\n", atual->dado->data);
            printf("Hora: %s\n", atual->dado->hora);
            printf("Tipo de Serviço: %s\n", atual->dado->tipoServico);
            printf("Observações: %s\n", atual->dado->observacoes);
            atual = atual->prox;
        }
    }

    clock_t final = clock();
    double tempo = (double) (final - inicio)/CLOCKS_PER_SEC;
    printf("\nTempo para visualizar: %f\n",tempo);

}

void liberarPilha(HistoricoAtendimento *pilha) {
    NoPilha *atual = pilha->topo;
    while (atual) {
        NoPilha *temp = atual;
        atual = atual->prox;
        free(temp);
    }
    pilha->topo = NULL;
}


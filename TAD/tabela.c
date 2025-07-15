#include "tabela.h"
#include "lista.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>



TabelaCliente* criarTabelaCliente(int tamanhoTabela) {
    TabelaCliente* tabela = (TabelaCliente*)malloc(sizeof(TabelaCliente));

    if(tabela != NULL) {
        int i;

        tabela->tamanhoTabela = tamanhoTabela;
        tabela->clientes = (Cliente**)malloc(tamanhoTabela * sizeof(Cliente*));
        if(tabela->clientes == NULL) {
            free(tabela);
            return NULL;
        }
        tabela->qtd = 0;
        for(i = 0; i < tabela->tamanhoTabela; i++) {
            tabela->clientes[i] = NULL;
        }
    }
    return tabela;
}

int chaveDivisao (long int chave, int tamanhoTabela) {
    return (chave & 0x7FFFFFFF) % tamanhoTabela;
}

int chaveMultiplicacao (long int chave, int tamanhoTabela) {
    float A = 0.6180339887;
    float valorChave = chave * A;

    valorChave = valorChave - (int)A;

    return (int)(tamanhoTabela*valorChave);
}

long int valorChaveCPF(const char *cpf) {
    int i;
    long int valor = 0;
    int tamanho = strlen(cpf);

    for(i = 0; i < tamanho; i++) {
        valor = 7 * valor + (int)cpf[i];
    }
    return valor;
}

int insereCliente (TabelaCliente *tabela, Cliente *cliente) {

    clock_t inicio = clock();
    if (tabela->qtd == tabela->tamanhoTabela || tabela == NULL) {
        return 0;
    }
    long int chave = valorChaveCPF(cliente->cpf);
    int novaPosicao;
    int posicao = chaveDivisao(chave, tabela->tamanhoTabela);

    for (int i = 0; i < tabela->tamanhoTabela; i++) {
        novaPosicao = duplaInsercaoCliente(posicao, chave, i, tabela->tamanhoTabela);
        if (tabela->clientes[novaPosicao] == NULL) {

            Cliente *copia = malloc(sizeof(Cliente));
            if (copia == NULL) return 0;
            *copia = *cliente;
            inicializarPilha((HistoricoAtendimento *) &copia->historico);

            tabela->clientes[novaPosicao] = copia;
            tabela->qtd++;
            printf("Cliente %s inserido com sucesso", tabela->clientes[novaPosicao]->cpf);

            clock_t final = clock();
            double tempo = (double) (final - inicio)/CLOCKS_PER_SEC;
            printf("\nTempo para inserção: %f\n",tempo);

            return 1;
        }
        if (strcmp(tabela->clientes[novaPosicao]->cpf, cliente->cpf) == 0) {
            printf("Esse cpf ja esta sendo utilizado");
            return 0;
        }

    }
    return 0;
}

int duplaInsercaoCliente (int posicao1, long int chave, int i, int tamanhoTabela) {
    int posicao2 = chaveDivisao(chave, tamanhoTabela - 1) + 1;
    return ((posicao1 + i*posicao2) & 0x7FFFFFFF) % tamanhoTabela;
}


int buscaCliente(struct Tabela *tabela, const char *cpf, Cliente *cliente, Agendamento *lista, int tipo) {

    long int chave = valorChaveCPF(cpf);
    int novaPosicao;

    int posicao = chaveDivisao(chave, tabela->tamanhoTabela);

    for (int i = 0; i < tabela->tamanhoTabela; i++) {
        novaPosicao = duplaInsercaoCliente(posicao, chave, i, tabela->tamanhoTabela);
        if (tabela->clientes[novaPosicao] == NULL) {
            break;
        }
        if (strcmp(tabela->clientes[novaPosicao]->cpf, cpf) == 0) {
            switch (tipo){
                case 1:
                    *cliente = *(tabela->clientes[novaPosicao]);
                    return 1;
                case 2:
                    *(tabela->clientes[novaPosicao]) = *cliente;
                    return 1;
                case 3:
                    while (lista != NULL) {
                        if (strcmp(lista->cpf, tabela->clientes[novaPosicao]->cpf) == 0) {
                            printf("Cliente com agendamento pendente!\n\n");
                            return 0;
                        }
                        lista = lista->prox;
                    }
                    tabela->clientes[novaPosicao] = NULL;
                    return 1;
                default:
                    return 1;
            }
        }
    }
    return 0;
}

void listarCliente(TabelaCliente *tabela, const char *cpf) {
    Cliente *cliente;
    cliente = malloc(sizeof(Cliente));

    clock_t inicio = clock();
    if (buscaCliente(tabela, cpf, cliente, NULL, 1)) {
        printf("CPF: %s | Nome: %s | Telefone: %s | Endereço: %s\n",
                   cliente->cpf, cliente->nome, cliente->telefone, cliente->endereco);
        free(cliente);

        clock_t final = clock();
        double tempo = (double) (final - inicio)/CLOCKS_PER_SEC;
        printf("\nTempo para busca: %f\n",tempo);

        return;
    }

    printf("Nenhum cliente encontrado para o CPF %s.\n", cpf);

}

void atualizarCliente(struct Tabela *tabela, const char *cpf, Historico *dado, int opcao) {
    Cliente *cliente = malloc(sizeof(Cliente));
    if (!cliente) {
        fprintf(stderr, "Erro de alocação\n");
        return;
    }

    if (buscaCliente(tabela, cpf, cliente, NULL, 1)) {
        if (opcao != 4) {
            printf("Cliente encontrado para o CPF %s.\n", cpf);

            printf("Novo nome do cliente: ");
            scanf("%s", cliente->nome);

            printf("Novo endereço do cliente: ");
            scanf("%s", cliente->endereco);

            printf("Novo telefone: ");
            scanf("%s", cliente->telefone);

            buscaCliente(tabela, cpf, cliente, NULL, 2);
        } else {
            // Adiciona o histórico diretamente
            pushAtendimento(&cliente->historico, dado);
            // Atualiza o cliente na tabela
            buscaCliente(tabela, cpf, cliente, NULL, 2);
        }
        free(cliente);
        return;
    }

    printf("Nenhum cliente encontrado para o CPF %s.\n", cpf);
    free(cliente);
}

void removerCliente(TabelaCliente *tabela, Agendamento *lista, const char *cpf_cnpj) {

    clock_t inicio = clock();
    if (buscaCliente(tabela, cpf_cnpj, NULL, lista, 3)) {
        printf("Cliente removido com sucesso!!");

        clock_t final = clock();
        double tempo = (double) (final - inicio)/CLOCKS_PER_SEC;
        printf("\nTempo para remoção: %f\n",tempo);
    }

}

void liberarTabelaCliente(TabelaCliente *tabela){
    if (tabela != NULL) {
        int i;
        for (i = 0; i < tabela->tamanhoTabela; i++) {
            if (tabela->clientes[i] != NULL) {
                free(tabela->clientes[i]);
            }
        }
        free(tabela->clientes);
        free(tabela);
    }
}



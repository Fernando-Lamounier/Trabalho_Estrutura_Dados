#include "tabela.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>



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


int buscaCliente(struct Tabela *tabela, const char *cpf, Cliente *cliente, int tipo) {

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

    if (buscaCliente(tabela, cpf, cliente, 1)) {
        printf("CPF: %s | Nome: %s | Telefone: %s | Endereço: %s\n",
                   cliente->cpf, cliente->nome, cliente->telefone, cliente->endereco);
        free(cliente);
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

    if (buscaCliente(tabela, cpf, cliente, 1)) {
        if (opcao != 4) {
            printf("Cliente encontrado para o CPF %s.\n", cpf);

            printf("Novo nome do cliente: ");
            scanf("%s", cliente->nome);

            printf("Novo endereço do cliente: ");
            scanf("%s", cliente->endereco);

            printf("Novo telefone: ");
            scanf("%s", cliente->telefone);

            buscaCliente(tabela, cpf, cliente, 2);
        } else {
            // Adiciona o histórico diretamente
            pushAtendimento(&cliente->historico, dado);
            // Atualiza o cliente na tabela
            buscaCliente(tabela, cpf, cliente, 2);
        }
        free(cliente);
        return;
    }

    printf("Nenhum cliente encontrado para o CPF %s.\n", cpf);
    free(cliente);
}

void removerCliente(TabelaCliente *tabela, const char *cpf_cnpj) {

    if (buscaCliente(tabela, cpf_cnpj, NULL, 3)) {
        printf("Cliente removido com sucesso!!");
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



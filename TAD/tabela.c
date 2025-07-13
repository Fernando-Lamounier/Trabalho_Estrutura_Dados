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

long int valorChaveCPF(const char *cpf_cnpj) {
    int i;
    long int valor = 0;
    int tamanho = strlen(cpf_cnpj);

    for(i = 0; i < tamanho; i++) {
        valor = 7 * valor + (int)cpf_cnpj[i];
    }
    return valor;
}

int insereCliente (TabelaCliente *tabela, Cliente *cliente) {
    
    if (tabela->qtd == tabela->tamanhoTabela || tabela == NULL) {
        return 0;
    }
    long int chave = valorChaveCPF(cliente->cpf_cnpj);
    int novaPosicao;
    int posicao = chaveDivisao(chave, tabela->tamanhoTabela);

    for (int i = 0; i < tabela->tamanhoTabela; i++) {
        novaPosicao = duplaInsercaoCliente(posicao, chave, i, tabela->tamanhoTabela);
        if (tabela->clientes[novaPosicao] == NULL) {

            Cliente *copia = malloc(sizeof(Cliente));
            if (copia == NULL) return 0;
            *copia = *cliente;

            tabela->clientes[novaPosicao] = copia;

            tabela->qtd++;
            return 1;
        }
    }
    return 0;
}

int duplaInsercaoCliente (int posicao1, long int chave, int i, int tamanhoTabela) {
    int posicao2 = chaveDivisao(chave, tamanhoTabela - 1) + 1;
    return ((posicao1 + i*posicao2) & 0x7FFFFFFF) % tamanhoTabela;
}

int buscaCliente(TabelaCliente *tabela, const char *cpf_cnpj, Cliente *cliente, int tipo) {

    long int chave = valorChaveCPF(cpf_cnpj);
    int novaPosicao;

    int posicao = chaveDivisao(chave, tabela->tamanhoTabela);

    for (int i = 0; i < tabela->tamanhoTabela; i++) {
        novaPosicao = duplaInsercaoCliente(posicao, chave, i, tabela->tamanhoTabela);
        if (tabela->clientes[novaPosicao] == NULL) {
            break;
        }
        if (strcmp(tabela->clientes[novaPosicao]->cpf_cnpj, cpf_cnpj) == 0) {
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

void listarCliente(TabelaCliente *tabela, const char *cpf_cnpj) {
    Cliente *cliente;
    cliente = malloc(sizeof(Cliente));

    if (buscaCliente(tabela, cpf_cnpj, cliente, 1)) {
        printf("CPF: %s | Nome: %s | Telefone: %s | Endereço: %s\n",
                   cliente->cpf_cnpj, cliente->nome, cliente->telefone, cliente->endereco);
        free(cliente);
        return;
    }

    printf("Nenhum cliente encontrado para o CPF %s.\n", cpf_cnpj);

}

void atualizarCliente(TabelaCliente *tabela, const char *cpf_cnpj) {
    Cliente *cliente;
    cliente = (struct Cliente*)malloc(sizeof(struct Cliente));

    if (buscaCliente(tabela, cpf_cnpj, cliente, 1)) {
        printf("Cliente encontrado para o CPF %s.\n", cpf_cnpj);

        printf("Novo nome do cliente: ");
        scanf("%s", cliente->nome);

        printf("Novo endereço do cliente: ");
        scanf("%s", cliente->endereco);

        printf("Novo telefone: ");
        scanf("%s", cliente->telefone);

        buscaCliente(tabela, cpf_cnpj, cliente, 2);
    }

    printf("Nenhum cliente encontrado para o CPF %s.\n", cpf_cnpj);
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



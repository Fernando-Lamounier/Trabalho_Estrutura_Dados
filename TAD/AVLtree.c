#include "AVLtree.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

NoAVL* criarArvore() {
    return NULL;
}

// Função utilitárias
int max(int a, int b) {
    return (a > b) ? a : b;
}

int altura(NoAVL* no) {
    return no ? no->altura : 0;
}

int fatorBalanceamento(NoAVL* no) {
    return no ? altura(no->esquerda) - altura(no->direita) : 0;
}

NoAVL* rotacaoDireita(NoAVL* y) {
    NoAVL* x = y->esquerda;
    NoAVL* T2 = x->direita;

    x->direita = y;
    y->esquerda = T2;

    y->altura = max(altura(y->esquerda), altura(y->direita)) + 1;
    x->altura = max(altura(x->esquerda), altura(x->direita)) + 1;

    return x;
}

NoAVL* rotacaoEsquerda(NoAVL* x) {
    NoAVL* y = x->direita;
    NoAVL* T2 = y->esquerda;

    y->esquerda = x;
    x->direita = T2;

    x->altura = max(altura(x->esquerda), altura(x->direita)) + 1;
    y->altura = max(altura(y->esquerda), altura(y->direita)) + 1;

    return y;
}

NoAVL* criarNo(Servico servico) {
    NoAVL* novo = (NoAVL*)malloc(sizeof(NoAVL));
    if (!novo) {
        fprintf(stderr, "Erro ao alocar memória\n");
        exit(1);
    }
    novo->servico = servico;
    novo->esquerda = novo->direita = NULL;
    novo->altura = 1;
    return novo;
}

int inserirServico(NoAVL **raiz, Servico servico) {
    if (*raiz == NULL) {
        *raiz = criarNo(servico);
        return 1; // Inserção OK
    }

    int cmp = strcmp(servico.nome, (*raiz)->servico.nome);
    if (cmp == 0) {
        return 0; // Já existe, não insere
    } else if (cmp < 0) {
        if (!inserirServico(&((*raiz)->esquerda), servico))
            return 0;
    } else {
        if (!inserirServico(&((*raiz)->direita), servico))
            return 0;
    }

    // Atualiza altura e balanceia a árvore
    (*raiz)->altura = 1 + max(altura((*raiz)->esquerda), altura((*raiz)->direita));
    int balance = fatorBalanceamento(*raiz);

    // Rotação Left Left
    if (balance > 1 && strcmp(servico.nome, (*raiz)->esquerda->servico.nome) < 0)
        *raiz = rotacaoDireita(*raiz);

        // Rotação Right Right
    else if (balance < -1 && strcmp(servico.nome, (*raiz)->direita->servico.nome) > 0)
        *raiz = rotacaoEsquerda(*raiz);

        // Rotação Left Right
    else if (balance > 1 && strcmp(servico.nome, (*raiz)->esquerda->servico.nome) > 0) {
        (*raiz)->esquerda = rotacaoEsquerda((*raiz)->esquerda);
        *raiz = rotacaoDireita(*raiz);
    }

        // Rotação Right Left
    else if (balance < -1 && strcmp(servico.nome, (*raiz)->direita->servico.nome) < 0) {
        (*raiz)->direita = rotacaoDireita((*raiz)->direita);
        *raiz = rotacaoEsquerda(*raiz);
    }

    return 1; // Inserção OK
}

NoAVL* buscarServico(NoAVL* raiz, const char* nome, int opcao) {
        if (raiz == NULL) {
            printf("\n--- Resultado da busca ---\n");
            printf("Serviço '%s' não encontrado.\n", nome);
            return NULL;
        }

        int cmp = strcmp(nome, raiz->servico.nome);
        if (cmp == 0) {
            if (opcao == 2) {
                printf("\n--- Resultado da busca ---\n");
                printf("Nome: %s\n", raiz->servico.nome);
                printf("Descrição: %s\n", raiz->servico.descricao);
                printf("Preço Médio: R$ %.2f\n", raiz->servico.precoMedio);
            }
            return raiz;
        }
        else if (cmp < 0) {
            if (opcao == 0) {
                return buscarServico(raiz->esquerda, nome, 0);
            } else {
                return buscarServico(raiz->esquerda, nome, 2);
            }
        }
        else {
            if (opcao == 0) {
                return buscarServico(raiz->direita, nome, 0);
            } else {
                return buscarServico(raiz->direita, nome, 2);
            }
        }
}


void listarServicos(NoAVL* raiz) {
    if (raiz == NULL) {
        printf("Relatório Vazio\n");
        return;
    }

    printf("=== RELATÓRIO DE SERVIÇOS ===\n\n");
    listarServicosAux(raiz);
}

void listarServicosAux(NoAVL* raiz) {
    if (raiz == NULL) return;

    listarServicosAux(raiz->esquerda);
    printf("Nome: %s\nDescrição: %s\nPreço Médio: R$ %.2f\n\n",
           raiz->servico.nome,
           raiz->servico.descricao,
           raiz->servico.precoMedio);
    listarServicosAux(raiz->direita);
}

void liberarArvore(NoAVL* raiz) {
    if (raiz == NULL)
        return;
    liberarArvore(raiz->esquerda);
    liberarArvore(raiz->direita);
    free(raiz);
}

#ifndef TRABALHO_ESTRUTURA_DADOS_AVLTREE_H
#define TRABALHO_ESTRUTURA_DADOS_AVLTREE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Servico {
    char nome[50];
    char descricao[200];
    float precoMedio;
} Servico;

typedef struct NoAVL {
    Servico servico;
    struct NoAVL *esquerda;
    struct NoAVL *direita;
    int altura;
} NoAVL;

// Funções principais
NoAVL* criarArvore();
int inserirServico(NoAVL **raiz, Servico servico);
NoAVL* buscarServico(NoAVL* raiz, const char* nome, int opcao);
void listarServicos(NoAVL* raiz);
void listarServicosAux(NoAVL* raiz);
void liberarArvore(NoAVL* raiz);

#endif //TRABALHO_ESTRUTURA_DADOS_AVLTREE_H

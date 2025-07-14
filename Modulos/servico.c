#include "servico.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void pegarDadosServico (NoAVL **raiz) {
    Servico *novo = malloc(sizeof(Servico));
    if (!novo) {
        fprintf(stderr, "Erro de alocação\n");
        return;
    }

    printf("Digite o nome do Serviço: ");
    fgets(novo->nome, sizeof(novo->nome), stdin);
    novo->nome[strcspn(novo->nome, "\n")] = '\0';

    printf("Digite a Descrição do Serviço: ");
    fgets(novo->descricao, sizeof(novo->descricao), stdin);
    novo->descricao[strcspn(novo->descricao, "\n")] = '\0';

    printf("Digite o Preço do Serviço: ");
    scanf("%f", &novo->precoMedio);
    while (getchar()!= '\n');

    if (inserirServico(raiz, *novo))
        printf("Serviço inserido com sucesso!\n");
    else
        printf("Erro: Serviço com esse nome já existe!\n");

    free(novo);
}

void pegarNome (NoAVL *raiz) {
    char nome[50];
    printf("Digite o nome do Serviço: ");
    fgets(nome, sizeof(nome), stdin);
    nome[strcspn(nome, "\n")] = '\0';

    buscarServico(raiz, nome, 2);

}

void menuServico (NoAVL *raiz) {
    int opcao;
    do {
        printf("\n----------MENU DE SERVIÇOS----------\n"
               "1 - Adicionar Serviço\n"
               "2 - Buscar Serviço\n"
               "3 - Listar Todos os Serviços\n"
               "4 - Voltar\n"
               "Escolha uma opção: ");
        scanf("%d", &opcao);

        while (getchar() != '\n');

        switch (opcao) {
            case 1:
                pegarDadosServico(&raiz);
                break;
            case 2:
                pegarNome(raiz);
                break;
            case 3:
                listarServicos(raiz);
                break;
            case 4:
                printf("Voltando...\n\n");
                break;
            default:
                printf("Opção Inválida\n");
                break;
        }

    } while (opcao != 4);
}
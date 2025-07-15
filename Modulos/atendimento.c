#include "atendimento.h"

#include <stdio.h>
#include <time.h>


void menuAtendimento(struct Tabela *tabela, filaAtendimento *fila) {
    int opcao;
    char cpf[12];

    do {
        printf("-------MENU FILA--------\n"
               "1 - Inserir\n"
               "2 - Remover\n"
               "3 - Listar\n"
               "4 - Voltar\n");
        scanf("%d", &opcao);
        switch (opcao) {
            case 1:
                printf("Insira o cpf do cliente que será atendido: ");
                setbuf(stdin, NULL);
                scanf(" %[^\n]", cpf);
                clock_t inicio = clock();
                inserirAtendimento(&fila, cpf);
                clock_t final = clock();
                double tempo = (double) (final - inicio)/CLOCKS_PER_SEC;
                printf("\nTempo para inserção: %f\n",tempo);
            case 2:
                printf("Removendo o primeiro da fila");
                filaAtendimento *removido;

                inicio = clock();

                removido = removerAtendimento(&fila);
                printf("CPF: %s\n", removido->cpf);

                final = clock();
                tempo = (double) (final - inicio)/CLOCKS_PER_SEC;
                printf("\nTempo para remoção: %f\n",tempo);
            case 3:
                imprimirFila(fila, tabela);
            case 4:
                break;
            default:
                printf("Opção invalida\n");
                break;
        }
    }
    while (opcao != 4);

}

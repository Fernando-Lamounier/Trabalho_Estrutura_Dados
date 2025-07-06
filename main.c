#include <stdio.h>
#include <stdlib.h>


int main() {
    printf("------------TRABALHO Estrutura de Dados I------------\n"
           "Tema: Oficina\n\n");

    int opcao = 0;
    do {
        printf("MENU\n"
               "1 - Clientes\n"
        787
        "2 - Agendamento\n"
        "3 - Fila de Atendimento\n"
        "4 - Histórico de Atendimento\n"
        "5 - Relatório de Serviços\n"
        "6 - Sair\n"
        "Escolha uma opção: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                break;
            case 2:
                break;
            case 3:
                break;
            case 4:
                break;
            case 5:
                break;
            default:
                printf("Opção Inválida!\n");
                break;
        }
    } while (opcao != 6);

    return 0;
    }


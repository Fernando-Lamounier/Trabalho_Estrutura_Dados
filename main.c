#include <stdio.h>
#include <stdlib.h>
#include "ParseXML/parse.h"
#include "tabela.h"
#include "AVLtree.h"
#include "agendamento.h"
#include "servico.h"

int main() {

    TabelaCliente *clientes = criarTabelaCliente(1024);
    Agendamento *agendamentos = criarLista();
    NoAVL *raiz = criarArvore();

    // Le um arquivo XML
    parseXML("C:\\Users\\Usuario\\OneDrive\\Área de Trabalho\\Trabalho_Estrutura_Dados\\teste.txt", clientes, &agendamentos, &raiz);

    printf("------------TRABALHO Estrutura de Dados I------------\n"
           "Tema: Oficina\n\n");

    int opcao = 0;
    do {
        printf("MENU\n"
               "1 - Clientes\n"
               "2 - Agendamento\n"
               "3 - Fila de Atendimento\n"
               "4 - Relatório de Serviços\n"
               "5 - Sair\n"
               "Escolha uma opção: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                menuClientes(clientes);
                break;

            case 2:
                menuAgendamento(clientes ,agendamentos, raiz);
                break;

            case 3:
                // Implementar fila de atendimento
                break;

            case 4:
                menuServico(raiz);
                break;

            case 5:
                printf("Saindo!\n");
                liberarLista(agendamentos);
                liberarTabelaCliente(clientes);
                liberarArvore(raiz);
                break;
            default:
                printf("Opção Inválida!\n");
                break;
        }
    } while (opcao != 5);

    // liberar memória das listas aqui, se necessário

    return 0;
}

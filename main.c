#include <stdio.h>
#include <stdlib.h>
#include "TAD/lista.h"
#include "ParseXML/parse.h"
#include "Modulos/agendamento.h"
#include "Modulos/cliente.h"
#include "Modulos/servico.h"
#include "TAD/tabela.h"
#include "TAD/AVLtree.h"

int main() {

    TabelaCliente *cliente = criarTabelaCliente(1024);
    Agendamento *agendamento = criarLista(); // lista encadeada inicialmente vazia
    NoAVL *raiz = criarArvore();

    // Le um arquivo XML
    parseXML("C:\\Users\\Usuario\\OneDrive\\Área de Trabalho\\Trabalho_Estrutura_Dados\\teste.txt", &agendamento, &raiz);

    printf("------------TRABALHO Estrutura de Dados I------------\n"
           "Tema: Oficina\n\n");

    int opcao = 0;
    do {
        printf("MENU\n"
               "1 - Clientes\n"
               "2 - Agendamento\n"
               "3 - Fila de Atendimento\n"
               "4 - Histórico de Atendimento\n"
               "5 - Relatório de Serviços\n"
               "6 - Sair\n"
               "Escolha uma opção: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                menuClientes(cliente);
                break;

            case 2:
                menuAgendamento(agendamento, raiz);
                break;

            case 3:
                // Implementar fila de atendimento
                break;

            case 4:
                // Implementar histórico
                break;

            case 5:
                menuServico(raiz);
                break;

            case 6:
                printf("Saindo!\n");
                liberarLista(agendamento);
                liberarTabelaCliente(cliente);
                liberarArvore(raiz);
                break;
            default:
                printf("Opção Inválida!\n");
                break;
        }
    } while (opcao != 6);

    // liberar memória das listas aqui, se necessário

    return 0;
}

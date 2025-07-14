#include <stdio.h>
#include <stdlib.h>
#include "TAD/lista.h"
#include "ParseXML/parse.h"
#include "Modulos/agendamento.h"
#include "Modulos/cliente.h"
#include "Modulos/servico.h"
#include "Modulos/atendimento.h"
#include "TAD/tabela.h"
#include "TAD/AVLtree.h"
#include "TAD/fila.h"

int main() {

    TabelaCliente *tabelaCliente = criarTabelaCliente(1024);
    Agendamento *agendamento = criarLista(); // lista encadeada inicialmente vazia
    NoAVL *raiz = criarArvore();
    filaAtendimento *fila = NULL;

    // Le um arquivo XML
    //parseXML("..\\..\\Trabalho_Estrutura_Dados\\teste.txt", &agendamento, &raiz);

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
                menuClientes(tabelaCliente);
                break;

            case 2:
                menuAgendamento(agendamento, raiz);
                break;

            case 3:
                menuAtendimento(tabelaCliente, fila);
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
                liberarTabelaCliente(tabelaCliente);
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

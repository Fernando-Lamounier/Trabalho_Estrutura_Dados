#include <stdio.h>
#include <stdlib.h>
#include "ParseXML/parse.h"
#include "tabela.h"
#include "AVLtree.h"
#include "Modulos/agendamento.h"
#include "Modulos/cliente.h"
#include "Modulos/servico.h"
#include "Modulos/atendimento.h"
#include "TAD/tabela.h"
#include "TAD/AVLtree.h"
#include "TAD/fila.h"

int main() {

    TabelaCliente *clientes = criarTabelaCliente(1000003);
    Agendamento *agendamentos = criarLista();
    NoAVL *raiz = criarArvore();
    filaAtendimento *fila = NULL;

    // Le um arquivo XML
    parseXML("C:\\Users\\Usuario\\OneDrive\\Área de Trabalho\\Trabalho_Estrutura_Dados\\teste.txt", clientes, &agendamentos, &raiz, &fila);

    printf("------------TRABALHO Estrutura de Dados I------------\n"
           "Tema: Sistema de Atendimento\n\n");

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
                menuClientes(clientes, agendamentos);
                break;

            case 2:
                menuAgendamento(clientes ,agendamentos, raiz);
                break;

            case 3:
                menuAtendimento(clientes, fila);
                break;

            case 4:
                menuServico(raiz);
                break;

            case 5:
                printf("Saindo!\n");
                liberarLista(agendamentos);
                liberarTabelaCliente(clientes);
                liberarArvore(raiz);
                while(fila) {
                    removerAtendimento(&fila);
            }
                break;
            default:
                printf("Opção Inválida!\n");
                break;
        }
    } while (opcao != 5);

    // liberar memória das listas aqui, se necessário

    return 0;
}

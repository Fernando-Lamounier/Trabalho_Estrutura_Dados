#include "cliente.h"
#include "tabela.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void menuClientes(struct Tabela *tabela) {
    int opcao;
    do {
        printf("\n----------MENU DE CLIENTES----------\n"
               "1 - Cadastrar clientes\n"
               "2 - Vizualizar clientes\n"
               "3 - Apagar cliente\n"
               "4 - Atualizar cliente\n"
               "5 - Vizualizar Histórico de Atendimentos\n"
               "6 - Voltar\n"
               "Escolha uma opção: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                pegarDadosCliente(tabela);
                break;
            case 2:
                if (tabela == NULL) {
                    printf("Nenhum agendamento carregado.\n");
                } else {
                   int opcao2;

                    do {
                        printf("\n----------MENU DE VISUALIZAÇÂO----------\n"
                               "1 - Vizualizar todos os clientes\n"
                               "2 - Vizualizar um cliente\n"
                               "3 - Voltar\n"
                               "Escolha uma opção: ");
                        scanf("%d", &opcao2);
                        switch (opcao2) {
                            case 1:
                                for (int i = 0; i < tabela->tamanhoTabela; i++) {
                                    if (tabela->clientes[i] != NULL) {
                                        printf("Cliente: %s\n"
                                               "CPF: %s\n"
                                               "Endereco: %s\n"
                                               "Telefone: %s\n\n", tabela->clientes[i]->nome, tabela->clientes[i]->cpf,
                                               tabela->clientes[i]->endereco, tabela->clientes[i]->telefone);
                                    }
                                }
                                break;
                            case 2:
                                char cpf[15];
                                printf("Digite o cpf do cliente: ");
                                setbuf(stdin, NULL);
                                scanf("%s", cpf);
                                listarCliente(tabela, cpf);
                                break;
                            default:
                                break;
                        }
                    }while (opcao2 != 3);

                }
                break;
            case 3:
                deletarCliente(tabela);
                break;
            case 4:
                alterarCliente(tabela);
                break;
            case 5:
                visualizarHistorico(tabela);
                break;
            case 6:
                printf("Voltando...\n\n");
                break;
            default:
                printf("Opção Inválida\n");
                break;
        }

    } while (opcao != 6);
}


void pegarDadosCliente (struct Tabela *tabela) {
    //Aloca memória temporária
    Cliente *novo = malloc(sizeof(Cliente));
    if (!novo) {
        fprintf(stderr, "Erro de alocação\n");
        return;
    }
    memset(novo, 0, sizeof(Cliente));

    printf("Digite o CPF do Cliente: ");
    setbuf(stdin, NULL);
    scanf(" %[^\n]", novo->cpf);

    printf("Digite o nome do cliente: ");
    setbuf(stdin, NULL);
    scanf(" %[^\n]", novo->nome);


    printf("Digite o endereço do cliente: ");
    setbuf(stdin, NULL);
    scanf(" %[^\n]", novo->endereco);


    printf("Digite o telefone do cliente: ");
    setbuf(stdin, NULL);
    scanf(" %[^\n]", novo->telefone);



    insereCliente(tabela, novo);

    free(novo);
}

void deletarCliente(TabelaCliente *tabela) {

    char cpf[12];
    printf("Digite o CPF do Cliente: ");
    setbuf(stdin, NULL);
    scanf(" %[^\n]", cpf);

    removerCliente(tabela, cpf);

}

void alterarCliente(TabelaCliente *tabela) {
    char cpf[12];
    printf("Digite o CPF do Cliente: ");
    setbuf(stdin, NULL);
    scanf(" %[^\n]", cpf);

    atualizarCliente(tabela, cpf, NULL, 0);
}
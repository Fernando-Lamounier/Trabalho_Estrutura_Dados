#include "agendamento.h"


void pegarDados (Agendamento **agendamentos) {
    //Aloca memória temporária
    Agendamento *novo = malloc(sizeof(Agendamento));
    if (!novo) {
        fprintf(stderr, "Erro de alocação\n");
        return;
    }
    memset(novo, 0, sizeof(Agendamento));

    printf("Digite o CPF do Cliente: ");
    fgets(novo->cpf, sizeof(novo->cpf), stdin);
    // Remove o '\n' que fgets adiciona, se presente
    novo->cpf[strcspn(novo->cpf, "\n")] = '\0';

    while (getchar() != '\n');
    printf("Digite a Data(DD/MM/AAAA): ");
    fgets(novo->data, sizeof(novo->data), stdin);
    novo->data[strcspn(novo->data, "\n")] = '\0';

    while (getchar() != '\n');
    printf("Digite a Hora (HH:MM): ");
    fgets(novo->hora, sizeof(novo->hora), stdin);
    novo->hora[strcspn(novo->hora, "\n")] = '\0';

    while (getchar() != '\n');
    printf("Digite o Tipo de Serviço: ");
    fgets(novo->tipoServico, sizeof(novo->tipoServico), stdin);
    novo->tipoServico[strcspn(novo->tipoServico, "\n")] = '\0';

    strcpy(novo->status, "Agendado");
    novo->status[strcspn(novo->status, "\n")] = '\0';

    int verif = verificarConflito(*agendamentos, novo->data, novo->hora);
    if (verif == 0) {
        *agendamentos = agendar(*agendamentos, novo->cpf, novo->data, novo->hora, novo->tipoServico, novo->status);
        printf("Serviço agendado com sucesso!\n");
    } else {
        printf("Erro: Já existe um agendamento para a data %s às %s.\n", novo->data, novo->hora);
    }

    free(novo);
}

void menuAgendamento (Agendamento *agendamentos) {
    int opcao;
    do {
        printf("\n----------MENU DE AGENDAMENTOS----------\n"
               "1 - Agendar Serviço\n"
               "2 - Vizualizar todos os agendamentos de um cliente\n"
               "3 - Cancelar Agendamento\n"
               "4 - Alterar Status\n"
               "5 - Voltar\n"
               "Escolha uma opção: ");
        scanf("%d", &opcao);

        while (getchar() != '\n');

        switch (opcao) {
            case 1:
                pegarDados(&agendamentos);
                break;
            case 2:
                // Exemplo de percorrer lista encadeada de agendamentos e imprimir status
                if (agendamentos == NULL) {
                    printf("Nenhum agendamento carregado.\n");
                } else {
                    Agendamento *aux = agendamentos;
                    printf("Agendamentos carregados:\n");
                    while (aux != NULL) {
                        printf("CPF: %s, Data: %s, Hora: %s, Serviço: %s, Status: %s\n",
                               aux->cpf, aux->data, aux->hora, aux->tipoServico, aux->status);
                        aux = aux->prox;
                    }
                }
                break;
            case 3:
                printf("espere");
                break;
            case 4:
                break;
            case 5:
                printf("Voltando...\n\n");
                break;
            default:
                printf("Opção Inválida\n");
                break;
        }

    } while (opcao != 5);
}
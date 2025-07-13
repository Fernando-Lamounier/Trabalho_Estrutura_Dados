#include "agendamento.h"
#include <regex.h>
#include <stdbool.h>
#include <ctype.h>

// Retorna true se o CPF tiver 11 dígitos e apenas números
bool validarCPF(const char *cpf) {
    if (strlen(cpf) != 11) return false;

    for (int i = 0; i < 11; i++) {
        if (!isdigit((unsigned char)cpf[i])) return false;
    }

    return true;
}

// Valida data no formato DD/MM/AAAA
bool validarData(const char *data) {
    regex_t regex;
    int ret = regcomp(&regex, "^[0-3][0-9]/[0-1][0-9]/[0-9]{4}$", REG_EXTENDED);
    if (ret != 0) return false;
    ret = regexec(&regex, data, 0, NULL, 0);
    regfree(&regex);
    return ret == 0;
}

// Valida hora no formato HH:MM (00–23:59)
bool validarHora(const char *hora) {
    regex_t regex;
    int ret = regcomp(&regex, "^[0-2][0-9]:[0-5][0-9]$", REG_EXTENDED);
    if (ret != 0) return false;
    ret = regexec(&regex, hora, 0, NULL, 0);
    regfree(&regex);
    return ret == 0;
}

// Pega o CPF para realizar a busca pelos agendamentos de um cliente
void buscaCPF (Agendamento *agendamentos) {
    char busca[12];

    printf("Digire o CPF para realizar a busca (SOMENTE NÚMEROS): ");
    fgets(busca, sizeof(busca), stdin);
    busca[strcspn(busca, "\n")] = '\0';

    visualizarAgendamentos(agendamentos, busca);


}

// Pega todos os dados para agendar um serviço
void pegarDados (Agendamento **agendamentos, const int opcao) {
    Agendamento *novo = malloc(sizeof(Agendamento));
    if (!novo) {
        fprintf(stderr, "Erro de alocação\n");
        return;
    }
    memset(novo, 0, sizeof(Agendamento));

    printf("Digite o CPF do Cliente (somente números): ");
    fgets(novo->cpf, sizeof(novo->cpf), stdin);
    novo->cpf[strcspn(novo->cpf, "\n")] = '\0';

    if (!validarCPF(novo->cpf)) {
        printf("Erro: CPF inválido. (Ausência de números ou retire caracteres especiais [pontos e traços])\n");
        free(novo);
        return;
    }

    while (getchar() != '\n');
    printf("Digite a Data (DD/MM/AAAA): ");
    fgets(novo->data, sizeof(novo->data), stdin);
    novo->data[strcspn(novo->data, "\n")] = '\0';

    if (!validarData(novo->data)) {
        printf("Erro: Data Inválida.\n");
        free(novo);
        return;
    }

    while (getchar() != '\n');
    printf("Digite a Hora (HH:MM): ");
    fgets(novo->hora, sizeof(novo->hora), stdin);
    novo->hora[strcspn(novo->hora, "\n")] = '\0';

    if (!validarHora(novo->hora)) {
        printf("Erro: Hora Inválida.\n");
        free(novo);
        return;
    }

    if (opcao == 3) {
        atualizarStatus(*agendamentos, novo->cpf, novo->data, novo->hora, "Cancelado");
        free(novo);
        return;
    } else if (opcao == 4) {
        atualizarStatus(*agendamentos, novo->cpf, novo->data, novo->hora, "Concluido");
        free(novo);
        return;
    }

    while (getchar() != '\n');
    printf("Digite o Tipo de Serviço: ");
    fgets(novo->tipoServico, sizeof(novo->tipoServico), stdin);
    novo->tipoServico[strcspn(novo->tipoServico, "\n")] = '\0';

    strcpy(novo->status, "Agendado");

    int verif = verificarConflito(*agendamentos, novo->data, novo->hora);
    if (verif == 0) {
        *agendamentos = agendar(*agendamentos, novo->cpf, novo->data, novo->hora, novo->tipoServico, novo->status);
        printf("Serviço agendado com sucesso!\n");
    } else {
        printf("Erro: Já existe um agendamento para a data %s às %s.\n", novo->data, novo->hora);
    }

    free(novo);
}

// Menu da seção de Agendamentos (Lista)
void menuAgendamento (Agendamento *agendamentos) {
    int opcao;
    do {
        printf("\n----------MENU DE AGENDAMENTOS----------\n"
               "1 - Agendar Serviço\n"
               "2 - Vizualizar todos os agendamentos de um cliente\n"
               "3 - Cancelar Serviço\n"
               "4 - Concluir Serviço\n"
               "5 - Voltar\n"
               "Escolha uma opção: ");
        scanf("%d", &opcao);

        while (getchar() != '\n');

        switch (opcao) {
            case 1:
                pegarDados(&agendamentos, opcao);
                break;
            case 2:
                buscaCPF(agendamentos);
                break;
            case 3:
            case 4:
                pegarDados(&agendamentos, opcao);
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
#include "agendamento.h"
#include "tabela.h"
#include <regex.h>
#include <ctype.h>
#include <time.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>


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

    clock_t inicio = clock();
    visualizarAgendamentos(agendamentos, busca);
    clock_t final = clock();
    double tempo = (double) (final - inicio)/CLOCKS_PER_SEC;
    printf("\nTempo para visualizar: %f\n",tempo);

}

Agendamento* buscarAgendamento(Agendamento *agendamentos, const char *cpf, const char *data, const char *hora) {
    Agendamento *atual = agendamentos;
    while (atual) {
        if (strcmp(atual->cpf, cpf) == 0 &&
            strcmp(atual->data, data) == 0 &&
            strcmp(atual->hora, hora) == 0) {
            return atual;
        }
        atual = atual->prox;
    }
    return NULL;
}


// Pega todos os dados para agendar um serviço
void pegarDados (struct Tabela *tabela, Agendamento **agendamentos, NoAVL *raiz, const int opcao) {
    Agendamento *novo = malloc(sizeof(Agendamento));
    Historico *novo2 = malloc(sizeof(Historico));
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
        while (getchar() != '\n');
        printf("Digite uma observação para o serviço:\n");
        fgets(novo2->observacoes, sizeof(novo2->observacoes), stdin);
        novo2->observacoes[strcspn(novo2->observacoes, "\n")] = '\0';

        time_t agora = time(NULL);
        if (agora == ((time_t) -1)) {
            printf("Erro ao obter o tempo atual\n");
            free(novo);
            free(novo2);
            return;
        }

        struct tm *dataHoraLocal = localtime(&agora);
        if (dataHoraLocal == NULL) {
            printf("Erro ao converter para hora local\n");
            free(novo);
            free(novo2);
            return;
        }

        char data[11];
        char hora[6];
        strftime(data, sizeof(data), "%d/%m/%Y", dataHoraLocal);
        strftime(hora, sizeof(hora), "%H:%M", dataHoraLocal);

        Agendamento *ag = buscarAgendamento(*agendamentos, novo->cpf, novo->data, novo->hora);
        if (ag == NULL) {
            printf("Erro: Agendamento não encontrado.\n");
            free(novo);
            free(novo2);
            return;
        }

        strcpy(novo2->tipoServico, ag->tipoServico);
        strcpy(novo2->data, data);
        strcpy(novo2->hora, hora);

        atualizarStatus(*agendamentos, novo->cpf, novo->data, novo->hora, "Concluido");
        atualizarCliente(tabela, novo->cpf, novo2, 4);

        free(novo);
        return;
    }

    while (getchar() != '\n');
    printf("Digite o Tipo de Serviço: ");
    fgets(novo->tipoServico, sizeof(novo->tipoServico), stdin);
    novo->tipoServico[strcspn(novo->tipoServico, "\n")] = '\0';

    if (buscarServico(raiz, novo->tipoServico, 0) == NULL) {
        free(novo);
        return;
    }

    strcpy(novo->status, "Agendado");

    int verif = verificarConflito(*agendamentos, novo->data, novo->hora);
    if (verif == 0) {
        clock_t inicio = clock();

        *agendamentos = agendar(*agendamentos, novo->cpf, novo->data, novo->hora, novo->tipoServico, novo->status);

        printf("Serviço agendado com sucesso!\n");
        clock_t final = clock();
        double tempo = (double) (final - inicio)/CLOCKS_PER_SEC;
        printf("\nTempo para agendar: %f\n",tempo);
    } else {
        printf("Erro: Já existe um agendamento para a data %s às %s.\n", novo->data, novo->hora);
    }

    free(novo);
}

// Menu da seção de Agendamentos (Lista)
void menuAgendamento (struct Tabela *tabela, Agendamento *agendamentos, NoAVL *raiz) {
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
                pegarDados(tabela, &agendamentos, raiz, opcao);
                break;
            case 2:
                buscaCPF(agendamentos);
                break;
            case 3:
            case 4:
                pegarDados(tabela, &agendamentos, raiz, opcao);
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
//
// Created by Usuario on 06/07/2025.
//

#ifndef TRABALHO_ESTRUTURA_DADOS_LISTA_H
#define TRABALHO_ESTRUTURA_DADOS_LISTA_H

typedef struct Agendamento {
    char cpf[12];
    char data[11];       // DD/MM/AAAA
    char hora[6];       // HH:MM
    char tipoServico[50];
    char status[15];
    struct Agendamento *prox;
} Agendamento;

// Funções do TAD
Agendamento* criarLista();
Agendamento* agendar(Agendamento *lista, const char *cpf, const char *data, const char *hora, const char *tipoServico);
void visualizarAgendamentos(Agendamento *lista, const char *cpf);
Agendamento* cancelarAgendamento(Agendamento *lista, const char *cpf, const char *data, const char *hora);
Agendamento* atualizarStatus(Agendamento *lista, const char *cpf, const char *data, const char *hora, const char *novoStatus);
void liberarLista(Agendamento *lista);

#endif //TRABALHO_ESTRUTURA_DADOS_LISTA_H

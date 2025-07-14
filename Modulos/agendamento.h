
#ifndef TRABALHO_ESTRUTURA_DADOS_MENU_H
#define TRABALHO_ESTRUTURA_DADOS_MENU_H


#include <stdbool.h>
#include "lista.h"
#include "pilha.h"
#include "AVLtree.h"


bool validarCPF(const char *cpf);
bool validarData(const char *data);
bool validarHora(const char *hora);
void menuAgendamento (struct Tabela *tabela, Agendamento *agendamentos, NoAVL *raiz);

#endif //TRABALHO_ESTRUTURA_DADOS_MENU_H

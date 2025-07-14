#ifndef CLIENTE_H
#define CLIENTE_H

#include "pilha.h"
#include "tabela.h"


void menuClientes(struct Tabela *tabela, Agendamento *lista);
void pegarDadosCliente (struct Tabela *tabela);
void deletarCliente(TabelaCliente *tabela, Agendamento *lista);
void alterarCliente(struct Tabela *tabela);

#endif //CLIENTE_H

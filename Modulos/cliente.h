#ifndef CLIENTE_H
#define CLIENTE_H

#include "pilha.h"


void menuClientes(struct Tabela *tabela);
void pegarDadosCliente (struct Tabela *tabela);
void deletarCliente(struct Tabela *tabela);
void alterarCliente(struct Tabela *tabela);

#endif //CLIENTE_H

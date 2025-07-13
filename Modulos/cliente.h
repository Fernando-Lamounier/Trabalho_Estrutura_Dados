#ifndef CLIENTE_H
#define CLIENTE_H

#include "../TAD/tabela.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


void menuClientes(TabelaCliente *tabela);
void pegarDadosCliente (TabelaCliente *tabela);
void deletarCliente(TabelaCliente *tabela);
void alterarCliente(TabelaCliente *tabela);

#endif //CLIENTE_H

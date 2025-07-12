#ifndef CLIENTE_H
#define CLIENTE_H

#include "cliente.h"
#include "../TAD/TAD_Clientes/lista_Clientes.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void menuClientes(TabelaCliente *tabela);
void pegarDadosCliente (TabelaCliente *tabela);
void deletarCliente(TabelaCliente *tabela);
void alterarCliente(TabelaCliente *tabela);

#endif //CLIENTE_H

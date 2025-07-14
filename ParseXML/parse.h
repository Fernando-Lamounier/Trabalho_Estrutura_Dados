//
// Created by Usuario on 06/07/2025.
//

#ifndef TRABALHO_ESTRUTURA_DADOS_PARSE_H
#define TRABALHO_ESTRUTURA_DADOS_PARSE_H


#include "lista.h"
#include "AVLtree.h"
#include "tabela.h"

void parseXML(const char *filename, TabelaCliente *tabela, Agendamento **agendamento, NoAVL **raiz);

#endif //TRABALHO_ESTRUTURA_DADOS_PARSE_H

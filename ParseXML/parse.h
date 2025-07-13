//
// Created by Usuario on 06/07/2025.
//

#ifndef TRABALHO_ESTRUTURA_DADOS_PARSE_H
#define TRABALHO_ESTRUTURA_DADOS_PARSE_H

#include "../TAD/lista.h"
#include <string.h>
#include <libxml/tree.h>
#include <libxml/parser.h>
#include <libxml/xmlversion.h>

void parseXML(const char *filename, Agendamento **agendamento);

#endif //TRABALHO_ESTRUTURA_DADOS_PARSE_H

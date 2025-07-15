#include <libxml/tree.h>
#include "parse.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "tabela.h"
#include "time.h"

void parseClientes(xmlNode *node, TabelaCliente *tabela) {

    clock_t inicio = clock();
    for (xmlNode *cur = node; cur; cur = cur->next) {
        if (cur->type == XML_ELEMENT_NODE && strcmp((char *)cur->name, "cliente") == 0) {
            Cliente *novo = malloc(sizeof(Cliente));
            if (!novo) {
                fprintf(stderr, "Erro de alocação\n");
                continue;
            }
            memset(novo, 0, sizeof(Cliente));

            for (xmlNode *child = cur->children; child; child = child->next) {
                if (child->type == XML_ELEMENT_NODE) {
                    char *content = (char *)xmlNodeGetContent(child);
                    if (strcmp((char *)child->name, "cpf") == 0)
                        strncpy(novo->cpf, content, sizeof(novo->cpf)-1);
                    else if (strcmp((char *)child->name, "nome") == 0)
                        strncpy(novo->nome, content, sizeof(novo->nome)-1);
                    else if (strcmp((char *)child->name, "telefone") == 0)
                        strncpy(novo->telefone, content, sizeof(novo->telefone)-1);
                    else if (strcmp((char *)child->name, "endereco") == 0)
                        strncpy(novo->endereco, content, sizeof(novo->endereco)-1);
                    xmlFree(content);
                }
            }

            insereCliente(tabela, novo);
            free(novo);
        }
    }
    clock_t fim = clock();
    double tempo = (double) (fim - inicio) / CLOCKS_PER_SEC;
    printf("Tempo da leitura de clientes: %f\n", tempo);
}

void parseAgendamentos(xmlNode *node, Agendamento **agendamentos) {

    clock_t inicio = clock();

    for (xmlNode *cur = node; cur; cur = cur->next) {
        if (cur->type == XML_ELEMENT_NODE && strcmp((char *)cur->name, "agendamento") == 0) {
            Agendamento *novo = malloc(sizeof(Agendamento));
            if (!novo) {
                fprintf(stderr, "Erro de alocação\n");
                continue;
            }
            memset(novo, 0, sizeof(Agendamento));
            novo->prox = NULL;

            for (xmlNode *child = cur->children; child; child = child->next) {
                if (child->type == XML_ELEMENT_NODE) {
                    char *content = (char *)xmlNodeGetContent(child);
                    if (strcmp((char *)child->name, "cpf") == 0)
                        strncpy(novo->cpf, content, sizeof(novo->cpf)-1);
                    else if (strcmp((char *)child->name, "data") == 0)
                        strncpy(novo->data, content, sizeof(novo->data)-1);
                    else if (strcmp((char *)child->name, "hora") == 0)
                        strncpy(novo->hora, content, sizeof(novo->hora)-1);
                    else if (strcmp((char *)child->name, "tipo_servico") == 0)
                        strncpy(novo->tipoServico, content, sizeof(novo->tipoServico)-1);
                    else if (strcmp((char *)child->name, "status") == 0)
                        strncpy(novo->status, content, sizeof(novo->status)-1);
                    xmlFree(content);
                }
            }

            *agendamentos = agendar(*agendamentos, novo->cpf, novo->data, novo->hora, novo->tipoServico, novo->status);
            free(novo);
        }
    }

    clock_t fim = clock();
    double tempo = (double) (fim - inicio) / CLOCKS_PER_SEC;
    printf("Tempo da leitura de agendamentos: %f\n", tempo);
}

void parseHistoricoAtendimentos(xmlNode *node, TabelaCliente *tabela) {

    clock_t inicio = clock();

    for (xmlNode *cur = node; cur; cur = cur->next) {
        if (cur->type == XML_ELEMENT_NODE && strcmp((char *)cur->name, "atendimento") == 0) {
            Historico *novo = malloc(sizeof(Historico));
            if (!novo) {
                fprintf(stderr, "Erro de alocação\n");
                continue;
            }
            memset(novo, 0, sizeof(Historico));

            char cpf[12] = {0};

            for (xmlNode *child = cur->children; child; child = child->next) {
                if (child->type == XML_ELEMENT_NODE) {
                    char *content = (char *)xmlNodeGetContent(child);
                    if (strcmp((char *)child->name, "cpf") == 0)
                        strncpy(cpf, content, sizeof(cpf)-1);
                    else if (strcmp((char *)child->name, "data") == 0)
                        strncpy(novo->data, content, sizeof(novo->data)-1);
                    else if (strcmp((char *)child->name, "hora") == 0)
                        strncpy(novo->hora, content, sizeof(novo->hora)-1);
                    else if (strcmp((char *)child->name, "tipo_servico") == 0)
                        strncpy(novo->tipoServico, content, sizeof(novo->tipoServico)-1);
                    else if (strcmp((char *)child->name, "observacoes") == 0)
                        strncpy(novo->observacoes, content, sizeof(novo->observacoes)-1);
                    xmlFree(content);
                }
            }

            atualizarCliente(tabela, cpf, novo, 4);
            free(novo);
        }
    }

    clock_t fim = clock();
    double tempo = (double) (fim - inicio) / CLOCKS_PER_SEC;
    printf("Tempo da leitura de historicos de atendimentos: %f\n", tempo);
}

void parseServicos(xmlNode *node, NoAVL **raiz) {

    clock_t inicio = clock();

    for (xmlNode *cur = node; cur; cur = cur->next) {
        if (cur->type == XML_ELEMENT_NODE && strcmp((char *)cur->name, "servico") == 0) {
            Servico *novo = malloc(sizeof(Servico));
            if (!novo) {
                fprintf(stderr, "Erro de alocação\n");
                continue;
            }
            memset(novo, 0, sizeof(Servico));

            for (xmlNode *child = cur->children; child; child = child->next) {
                if (child->type == XML_ELEMENT_NODE) {
                    char *content = (char *)xmlNodeGetContent(child);
                    if (strcmp((char *)child->name, "nome") == 0)
                        strncpy(novo->nome, content, sizeof(novo->nome)-1);
                    else if (strcmp((char *)child->name, "descricao") == 0)
                        strncpy(novo->descricao, content, sizeof(novo->descricao)-1);
                    else if (strcmp((char *)child->name, "preco_medio") == 0)
                        novo->precoMedio = atof(content);
                    xmlFree(content);
                }
            }

            inserirServico(raiz, *novo);
            free(novo);
        }
    }

    clock_t fim = clock();
    double tempo = (double) (fim - inicio) / CLOCKS_PER_SEC;
    printf("Tempo da leitura de serviços: %f\n", tempo);
}

void parseXML(const char *filename, TabelaCliente *tabela, Agendamento **agendamento, NoAVL **raiz) {
    xmlDoc *doc = xmlReadFile(filename, NULL, 0);
    if (!doc) {
        printf("Erro ao abrir o arquivo %s\n", filename);
        return;
    }

    xmlNode *root = xmlDocGetRootElement(doc);

    for (xmlNode *cur = root->children; cur; cur = cur->next) {
        if (cur->type == XML_ELEMENT_NODE) {
            if (strcmp((char *)cur->name, "clientes") == 0) {
                parseClientes(cur->children, tabela);
            } else if (strcmp((char *)cur->name, "agendamentos") == 0) {
                parseAgendamentos(cur->children, agendamento);
            } else if (strcmp((char *)cur->name, "historico_atendimentos") == 0) {
                parseHistoricoAtendimentos(cur->children, tabela);
            } else if (strcmp((char *)cur->name, "servicos") == 0) {
                parseServicos(cur->children, raiz);
            }
        }
    }

    xmlFreeDoc(doc);
    xmlCleanupParser();
}
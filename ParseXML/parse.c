#include "parse.h"


/*void parseClientes(xmlNode *node, Cliente clientes[], int *count) {
    for (xmlNode *cur = node; cur; cur = cur->next) {
        if (cur->type == XML_ELEMENT_NODE && strcmp((char *)cur->name, "cliente") == 0) {
            Cliente c = {0};
            for (xmlNode *child = cur->children; child; child = child->next) {
                if (child->type == XML_ELEMENT_NODE) {
                    char *content = (char *)xmlNodeGetContent(child);
                    if (strcmp((char *)child->name, "cpf") == 0)
                        strncpy(c.cpf, content, sizeof(c.cpf)-1);
                    else if (strcmp((char *)child->name, "nome") == 0)
                        strncpy(c.nome, content, sizeof(c.nome)-1);
                    else if (strcmp((char *)child->name, "telefone") == 0)
                        strncpy(c.telefone, content, sizeof(c.telefone)-1);
                    else if (strcmp((char *)child->name, "endereco") == 0)
                        strncpy(c.endereco, content, sizeof(c.endereco)-1);
                    xmlFree(content);
                }
            }
            clientes[(*count)++] = c;
        }
    }
}*/

void parseAgendamentos(xmlNode *node, Agendamento **agendamentos, int *count) {
    Agendamento *aux = NULL;
    for (xmlNode *cur = node; cur; cur = cur->next) {
        if (cur->type == XML_ELEMENT_NODE && strcmp((char *)cur->name, "agendamento") == 0) {

            // Cria novo nó dinamicamente
            Agendamento *novo = malloc(sizeof(Agendamento));
            if (!novo) {
                fprintf(stderr, "Erro de alocação\n");
                return;
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


            // Insere o nó no final da lista
            if (*agendamentos == NULL) {
                *agendamentos = novo;  // Se lista está vazia, novo é o primeiro
            } else {
                Agendamento *temp = *agendamentos;
                while (temp->prox != NULL)
                    temp = temp->prox;
                temp->prox = novo;  // Insere no final
            }

            (*count)++;
        }
    }
}


/*void parseFilaAtendimento(xmlNode *node, ClienteFila fila[], int *count) {
    for (xmlNode *cur = node; cur; cur = cur->next) {
        if (cur->type == XML_ELEMENT_NODE && strcmp((char *)cur->name, "cliente_fila") == 0) {
            ClienteFila cf = {0};
            for (xmlNode *child = cur->children; child; child = child->next) {
                if (child->type == XML_ELEMENT_NODE) {
                    char *content = (char *)xmlNodeGetContent(child);
                    if (strcmp((char *)child->name, "cpf") == 0)
                        strncpy(cf.cpf, content, sizeof(cf.cpf)-1);
                    else if (strcmp((char *)child->name, "data") == 0)
                        strncpy(cf.data, content, sizeof(cf.data)-1);
                    else if (strcmp((char *)child->name, "hora_chegada") == 0)
                        strncpy(cf.hora_chegada, content, sizeof(cf.hora_chegada)-1);
                    else if (strcmp((char *)child->name, "tipo") == 0)
                        strncpy(cf.tipo, content, sizeof(cf.tipo)-1);
                    xmlFree(content);
                }
            }
            fila[(*count)++] = cf;
        }
    }
}*/

/*void parseHistoricoAtendimentos(xmlNode *node, Atendimento historico[], int *count) {
    for (xmlNode *cur = node; cur; cur = cur->next) {
        if (cur->type == XML_ELEMENT_NODE && strcmp((char *)cur->name, "atendimento") == 0) {
            Atendimento at = {0};
            for (xmlNode *child = cur->children; child; child = child->next) {
                if (child->type == XML_ELEMENT_NODE) {
                    char *content = (char *)xmlNodeGetContent(child);
                    if (strcmp((char *)child->name, "cpf") == 0)
                        strncpy(at.cpf, content, sizeof(at.cpf)-1);
                    else if (strcmp((char *)child->name, "data") == 0)
                        strncpy(at.data, content, sizeof(at.data)-1);
                    else if (strcmp((char *)child->name, "hora") == 0)
                        strncpy(at.hora, content, sizeof(at.hora)-1);
                    else if (strcmp((char *)child->name, "tipo_servico") == 0)
                        strncpy(at.tipo_servico, content, sizeof(at.tipo_servico)-1);
                    else if (strcmp((char *)child->name, "observacoes") == 0)
                        strncpy(at.observacoes, content, sizeof(at.observacoes)-1);
                    xmlFree(content);
                }
            }
            historico[(*count)++] = at;
        }
    }
}

void parseServicos(xmlNode *node, Servico servicos[], int *count) {
    for (xmlNode *cur = node; cur; cur = cur->next) {
        if (cur->type == XML_ELEMENT_NODE && strcmp((char *)cur->name, "servico") == 0) {
            Servico s = {0};
            for (xmlNode *child = cur->children; child; child = child->next) {
                if (child->type == XML_ELEMENT_NODE) {
                    char *content = (char *)xmlNodeGetContent(child);
                    if (strcmp((char *)child->name, "nome") == 0)
                        strncpy(s.nome, content, sizeof(s.nome)-1);
                    else if (strcmp((char *)child->name, "descricao") == 0)
                        strncpy(s.descricao, content, sizeof(s.descricao)-1);
                    else if (strcmp((char *)child->name, "preco_medio") == 0)
                        s.preco_medio = atof(content);
                    xmlFree(content);
                }
            }
            servicos[(*count)++] = s;
        }
    }
}*/

void parseXML(const char *filename, Agendamento **agendamento) {
    xmlDoc *doc = xmlReadFile(filename, NULL, 0);
    if (!doc) {
        printf("Erro ao abrir o arquivo %s\n", filename);
        return;
    }

    xmlNode *root = xmlDocGetRootElement(doc);

    //Cliente clientes[200];
    int qtd_clientes = 0;

    //Agendamento agendamentos[200];
    int qtd_agendamentos = 0;

    //ClienteFila fila[200];
    int qtd_fila = 0;

    //Atendimento historico[200];
    int qtd_historico = 0;

    //Servico servicos[200];
    int qtd_servicos = 0;

    for (xmlNode *cur = root->children; cur; cur = cur->next) {
        if (cur->type == XML_ELEMENT_NODE) {
            if (strcmp((char *) cur->name, "clientes") == 0) {
                //parseClientes(cur->children, clientes, &qtd_clientes);
            } else if (strcmp((char *) cur->name, "agendamentos") == 0) {
               printf("cheguei aqui");
                parseAgendamentos(cur->children, agendamento, &qtd_agendamentos);
            } else if (strcmp((char *) cur->name, "fila_atendimento") == 0) {
                //parseFilaAtendimento(cur->children, fila, &qtd_fila);
            } else if (strcmp((char *) cur->name, "historico_atendimentos") == 0) {
                //parseHistoricoAtendimentos(cur->children, historico, &qtd_historico);
            } else if (strcmp((char *) cur->name, "servicos") == 0) {
                //parseServicos(cur->children, servicos, &qtd_servicos);
            }
        }
    }
    xmlFreeDoc(doc);
    xmlCleanupParser();
}
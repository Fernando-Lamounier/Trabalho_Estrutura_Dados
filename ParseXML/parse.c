// #include "parse.h"
//
//
// /*void parseClientes(xmlNode *node, Cliente clientes[], int *count) {
//     for (xmlNode *cur = node; cur; cur = cur->next) {
//         if (cur->type == XML_ELEMENT_NODE && strcmp((char *)cur->name, "cliente") == 0) {
//             Cliente c = {0};
//             for (xmlNode *child = cur->children; child; child = child->next) {
//                 if (child->type == XML_ELEMENT_NODE) {
//                     char *content = (char *)xmlNodeGetContent(child);
//                     if (strcmp((char *)child->name, "cpf") == 0)
//                         strncpy(c.cpf, content, sizeof(c.cpf)-1);
//                     else if (strcmp((char *)child->name, "nome") == 0)
//                         strncpy(c.nome, content, sizeof(c.nome)-1);
//                     else if (strcmp((char *)child->name, "telefone") == 0)
//                         strncpy(c.telefone, content, sizeof(c.telefone)-1);
//                     else if (strcmp((char *)child->name, "endereco") == 0)
//                         strncpy(c.endereco, content, sizeof(c.endereco)-1);
//                     xmlFree(content);
//                 }
//             }
//             clientes[(*count)++] = c;
//         }
//     }
// }*/
//
// void parseAgendamentos(xmlNode *node, Agendamento **agendamentos) {
//     for (xmlNode *cur = node; cur; cur = cur->next) {
//         if (cur->type == XML_ELEMENT_NODE && strcmp((char *)cur->name, "agendamento") == 0) {
//
//             //Aloca memória temporária
//             Agendamento *novo = malloc(sizeof(Agendamento));
//             if (!novo) {
//                 fprintf(stderr, "Erro de alocação\n");
//                 return;
//             }
//             memset(novo, 0, sizeof(Agendamento));
//             novo->prox = NULL;
//
//             for (xmlNode *child = cur->children; child; child = child->next) {
//                 if (child->type == XML_ELEMENT_NODE) {
//                     char *content = (char *)xmlNodeGetContent(child);
//                     if (strcmp((char *)child->name, "cpf") == 0)
//                         strncpy(novo->cpf, content, sizeof(novo->cpf)-1);
//                     else if (strcmp((char *)child->name, "data") == 0)
//                         strncpy(novo->data, content, sizeof(novo->data)-1);
//                     else if (strcmp((char *)child->name, "hora") == 0)
//                         strncpy(novo->hora, content, sizeof(novo->hora)-1);
//                     else if (strcmp((char *)child->name, "tipo_servico") == 0)
//                         strncpy(novo->tipoServico, content, sizeof(novo->tipoServico)-1);
//                     else if (strcmp((char *)child->name, "status") == 0)
//                         strncpy(novo->status, content, sizeof(novo->status)-1);
//                     xmlFree(content);
//                 }
//             }
//
//             *agendamentos = agendar(*agendamentos, novo->cpf, novo->data, novo->hora, novo->tipoServico, novo->status);
//
//             free(novo);
//
//         }
//     }
// }
//
//
// /*void parseFilaAtendimento(xmlNode *node, ClienteFila fila[], int *count) {
//     for (xmlNode *cur = node; cur; cur = cur->next) {
//         if (cur->type == XML_ELEMENT_NODE && strcmp((char *)cur->name, "cliente_fila") == 0) {
//             ClienteFila cf = {0};
//             for (xmlNode *child = cur->children; child; child = child->next) {
//                 if (child->type == XML_ELEMENT_NODE) {
//                     char *content = (char *)xmlNodeGetContent(child);
//                     if (strcmp((char *)child->name, "cpf") == 0)
//                         strncpy(cf.cpf, content, sizeof(cf.cpf)-1);
//                     else if (strcmp((char *)child->name, "data") == 0)
//                         strncpy(cf.data, content, sizeof(cf.data)-1);
//                     else if (strcmp((char *)child->name, "hora_chegada") == 0)
//                         strncpy(cf.hora_chegada, content, sizeof(cf.hora_chegada)-1);
//                     else if (strcmp((char *)child->name, "tipo") == 0)
//                         strncpy(cf.tipo, content, sizeof(cf.tipo)-1);
//                     xmlFree(content);
//                 }
//             }
//             fila[(*count)++] = cf;
//         }
//     }
// }*/
//
// /*void parseHistoricoAtendimentos(xmlNode *node, Atendimento historico[], int *count) {
//     for (xmlNode *cur = node; cur; cur = cur->next) {
//         if (cur->type == XML_ELEMENT_NODE && strcmp((char *)cur->name, "atendimento") == 0) {
//             Atendimento at = {0};
//             for (xmlNode *child = cur->children; child; child = child->next) {
//                 if (child->type == XML_ELEMENT_NODE) {
//                     char *content = (char *)xmlNodeGetContent(child);
//                     if (strcmp((char *)child->name, "cpf") == 0)
//                         strncpy(at.cpf, content, sizeof(at.cpf)-1);
//                     else if (strcmp((char *)child->name, "data") == 0)
//                         strncpy(at.data, content, sizeof(at.data)-1);
//                     else if (strcmp((char *)child->name, "hora") == 0)
//                         strncpy(at.hora, content, sizeof(at.hora)-1);
//                     else if (strcmp((char *)child->name, "tipo_servico") == 0)
//                         strncpy(at.tipo_servico, content, sizeof(at.tipo_servico)-1);
//                     else if (strcmp((char *)child->name, "observacoes") == 0)
//                         strncpy(at.observacoes, content, sizeof(at.observacoes)-1);
//                     xmlFree(content);
//                 }
//             }
//             historico[(*count)++] = at;
//         }
//     }
// } */
//
// void parseServicos(xmlNode *node, NoAVL **raiz) {
//     for (xmlNode *cur = node; cur; cur = cur->next) {
//         if (cur->type == XML_ELEMENT_NODE && strcmp((char *)cur->name, "servico") == 0) {
//
//             //Aloca memória temporária
//             Servico *novo = malloc(sizeof(Servico));
//             if (!novo) {
//                 fprintf(stderr, "Erro de alocação\n");
//                 return;
//             }
//
//             for (xmlNode *child = cur->children; child; child = child->next) {
//                 if (child->type == XML_ELEMENT_NODE) {
//                     char *content = (char *)xmlNodeGetContent(child);
//                     if (strcmp((char *)child->name, "nome") == 0)
//                         strncpy(novo->nome, content, sizeof(novo->nome)-1);
//                     else if (strcmp((char *)child->name, "descricao") == 0)
//                         strncpy(novo->descricao, content, sizeof(novo->descricao)-1);
//                     else if (strcmp((char *)child->name, "preco_medio") == 0)
//                         novo->precoMedio = atof(content);
//                     xmlFree(content);
//                 }
//             }
//
//             inserirServico(raiz, *novo);
//
//             free(novo);
//
//         }
//     }
// }
//
// void parseXML(const char *filename, Agendamento **agendamento, NoAVL **raiz) {
//     xmlDoc *doc = xmlReadFile(filename, NULL, 0);
//     if (!doc) {
//         printf("Erro ao abrir o arquivo %s\n", filename);
//         return;
//     }
//
//     xmlNode *root = xmlDocGetRootElement(doc);
//
//
//     for (xmlNode *cur = root->children; cur; cur = cur->next) {
//         if (cur->type == XML_ELEMENT_NODE) {
//             if (strcmp((char *) cur->name, "clientes") == 0) {
//                 //parseClientes(cur->children, clientes, &qtd_clientes);
//             } else if (strcmp((char *) cur->name, "agendamentos") == 0) {
//                 parseAgendamentos(cur->children, agendamento);
//             } else if (strcmp((char *) cur->name, "fila_atendimento") == 0) {
//                 //parseFilaAtendimento(cur->children, fila, &qtd_fila);
//             } else if (strcmp((char *) cur->name, "historico_atendimentos") == 0) {
//                 //parseHistoricoAtendimentos(cur->children, historico, &qtd_historico);
//             } else if (strcmp((char *) cur->name, "servicos") == 0) {
//                 parseServicos(cur->children, raiz);
//             }
//         }
//     }
//
//
//     xmlFreeDoc(doc);
//     xmlCleanupParser();
// }
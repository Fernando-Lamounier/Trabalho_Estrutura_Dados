#ifndef TRABALHO_ESTRUTURA_DADOS_TABELA_H
#define TRABALHO_ESTRUTURA_DADOS_TABELA_H

#include "pilha.h"
#include "../Modulos/cliente.h"
#include "lista.h"


typedef struct Cliente Cliente;

struct Cliente {
    char cpf[12];
    char nome[255];
    char telefone[12];
    char endereco[255];
    HistoricoAtendimento historico;
};

typedef struct Tabela TabelaCliente;


struct Tabela {
    int qtd, tamanhoTabela;
    struct Cliente **clientes;
};



// Funções do TAD

int chaveDivisao (long int chave, int tamanhoTabela);
int chaveMultiplicacao (long int chave, int tamanhoTabela);
int insereCliente (struct Tabela *tabela, Cliente *cliente);
int buscaCliente(struct Tabela *tabela, const char *cpf, Cliente *cliente, Agendamento *lista, int tipo) ;
long int valorChaveCPF(const char *cpf_cnpj);
int duplaInsercaoCliente (int posicao1, long int chave, int i, int tamanhoTabela);
void atualizarCliente(struct Tabela *tabela, const char *cpf, Historico *dado, int opcao);
void removerCliente(TabelaCliente *tabela, Agendamento *lista, const char *cpf_cnpj);
TabelaCliente* criarTabelaCliente(int tamanhoTabela);
void liberarTabelaCliente(struct Tabela *tabela);
void listarCliente(struct Tabela *tabela, const char *cpf_cnpj);

#endif

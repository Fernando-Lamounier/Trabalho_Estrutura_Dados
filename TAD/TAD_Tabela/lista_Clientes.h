

#ifndef LISTA_CLIENTES_H
#define LISTA_CLIENTES_H

typedef struct Cliente {
    char cpf_cnpj[15];
    char nome[255];
    char telefone[12];
    char endereco[255];
} Cliente;



typedef struct Tabela TabelaCliente;

struct Tabela {
    int qtd, tamanhoTabela;
    struct Cliente **clientes;
};

// Funções do TAD


int chaveDivisao (long int chave, int tamanhoTabela);
int chaveMultiplicacao (long int chave, int tamanhoTabela);
int insereCliente (TabelaCliente *tabela, Cliente *cliente);
int buscaCliente(TabelaCliente *tabela, const char *cpf_cnpj, Cliente *cliente, int tipo);
long int valorChaveCPF(const char *cpf_cnpj);


int duplaInsercaoCliente (int posicao1, long int chave, int i, int tamanhoTabela);
void atualizarCliente(TabelaCliente *tabela, const char *cpf_cnpj);
void removerCliente(TabelaCliente *tabela, const char *cpf_cnpj);
TabelaCliente* criarTabelaCliente(int tamanhoTabela);
void liberarTabelaCliente(TabelaCliente *tabela);
void listarCliente(TabelaCliente *tabela, const char *cpf_cnpj);

#endif //LISTA_CLIENTES_H

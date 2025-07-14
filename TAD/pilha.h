#ifndef TRABALHO_ESTRUTURA_DADOS_PILHA_H
#define TRABALHO_ESTRUTURA_DADOS_PILHA_H

struct Tabela; // Forward declaration (opaque type)

typedef struct {
    char data[11];
    char hora[6];
    char tipoServico[50];
    char observacoes[200];
} Historico;

typedef struct NoPilha {
    Historico *dado;
    struct NoPilha *prox;
} NoPilha;

typedef struct {
    NoPilha *topo;
} HistoricoAtendimento;

// Funções para manipular a pilha
void inicializarPilha(HistoricoAtendimento *pilha);
void pushAtendimento(HistoricoAtendimento *pilha, Historico *dado);
void liberarPilha(HistoricoAtendimento *pilha);
void visualizarHistorico(struct Tabela *clientes);

#endif

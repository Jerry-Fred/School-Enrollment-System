#ifndef LISTA_H
#define LISTA_H  // As include guards, guardas de

#include "estudante.h"

typedef struct No
{
    Estudante aluno;
    struct No *prox;

} No;

// Funções da lista - Grupo 5
No* criarNo(Estudante aluno);

void inserirEstudante(No **inicio, Estudante aluno);

void listarEstudantes(No *inicio);

No* pesquisarEstudante(No *inicio, int codigo);

void removerEstudante(No **inicio, int codigo);

void libertarLista(No **inicio);

// Protótipos para persistência (Adicionados)
void guardarDadosNoFicheiro(No *inicio);
void carregarDadosDoFicheiro(No **inicio);

#endif
#ifndef FILA_H
#define FILA_H

#include "lista.h"

#define MAX_FILA 100

typedef struct {
    No *dados[MAX_FILA];
    int frente;
    int tras;
    int qtd;
} Fila;

// Funções da fila
void inicializarFila(Fila *f);
int filaVazia(Fila *f);
int filaCheia(Fila *f);
void enqueue(Fila *f, No *noEstudante);
No* dequeue(Fila *f);

// Protótipos para persistência da fila
void guardarFilaNoFicheiro(Fila *f);
void carregarFilaDoFicheiro(Fila *f, No *inicio);

#endif
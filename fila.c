#include <stdio.h>
#include <stdlib.h>
#include "fila.h"
#include "lista.h"

void inicializarFila(Fila *f) {
    f->frente = 0;
    f->tras = -1;
    f->qtd = 0;
}

int filaVazia(Fila *f) {
    return (f->qtd == 0);
}

int filaCheia(Fila *f) {
    return (f->qtd == MAX_FILA);
}

void enqueue(Fila *f, No *noEstudante) {
    if (filaCheia(f)) return;
    
    f->tras = (f->tras + 1) % MAX_FILA;
    f->dados[f->tras] = noEstudante; // Guarda a referência (ponteiro) da lista
    f->qtd++;
}

No* dequeue(Fila *f) {
    if (filaVazia(f)) return NULL;
    
    No* removido = f->dados[f->frente];
    f->frente = (f->frente + 1) % MAX_FILA;
    f->qtd--;
    return removido;
}

// --- PERSISTÊNCIA: GUARDAR FILA ---
void guardarFilaNoFicheiro(Fila *f) {
    FILE *arq = fopen("fila.txt", "w");
    if (arq == NULL) return;

    int idx = f->frente;
    for (int i = 0; i < f->qtd; i++) {
        // Salvamos apenas o código para identificar o aluno na lista ligada
        fprintf(arq, "%d\n", f->dados[idx]->aluno.codigo);
        idx = (idx + 1) % MAX_FILA;
    }
    
    fclose(arq);
}

// --- PERSISTÊNCIA: CARREGAR FILA ---
void carregarFilaDoFicheiro(Fila *f, No *inicio) {
    FILE *arq = fopen("fila.txt", "r");
    if (arq == NULL) return;

    int codigo;
    while (fscanf(arq, "%d\n", &codigo) != EOF) {
        // Procuramos o nó na lista ligada pelo código e religamos à fila
        No *alunoEncontrado = pesquisarEstudante(inicio, codigo);
        if (alunoEncontrado != NULL) {
            enqueue(f, alunoEncontrado);
        }
    }
    fclose(arq);
}
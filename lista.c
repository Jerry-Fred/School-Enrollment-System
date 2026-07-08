#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lista.h"

// Cria um novo nó na memória do computador
No* criarNo(Estudante aluno) {
    No *novo = (No*) malloc(sizeof(No));
    if(novo == NULL) {
        printf("Erro ao alocar memoria!\n");
        return NULL;
    }
    novo->aluno = aluno;
    novo->prox = NULL;
    return novo;
}

// Inserimos um estudante no início da lista
void inserirEstudante(No **inicio, Estudante aluno) {
    No *novo = criarNo(aluno);
    if(novo != NULL) {
        novo->prox = *inicio;
        *inicio = novo;
    }
}

// Mostra todos os estudantes da lista
void listarEstudantes(No *inicio) {
    No *aux = inicio;
    if(aux == NULL) {
        printf("\nLista vazia!\n");
        return;
    }
    while(aux != NULL) {
        mostrarEstudante(aux->aluno);
        aux = aux->prox;
    }
}

// Pesquisa estudante pelo código
No* pesquisarEstudante(No *inicio, int codigo) {
    No *aux = inicio;
    while(aux != NULL) {
        if(aux->aluno.codigo == codigo) {
            return aux;
        }
        aux = aux->prox;
    }
    return NULL;
}

// Remoção
void removerEstudante(No **inicio, int codigo) {
    No *actual = *inicio;
    No *anterior = NULL;

    while(actual != NULL) {
        if(actual->aluno.codigo == codigo) {
            if(anterior == NULL) {
                *inicio = actual->prox;
            } else {
                anterior->prox = actual->prox;
            }
            free(actual);
            return;
        }
        anterior = actual;
        actual = actual->prox;
    }
}

// Liberta toda a memória da lista
void libertarLista(No **inicio) {
    No *aux;
    while(*inicio != NULL) {
        aux = *inicio;
        *inicio = (*inicio)->prox;
        free(aux);
    }
}

// --- PERSISTÊNCIA: GUARDAR DADOS ---
void guardarDadosNoFicheiro(No *inicio) {
    FILE *arq = fopen("estudantes.txt", "w");
    if (arq == NULL) return;

    No *aux = inicio;
    while (aux != NULL) {
        fprintf(arq, "%d;%s;%s;%d\n", aux->aluno.codigo, aux->aluno.nome, aux->aluno.curso, aux->aluno.idade);
        aux = aux->prox;
    }
    fflush(arq);
    fclose(arq);
}

// --- PERSISTÊNCIA: CARREGAR DADOS ---
void carregarDadosDoFicheiro(No **inicio) {
    FILE *arq = fopen("estudantes.txt", "r");
    if (arq == NULL) return;

    Estudante e;
    // Leitura . Usando largura máx para segurança
    while (fscanf(arq, "%d;%49[^;];%49[^;];%d\n", &e.codigo, e.nome, e.curso, &e.idade) != EOF) {
        inserirEstudante(inicio, e);
    }
    fclose(arq);
}
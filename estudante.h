#ifndef ESTUDANTE_H
#define ESTUDANTE_H

#define TAM_NOME 50
#define TAM_CURSO 50

// Os Nossos .h sao os nossos HEADERS, Grupo 5
typedef struct
{
    int codigo;
    char nome[TAM_NOME];
    char curso[TAM_CURSO];
    int idade;

} Estudante;


// Funções do  estudante - Grupo 5

void lerEstudante(Estudante *e);

void mostrarEstudante(Estudante e);


#endif
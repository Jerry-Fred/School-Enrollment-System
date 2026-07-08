#include <stdio.h>
#include "estudante.h"


void lerEstudante(Estudante *e)
{
    printf("\nCodigo do estudante: ");
    scanf("%d", &e->codigo);

    printf("Nome: ");
    scanf(" %[^\n]", e->nome);

    printf("Curso: ");
    scanf(" %[^\n]", e->curso);

    printf("Idade: ");
    scanf("%d", &e->idade);
}


void mostrarEstudante(Estudante e)
{
    printf("\n----------------------------");
    printf("\nCodigo: %d", e.codigo);
    printf("\nNome: %s", e.nome);
    printf("\nCurso: %s", e.curso);
    printf("\nIdade: %d", e.idade);
    printf("\n----------------------------\n");
}
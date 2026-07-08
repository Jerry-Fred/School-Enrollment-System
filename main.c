#include "raylib.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "estudante.h"
#include "lista.h"
#include "fila.h"

typedef enum { TELA_MENU, TELA_CADASTRAR, TELA_LISTAR, TELA_PESQUISAR, TELA_FILA } TelaAtual;

// Função Auxiliar - Botão
int DesenharBotao(Rectangle ret, const char* texto, Color corBase) {
    Vector2 mouse = GetMousePosition();
    int colidindo = CheckCollisionPointRec(mouse, ret);
    Color corAtual = colidindo ? ColorAlpha(corBase, 0.8f) : corBase;
    DrawRectangleRec(ret, corAtual);
    DrawRectangleLinesEx(ret, 1, DARKGRAY);
    DrawText(texto, ret.x + (ret.width - MeasureText(texto, 18))/2, ret.y + (ret.height - 18)/2, 18, WHITE);
    return (colidindo && IsMouseButtonPressed(MOUSE_BUTTON_LEFT));
}

// Função para entrada
void GerenciarInputTexto(char* buffer, int maxTamanho, int* contagem, int focado) {
    if (!focado) return;
    int chave = GetCharPressed();
    while (chave > 0) {
        if ((chave >= 32) && (chave <= 125) && (*contagem < maxTamanho - 1)) {
            buffer[*contagem] = (char)chave;
            buffer[*contagem + 1] = '\0';
            (*contagem)++;
        }
        chave = GetCharPressed();
    }
    if (IsKeyPressed(KEY_BACKSPACE) && *contagem > 0) {
        buffer[--(*contagem)] = '\0';
    }
}

int main(void) {
    InitWindow(900, 650, "Sistema Academico de Matriculas - Grupo 5");
    SetTargetFPS(60);

    // Inicialização 
    No *lista = NULL;
    carregarDadosDoFicheiro(&lista); //  Para Carrega a lista do arquivo
    
    Fila fila;
    inicializarFila(&fila);
    carregarFilaDoFicheiro(&fila, lista); // Religa a fila com base na lista carregada

    TelaAtual tela = TELA_MENU;
    char txtCodigo[16] = "", txtNome[TAM_NOME] = "", txtCurso[TAM_CURSO] = "", txtIdade[16] = "", txtPesquisa[16] = "", txtFilaCod[16] = "";
    int lenC=0, lenN=0, lenCur=0, lenI=0, lenP=0, lenF=0, campoFocado = 0;
    char mensagemStatus[128] = "Sistema Iniciado.";
    No* estudanteEncontrado = NULL;

    while (!WindowShouldClose()) {
        if (IsKeyPressed(KEY_ESCAPE)) tela = TELA_MENU;

        // Gestão de inputs
        if (tela == TELA_CADASTRAR) {
            if (campoFocado == 0) GerenciarInputTexto(txtCodigo, 15, &lenC, 1);
            if (campoFocado == 1) GerenciarInputTexto(txtNome, TAM_NOME, &lenN, 1);
            if (campoFocado == 2) GerenciarInputTexto(txtCurso, TAM_CURSO, &lenCur, 1);
            if (campoFocado == 3) GerenciarInputTexto(txtIdade, 15, &lenI, 1);
        } else if (tela == TELA_PESQUISAR) GerenciarInputTexto(txtPesquisa, 15, &lenP, 1);
        else if (tela == TELA_FILA) GerenciarInputTexto(txtFilaCod, 15, &lenF, 1);

        BeginDrawing();
        ClearBackground(GetColor(0xf5f6fa));

        DrawRectangle(0, 0, 900, 70, GetColor(0x2f3640));
        DrawText("SISTEMA ACADEMICO DE MATRICULAS", 40, 22, 24, RAYWHITE);
        DrawRectangle(0, 610, 900, 40, GetColor(0xdcdde1));
        DrawText(mensagemStatus, 20, 622, 15, DARKGRAY);

        switch (tela) {
            case TELA_MENU:
                if (DesenharBotao((Rectangle){50, 150, 240, 50}, "1. Cadastrar", GetColor(0x44bd32))) tela = TELA_CADASTRAR;
                if (DesenharBotao((Rectangle){50, 220, 240, 50}, "2. Listar", GetColor(0x0097e6))) tela = TELA_LISTAR;
                if (DesenharBotao((Rectangle){50, 290, 240, 50}, "3. Pesquisar / Remover", GetColor(0x8c7ae6))) tela = TELA_PESQUISAR;
                if (DesenharBotao((Rectangle){50, 360, 240, 50}, "4. Fila", GetColor(0xe1b12c))) tela = TELA_FILA;
                break;

            case TELA_CADASTRAR:
                if (DesenharBotao((Rectangle){350, 400, 140, 45}, "Salvar", GetColor(0x44bd32))) {
                    if (lenC > 0 && lenN > 0) {
                        Estudante novo = {atoi(txtCodigo), "", "", atoi(txtIdade)};
                        strcpy(novo.nome, txtNome); strcpy(novo.curso, txtCurso);
                        inserirEstudante(&lista, novo);
                        guardarDadosNoFicheiro(lista); // PERSISTÊNCIA
                        strcpy(mensagemStatus, "Estudante salvo com sucesso!");
                        tela = TELA_MENU;
                    }
                }
                break;

            case TELA_PESQUISAR:
                if (DesenharBotao((Rectangle){520, 150, 120, 40}, "Pesquisar", BLUE)) estudanteEncontrado = pesquisarEstudante(lista, atoi(txtPesquisa));
                if (estudanteEncontrado && DesenharBotao((Rectangle){180, 330, 180, 45}, "Remover", GetColor(0xc23616))) {
                    removerEstudante(&lista, estudanteEncontrado->aluno.codigo);
                    guardarDadosNoFicheiro(lista); // PERSISTÊNCIA
                    guardarFilaNoFicheiro(&fila);  // Atualiza fila se necessário
                    estudanteEncontrado = NULL;
                    strcpy(mensagemStatus, "Removido do ficheiro.");
                }
                break;

            case TELA_FILA:
                if (DesenharBotao((Rectangle){320, 140, 160, 40}, "Inserir na Fila", GetColor(0x192a56))) {
                    No* busca = pesquisarEstudante(lista, atoi(txtFilaCod));
                    if (busca) {
                        enqueue(&fila, busca);
                        guardarFilaNoFicheiro(&fila); // PERSISTÊNCIA DA FILA
                        strcpy(mensagemStatus, "Aluno na fila!");
                    }
                }
                break;
            default: break;
        }
        EndDrawing();
    }

    libertarLista(&lista);
    CloseWindow();
    return 0;
}
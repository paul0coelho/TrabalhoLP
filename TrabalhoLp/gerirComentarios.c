
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "gerirComentarios.h"
#include "input.h"

/**
 * @brief Esta função mostra no ecrã os dados existentes do registo dos comentarios
 * 
 * @param comentario struct Comentario
 */
void imprimirComentarios(Comentario comentario) {

    printf("\tNome utilizador: %s\n", comentario.nomeUtilizador);
    printf("\tEmail: %s@%s.com\n", comentario.enderecoEmail.nomeUtilizador, comentario.enderecoEmail.dominio);
    printf("\tNome empresa: %s\n", comentario.nomeEmpresa);
    printf("\tTitulo: %s\n", comentario.titulo);
    printf("\tTexto: %s\n", comentario.texto);
    puts(BARRA);

}

/**
 * @brief Esta função "apaga" o registo dos comentários
 * 
 * @param comentario apontador para a struct Comentario
 */

void apagarDadosComentarios(Comentario *comentario) {

    strcpy(comentario->nomeUtilizador, "");
    strcpy(comentario->enderecoEmail.nomeUtilizador, "");
    strcpy(comentario->enderecoEmail.dominio, "");
    strcpy(comentario->nomeEmpresa, "");
    strcpy(comentario->titulo, "");
    strcpy(comentario->texto, "");
}

/**
 * @brief Esta função verifica se o comentário existe nos registos dos Comentarios
 * 
 * @param comentarios struct Comentarios
 * @param titulo
 * @return 1 se o comentario existir e 0 se ele não existir
 */

int procurarComentario(Comentarios comentarios, char titulo[]) {
    int i;
    for (i = 0; i < comentarios.contador; i++) {
        if (strcmp(comentarios.comentario[i].titulo, titulo) == 0) {
            return 1;
        }
    }

    return 0;
}

/**
 * @brief Esta função verifica se existem comentarios com o nome da empresa dada nos registos dos Comentarios
 * 
 * @param comentarios struct Comentarios
 * @param nomeEmpresa
 * @return 1 se existir e 0 se não existir
 */

int procurarComentarioNomeEmpresa(Comentarios comentarios, char nomeEmpresa[]) {
    int i;
    for (i = 0; i < comentarios.contador; i++) {
        if (strcmp(comentarios.comentario[i].nomeEmpresa, nomeEmpresa) == 0) {
            return 1;
        }
    }

    return 0;
}

/**
 * @brief Procura se um comentário existe, caso se confirme retorna a posição no registo Comentarios, se não existir retorna -1
 * 
 * @param titulo
 * @param comentarios struct Comentarios
 * @return i se o comentário existir, -1 caso não exista
 */
int obterPosicaoComentario(char titulo[], Comentarios comentarios) {
    for (int i = 0; i < comentarios.contador; i++) {
        if (strcmp(comentarios.comentario[i].titulo, titulo) == 0) {
            return i;
        }
    }
    return -1;
}

/**
 * @brief Esta função verifica se o ficheiro existe(rb), senão cria-o (wb)
 * Com a função fread é retornado o número de itens completos lidos pela função
 * 
 * @param comentarios apontador para a struct Comentarios
 * @param ficheiro apontador para o ficheiro binário de onde serão carregados os dados
 */
void carregarComentarios(Comentarios *comentarios, char *ficheiro) {
    int i, sucesso = 0;

    // Tenta abrir o ficheiro
    FILE *fp = fopen(ficheiro, "rb");
    if (fp != NULL) {

        // Retorna o número de itens completos lidos pela função
        fread(&comentarios->contador, sizeof (int), 1, fp);

        if (comentarios->contador > 0) {
            comentarios->comentario = (Comentario*) malloc(comentarios->contador * sizeof (Comentario));
            comentarios->tamanho = comentarios->contador;
            fread(comentarios->comentario, sizeof (Comentario), comentarios->contador, fp);

            sucesso = 1;
        }
        fclose(fp);
    }

    if (!sucesso) {
        fp = fopen(ficheiro, "wb");
        if (fp != NULL) {

            comentarios->comentario = (Comentario*) malloc(COMENTARIOS_TAM_INICIAL * sizeof (Comentario));
            comentarios->contador = 0;
            comentarios->tamanho = COMENTARIOS_TAM_INICIAL;
            fclose(fp);
        }
    }
}

/**
 * @brief Esta função desaloca a memória alocada 
 * 
 * @param comentarios apontador para a struct Comentarios
 */
void libertarComentarios(Comentarios *comentarios) {

    free(comentarios->comentario);

}

/**
 * @brief Esta função atualiza os dados de um comentário
 * 
 * @param comentario apontador para a struct Comentario
 */
void editarComentario(Comentario *comentario) {

    lerString((*comentario).titulo, MAX_TITULO, MSG_OBTER_TITULO_COMENT);
    lerString((*comentario).texto, MAX_COMENTARIO, MSG_OBTER_TEXTO);
}

/**
 * @brief Esta função aumenta o tamanho da memória para registar comentários
 * 
 * @param comentarios apontador para a struct Comentarios
 */
void expandirComentarios(Comentarios *comentarios) {
    Comentario *temp = (Comentario*) realloc(comentarios->comentario, sizeof (Comentario) * (comentarios->tamanho * 2));
    if (temp != NULL) {
        comentarios->tamanho *= 2;
        comentarios->comentario = temp;
    }
}

/**
 * @brief Esta função lista os comentários existentes
 * 
 * @param comentarios struct Comentarios
 */
void listarComentarios(Comentarios comentarios) {
    int i;

    if (comentarios.contador > 0) {
        printf("\n--------------- COMENTÁRIOS ---------------\n\n");
        for (i = 0; i < comentarios.contador; i++) {
            imprimirComentarios(comentarios.comentario[i]);
        }
    } else {
        puts(COMENTARIO_LISTA_VAZIA);
    }
}

/**
 * @brief Esta função guarda todas as alterações que o usuário tenha feito aos comentários existentes e armazena-as no ficheiro comentarios.bin
 * 
 * @param comentarios apontador para a struct Comentarios
 * @param ficheiro apontador para o ficheiro binário no qual serão guardados os dados referentes aos comentarios
 */
void guardarComentarios(Comentarios *comentarios, char *ficheiro) {
    int i;

    FILE *fp = fopen(ficheiro, "wb");
    if (fp == NULL) {
        exit(EXIT_FAILURE);
    }

    fwrite(&comentarios->contador, sizeof (int), 1, fp);

    for (i = 0; i < comentarios->contador; i++) {
        fwrite(&comentarios->comentario[i], sizeof (Comentario), 1, fp);
    }

    fclose(fp);
}

/**
 * @brief Remove um comentário com base no título fornecido.
 * 
 * @param comentarios Apontador para a struct Comentarios
 */
void removerComentario(Comentarios *comentarios) {
    int i, numero;
    char titulo[MAX_TITULO];

    lerString(titulo, MAX_TITULO, MSG_OBTER_TITULO_COMENT);

    if (procurarComentario(*comentarios, titulo) == 1) {
        numero = obterPosicaoComentario(titulo, *comentarios);

        for (i = numero; i < comentarios->contador - 1; i++) {
            comentarios->comentario[i] = comentarios->comentario[i + 1];
        }

        apagarDadosComentarios(&comentarios->comentario[i]);
        comentarios->contador--;
        puts(COMENTARIO_REMOVIDO_SUCESSO);
    } else {
        puts(COMENTARIO_NAO_EXISTE);
    }
}
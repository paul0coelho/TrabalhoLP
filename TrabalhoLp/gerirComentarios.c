/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/cFiles/file.c to edit this template
 */

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
    printf("\tEmail: %s\n", comentario.email);
    printf("\tNome empresa: %s\n", comentario.nomeEmpresa);
    printf("\tTitulo: %s\n", comentario.titulo);
    printf("\tTexto: %s\n", comentario.texto);
    puts(BARRA);

}

/**
 * @brief Esta função "apaga" o registo das empresas
 * 
 * @param empresa apontador para a struct Empresa
 */

void apagarDadosComentarios(Comentario *comentario) {

    strcpy(comentario->nomeUtilizador, "");
    strcpy(comentario->email, "");
    strcpy(comentario->nomeEmpresa, "");
    strcpy(comentario->titulo, "");
    strcpy(comentario->texto, "");
}

/**
 * @brief Esta função verifica se a empresa existe nos registos das Empresas
 * 
 * @param empresas struct Empresas
 * @param NIF
 * @return 1 se a empresa existir e 0 se ela não existir
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
 * @brief Esta função verifica se a empresa existe nos registos das Empresas
 * 
 * @param empresas struct Empresas
 * @param NIF
 * @return 1 se a empresa existir e 0 se ela não existir
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
 * @brief Procura se uma empresa existe, caso se confirme retorna a posição no registo Empresas, se não existir retorna -1
 * 
 * @param NIF
 * @param empresas struct Empresas
 * @return i se a empresa existir, -1 caso não exista
 */
int obterPosicaoComentario(char titulo[], Comentarios comentarios) {
    for (int i = 0; i < comentarios.contador; i++) {
        if (strcmp(comentarios.comentario[i].titulo, titulo)) {
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
 * @param empresas apontador para a struct Empresas
 */
void libertarComentarios(Comentarios *comentarios) {

    free(comentarios->comentario);

}

/**
 * @brief Cria um novo NIF de Empresa
 * Insere um novo registo em Empresas e o contador aumenta por 1
 * 
 * @param empresas apontador para struct Empresas
 * @return -1 se o NIF já existir ou retorna o número do contador se os dados foram registados com sucesso
 */
int registarComentario(Comentarios *comentarios) {
    char titulo[MAX_TITULO];

    lerString(titulo, MAX_TITULO, MSG_OBTER_TITULO_COMENT);

    if (procurarComentario(*comentarios, titulo) == 0) {

        lerString(comentarios->comentario[comentarios->contador].nomeUtilizador, MAX_NOME_UTILIZADOR, MSG_OBTER_NOME_UTILIZADOR);
        lerString(comentarios->comentario[comentarios->contador].email, MAX_EMAIL, MSG_OBTER_EMAIL);
        lerString(comentarios->comentario[comentarios->contador].nomeEmpresa, MAX_NOME_EMPRESA_COMENT, MSG_OBTER_NOME_EMPRESA_COMENT);
        strcpy(comentarios->comentario[comentarios->contador].titulo, titulo);
        lerString(comentarios->comentario[comentarios->contador].texto, MAX_COMENTARIO, MSG_OBTER_TEXTO);
        comentarios->comentario[comentarios->contador].estado = 1;

        return comentarios->contador++;
    }
    return -1;
}

/**
 * @brief Esta função atualiza os dados de uma empresa
 * 
 * @param empresa apontador para a struct Empresa
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
 * @brief Verifica se o número do contador e do tamanho são iguais, se sim chama a função expandirComentarios()
 * Caso o contador seja menor que o tamanho verifica-se se o registo do comentário correu bem, caso não corresse retorna -1 e aparece uma mensagem (COMENTARIO_EXISTE)
 * 
 * @param comentarios apontador para a struct Comentarios
 */
void registarComentarios(Comentarios *comentarios) {
    if (comentarios->contador == comentarios->tamanho) {
        expandirComentarios(comentarios);
    }

    if (comentarios->contador < comentarios->tamanho) {
        if (registarComentario(comentarios) == -1) {
            puts(COMENTARIO_EXISTE);
        } else {
            puts(COMENTARIO_REGISTADO_SUCESSO);
        }
    } else {
        puts(COMENTARIO_LISTA_CHEIA);
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
 * @param ficheiro apontador para o ficheiro binário no qual serão guardados os dados referentes aos comentários
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
 * @brief Verifica se o ID do mercado inserido pelo utilizador existe
 * Se o vendedor tiver comissões associadas o seu estado muda para Inativo(0) (removerMercado())
 * Caso contrário o registo do mercado é removido e o contador descresce por 1
 * 
 * @param mercados apontador para a struct Mercados
 * @param comissões apontador para a struct Comissoes
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
/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/cFiles/file.h to edit this template
 */

/* 
 * File:   gerirComentarios.h
 * Author: paulo
 *
 * Created on 19 de dezembro de 2023, 14:43
 */

#ifndef COMENTARIOS_H
#define COMENTARIOS_H

#include "funcoes.h"

/**
 * @brief Macros usadas na gestão de comentários 
 */
#define COMENTARIO_NAO_EXISTE  "\n------ COMENTÁRIO INEXISTENTE ------\n\n"
#define COMENTARIO_EXISTE      "\n------ COMENTÁRIO JÁ EXISTENTE ------\n\n"
#define COMENTARIO_LISTA_CHEIA "\n------ NÃO É POSSÍVEL INSERIR OUTRO COMENTÁRIO ------\n\n"
#define COMENTARIO_LISTA_VAZIA "\n------ LISTA DE COMENTÁRIOS VAZIA ------\n\n"

#define MSG_OBTER_NOME_EMPRESA_COMENT "\nInsira o nome da empresa:"
#define MAX_NOME_EMPRESA_COMENT 40

#define MSG_OBTER_NOME_UTILIZADOR "\nInsira o seu nome:"
#define MAX_NOME_UTILIZADOR 40

#define MSG_OBTER_EMAIL "\nInsira o seu email:"
#define MAX_EMAIL 40

#define MSG_OBTER_TITULO_COMENT "\nInsira o titulo do comentário:"
#define MAX_TITULO 40

#define MSG_OBTER_TEXTO "\nInsira o seu comentário:"
#define MAX_COMENTARIO 500

#define COMENTARIOS_TAM_INICIAL 2

#define COMENTARIO_REGISTADO_SUCESSO "\n------ COMENTÁRIO REGISTADO COM SUCESSO ------\n\n"
#define COMENTARIO_EDITADO_SUCESSO   "\n------ COMENTÁRIO ATUALIZADO COM SUCESSO ------\n\n"
#define COMENTARIO_REMOVIDO_SUCESSO  "\n------ COMENTÁRIO REMOVIDO COM SUCESSO ------\n\n"

#define BARRA "----------------------------------------\n"


/**
 * @brief As estruturas de dados que armazenam os dados dos comentários
 */
typedef struct {
    char nomeUtilizador[MAX_NOME_UTILIZADOR];
    char nomeEmpresa[MAX_NOME_EMPRESA_COMENT];
    EnderecoEmail enderecoEmail;
    char titulo[MAX_TITULO];
    char texto[MAX_COMENTARIO];
    int estado;
} Comentario;

typedef struct {
    int contador, tamanho;
    Comentario *comentario;
} Comentarios;

/**
 * @brief Funções destinadas aos comentários
 */
void imprimirComentarios(Comentario comentario);
void apagarDadosComentarios(Comentario *comentario);
int procurarComentario(Comentarios comentarios, char titulo[]);
int procurarComentarioNomeEmpresa(Comentarios comentarios, char nomeEmpresa[]);
void carregarComentarios(Comentarios *comentarios, char *ficheiro);
void libertarComentarios(Comentarios *comentarios);
void editarComentario(Comentario *comentario);
void expandirComentarios(Comentarios *comentarios);
void removerComentario(Comentarios *comentarios);
void editarComentarios(Comentarios *comentarios);
void listarComentarios(Comentarios comentarios);
int obterPosicaoComentario(char titulo[], Comentarios comentarios);
void guardarComentarios(Comentarios *comentarios, char *ficheiro);

#endif /* COMENTARIOS_H */


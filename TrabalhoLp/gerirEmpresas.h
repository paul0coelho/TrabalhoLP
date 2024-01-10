/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/cFiles/file.h to edit this template
 */

/* 
 * File:   gerirEmpresas.h
 * Author: paulo
 *
 * Created on 19 de dezembro de 2023, 14:37
 */

#ifndef EMPRESAS_H
#define EMPRESAS_H

#include "gerirComentarios.h"
#include "funcoes.h"

/**
 * @brief Macros usadas na gestão de ramos de atividade 
 */

#define RAMO_NAO_EXISTE  "\n------ RAMO DE ATIVIDADE INEXISTENTE ------\n\n"
#define RAMO_EXISTE      "\n------ RAMO DE ATIVIDADE JÁ EXISTENTE ------\n\n"
#define RAMO_LISTA_CHEIA "\n------ NÃO É POSSÍVEL INSERIR OUTRO RAMO DE ATIVIDADE ------\n\n"
#define RAMO_LISTA_VAZIA "\n------ LISTA DE RAMOS DE ATIVIDADE VAZIA ------\n\n"

#define MSG_OBTER_RAMO "\nInsira o ramo de atividade:"
#define MAX_RAMO 20

#define RAMOS_TAM_INICIAL 2

#define RAMO_REGISTADO_SUCESSO "\n------ RAMO DE ATIVIDADE REGISTRADO COM SUCESSO ------\n\n"
#define RAMO_EDITADO_SUCESSO   "\n------ RAMO DE ATIVIDADE ATUALIZADO COM SUCESSO ------\n\n"
#define RAMO_REMOVIDO_SUCESSO  "\n------ RAMO DE ATIVIDADE REMOVIDO COM SUCESSO ------\n\n"

#define BARRA "----------------------------------------\n"

/**
 * @brief Macros usadas na gestão de Empresas 
 */

#define CRITERIOS_INVALIDOS  "\n------ CRITERIOS INEXISTENTES ------\n\n"

#define MSG_OBTER_RAMO_ATIVIDADE "\nInsira o ramo de atividade da empresa:"
#define MAX_NOME_RAMO_ATIVIDADE 40

#define EMPRESA_NAO_EXISTE   "\n------ EMPRESA INEXISTENTE ------\n\n"
#define EMPRESA_EXISTE       "\n------ EMPRESA JÁ EXISTENTE ------\n\n"
#define EMPRESA_LISTA_CHEIA  "\n------ NÃO É POSSÍVEL INSERIR OUTRA EMPRESA ------\n\n"
#define EMPRESA_LISTA_VAZIA  "\n------ LISTA DE EMPRESAS VAZIA ------\n\n"
#define EMPRESAS_ENCONTRADAS "\n------ LISTA DE EMPRESAS ENCONTRADAS ------\n\n"

#define MSG_OBTER_NOME_EMPRESA "\nInsira o nome da empresa:"
#define MAX_NOME_EMPRESA 40

#define MSG_OBTER_NIF_EMPRESA "\nInsira o NIF da empresa (100000000-999999999):"
#define MAX_NIF_EMPRESA 999999999
#define MIN_NIF_EMPRESA 100000000

#define MSG_OBTER_RUA "\nInsira a rua da empresa:"
#define MAX_RUA 40

#define MSG_OBTER_LOCALIDADE "\nInsira a localidade da empresa:"
#define MAX_LOCALIDADE 40

#define MSG_OBTER_COD_POSTAL_PREFIXO "\nInsira o prefixo do codigo postal da empresa:"
#define MIN_COD_POSTAL_PREFIXO 1000
#define MAX_COD_POSTAL_PREFIXO 9999

#define MSG_OBTER_COD_POSTAL_SUFIXO "\nInsira o sufixo do codigo postal da empresa:"
#define MIN_COD_POSTAL_SUFIXO 100
#define MAX_COD_POSTAL_SUFIXO 999

#define EMPRESAS_TAM_INICIAL 2

#define EMPRESA_REGISTADA_SUCESSO "\n------ EMPRESA REGISTADA COM SUCESSO ------\n\n"
#define EMPRESA_EDITADA_SUCESSO   "\n------ EMPRESA ATUALIZADA COM SUCESSO ------\n\n"
#define EMPRESA_REMOVIDA_SUCESSO  "\n------ EMPRESA REMOVIDA COM SUCESSO ------\n\n"

#define MSG_OBTER_CLASSIFICACAO "Inisira a classificacao desejada:"
#define MIN_CLASSIFICACAO 0
#define MAX_CLASSIFICACAO 5
#define MAX_CLASSIFICACOES 20

#define CLASSIFICACAO_REGISTADA "\n------ Classificacao registada com sucesso ------\n\n"
#define CLASSIFICACAO_INVALIDA "\n------ Classificacao registada com sucesso ------\n\n"

#define BARRA "----------------------------------------\n"

/**
 * @brief As estruturas de dados que armazenam os dados dos ramos de atividade
 */
typedef struct {
    char nome[MAX_RAMO];
    int estado;
} RamoAtividade;

typedef struct {
    int contador, tamanho;
    RamoAtividade *ramoAtividade;
} RamosAtividade;

/**
 * @brief As estruturas de dados que armazenam os dados das empresas
 */

typedef struct {
    char nomeEmpresa[MAX_NOME_EMPRESA];
    char ramoAtividade[MAX_NOME_RAMO_ATIVIDADE];
    int NIF;
    char rua[MAX_RUA];
    char localidade[MAX_LOCALIDADE];
    CodigoPostal codigoPostal;
    int estado;
    int classificacoes[MAX_CLASSIFICACOES];
    int numClassificacoes;
} Empresa;

typedef struct {
    int contador, tamanho;
    Empresa *empresa;
} Empresas;

/**
 * @brief Funções destinadas aos ramos de atividade
 */
void imprimirRamoAtividade(RamoAtividade ramoAtividade);
void apagarDadosRamoAtividade(RamoAtividade *ramoAtividade);
int procurarRamoAtividade(RamosAtividade ramosAtividade, char nome[]);
void carregarRamosAtividade(RamosAtividade *ramosAtividade, char *ficheiro);
void libertarRamosAtividade(RamosAtividade *ramosAtividade);
int registarRamoAtividade(RamosAtividade *ramosAtividade);
void editarRamoAtividade(RamoAtividade *ramoAtividade);
void expandirRamosAtividade(RamosAtividade *ramosAtividade);
void registarRamosAtividade(RamosAtividade *ramosAtividade);
void removerRamoAtividade(RamoAtividade *ramoAtividade);
void removerRamosAtividade(RamosAtividade *ramosAtividade, Empresas *empresas);
void editarRamosAtividade(RamosAtividade *ramosAtividade);
void listarRamosAtividade(RamosAtividade ramosAtividade);
int obterPosicaoRamoAtividade(char nome[], RamosAtividade ramosAtividade);
void guardarRamosAtividade(RamosAtividade *ramosAtividade, char *ficheiro);

/**
 * @brief Funções destinadas ás empresas
 */
void imprimirEmpresas(Empresa empresa);
void apagarDadosEmpresas(Empresa *empresa);
int procurarEmpresa(Empresas empresas, int NIF);
int procurarEmpresaNome(Empresas empresas, char nome[]);
void carregarEmpresas(Empresas *empresas, char *ficheiro);
void libertarEmpresas(Empresas *empresas);
int registarEmpresa(Empresas *empresas, RamosAtividade *ramosAtividade);
void editarEmpresa(Empresa *empresa);
void editarEmpresas(Empresas *empresas);
void expandirEmpresas(Empresas *empresas);
void registarEmpresas(Empresas *empresas, RamosAtividade *ramosAtividade);
void removerEmpresa(Empresa *empresa);
void removerEmpresas(Empresas *empresas, Comentarios *comentarios);
void editarEmpresas(Empresas *empresas);
void listarEmpresas(Empresas empresas);
int obterPosicaoEmpresa(int NIF, Empresas empresas);
void guardarEmpresas(Empresas *comentarios, char *ficheiro);
void pesquisarEmpresas(Empresas *empresas);
int registarComentario(Comentarios *comentarios, Empresas *empresas);
void registarComentarios(Comentarios *comentarios, Empresas *empresas);
void classificarEmpresa(Empresas *empresas);
void relatorioClassificacoes(Empresas *empresas);
int obterPosicaoNomeEmpresa(Empresas empresas, char nome[]);
#endif /* EMPRESAS_H */


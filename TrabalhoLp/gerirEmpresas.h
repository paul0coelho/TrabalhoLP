/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/cFiles/file.h to edit this template
 */

/* 
 * File:   empresas.h
 * Author: paulo
 *
 * Created on 19 de dezembro de 2023, 14:37
 */

#ifndef EMPRESAS_H
#define EMPRESAS_H

#include "gerirComentarios.h"

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

#define MSG_OBTER_NOME_EMPRESA "\nInsira o nome da empresa:"
#define MAX_NOME_EMPRESA 40

#define MSG_OBTER_NIF_EMPRESA "\nInsira o NIF da empresa (1000000000-1999999999):"
#define MAX_NIF_EMPRESA 1999999999
#define MIN_NIF_EMPRESA 1000000000

#define MSG_OBTER_RUA "\nInsira a rua da empresa:"
#define MAX_RUA 40

#define MSG_OBTER_LOCALIDADE "\nInsira a localidade da empresa:"
#define MAX_LOCALIDADE 40

#define MSG_OBTER_COD_POSTAL "\nInsira o codigo postal da empresa:"
#define MAX_COD_POSTAL 8


#define EMPRESAS_TAM_INICIAL 2

#define EMPRESA_REGISTADA_SUCESSO "\n------ EMPRESA REGISTADA COM SUCESSO ------\n\n"
#define EMPRESA_EDITADA_SUCESSO   "\n------ EMPRESA ATUALIZADA COM SUCESSO ------\n\n"
#define EMPRESA_REMOVIDA_SUCESSO  "\n------ EMPRESA REMOVIDA COM SUCESSO ------\n\n"

#define BARRA "----------------------------------------\n"

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
    RamoAtividade ramoAtividade;
    int NIF;
    char rua[MAX_RUA];
    char localidade[MAX_LOCALIDADE];
    char codPostal[MAX_COD_POSTAL];
    int estado;
} Empresa;

typedef struct {
    int contador, tamanho;
    Empresa *empresa;
} Empresas;

/**
 * @brief Funções destinadas ás empresas
 */

void imprimirEmpresas(Empresa empresa);
void apagarDadosEmpresas(Empresa *empresa);
int procurarEmpresa(Empresas empresas, int NIF);
void carregarEmpresas(Empresas *empresas, char *ficheiro);
void libertarEmpresas(Empresas *empresas);
int registarEmpresa(Empresas *empresas, RamosAtividade *ramosAtividade);
void editarEmpresa(Empresa *empresa);
void expandirEmpresas(Empresas *empresas);
void registarEmpresas(Empresas *empresas, RamosAtividade *ramosAtividade);
void removerEmpresa(Empresa *empresa);
void removerEmpresas(Empresas *empresas, Comentarios *comentarios);
void editarEmpresas(Empresas *empresas);
void listarEmpresas(Empresas empresas);
int obterPosicaoEmpresa(int NIF, Empresas empresas);
void guardarEmpresas(Empresas *comentarios, char *ficheiro);
void pesquisarEmpresas(Empresas *empresas);

/**
 * @brief Funções destinadas aos ramos de atividade
 */
void imprimirRamoAtividade(RamoAtividade ramoAtividade);
void apagarDadosRamoAtividade(RamoAtividade *ramoAtividade);
int procurarRamoAtividade(RamosAtividade ramosAtividade, char nome[]);
void carregarRamoAtividade(RamosAtividade *ramosAtividade, char *ficheiro);
void libertarRamoAtividade(RamosAtividade *ramosAtividade);
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

#endif /* EMPRESAS_H */


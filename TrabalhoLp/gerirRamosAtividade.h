/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/cFiles/file.h to edit this template
 */

/* 
 * File:   gerirRamosAtividade.h
 * Author: paulo
 *
 * Created on 19 de dezembro de 2023, 14:40
 */

#ifndef RAMOSATIVIDADE_H
#define RAMOSATIVIDADE_H

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

#endif /* RAMOSATIVIDADE_H */


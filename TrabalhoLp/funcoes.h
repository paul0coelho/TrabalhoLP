/* 
 * File:   funcoes.h
 * Author: paulo
 *
 * Created on 15 de fevereiro de 2023, 10:19
 */

#ifndef FUNCOES_H
#define FUNCOES_H

/**
    * @brief Macros usadas na gestão de Empresas 
 */

#define EMPRESA_NAO_EXISTE "\n------ EMPRESA INEXISTENTE ------\n\n"
#define EMPRESA_EXISTE "\n------ EMPRESA JÁ EXISTENTE ------\n\n"
#define EMPRESA_LISTA_CHEIA "\n------ NÃO É POSSÍVEL INSERIR OUTRA EMPRESA ------\n\n"
#define EMPRESA_LISTA_VAZIA "\n------ LISTA DE EMPRESAS VAZIA ------\n\n"

#define MSG_OBTER_NOME_EMPRESA "\nInsira o nome da empresa:"
#define MAX_NOME_EMPRESA 40

#define MSG_OBTER_NIF_EMPRESA "\nInsira o NIF da empresa (1000000000-1999999999):"
#define MAX_NIF_EMPRESA 1999999999
#define MIN_NIF_EMPRESA 1000000000

#define MSG_OBTER_EMAIL "\nInsira o email da empresa:"
#define MAX_EMAIL 40

#define MSG_OBTER_RUA "\nInsira a rua da empresa:"
#define MAX_RUA 40

#define MSG_OBTER_LOCALIDADE "\nInsira a localidade da empresa:"
#define MAX_LOCALIDADE 40

#define MSG_OBTER_COD_POSTAL "\nInsira o codigo postal da empresa:"
#define MAX_COD_POSTAL 8


#define EMPRESAS_TAM_INICIAL 2

#define EMPRESA_REGISTADA_SUCESSO "\n------ EMPRESA REGISTADA COM SUCESSO ------\n\n"
#define EMPRESA_EDITADA_SUCESSO "\n------ EMPRESA ATUALIZADA COM SUCESSO ------\n\n"
#define EMPRESA_REMOVIDA_SUCESSO "\n------ EMPRESA REMOVIDA COM SUCESSO ------\n\n"

#define BARRA "----------------------------------------\n"

/**
 * @brief As estruturas de dados que armazenam os dados das empresas
 */

typedef struct {
    char nomeEmpresa[MAX_NOME_EMPRESA];
    int NIF;
    char email[MAX_EMAIL];
    char rua[MAX_RUA];
    char localiade[MAX_LOCALIDADE];
    char codPostal[MAX_COD_POSTAL];
} Empresa;

typedef struct {
    int contador, tamanho;
    Empresa *empresa;
} Empresas;

/**
 * @brief A estrutura de dados que permite formatar datas
 */

typedef struct {
    int diaInicial, mesInicial, anoInicial;
    int diaFinal, mesFinal, anoFinal;
} Data;

/**
 * @brief Ficheiros utilizados para guardar os registos
 */
#define VEND_DB_FILE "vendedores.bin"
#define MERC_DB_FILE "mercados.bin"
#define COMISSOES_DB_FILE "comissoes.bin"
#define COMISSOES_TXT_FILE "comissoes.txt"

/**
 * @brief Funções destinadas aos vendedores
 */

void imprimirEmpresas(Empresa empresa);
void apagarDadosEmpresas(Empresa *empresa);
int procurarEmpresa(Empresas empresas, int NIF);
void carregarEmpresas(Empresas *empresas, char *ficheiro);
void libertarEmpresas(Empresas *empresas);
int registarEmpresa(Empresas *empresas);
void editarEmpresa(Empresa *empresa);
void expandirEmpresas(Empresas *empresas);
void registarEmpresas(Empresas *empresas);
void removerEmpresa(Empresa *empresa);
//void removerEmpresas(Empresas *empresas, Comissoes *comissoes);
void editarEmpresas(Empresas *empresas);
void listarEmpresas(Empresas empresas);
int obterPosicaoEmpresa(int NIF, Empresas empresas);
void guardarEmpresas(Empresas *vendedores, char *ficheiro);
//void obterListaEmpresas(Comissoes *comissoes, Vendedores *vendedores);

#endif /* FUNCOES_H */


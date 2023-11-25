/* 
 * File:   funcoes.h
 * Author: paulo
 *
 * Created on 15 de fevereiro de 2023, 10:19
 */

#ifndef FUNCOES_H
#define FUNCOES_H

/**
 * @brief Macros usadas na gestão de Vendedores 
 */

#define VENDEDOR_NAO_EXISTE "\n------ VENDEDOR INEXISTENTE ------\n\n"
#define VENDEDOR_EXISTE "\n------ VENDEDOR JÁ EXISTENTE ------\n\n"
#define VENDEDORES_LISTA_CHEIA "\n------ NÃO É POSSÍVEL INSERIR OUTRO VENDEDOR ------\n\n"
#define VENDEDORES_LISTA_VAZIA "\n------ LISTA DE VENDEDORES VAZIA ------\n\n"

#define MSG_OBTER_ID_VENDEDOR "\nInsira o id do vendedor (10000-99999):"
#define MAX_ID_VENDEDOR 99999
#define MIN_ID_VENDEDOR 10000

#define MSG_OBTER_EMAIL "\nInsira o email do vendedor:"
#define MAX_EMAIL 30

#define MSG_OBTER_TELEFONE "\nInsira o numero de telefone do vendedor:"
#define MAX_TELEFONE 1000000000
#define MIN_TELEFONE 99999999

#define MSG_OBTER_NOME_VENDEDOR "\nInsira o nome do vendedor:"
#define MAX_NOME_VENDEDOR 30

#define VENDEDORES_TAM_INICIAL 2

#define VENDEDOR_REGISTADO_SUCESSO "\n------ VENDEDOR REGISTADO COM SUCESSO ------\n\n"
#define VENDEDOR_EDITADO_SUCESSO "\n------ VENDEDOR ATUALIZADO COM SUCESSO ------\n\n"
#define VENDEDOR_REMOVIDO_SUCESSO "\n------ VENDEDOR REMOVIDO COM SUCESSO ------\n\n"

#define BARRA "----------------------------------------\n"
/**
 * @brief Macros usadas na gestão de Mercados
 */

#define MERCADO_NAO_EXISTE "\n------ MERCADO INEXISTENTE ------\n\n"
#define MERCADO_EXISTE "\n------ MERCADO JÁ EXISTENTE ------\n\n"
#define MERCADOS_LISTA_CHEIA "\n------ NÃO É POSSÍVEL INSERIR OUTRO MERCADO ------\n\n"
#define MERCADOS_LISTA_VAZIA "\n------ LISTA DE MERCADOS VAZIA ------\n\n"
#define MERCADOS_COMISSOES "\n------ MERCADO COM COMISSOES ASSOCIADAS ------\n\n"

#define MSG_OBTER_ID_MERCADO "\nInsira o id do mercado(1000-9999):"
#define MAX_ID_MERCADO 9999
#define MIN_ID_MERCADO 1000

#define MSG_OBTER_NOME_MERCADO "\nInsira o nome do mercado:"
#define MAX_NOME_MERCADO 30

#define MSG_OBTER_PERCENTAGEM "\nInsira a percentagem de comissao (1-49):"
#define MAX_PERCENTAGEM 49
#define MIN_PERCENTAGEM 1

#define MERCADOS_TAM_INICIAL 2

#define MERCADO_REGISTADO_SUCESSO "\n------ MERCADO REGISTADO COM SUCESSO ------\n\n"
#define MERCADO_EDITADO_SUCESSO "\n------ MERCADO ATUALIZADO COM SUCESSO ------\n\n"
#define MERCADO_REMOVIDO_SUCESSO "\n------ MERCADO REMOVIDO COM SUCESSO ------\n\n"

/**
 * @brief Macros usadas na gestão de Comissões
 */

#define COMISSAO_NAO_EXISTE "\n------ COMISSAO INEXISTENTE ------\n\n"
#define COMISSAO_EXISTE "\n------ COMISSAO JA EXISTENTE ------\n\n"
#define COMISSAO_LISTA_CHEIA "\n------ NÃO É POSSÍVEL INSERIR OUTRA COMISSAO ------\n\n"
#define COMISSAO_LISTA_VAZIA "\n------ LISTA DE COMISSOES VAZIA ------\n\n"

#define MSG_ASSOC_VENDEDOR "Insira o mercado ao qual quer associar o vendedor: "

#define COMISSOES_TAM_INICIAL 2

#define COMISSAO_REGISTADA_SUCESSO "\n------ COMISSAO REGISTADA COM SUCESSO ------\n\n"

#define MESES_COMISSOES_MIN 1
#define MESES_COMISSOES_MAX 24

/**
 * @brief As estruturas de dados que armazenam os dados dos vendedores
 */

typedef struct{
    int idVendedor;
    char nomeVendedor[MAX_NOME_VENDEDOR];
    int telefone;
    char email[MAX_EMAIL];
    int estado;
}Vendedor;

typedef struct{
    int contador, tamanho;
    Vendedor *vendedor;
}Vendedores;

/**
 * @brief As estruturas de dados que armazenam os dados dos mercados
 */

typedef struct{
    int idMercado;
    char nomeMercado[MAX_NOME_MERCADO];
    int percentagem;
    int estado;
}Mercado;

typedef struct{
    int contador, tamanho;
    Mercado *mercado;
}Mercados;

/**
 * @brief A estrutura de dados que permite formatar datas
 */

typedef struct {
    int diaInicial, mesInicial, anoInicial;
    int diaFinal, mesFinal, anoFinal;
} Data;

/**
 * @brief As estruturas de dados que armazenam os dados das comissões
 */

typedef struct{
    int idMercado;
    int idVendedor;
    int percentagem;
    Data dataComissao;
}Comissao;

typedef struct{
    int contador, tamanho;
    Comissao *comissao;
}Comissoes;

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

void imprimirVendedores(Vendedor vendedor);
void apagarDadosVendedores(Vendedor *vendedor);
int procurarVendedor(Vendedores vendedores, int idVendedor);
void carregarVendedores(Vendedores *vendedores, char *ficheiro);
void libertarVendedores(Vendedores *vendedores);
int registarVendedor(Vendedores *vendedores);
void editarVendedor(Vendedor *vendedor);
void expandirVendedores(Vendedores *vendedores);
void registarVendedores(Vendedores *vendedores);
void removerVendedor(Vendedor *vendedor);
void removerVendedores(Vendedores *vendedores, Comissoes *comissoes);
void editarVendedores(Vendedores *vendedores);
void listarVendedores(Vendedores vendedores);
int obterPosicaoVendedor(int idVendedor, Vendedores vendedores);
void guardarVendedores(Vendedores *vendedores, char *ficheiro);
void obterListaVendedores(Comissoes *comissoes, Vendedores *vendedores);

/**
 * @brief Funções destinadas aos mercados
 */

void imprimirMercados(Mercado mercado);
void apagarDadosMercados(Mercado *mercado);
int procurarMercado(Mercados mercados, int idMercado);
void carregarMercados(Mercados *mercados, char *ficheiro);
void libertarMercados(Mercados *mercados);
int registarMercado(Mercados *mercados);
void editarMercado(Mercado *mercado);
void expandirMercados(Mercados *mercados);
void registarMercados(Mercados *mercados);
void removerMercado(Mercado *mercado);
void removerMercados(Mercados *mercados, Comissoes *comissoes);
void editarMercados(Mercados *mercados);
void listarMercados(Mercados mercados);
int obterPosicaoMercado(int idMercado, Mercados mercados);
void guardarMercados(Mercados *mercados, char *ficheiro);
void obterListaMercados(Comissoes *comissoes, Mercados *mercados);

/**
 * @brief Funções destinadas às comissões
 */

void imprimirComissoes(Comissao comissao);
int verificarDataComissao(Comissoes comissoes, int idMercado, int idVendedor, Data novaData);
int procurarVendComissao(Comissoes comissoes, int idVendedor);
int procurarMercComissao(Comissoes comissoes, int idMercado);
void carregarComissoes(Comissoes *comissoes, char *ficheiro);
void libertarComissoes(Comissoes *comissoes);
int registarComissao(Comissoes *comissoes, Vendedores *vendedores, Mercados *mercados);
void expandirComissoes(Comissoes *comissoes);
void registarComissoes(Comissoes *comissoes, Vendedores *vendedores, Mercados *mercados);
int exportarComissoes(Comissoes comissoes, char* ficheiroBin, char* ficheiroTxt);
void listarComissoes(Comissoes comissoes);
void guardarComissoes(Comissoes *comissoes, char *ficheiro);

#endif /* FUNCOES_H */


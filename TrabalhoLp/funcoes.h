/* 
 * File:   funcoes.h
 * Author: paulo
 *
 * Created on 15 de fevereiro de 2023, 10:19
 */

#ifndef FUNCOES_H
#define FUNCOES_H

/**
 * @brief Ficheiros utilizados para guardar os registos
 */
#define EMP_DB_FILE "empresas.bin"
#define RAMOS_DB_FILE "ramos.bin"
#define COMENTS_DB_FILE "comentarios.bin"

#define MSG_OBTER_NOME_UTILIZADOR_EMAIL "\nInsira o nome de utilizador (identificador antes de @):"
#define MAX_NOME_UTILIZADOR_EMAIL 50

#define MSG_OBTER_DOMINIO "\nInsira o dominio (serviço de email):"
#define MAX_DOMINIO 50

#define MSG_OBTER_COD_POSTAL_PREFIXO "\nInsira o prefixo do codigo postal da empresa:"
#define MIN_COD_POSTAL_PREFIXO 1000
#define MAX_COD_POSTAL_PREFIXO 9999

#define MSG_OBTER_COD_POSTAL_SUFIXO "\nInsira o sufixo do codigo postal da empresa:"
#define MIN_COD_POSTAL_SUFIXO 100
#define MAX_COD_POSTAL_SUFIXO 999

typedef struct{
    int prefixo;
    int sufixo;
}CodigoPostal;

typedef struct {
    char nomeUtilizador[MAX_NOME_UTILIZADOR_EMAIL];
    char dominio[MAX_DOMINIO];
} EnderecoEmail;

#endif /* FUNCOES_H */


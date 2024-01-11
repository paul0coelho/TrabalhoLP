/**
* @file funcoes.h
* @author 8220195 e 8220196
* @date 10-01-2024
*
*
* @brief Header file que contém macros e estruturas para a validação de emails e códigos postais.
*
*/

#ifndef FUNCOES_H
#define FUNCOES_H

/**
 * @brief Ficheiros utilizados para guardar os registos
 */
#define EMP_DB_FILE "empresas.bin"
#define RAMOS_DB_FILE "ramos.bin"
#define COMENTS_DB_FILE "comentarios.bin"

/**
 * @brief Macros usadas na gestão de emails
 */
#define MSG_OBTER_NOME_UTILIZADOR_EMAIL "\nInsira o nome de utilizador (identificador antes de @):"
#define MAX_NOME_UTILIZADOR_EMAIL 50

#define MSG_OBTER_DOMINIO "\nInsira o dominio (serviço de email):"
#define MAX_DOMINIO 50

/**
 * @brief Macros usadas na gestão de códigos postais
 */
#define MSG_OBTER_COD_POSTAL_PREFIXO "\nInsira o prefixo do codigo postal da empresa:"
#define MIN_COD_POSTAL_PREFIXO 1000
#define MAX_COD_POSTAL_PREFIXO 9999

#define MSG_OBTER_COD_POSTAL_SUFIXO "\nInsira o sufixo do codigo postal da empresa:"
#define MIN_COD_POSTAL_SUFIXO 100
#define MAX_COD_POSTAL_SUFIXO 999

/**
 * @brief A estrutura de dados que armazena os dados do código postal
 */
typedef struct{
    int prefixo;
    int sufixo;
}CodigoPostal;

/**
 * @brief A estrutura de dados que armazena os dados do email
 */
typedef struct {
    char nomeUtilizador[MAX_NOME_UTILIZADOR_EMAIL];
    char dominio[MAX_DOMINIO];
} EnderecoEmail;

#endif /* FUNCOES_H */


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


typedef struct{
    int prefixo;
    int sufixo;
}CodigoPostal;

#endif /* FUNCOES_H */


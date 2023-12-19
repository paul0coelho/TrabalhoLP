/* 
 * File:   funcoes.h
 * Author: paulo
 *
 * Created on 15 de fevereiro de 2023, 10:19
 */

#ifndef FUNCOES_H
#define FUNCOES_H

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
#define EMP_DB_FILE "empresas.bin"
#define RAMOS_DB_FILE "ramos.bin"
#define COMENTS_DB_FILE "comentarios.bin"

#endif /* FUNCOES_H */


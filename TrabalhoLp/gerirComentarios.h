/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/cFiles/file.h to edit this template
 */

/* 
 * File:   comentarios.h
 * Author: paulo
 *
 * Created on 19 de dezembro de 2023, 14:43
 */

#ifndef COMENTARIOS_H
#define COMENTARIOS_H

typedef struct {
    char nomeUtilizador[100];
    char nomeEmpresa[100];
    char email[100];
    char titulo[100];
    char texto[500];
} Comentario;

typedef struct {
    int contador, tamanho;
    Comentario *comentario;
} Comentarios;

#endif /* COMENTARIOS_H */


/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/cFiles/file.h to edit this template
 */

/* 
 * File:   ramosAtividade.h
 * Author: paulo
 *
 * Created on 19 de dezembro de 2023, 14:40
 */

#ifndef RAMOSATIVIDADE_H
#define RAMOSATIVIDADE_H

/**
 * @brief As estruturas de dados que armazenam os dados dos ramos de atividade
 */

typedef struct {
    char nome[100];
    int ativo;
} RamoAtividade;

typedef struct {
    int contador, tamanho;
    RamoAtividade *ramoAtividade;
} RamosAtividade;

#endif /* RAMOSATIVIDADE_H */


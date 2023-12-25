/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/cFiles/main.c to edit this template
 */

/* 
 * File:   main.c
 * Author: paulo
 *
 * Created on 1 de dezembro de 2023, 15:41
 */

#include <stdio.h>
#include <stdlib.h>
#include "funcoes.h"
#include "gerirComentarios.h"
#include "gerirEmpresas.h"
#include "gerirRamosAtividade.h"

/*
 * 
 */
void menuAdmin(Empresas *empresas, RamosAtividade *ramosAtividade, Comentarios *comentarios) {
    int opcao;

    do {
        printf("-------- ADMINISTRADOR --------\n");
        printf("\t1 - Gerir o Catálogo de Empresas\n");
        printf("\t2 - Gerir Ramos de Atividade\n");
        printf("\t3 - Gerir Comentários\n");
        printf("\t4 - Visualizar Relatórios\n");
        printf("\t0 - Sair\n");

        opcao = obterInt(0, 3, "\nOpção: ");

        switch (opcao) {
            case 0:
                puts("");
                break;
            case 1:
                menuEmpresas(empresas, ramosAtividade);
                puts("");
                break;
            case 2:
                menuRamosAtividade(ramosAtividade);
                puts("");
                break;
            case 3:
                //menuComentarios(comentarios);
                puts("");
                break;
            case 4:
                //relatorios();
                break;
            default:
                printf("Insira uma opção válida");
                puts("");
                break;
        }

    } while (opcao != 0);
}

void menuEmpresas(Empresas *empresas, RamosAtividade *ramosAtividade) {
    int opcao;

    do {
        printf("-------- GESTÃO DE EMPRESAS --------\n");
        printf("\t1 - Registar empresa\n");
        printf("\t2 - Remover Empresa\n");
        printf("\t3 - Editar empresa\n");
        printf("\t4 - Guardar alterações\n");
        printf("\t0 - Sair\n");

        opcao = obterInt(0, 4, "\nOpção: ");

        switch (opcao) {
            case 0:
                puts("");
                break;
            case 1:
                //registarEmpresa(empresas);
                puts("");
                break;
            case 2:
                //removerEmpresa(empresas);
                break;
            case 3:
                //editarEmpresa(empresas);
                break;
            case 4:
                //guardarAlteracoes(empresas);
                break;
            default:
                printf("Insira uma opção válida");
                break;
        }

    } while (opcao != 0);
}

void menuRamosAtividade(RamosAtividade *ramosAtividade) {
    int opcao;

    do {
        printf("-------- GESTÃO DE RAMOS DE ATIVIDADE --------\n");
        printf("\t1 - Registar ramo de atividade\n");
        printf("\t2 - Remover ramo de atividade\n");
        printf("\t3 - Editar ramo de atividade\n");
        printf("\t4 - Guardar alterações\n");
        printf("\t0 - Sair\n");

        opcao = obterInt(0, 4, "\nOpção: ");

        switch (opcao) {
            case 0:
                puts("");
                break;
            case 1:
                //registarRamoDeAtividade(ramosAtividade);
                puts("");
                break;
            case 2:
                //removerRamoDeAtividade(ramosAtividade);
                break;
            case 3:
                //editarRamoDeAtividade(ramosAtividade);
                break;
            case 4:
                //guardarAlteracoes(ramosAtividade);
                break;
            default:
                printf("Insira uma opção válida");
                break;
        }

    } while (opcao != 0);
}

void menuUser(Empresas *empresas, Comentarios *comentarios) {
    int opcao;

    do {
        printf("-------- UTILIZADOR --------\n");
        printf("\t1 - Pesquisar empresas\n");
        printf("\t2 - Classificar Empresa\n");
        printf("\t3 - Comentar Empresa\n");
        printf("\t0 - Sair\n");

        opcao = obterInt(0, 3, "\nOpção: ");

        switch (opcao) {
            case 0:
                puts("");
                break;
            case 1:
                //pesquisarEmpresa(empresas);
                puts("");
                break;
            case 2:
                //classificarEmpresa(empresas);
                puts("");
                break;
            case 3:
                //comentarEmpresa(comentarios);
                puts("");
                break;
            default:
                printf("Insira uma opção válida");
                puts("");
                break;
        }

    } while (opcao != 0);
}

void menuPrincipal(Empresas *empresas, RamosAtividade *ramosAtividade, Comentarios *comentarios) {
    int opcao;

    do {
        printf("----------- Selecione o seu perfl de utilizador -----------\n");
        printf("\t1 - Administrador\n");
        printf("\t2 - Utilizador\n");
        printf("\t0 - Sair\n");

        opcao = obterInt(0, 2, "\nOpção: ");

        switch (opcao) {
            case 1:
                menuAdmin(empresas, ramosAtividade, comentarios);
                break;
            case 2:
                menuUser(empresas, comentarios);
                break;
            case 0:
                return;
            default:
                puts("Insira uma opção válida!");
                break;
        }

    } while (opcao);
}

int main() {

    Empresas empresas;
    Comentarios comentarios;
    RamosAtividade ramosAtividade;

    carregarEmpresas(&empresas, EMP_DB_FILE);
    carregarComentarios(&comentarios, COMENTS_DB_FILE);
    carregarRamosAtividade(&ramosAtividade, RAMOS_DB_FILE);

    menuPrincipal(&empresas, &ramosAtividade, &comentarios);

    libertarEmpresas(&empresas);
    libertarComentarios(&comentarios);
    libertarRamosAtividade(&ramosAtividade);

    return (EXIT_SUCCESS);
}


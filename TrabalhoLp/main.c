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
void menuAdmin() {
    int opcao;

    do {
        printf("-------- ADMINISTRADOR --------\n");
        printf("\t1 - Gerir o Catálogo de Empresas\n");
        printf("\t2 - Gerir Ramos de Atividade\n");
        printf("\t3 - Visualizar Relatórios\n");
        printf("\t0 - Sair\n");

        opcao = obterInt(0, 3, "\nOpção: ");

        switch (opcao) {
            case 0:
                puts("");
                break;
            case 1:
                menuEmpresas();
                puts("");
                break;
            case 2:
                menuRamosAtividade();
                puts("");
                break;
            case 3:
                //relatóriox();
                //realtórioy();
                puts("");
                break;
            default:
                printf("Insira uma opção válida");
                puts("");
                break;
        }

    } while (opcao != 0);
}

void menuEmpresas() {
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
                //registarEmpresa();
                puts("");
                break;
            case 2:
                //removerEmpresa();
                break;
            case 3:
                //editarEmpresa();
                break;
            case 4:
                break;
            default:
                printf("Insira uma opção válida");
                break;
        }

    } while (opcao != 0);
}

void menuRamosAtividade() {
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
                //registarRamoDeAtividade();
                puts("");
                break;
            case 2:
                //removerRamoDeAtividade();
                break;
            case 3:
                //editarRamoDeAtividade();
                break;
            case 4:
                break;
            default:
                printf("Insira uma opção válida");
                break;
        }

    } while (opcao != 0);
}

void menuUser() {
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
                //pesquisarEmpresa(nomeEmpresa,categoria,ramoDeAtividade);
                puts("");
                break;
            case 2:
                //classificarEmpresa(nomeEmpresa,nota);
                puts("");
                break;
            case 3:
                //comentarEmpresa(nomeEmpresa,comentario,nome,email);
                puts("");
                break;
            default:
                printf("Insira uma opcão válida");
                puts("");
                break;
        }

    } while (opcao != 0);

}

void menuPrincipal() {
    int opcao;

    do {
        printf("----------- Selecione o seu perfl de utilizador -----------\n");
        printf("\t1 - Administrador\n");
        printf("\t2 - Utilizador\n");
        printf("\t0 - Sair\n");

        opcao = obterInt(0, 2, "\nOpção: ");

        switch (opcao) {
            case 1:
                menuAdmin();
                break;
            case 2:
                menuUser();
                break;
            case 0:
                return;
            default:
                puts("Insira uma opcão válida!");
                break;
        }

    } while (opcao);
}

int main() {

    menuPrincipal();

    return (EXIT_SUCCESS);
}


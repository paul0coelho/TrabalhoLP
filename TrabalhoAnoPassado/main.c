/* 
 * File:   main.c
 * Author: paulo
 *
 * Created on 15 de fevereiro de 2023, 10:16
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * @brief Bibliotecas utilizadas
 */

#include "funcoes.h"
#include "input.h"

void menuComissoes(){
    int opcao;
    Mercados mercados;
    Vendedores vendedores;
    Comissoes comissoes;

    carregarComissoes(&comissoes, COMISSOES_DB_FILE);
    carregarMercados(&mercados, MERC_DB_FILE);
    carregarVendedores(&vendedores, VEND_DB_FILE);

    do {

        printf("-------- GESTÃO DE COMISSÕES --------\n");
        printf("\t1 - Inserir Comissão\n");
        printf("\t2 - Listagem de Mercados por comissões\n");
        printf("\t3 - Listagem de Vendedores por comissões\n");
        printf("\t4 - Listagem total de comissões\n");
        printf("\t5 - Exportar Comissão\n");
        printf("\t6 - Guardar comissões registadas\n");
        printf("\t0 - Sair\n");
        printf("\nComissões: %d-%d", comissoes.contador, comissoes.tamanho);

        opcao = obterInt(0, 6, "\nOpção: ");

        switch (opcao) {
            case 0:
                puts("");
                break;
            case 1:
                registarComissoes(&comissoes, &vendedores, &mercados);
                puts("");
                break;
            case 2:
                obterListaMercados(&comissoes, &mercados);
                break;
            case 3:
                obterListaVendedores(&comissoes, &vendedores);
                break;
            case 4:
                listarComissoes(comissoes);
                break;
            case 5:
                if (exportarComissoes(comissoes, COMISSOES_DB_FILE, COMISSOES_TXT_FILE) == 1)
                    printf("\n-----FICHEIRO EXPORTADO COM SUCESSO -----\n");
                else
                    printf("\n-----FICHEIRO EXPORTADO SEM SUCESSO -----\n");
                break;
            case 6:
                guardarComissoes(&comissoes, COMISSOES_DB_FILE);
                break;
            default:
                printf("Insira uma opção válida");
                break;
        }

    } while (opcao != 0);

    libertarComissoes(&comissoes);
}

void menuVendedores(){
    int opcao;
    Mercados mercados;
    Vendedores vendedores;
    Comissoes comissoes;
    
    carregarVendedores(&vendedores, VEND_DB_FILE);
    
    do {
        

        printf("-------- GESTÃO DE VENDEDORES --------\n");
        printf("\t1 - Inserir Vendedores\n");
        printf("\t2 - Remover Vendedores\n");
        printf("\t3 - Editar Vendedores\n");
        printf("\t4 - Listagem de Vendedores\n");
        printf("\t5 - Guardar alterações nos Vendedores\n");
        printf("\t0 - Sair\n");
        printf("\nVendedores: %d-%d", vendedores.contador, vendedores.tamanho);

        opcao = obterInt(0, 5, "\nOpção: ");

        switch (opcao) {
            case 0:
                puts("");
                break;
            case 1:
                registarVendedores(&vendedores);
                puts("");
                break;
            case 2:
                removerVendedores(&vendedores, &comissoes);
                puts("");
                break;
            case 3:
                editarVendedores(&vendedores);
                puts("");
                break;
            case 4:
                listarVendedores(vendedores);
                break;
            case 5:
                guardarVendedores(&vendedores, VEND_DB_FILE);
                break;
            default:
                printf("Insira uma opção válida");
                puts("");
                break;
        }

    } while (opcao != 0);

    libertarVendedores(&vendedores);

}
void menuMercados(){
    int opcao;
    Mercados mercados;
    Vendedores vendedores;
    Comissoes comissoes;
    
    carregarMercados(&mercados, MERC_DB_FILE);
    
    do {
        
        printf("-------- GESTÃO DE MERCADOS --------\n");
        printf("\t1 - Inserir Mercados\n");
        printf("\t2 - Remover Mercados\n");
        printf("\t3 - Editar Mercados\n");
        printf("\t4 - Listagem de Mercados\n");
        printf("\t5 - Guardar alterações nos Mercados\n");
        printf("\t0 - Sair\n");
        printf("\nMercados: %d-%d", mercados.contador, mercados.tamanho);

        opcao = obterInt(0, 5, "\nOpção: ");

        switch (opcao) {
            case 0:
                puts("");
                break;
            case 1:
                registarMercados(&mercados);
                puts("");
                break;
            case 2:
                removerMercados(&mercados, &comissoes);
                puts("");
                break;
            case 3:
                editarMercados(&mercados);
                puts("");
                break;
            case 4:
                listarMercados(mercados);
                break;
            case 5:
                guardarMercados(&mercados, MERC_DB_FILE);
                break;
            default:
                printf("Insira uma opcão válida");
                puts("");
                break;
        }

    } while (opcao != 0);

    libertarMercados(&mercados);

}

void menuPrincipal(){
    int opcao;
    
    do {

        printf("----------- MÓVEIS PARA TODOS -----------\n");
        printf("\t1 - Gestão de Vendedores\n");
        printf("\t2 - Gestão de Mercados\n");
        printf("\t3 - Gestão de Comissões\n");
        printf("\t0 - Sair\n");
        puts(BARRA);

        opcao = obterInt(0, 3, "\nOpção: ");
        
        switch (opcao) {
            case 1:
                menuVendedores();
                break;
            case 2:
                menuMercados();
                break;
            case 3:
                menuComissoes();
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


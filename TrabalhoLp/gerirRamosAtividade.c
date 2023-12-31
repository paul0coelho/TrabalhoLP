/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/cFiles/file.c to edit this template
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "gerirRamosAtividade.h"
#include "gerirEmpresas.h" 
#include "input.h"

/**
 * @brief Esta função mostra no ecrã os dados existentes do registo dos ramos de atividade
 * 
 * @param ramoAtividade struct RamoAtividade
 */
void imprimirRamoAtividade(RamoAtividade ramoAtividade) {

    printf("\tNome: %s\n", ramoAtividade.nome);
    puts(BARRA);

}

/**
 * @brief Esta função "apaga" o registo dos ramos de atividade
 * 
 * @param ramoAtividade apontador para a struct RamoAtividade
 */
void apagarDadosRamoAtividade(RamoAtividade *ramoAtividade) {

    strcpy(ramoAtividade->nome, "");
}

/**
 * @brief Esta função verifica se o ramo de atividade existe nos registos dos RamosAtividade
 * 
 * @param ramosAtividade struct RamosAtividade
 * @param nome
 * @return 1 se o ramo de atividade existir e 0 se ele não existir
 */
int procurarRamoAtividade(RamosAtividade ramosAtividade, char nome[]) {
    int i;
    for (i = 0; i < ramosAtividade.contador; i++) {
        if (strcmp(ramosAtividade.ramoAtividade[i].nome, nome) == 0) {
            return 1;
        }
    }

    return 0;
}

/**
 * @brief Procura se um ramo de atividade existe, caso se confirme retorna a posição no registo RamosAtividade, se não existir retorna -1
 * 
 * @param nome
 * @param ramosAtividade struct RamosAtividade
 * @return i se o ramo de atividade existir, -1 caso não exista
 */
int obterPosicaoRamoAtividade(char nome[], RamosAtividade ramosAtividade) {
    for (int i = 0; i < ramosAtividade.contador; i++) {
        if (strcmp(ramosAtividade.ramoAtividade[i].nome, nome) == 0) {
            return i;
        }
    }
    return -1;
}

/**
 * @brief Esta função verifica se o ficheiro existe(rb), senão cria-o (wb)
 * Com a função fread é retornado o número de itens completos lidos pela função
 * 
 * @param ramosAtividade apontador para a struct RamosAtividade
 * @param ficheiro apontador para o ficheiro binário de onde serão carregados os dados
 */
void carregarRamosAtividade(RamosAtividade *ramosAtividade, char *ficheiro) {
    int i, sucesso = 0;

    // Tenta abrir o ficheiro
    FILE *fp = fopen(ficheiro, "rb");
    if (fp != NULL) {

        // Retorna o número de itens completos lidos pela função
        fread(&ramosAtividade->contador, sizeof (int), 1, fp);

        if (ramosAtividade->contador > 0) {
            ramosAtividade->ramoAtividade = (RamoAtividade*) malloc(ramosAtividade->contador * sizeof (RamoAtividade));
            ramosAtividade->tamanho = ramosAtividade->contador;
            fread(ramosAtividade->ramoAtividade, sizeof (RamoAtividade), ramosAtividade->contador, fp);

            sucesso = 1;
        }
        fclose(fp);
    }

    if (!sucesso) {
        fp = fopen(ficheiro, "wb");
        if (fp != NULL) {

            ramosAtividade->ramoAtividade = (RamoAtividade*) malloc(RAMOS_TAM_INICIAL * sizeof (RamoAtividade));
            ramosAtividade->contador = 0;
            ramosAtividade->tamanho = RAMOS_TAM_INICIAL;
            fclose(fp);
        }
    }
}

/**
 * @brief Esta função desaloca a memória alocada 
 * 
 * @param ramosAtividade apontador para a struct RamosAtividade
 */
void libertarRamosAtividade(RamosAtividade *ramosAtividade) {

    free(ramosAtividade->ramoAtividade);

}

/**
 * @brief Cria um novo ramo de atividade
 * Insere um novo registo em RamosAtividade e o contador aumenta por 1
 * 
 * @param ramosAtividade apontador para struct RamosAtividade
 * @return -1 se o ramo de atividade já existir ou retorna o número do contador se os dados foram registados com sucesso
 */
int registarRamoAtividade(RamosAtividade *ramosAtividade) {
    char nome[MAX_RAMO];

    lerString(nome, MAX_RAMO, MSG_OBTER_RAMO);

    if (procurarRamoAtividade(*ramosAtividade, nome) == 0) {

        lerString(ramosAtividade->ramoAtividade[ramosAtividade->contador].nome, MAX_RAMO, MSG_OBTER_RAMO);
        ramosAtividade->ramoAtividade[ramosAtividade->contador].estado = 1;

        return ramosAtividade->contador++;
    }
    return -1;
}

/**
 * @brief Esta função atualiza os dados de um ramo de atividade
 * 
 * @param ramoAtividade apontador para a struct RamoAtividade
 */
void editarRamoAtividade(RamoAtividade *ramoAtividade) {

    lerString((*ramoAtividade).nome, MAX_RAMO, MSG_OBTER_RAMO);
}

/**
 * @brief Verifica se o código do vendedor inserido pelo utilizador existe
 * Se sim chama-se a função editarVendedor() que vai mudar os dados do vendedor
 * 
 * @param vendedores apontador para a struct Vendedores
 */
void editarRamosAtividade(RamosAtividade *ramosAtividade) {
    char nome[MAX_RAMO];
    
    lerString(nome, MAX_RAMO, MSG_OBTER_RAMO);

    int pos = obterPosicaoRamoAtividade(nome, *ramosAtividade);

    if (pos != -1) {
        editarRamoAtividade(&(*ramosAtividade).ramoAtividade[pos]);
        puts(RAMO_EDITADO_SUCESSO);
    } else {
        puts(RAMO_NAO_EXISTE);
    }
}

/**
 * @brief Esta função aumenta o tamanho da memória para registar ramos de atividade
 * 
 * @param ramosAtividade apontador para a struct RamosAtividade
 */
void expandirRamosAtividade(RamosAtividade *ramosAtividade) {
    RamoAtividade *temp = (RamoAtividade*) realloc(ramosAtividade->ramoAtividade, sizeof (RamoAtividade) * (ramosAtividade->tamanho * 2));
    if (temp != NULL) {
        ramosAtividade->tamanho *= 2;
        ramosAtividade->ramoAtividade = temp;
    }
}

/**
 * @brief Verifica se o número do contador e do tamanho são iguais, se sim chama a função expandirRamosAtividade()
 * Caso o contador seja menor que o tamanho verifica-se se o registo do ramo de atividade correu bem, caso não corresse retorna -1 e aparece uma mensagem (RAMO_EXISTE)
 * 
 * @param ramosAtividade apontador para a struct RamosAtividade
 */
void registarRamosAtividade(RamosAtividade *ramosAtividade) {
    if (ramosAtividade->contador == ramosAtividade->tamanho) {
        expandirRamosAtividade(ramosAtividade);
    }

    if (ramosAtividade->contador < ramosAtividade->tamanho) {
        if (registarRamoAtividade(ramosAtividade) == -1) {
            puts(RAMO_EXISTE);
        } else {
            puts(RAMO_REGISTADO_SUCESSO);
        }
    } else {
        puts(RAMO_LISTA_CHEIA);
    }
}

/**
 * @brief Esta função lista os ramos de atividade existentes
 * 
 * @param ramosAtividade struct RamosAtividade
 */
void listarRamosAtividade(RamosAtividade ramosAtividade) {
    int i;

    if (ramosAtividade.contador > 0) {
        printf("\n--------------- RAMOS DE ATIVIDADE ---------------\n\n");
        for (i = 0; i < ramosAtividade.contador; i++) {
            imprimirRamoAtividade(ramosAtividade.ramoAtividade[i]);
        }
    } else {
        puts(RAMO_LISTA_VAZIA);
    }
}

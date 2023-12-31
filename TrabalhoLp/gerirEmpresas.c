#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "gerirComentarios.h"
#include "gerirRamosAtividade.h"
#include "gerirEmpresas.h"
#include "input.h"

/**
 * @brief Esta função mostra no ecrã os dados existentes do registo das empresas
 * 
 * @param empresa struct Empresa
 */
void imprimirEmpresas(Empresa empresa) {

    printf("\tNome: %s\n", empresa.nomeEmpresa);
    printf("\tRamo de atividade: %s\n", empresa.ramoAtividade);
    printf("\tNIF: %d\n", empresa.NIF);
    printf("\tRua: %s\n", empresa.rua);
    printf("\tLocalidade: %s\n", empresa.localidade);
    printf("\tCódigo Postal: %s\n", empresa.codPostal);
    puts(BARRA);

}

/**
 * @brief Esta função "apaga" o registo das empresas
 * 
 * @param empresa apontador para a struct Empresa
 */

void apagarDadosEmpresas(Empresa *empresa) {

    empresa->NIF = 0;
    strcpy(empresa->nomeEmpresa, "");
    strcpy(empresa->rua, "");
    strcpy(empresa->localidade, "");
    strcpy(empresa->codPostal, "");
}

/**
 * @brief Esta função verifica se a empresa existe nos registos das Empresas
 * 
 * @param empresas struct Empresas
 * @param NIF
 * @return 1 se a empresa existir e 0 se ela não existir
 */

int procurarEmpresa(Empresas empresas, int NIF) {
    int i;
    for (i = 0; i < empresas.contador; i++) {
        if (empresas.empresa[i].NIF == NIF) {
            return 1;
        }
    }

    return 0;
}

/**
 * @brief Procura se uma empresa existe, caso se confirme retorna a posição no registo Empresas, se não existir retorna -1
 * 
 * @param NIF
 * @param empresas struct Empresas
 * @return i se a empresa existir, -1 caso não exista
 */
int obterPosicaoEmpresa(int NIF, Empresas empresas) {
    for (int i = 0; i < empresas.contador; i++) {
        if (empresas.empresa[i].NIF == NIF) {
            return i;
        }
    }
    return -1;
}

/**
 * @brief Esta função verifica se o ficheiro existe(rb), senão cria-o (wb)
 * Com a função fread é retornado o número de itens completos lidos pela função
 * 
 * @param empresas apontador para a struct Empresas
 * @param ficheiro apontador para o ficheiro binário de onde serão carregados os dados
 */
void carregarEmpresas(Empresas *empresas, char *ficheiro) {
    int i, sucesso = 0;

    FILE *fp = fopen(ficheiro, "rb");
    if (fp != NULL) {

        fread(&empresas->contador, sizeof (int), 1, fp);

        if (empresas->contador > 0) {
            empresas->empresa = (Empresa*) malloc(empresas->contador * sizeof (Empresa));
            empresas->tamanho = empresas->contador;
            fread(empresas->empresa, sizeof (Empresa), empresas->contador, fp);

            sucesso = 1;
        }
        fclose(fp);
    }

    if (!sucesso) {
        fp = fopen(ficheiro, "wb");
        if (fp != NULL) {

            empresas->empresa = (Empresa*) malloc(EMPRESAS_TAM_INICIAL * sizeof (Empresa));
            empresas->contador = 0;
            empresas->tamanho = EMPRESAS_TAM_INICIAL;
            fclose(fp);
        }
    }

}

/**
 * @brief Esta função desaloca a memória alocada 
 * 
 * @param empresas apontador para a struct Empresas
 */
void libertarEmpresas(Empresas *empresas) {

    free(empresas->empresa);

}

/**
 * @brief Cria um novo NIF de Empresa
 * Insere um novo registo em Empresas e o contador aumenta por 1
 * 
 * @param empresas apontador para struct Empresas
 * @return -1 se o NIF já existir ou retorna o número do contador se os dados foram registados com sucesso
 */
int registarEmpresa(Empresas *empresas, RamosAtividade *ramosAtividade) {
    int NIFNovo;

    NIFNovo = obterInt(MIN_NIF_EMPRESA, MAX_NIF_EMPRESA, MSG_OBTER_NIF_EMPRESA);

    if (procurarEmpresa(*empresas, NIFNovo) == 0) {

        empresas->empresa[empresas->contador].NIF = NIFNovo;
        lerString(empresas->empresa[empresas->contador].nomeEmpresa, MAX_NOME_EMPRESA, MSG_OBTER_NOME_EMPRESA);

        do {
            lerString(empresas->empresa[empresas->contador].ramoAtividade, MAX_NOME_RAMO_ATIVIDADE, MSG_OBTER_RAMO_ATIVIDADE);

            if (procurarRamoAtividade(*ramosAtividade, empresas->empresa[empresas->contador].ramoAtividade) == 0) {
                printf("O ramo de atividade '%s' não existe. Por favor, insira um ramo de atividade válido.\n", empresas->empresa[empresas->contador].ramoAtividade);
            }

        } while (procurarRamoAtividade(*ramosAtividade, empresas->empresa[empresas->contador].ramoAtividade) != 1);

        lerString(empresas->empresa[empresas->contador].rua, MAX_RUA, MSG_OBTER_RUA);
        lerString(empresas->empresa[empresas->contador].localidade, MAX_LOCALIDADE, MSG_OBTER_LOCALIDADE);
        lerString(empresas->empresa[empresas->contador].codPostal, MAX_COD_POSTAL, MSG_OBTER_COD_POSTAL);
        empresas->empresa[empresas->contador].estado = 1;

        return empresas->contador++;
    }
    return -1;
}

/**
 * @brief Esta função atualiza os dados de uma empresa
 * 
 * @param empresa apontador para a struct Empresa
 */
void editarEmpresa(Empresa *empresa) {

    lerString((*empresa).nomeEmpresa, MAX_NOME_EMPRESA, MSG_OBTER_NOME_EMPRESA);
    lerString((*empresa).rua, MAX_RUA, MSG_OBTER_RUA);
    lerString((*empresa).localidade, MAX_LOCALIDADE, MSG_OBTER_LOCALIDADE);
    lerString((*empresa).codPostal, MAX_COD_POSTAL, MSG_OBTER_COD_POSTAL);
}

/**
 * @brief Verifica se o código do vendedor inserido pelo utilizador existe
 * Se sim chama-se a função editarVendedor() que vai mudar os dados do vendedor
 * 
 * @param vendedores apontador para a struct Vendedores
 */
void editarEmpresas(Empresas *empresas) {
    int NIF = obterPosicaoEmpresa(obterInt(MIN_NIF_EMPRESA, MAX_NIF_EMPRESA, MSG_OBTER_NIF_EMPRESA), *empresas);
   
    if (NIF != -1) {
        editarEmpresa(&(*empresas).empresa[NIF]);
        puts(EMPRESA_EDITADA_SUCESSO);
    } else {
        puts(EMPRESA_NAO_EXISTE);
    }
}

/**
 * @brief Esta função aumenta o tamanho da memória para registar empresas
 * 
 * @param empresas apontador para a struct Empresas
 */
void expandirEmpresas(Empresas *empresas) {
    Empresa *temp = (Empresa*) realloc(empresas->empresa, sizeof (Empresa) * (empresas->tamanho * 2));
    if (temp != NULL) {
        empresas->tamanho *= 2;
        empresas->empresa = temp;
    }
}

/**
 * @brief Verifica se o número do contador e do tamanho são iguais, se sim chama a função expandirEmpresas()
 * Caso o contador seja menor que o tamanho verifica-se se o registo da empresa correu bem, caso não corresse retorna -1 e aparece uma mensagem (EMPRESA_EXISTE)
 * 
 * @param empresas apontador para a struct Empresas
 */
void registarEmpresas(Empresas *empresas, RamosAtividade *ramosAtividade) {
    if (empresas->contador == empresas->tamanho) {
        expandirEmpresas(empresas);
    }

    if (empresas->contador < empresas->tamanho) {
        if (registarEmpresa(empresas,ramosAtividade) == -1) {
            puts(EMPRESA_EXISTE);
        } else {
            puts(EMPRESA_REGISTADA_SUCESSO);
        }
    } else {
        puts(EMPRESA_LISTA_CHEIA);
    }
}

/**
 * @brief Esta função lista as empresas existentes
 * 
 * @param empresas struct Empresas
 */
void listarEmpresas(Empresas empresas) {
    int i;

    if (empresas.contador > 0) {
        printf("\n--------------- EMPRESAS ---------------\n\n");
        for (i = 0; i < empresas.contador; i++) {
            imprimirEmpresas(empresas.empresa[i]);
        }
    } else {
        puts(EMPRESA_LISTA_VAZIA);
    }
}

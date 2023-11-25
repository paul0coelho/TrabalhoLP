#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "funcoes.h"
#include "input.h"

/**
 * @brief Esta função mostra no ecrã os dados existentes do registo dos vendedores
 * 
 * @param vendedor struct Vendedor
 */
void imprimirVendedores(Vendedor vendedor) {

    printf("\tId do vendedor: %d\n", vendedor.idVendedor);
    printf("\tNome: %s\n", vendedor.nomeVendedor);
    printf("\tTelefone: %d\n", vendedor.telefone);
    printf("\tEmail: %s\n", vendedor.email);
    printf("\tEstado: %d\n", vendedor.estado);
    puts(BARRA);

}

/**
 * @brief Esta função "apaga" o registo dos vendedores
 * 
 * @param vendedor apontador para a struct Vendedor
 */

void apagarDadosVendedores(Vendedor *vendedor) {

    vendedor->idVendedor = 0;
    strcpy(vendedor->nomeVendedor, "");
    vendedor->telefone = 0;
    strcpy(vendedor->email, "");

}

/**
 * @brief Esta função verifica se o vendedor existe nos registos dos Vendedores
 * 
 * @param vendedores struct Vendedores
 * @param idVendedor
 * @return 1 se o vendedor existir e 0 se ele não existir
 */

int procurarVendedor(Vendedores vendedores, int idVendedor) {
    int i;
    for (i = 0; i < vendedores.contador; i++) {
        if (vendedores.vendedor[i].idVendedor == idVendedor) {
            return 1;
        }
    }

    return 0;
}

/**
 * @brief Procura se um vendedor existe, caso se confirme retorna a posição no registo Vendedores, se não existir retorna -1
 * 
 * @param idVendedor
 * @param vendedores struct Vendedores
 * @return i se o vendedor existir, -1 caso não exista
 */
int obterPosicaoVendedor(int idVendedor, Vendedores vendedores) {
    for (int i = 0; i < vendedores.contador; i++) {
        if (vendedores.vendedor[i].idVendedor == idVendedor) {
            return i;
        }
    }
    return -1;
}

/**
 * @brief Esta função verifica se o ficheiro existe(rb), senão cria-o (wb)
 * Com a função fread é retornado o número de itens completos lidos pela função
 * 
 * @param vendedores apontador para a struct Vendedores
 * @param ficheiro apontador para o ficheiro binário de onde serão carregados os dados
 */
void carregarVendedores(Vendedores *vendedores, char *ficheiro) {
    int i, sucesso = 0;

    //Tenta abrir o ficheiro
    FILE *fp = fopen(ficheiro, "rb");
    if (fp != NULL) {

        //retorna o número de itens completos lidos pela função
        fread(&vendedores->contador, sizeof (int), 1, fp);

        if (vendedores->contador > 0) {
            vendedores->vendedor = (Vendedor*) malloc(vendedores->contador * sizeof (Vendedor));
            vendedores->tamanho = vendedores->contador;
            fread(vendedores->vendedor, sizeof (Vendedor), vendedores->contador, fp);

            sucesso = 1;
        }
        fclose(fp);
    }

    if (!sucesso) {
        fp = fopen(ficheiro, "wb");
        if (fp != NULL) {

            vendedores->vendedor = (Vendedor*) malloc(VENDEDORES_TAM_INICIAL * sizeof (Vendedor));
            vendedores->contador = 0;
            vendedores->tamanho = VENDEDORES_TAM_INICIAL;
            fclose(fp);
        }
    }

}

/**
 * @brief Esta função desaloca a memória alocada 
 * 
 * @param vendedores apontador para a struct Vendedores
 */
void libertarVendedores(Vendedores *vendedores) {

    free(vendedores->vendedor);

}

/**
 * @brief Cria um novo id de Vendedor
 * Insere um novo registo em Vendedores e o contador aumenta por 1
 * 
 * 
 * @param vendedores apontador para struct Vendedores
 * @return -1 se o código já existir ou retorna o número do contador se os dados foram registados com sucesso
 */
int registarVendedor(Vendedores *vendedores) {
    int idVendedorNovo;
    char email[MAX_EMAIL];
    
    idVendedorNovo = obterInt(MIN_ID_VENDEDOR, MAX_ID_VENDEDOR, MSG_OBTER_ID_VENDEDOR);

    if(procurarVendedor(*vendedores, idVendedorNovo) == 0){
        
        vendedores->vendedor[vendedores->contador].idVendedor = idVendedorNovo;
        lerString(vendedores->vendedor[vendedores->contador].nomeVendedor, MAX_NOME_VENDEDOR, MSG_OBTER_NOME_VENDEDOR);
        vendedores->vendedor[vendedores->contador].telefone = obterInt(MIN_TELEFONE, MAX_TELEFONE, MSG_OBTER_TELEFONE);
        do{
            lerString(email,30,MSG_OBTER_EMAIL);
        }while(!validarEmail(email));
        
        strcpy(vendedores->vendedor[vendedores->contador].email, email);
        vendedores->vendedor[vendedores->contador].estado = 1;

        return vendedores->contador++;
    }
    return -1;
}

/**
 * @brief Esta função atualiza os dados de um vendedor
 * 
 * @param vendedor apontador para a struct Vendedores
 */
void editarVendedor(Vendedor *vendedor) {
    char email[MAX_EMAIL];
    
    lerString((*vendedor).nomeVendedor, MAX_NOME_VENDEDOR, MSG_OBTER_NOME_VENDEDOR);
    (*vendedor).telefone = obterInt(MIN_TELEFONE, MAX_TELEFONE, MSG_OBTER_TELEFONE);
    do{
            lerString(email,30,MSG_OBTER_EMAIL);
        }while(!validarEmail(email));
        
        strcpy(vendedor->email, email);
}

/**
 * @brief Esta função aumenta o tamanho da memória para registar vendedores
 * 
 * @param vendedores apontador para a struct Vendedores
 */
void expandirVendedores(Vendedores *vendedores) {
    Vendedor *temp = (Vendedor*) realloc(vendedores->vendedor, sizeof (Vendedor) * (vendedores->tamanho * 2));
    if (temp != NULL) {
        vendedores->tamanho *= 2;
        vendedores->vendedor = temp;
    }
}

/**
 * @brief Verifica se o número do contador e do tamanho são iguais, se sim chama a função expandirVendedores()
 * Caso o contador seja menor que o tamanho verifica-se se o registo do vendedor correu bem, caso não corresse retorna -1 e aparece uma mensagem (VEND_EXISTE)
 * 
 * @param vendedores apontador para a struct Vendedores
 */
void registarVendedores(Vendedores *vendedores) {
    if (vendedores->contador == vendedores->tamanho) {
        expandirVendedores(vendedores);
    }

    if (vendedores->contador < vendedores->tamanho) {
        if (registarVendedor(vendedores) == -1) {
            puts(VENDEDOR_EXISTE);
        } else {
            puts(VENDEDOR_REGISTADO_SUCESSO);
        }
    } else {
        puts(VENDEDORES_LISTA_CHEIA);
    }
}

/**
 * @brief Esta função atualiza o estado do vendedor para "Inativo"
 * 
 * @param vendedor apontador para a struct Vendedor
 */
void removerVendedor(Vendedor *vendedor) {
    vendedor->estado = 0;
}

/**
 * @brief Verifica se o ID do vendedor inserido pelo utilizador existe
 * Se o vendedor tiver comissões associadas o seu estado muda para Inativo(0) (removerVendedor())
 * Caso contrário o registo do vendedor é removido e o contador descresce por 1
 * 
 * @param vendedores apontador para a struct Vendedores
 * @param comissões apontador para a struct Comissoes
 */
void removerVendedores(Vendedores *vendedores, Comissoes *comissoes) {
    int i, idVendedor, numero;

    idVendedor = obterInt(MIN_ID_VENDEDOR, MAX_ID_VENDEDOR, MSG_OBTER_ID_VENDEDOR);

    if (procurarVendedor(*vendedores, idVendedor) == 1) {
        numero = obterPosicaoVendedor(idVendedor, *vendedores);
        if (procurarVendComissao(*comissoes, idVendedor) == 0) {
            for (i = numero; i < vendedores->contador - 1; i++) {
                vendedores->vendedor[i] = vendedores->vendedor[i + 1];
            }

            apagarDadosVendedores(&vendedores->vendedor[i]);
            vendedores->contador--;
            puts(VENDEDOR_REMOVIDO_SUCESSO);
        } else {
            removerVendedor(&(*vendedores).vendedor[numero]);
        }
    } else {
        puts(VENDEDOR_NAO_EXISTE);
    }
}

/**
 * @brief Verifica se o código do vendedor inserido pelo utilizador existe
 * Se sim chama-se a função editarVendedor() que vai mudar os dados do vendedor
 * 
 * @param vendedores apontador para a struct Vendedores
 */
void editarVendedores(Vendedores *vendedores) {
    int idVendedorNovo = obterPosicaoVendedor(obterInt(MIN_ID_VENDEDOR, MAX_ID_VENDEDOR, MSG_OBTER_ID_VENDEDOR), *vendedores);
   
    if (idVendedorNovo != -1) {
        editarVendedor(&(*vendedores).vendedor[idVendedorNovo]);
        puts(VENDEDOR_EDITADO_SUCESSO);
    } else {
        puts(VENDEDOR_NAO_EXISTE);
    }
}

/**
 * @brief Esta função lista os vendedores existentes
 * 
 * @param vendedores struct Vendedores
 */
void listarVendedores(Vendedores vendedores) {
    int i;

    if (vendedores.contador > 0) {
        printf("\n--------------- VENDEDORES ---------------\n\n");
        for (i = 0; i < vendedores.contador; i++) {
            imprimirVendedores(vendedores.vendedor[i]);
        }
    } else {
        puts(VENDEDORES_LISTA_VAZIA);
    }
}

/**
 * @brief Esta função guarda todas as alterações que o usuário tenha feito aos vendedores existentes e armazena-as no ficheiro vendedores.bin
 * 
 * @param vendedores apontador para a struct Vendedores
 * @param ficheiro apontador para o ficheiro binário no qual serão guardados os dados referentes aos vendedores
 */
void guardarVendedores(Vendedores *vendedores, char *ficheiro) {
    int i;

    FILE *fp = fopen(ficheiro, "wb");
    if (fp == NULL) {
        exit(EXIT_FAILURE);
    }

    fwrite(&vendedores->contador, sizeof (int), 1, fp);

    for (i = 0; i < vendedores->contador; i++) {
        fwrite(&vendedores->vendedor[i], sizeof (Vendedor), 1, fp);
    }

    fclose(fp);
}

/**
 * Esta função lista o número de comissões de todos os vendedores
 * 
 * @param comissoes apontador para a struct Comissoes
 * @param vendedores apontador para a struct Vendedores
 */
void obterListaVendedores(Comissoes *comissoes, Vendedores *vendedores) {
    int idVendedores[vendedores->contador];
    int comissoesVendedores[vendedores->contador];
    
    for(int i = 0; i < vendedores->contador; i++){
        
        idVendedores[i] = 0;
        comissoesVendedores[i] = 0;
        
    }
    
    for(int j = 0; j < vendedores->contador; j++){
        
        idVendedores[j] = vendedores->vendedor[j].idVendedor;
        
        for(int k = 0; k < comissoes->contador;k++){
            
            if(comissoes->comissao[k].idVendedor == idVendedores[j]){
                comissoesVendedores[j]++;
            }
        }
    }
    
    for(int l = 0; l < vendedores->contador; l++){
      printf("\n%d: %d comissões associadas\n", idVendedores[l], comissoesVendedores[l]);  
    }
    
}
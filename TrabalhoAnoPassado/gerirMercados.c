#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "funcoes.h"
#include "input.h"

/**
 * @brief Mostra no ecrã os dados existentes no registo dos Mercados
 * 
 * @param mercado struct Mercado
 */
void imprimirMercados(Mercado mercado) {

    printf("\tID do mercado: %d\n", mercado.idMercado);
    printf("\tNome: %s\n", mercado.nomeMercado);
    printf("\tPercentagem de comissão: %d%%\n", mercado.percentagem);
    printf("\tEstado: %d\n", mercado.estado);
    puts(BARRA);

}

/**
 * @brief Procura se um mercado existe, caso se confirme retorna a posição no registo Mercados, se não existir retorna -1
 * 
 * @param idMercado
 * @param mercados struct Mercados
 * 
 * @return i se o mercado existir, -1 se não existir
 */
int obterPosicaoMercado(int idMercado, Mercados mercados) {
    for (int i = 0; i < mercados.contador; i++) {
        if (mercados.mercado[i].idMercado == idMercado) {
            return i;
        }
    }
    return -1;
}

/**
 * @brief Esta função "apaga" o registo dos mercados 
 * 
 * @param mercado apontador para a struct Mercado
 */
void apagarDadosMercados(Mercado *mercado) {
    mercado->idMercado = 0;
    strcpy(mercado->nomeMercado, "");
    mercado->percentagem = 0;
    mercado->estado = 0;
}

/**
 * @brief Esta função verifica se o mercado existe nos registos dos Mercados
 * 
 * @param mercados struct Mercados
 * @param idMercado
 * 
 * @return 1 se o mercado existir e 0 se ele não existir
 */
int procurarMercado(Mercados mercados, int idMercado) {
    int i;
    for (i = 0; i < mercados.contador; i++) {
        if (mercados.mercado[i].idMercado == idMercado) {
            return 1;
        }
    }

    return 0;
}

/**
 * @brief Esta função verifica se o ficheiro existe(rb), senão cria-o (wb)
 * Com a função fread é retornado o número de itens completos lidos pela função
 * 
 * @param mercados apontador para a struct Mercados
 * @param ficheiro apontador para o ficheiro binário dos quais os dados serão carregados
 */
void carregarMercados(Mercados *mercados, char *ficheiro) {
    int i, sucesso = 0;

    //Tenta abrir o ficheiro
    FILE *fp = fopen(ficheiro, "rb");
    if (fp != NULL) {
        //retorna o número de itens completos lidos pela função
        fread(&mercados->contador, sizeof (int), 1, fp);

        if (mercados->contador > 0) {
            mercados->mercado = (Mercado*) malloc(mercados->contador * sizeof (Mercado));
            fread(mercados->mercado, sizeof (Mercado), mercados->contador, fp);
            mercados->tamanho = mercados->contador;
            sucesso = 1;
        }

        fclose(fp);
    }

    if (!sucesso) {
        fp = fopen(ficheiro, "wb");
        if (fp != NULL) {

            mercados->mercado = (Mercado*) malloc(MERCADOS_TAM_INICIAL * sizeof (Mercado));
            mercados->contador = 0;
            mercados->tamanho = MERCADOS_TAM_INICIAL;
            fclose(fp);
        }
    }
}

/**
 * @brief Esta função desaloca a memória alocada 
 * 
 * @param mercados apontador para a struct Mercados
 */
void libertarMercados(Mercados *mercados) {
    free(mercados->mercado);
}

/**
 * @brief Cria um novo id de Mercado
 * Insere um novo registo em Mercados e o contador aumenta por 1
 * 
 * @param mercados apontador para a struct Mercados
 * 
 * @return -1 se o ID já existir ou retorna o número do contador se os dados foram registados com sucesso
 */
int registarMercado(Mercados *mercados) {
    int idMercadoNovo;

    idMercadoNovo = 1000 + mercados->contador;

    mercados->mercado[mercados->contador].idMercado = idMercadoNovo;
    lerString(mercados->mercado[mercados->contador].nomeMercado, MAX_NOME_MERCADO, MSG_OBTER_NOME_MERCADO);
    mercados->mercado[mercados->contador].percentagem = obterInt(MIN_PERCENTAGEM, MAX_PERCENTAGEM, MSG_OBTER_PERCENTAGEM);
    mercados->mercado[mercados->contador].estado = 1;

    return mercados->contador++;

}

/**
 * @brief Esta função atualiza os dados de um mercado
 * 
 * @param mercado apontador para a struct Mercado
 */
void editarMercado(Mercado *mercado) {

    lerString((*mercado).nomeMercado, MAX_NOME_MERCADO, MSG_OBTER_NOME_MERCADO);
    (*mercado).percentagem = obterInt(MIN_PERCENTAGEM, MAX_PERCENTAGEM, MSG_OBTER_PERCENTAGEM);

}

/**
 * @brief Esta função aumenta o tamanho da memória para registar mercados
 * 
 * @param mercados apontador para a struct Mercados
 */
void expandirMercados(Mercados *mercados) {
    Mercado *temp = (Mercado*) realloc(mercados->mercado, sizeof (Mercado) * (mercados->tamanho * 2));
    if (temp != NULL) {
        mercados->tamanho *= 2;
        mercados->mercado = temp;
    }
}

/**
 * @brief Verifica se o número do contador e do tamanho são iguais, se sim chama a função expandirMercados()
 * Caso o contador seja menor que o tamanho verifica-se se o registo do mercado correu bem, caso não corresse retorna -1 e aparece uma mensagem (MERCADO_EXISTE)
 * 
 * @param mercados apontador para a struct Mercados
 */
void registarMercados(Mercados *mercados) {
    if (mercados->contador == mercados->tamanho) {
        expandirMercados(mercados);
    }

    if (mercados->contador < mercados->tamanho) {
        if (registarMercado(mercados) == -1) {
            puts(MERCADO_EXISTE);
        } else {
            puts(MERCADO_REGISTADO_SUCESSO);
        }
    } else {
        puts(MERCADOS_LISTA_CHEIA);
    }
}

/**
 * @brief Esta função atualiza o estado do mercado para "Inativo"
 * 
 * @param mercado apontador para a struct Mercado
 */
void removerMercado(Mercado *mercado) {
    mercado->estado = 0;
}

/**
 * @brief Verifica se o ID do mercado inserido pelo utilizador existe
 * Se o vendedor tiver comissões associadas o seu estado muda para Inativo(0) (removerMercado())
 * Caso contrário o registo do mercado é removido e o contador descresce por 1
 * 
 * @param mercados apontador para a struct Mercados
 * @param comissões apontador para a struct Comissoes
 */
void removerMercados(Mercados *mercados, Comissoes *comissoes) {
    int i, idMercado, numero;

    idMercado = obterInt(MIN_ID_MERCADO, MAX_ID_MERCADO, MSG_OBTER_ID_MERCADO);

    if (procurarMercado(*mercados, idMercado) == 1) {
        numero = obterPosicaoMercado(idMercado, *mercados);
        if (procurarMercComissao(*comissoes, idMercado) == 0) {
            for (i = numero; i < mercados->contador - 1; i++) {
                mercados->mercado[i] = mercados->mercado[i + 1];
            }

            apagarDadosMercados(&mercados->mercado[i]);
            mercados->contador--;
            puts(MERCADO_REMOVIDO_SUCESSO);
        } else {
            removerMercado(&(*mercados).mercado[numero]);
        }
    } else {
        puts(MERCADO_NAO_EXISTE);
    }
}

/**
 * @brief Verifica se o código do mercado inserido pelo utilizador existe
 * Se sim chama-se a função editarMercado() que vai mudar os dados do mercado
 * 
 * @param mercados apontador para struct Mercados
 */
void editarMercados(Mercados *mercados) {
    int idMercado = obterPosicaoMercado(obterInt(MIN_ID_MERCADO, MAX_ID_MERCADO, MSG_OBTER_ID_MERCADO), *mercados);

    if (idMercado != -1) {
        editarMercado(&(*mercados).mercado[idMercado]);
    } else {
        puts(MERCADO_NAO_EXISTE);
    }
}

/**
 * @brief Esta função lista os mercados existentes
 * 
 * @param mercados struct Mercados
 */
void listarMercados(Mercados mercados) {
    int i;

    if (mercados.contador > 0) {
        printf("\n--------------- MERCADOS ---------------\n\n");
        for (i = 0; i < mercados.contador; i++) {
            imprimirMercados(mercados.mercado[i]);
        }
    } else {
        puts(MERCADOS_LISTA_VAZIA);
    }
}

/**
 * @brief Esta função guarda todas as alterações que o usuário tenha feito aos mercados existentes
 * 
 * @param mercados apontador para a struct Mercados
 * @param ficheiro apontador para o ficheiro binário no qual serão guardados os dados referentes aos mercados
 */
void guardarMercados(Mercados *mercados, char *ficheiro) {
    int i;

    FILE *fp = fopen(ficheiro, "wb");
    if (fp == NULL) {
        exit(EXIT_FAILURE);
    }

    fwrite(&mercados->contador, sizeof (int), 1, fp);

    for (i = 0; i < mercados->contador; i++) {
        fwrite(&mercados->mercado[i], sizeof (Mercado), 1, fp);
    }

    fclose(fp);
}

/**
 * Esta função lista o número de comissões de todos os mercados
 * 
 * @param comissoes apontador para a struct Comissoes
 * @param mercados apontador para a struct Mercados
 */
void obterListaMercados(Comissoes *comissoes, Mercados *mercados) {
    int idMercados[mercados->contador];
    int comissoesMercados[mercados->contador];
    
    for(int i = 0; i < mercados->contador; i++){
        
        idMercados[i] = 0;
        comissoesMercados[i] = 0;
        
    }
    
    for(int j = 0; j < mercados->contador; j++){
        
        idMercados[j] = mercados->mercado[j].idMercado;
        
        for(int k = 0; k < comissoes->contador;k++){
            
            if(comissoes->comissao[k].idMercado == idMercados[j]){
                comissoesMercados[j]++;
            }
        }
    }
    
    for(int l = 0; l < mercados->contador; l++){
      printf("\n%d: %d comissões associadas\n", idMercados[l], comissoesMercados[l]);  
    }
    
}
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>
#include <ctype.h>

#include "funcoes.h"
#include "input.h"

/**
 * @brief Esta função mostra no ecrã os dados existentes no registo
 * 
 * @param comissoes struct Comissoes
 */

void imprimirComissoes(Comissao comissao) {


    printf("\tID do vendedor: %d\n", comissao.idVendedor);
    printf("\tID do mercado: %d\n", comissao.idMercado);
    printf("\tPercentagem de comissao: %d\n", comissao.percentagem);
    printf("\tData início: %02d/%02d/%04d\n", comissao.dataComissao.diaInicial, comissao.dataComissao.mesInicial, comissao.dataComissao.anoInicial);
    printf("\tData Fim: %02d/%02d/%04d\n", comissao.dataComissao.diaFinal, comissao.dataComissao.mesFinal, comissao.dataComissao.anoFinal);

    puts(BARRA);

}

/**
 * @brief Esta função serve para controlar a sobreposição de datas das comissões
 * 
 * @param comissoes struct Comissoes
 * @param idMercado
 * @param idVendedor
 * 
 * @return 1 se houver sobreposição, 0 se não houver
 */

 int verificarDataComissao(Comissoes comissoes, int idMercado, int idVendedor, Data novaData) {
    for (int i = 0; i < comissoes.contador; i++) {
        if (comissoes.comissao[i].idVendedor == idVendedor && comissoes.comissao[i].idMercado == idMercado) {
            Data dataExistente = comissoes.comissao[i].dataComissao;
            if ((novaData.anoInicial <= dataExistente.anoFinal && novaData.anoFinal >= dataExistente.anoInicial) &&
                    (novaData.mesInicial <= dataExistente.mesFinal && novaData.mesFinal >= dataExistente.mesInicial) &&
                    (novaData.diaInicial <= dataExistente.diaFinal && novaData.diaFinal >= dataExistente.diaInicial)) {
                return 1; // há sobreposição
            }
        }
    }
    return 0; // não há sobreposição
}


/**
 * @brief Esta função verifica se o vendedor existe nos registos das Comissões
 * 
 * @param comissoes struct Comissoes
 * @param idVendedor
 * 
 * @return i se o vendedor existir e -1 se ele não existir
 */

int procurarVendComissao(Comissoes comissoes, int idVendedor) {
    int i;

    for (i = 0; i < comissoes.contador; i++) {
        if (comissoes.comissao[i].idVendedor == idVendedor) {
            return 1;
        }

        return 0;
    }
}

/**
 * @brief Esta função verifica se o mercado existe nos registos das Comissões
 * 
 * @param comisoes struct Comissoes
 * @param idMercado
 * 
 * @return 1 se o mercado existir e 0 se ele não existir
 */

int procurarMercComissao(Comissoes comissoes, int idMercado) {
    int i;

    for (i = 0; i < comissoes.contador; i++) {
        if (comissoes.comissao[i].idMercado == idMercado) {
            return 1;
        }

        return 0;
    }
}

/**
 * @brief Esta função verifica se o ficheiro existe(rb), senão cria-o (wb)
 * Com a função fread é retornado o número de itens completos lidos pela função
 * 
 * @param comissoes apontador para a struct Comissoes
 * @param ficheiro apontador para o ficheiro no qual os dados serão carregados
 */

void carregarComissoes(Comissoes *comissoes, char *ficheiro) {
    int i, sucesso = 0;

    //Tenta abrir o ficheiro
    FILE *fp = fopen(ficheiro, "rb");
    if (fp != NULL) {
        //retorna o número de itens completos lidos pela função
        fread(&comissoes->contador, sizeof (int), 1, fp);

        if (comissoes->contador > 0) {
            comissoes->comissao = (Comissao*) malloc(comissoes->contador * sizeof (Comissao));
            fread(comissoes->comissao, sizeof (Comissao), comissoes->contador, fp);
            comissoes->tamanho = comissoes->contador;
            sucesso = 1;
        }
        fclose(fp);
    }

    if (!sucesso) {

        fp = fopen(ficheiro, "wb");
        if (fp != NULL) {

            comissoes->comissao = (Comissao*) malloc(COMISSOES_TAM_INICIAL * sizeof (Comissao));
            comissoes->contador = 0;
            comissoes->tamanho = COMISSOES_TAM_INICIAL;
            fclose(fp);
        }
    }

}

/**
 * @brief Esta função desaloca a memória alocada 
 * 
 * @param comissoes apontador para a struct Comissoes
 */
void libertarComissoes(Comissoes *comissoes) {
    free(comissoes->comissao);
}

/**
 * @brief Verifica se o ID do mercado e o ID do vendedor que o utilizador inseriu existe
 * Insere um novo registo nas comissões
 * 
 * @param comissoes apontador para a struct Comissoes
 * @param vendedores apontador para a struct Vendedores
 * @param mercados apontador para a struct Mercados
 * 
 * @return -1 se um dos IDs já existirem ou retorna o número do contador se os dados foram registados com sucesso
 */
int registarComissao(Comissoes *comissoes, Vendedores *vendedores, Mercados *mercados) {
    int verificacao, idMercado, idVendedor;
    int dI, mI, yI, dF, mF, yF;

    idMercado = obterInt(MIN_ID_MERCADO, MAX_ID_MERCADO, MSG_OBTER_ID_MERCADO);

    if (procurarMercado(*mercados, idMercado) == 1) {
        int pos = obterPosicaoMercado(idMercado, *mercados);
        idVendedor = obterInt(MIN_ID_VENDEDOR, MAX_ID_VENDEDOR, MSG_OBTER_ID_VENDEDOR);

        if (procurarVendedor(*vendedores, idVendedor) == 1) {

            comissoes->comissao[comissoes->contador].idMercado = idMercado;
            comissoes->comissao[comissoes->contador].idVendedor = idVendedor;
            comissoes->comissao[comissoes->contador].percentagem = mercados->mercado[pos].percentagem;

            do {
                printf("Escreva a data de inicio da associação(DD/MM/AAAA):");
                scanf("%d/%d/%d", &dI, &mI, &yI);
            } while (!verificaData(dI, mI, yI));

            do {
                printf("Escreva a data do fim da associação(DD/MM/AAAA):");
                scanf("%d/%d/%d", &dF, &mF, &yF);
            } while (!verificaData(dF, mF, yF));


            comissoes->comissao[comissoes->contador].dataComissao.anoFinal = yF;
            comissoes->comissao[comissoes->contador].dataComissao.diaFinal = dF;
            comissoes->comissao[comissoes->contador].dataComissao.mesFinal = mF;

            comissoes->comissao[comissoes->contador].dataComissao.diaInicial = dI;
            comissoes->comissao[comissoes->contador].dataComissao.mesInicial = mI;
            comissoes->comissao[comissoes->contador].dataComissao.anoInicial = yI;

            verificacao = verificarDataComissao(*comissoes, idMercado, idVendedor, comissoes->comissao[comissoes->contador].dataComissao);
            
            if (verificacao == 0) {
                return comissoes->contador++;
            }
        }
        return -1;
    }
}

/**
 * @brief Esta função aumenta o tamanho da memória para registar comissões
 * 
 * @param comissoes apontador para a struct Comissoes
 */
void expandirComissoes(Comissoes *comissoes) {
    Comissao *temp = (Comissao*) realloc(comissoes->comissao, sizeof (Comissao) * (comissoes->tamanho * 2));
    if (temp != NULL) {
        comissoes->tamanho *= 2;
        comissoes->comissao = temp;
    }
}

/**
 * @brief Verifica se o número do contador e do tamanho são iguais, se sim chama a função expandirComissoes()
 * Caso o contador seja menor que o tamanho verifica-se se o registo da comissão correu bem, caso não corresse retorna -1 e aparece uma mensagem (COMISSOES_EXISTE)
 * Se o valor retornado for diferente de -1 chama-se a função registarComissoesFX() para escrever no ficheiro o registo
 * 
 * @param comissoes apontador para a struct Comissoes
 * @param vendedores apontador para a struct Vendedores
 * @param mercados apontador para a struct Mercados
 */
void registarComissoes(Comissoes *comissoes, Vendedores *vendedores, Mercados *mercados) {
    if (comissoes->contador == comissoes->tamanho) {
        expandirComissoes(comissoes);
    }

    if (comissoes->contador < comissoes->tamanho) {
        if (registarComissao(comissoes, vendedores, mercados) == -1) {
            puts(COMISSAO_EXISTE);
        } else {
        }
    } else {
        puts(COMISSAO_LISTA_CHEIA);
    }
}

/**
 * @brief Esta função lê o ficheiro binário com os registos das comissoes e escreve num ficheiro de texto
 * 
 * 
 * @param comissoes apontador para a struct Comissoes
 * @param ficheiroBin apontador para o ficheiro binário de onde serão exportados os dados
 * @param ficheiroTxt apontador para o ficheiro binário de onde serão recebidos os dados
 * 
 * @return 1 se fôr concluido com sucesso, 0 se ocorrer algum erro
 */
int exportarComissoes(Comissoes comissoes, char* ficheiroBin, char* ficheiroTxt) {
    FILE *fbin, *ftxt;
    int i;

    if ((fbin = fopen(ficheiroBin, "rb")) == NULL)
        return 0; // sem sucesso

    if ((ftxt = fopen(ficheiroTxt, "wt")) == NULL) { // changed mode
        fclose(fbin);
        return 0; // sem sucesso
    }

    fprintf(ftxt, "Mercado\t\tVendedor\tPercentagem\tData Inicial\t\tData Final\n");
    fprintf(ftxt, "---------------------------------------------------------------------------------------------------------------------------------\n");

    if (comissoes.contador > 0) {
        for (i = 0; i < comissoes.contador; i++) {

            fprintf(ftxt, "%d\t\t%d\t\t%d%%\t\t%02d/%02d/%04d\t\t%02d/%02d/%04d\n", comissoes.comissao[i].idMercado, comissoes.comissao[i].idVendedor, comissoes.comissao[i].percentagem, comissoes.comissao[i].dataComissao.diaInicial, comissoes.comissao[i].dataComissao.mesInicial, comissoes.comissao[i].dataComissao.anoInicial, comissoes.comissao[i].dataComissao.diaFinal, comissoes.comissao[i].dataComissao.mesFinal, comissoes.comissao[i].dataComissao.anoFinal);

        }
    } else {
        printf("Failure\n");
    }

    fclose(ftxt);
    fclose(fbin);

    return 1;
}

/**
 * @brief Lista de todos as comissoes registadas
 * 
 * @param comissoes struct Comissoes
 */
void listarComissoes(Comissoes comissoes) {
    int i;

    if (comissoes.contador > 0) {
        puts("");
        printf("\n\n-------------------- COMISSÕES --------------------\n");
        for (i = 0; i < comissoes.contador; i++) {
            imprimirComissoes(comissoes.comissao[i]);
        }
    } else {
        puts(COMISSAO_LISTA_VAZIA);
    }
}

/**
 * @brief Esta função guarda todas as alterações que o usuário tenha feito às comissões existentes
 * 
 * @param mercados apontador para a struct Comissoes
 * @param ficheiro apontador para o ficheiro binário no qual serão guardados os dados referentes às comissoes
 */
void guardarComissoes(Comissoes *comissoes, char *ficheiro){
    int i;

    FILE *fp = fopen(ficheiro, "wb");
    if (fp == NULL) {
        exit(EXIT_FAILURE);
    }

    fwrite(&comissoes->contador, sizeof (int), 1, fp);

    for (i = 0; i < comissoes->contador; i++) {
        fwrite(&comissoes->comissao[i], sizeof (Comissao), 1, fp);
    }

    fclose(fp);
}
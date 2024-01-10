#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "gerirComentarios.h"
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
    printf("\tCódigo Postal: %d - %d\n", empresa.codigoPostal.prefixo, empresa.codigoPostal.sufixo);
    printf("\tClassificações: ");

    for (int i = 0; i < empresa.numClassificacoes; i++) {
        printf("%d ", empresa.classificacoes[i]);
    }
    printf("\n\tAtivo: %d\n", empresa.estado);
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
    empresa->codigoPostal.prefixo = 0;
    empresa->codigoPostal.sufixo = 0;
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
 * @brief Esta função verifica se a empresa existe nos registos das Empresas
 * 
 * @param empresas struct Empresas
 * @param NIF
 * @return 1 se a empresa existir e 0 se ela não existir
 */

int procurarEmpresaNome(Empresas empresas, char nome[]) {
    int i;
    for (i = 0; i < empresas.contador; i++) {
        if (strcmp(empresas.empresa[i].nomeEmpresa, nome) == 0) {
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
 * @brief Procura se uma empresa existe, caso se confirme retorna a posição no registo Empresas, se não existir retorna -1
 * 
 * @param NIF
 * @param empresas struct Empresas
 * @return i se a empresa existir, -1 caso não exista
 */
int obterPosicaoNomeEmpresa(Empresas empresas, char nome[]) {
    for (int i = 0; i < empresas.contador; i++) {
        if (empresas.empresa[i].nomeEmpresa == nome) {
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
        empresas->empresa[empresas->contador].codigoPostal.prefixo = obterInt(MIN_COD_POSTAL_PREFIXO, MAX_COD_POSTAL_PREFIXO, MSG_OBTER_COD_POSTAL_PREFIXO);
        empresas->empresa[empresas->contador].codigoPostal.sufixo = obterInt(MIN_COD_POSTAL_SUFIXO, MAX_COD_POSTAL_SUFIXO, MSG_OBTER_COD_POSTAL_SUFIXO);
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
    (*empresa).codigoPostal.prefixo = obterInt(MIN_COD_POSTAL_PREFIXO, MIN_COD_POSTAL_PREFIXO, MSG_OBTER_COD_POSTAL_PREFIXO);
    (*empresa).codigoPostal.sufixo = obterInt(MIN_COD_POSTAL_SUFIXO, MIN_COD_POSTAL_SUFIXO, MSG_OBTER_COD_POSTAL_SUFIXO);
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
        if (registarEmpresa(empresas, ramosAtividade) == -1) {
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

/**
 * @brief Esta função guarda todas as alterações que o usuário tenha feito às empresas existentes e armazena-as no ficheiro empresas.bin
 * 
 * @param empresas apontador para a struct Empresas
 * @param ficheiro apontador para o ficheiro binário no qual serão guardados os dados referentes às empresas
 */
void guardarEmpresas(Empresas *empresas, char *ficheiro) {
    int i;

    FILE *fp = fopen(ficheiro, "wb");
    if (fp == NULL) {
        exit(EXIT_FAILURE);
    }

    fwrite(&empresas->contador, sizeof (int), 1, fp);

    for (i = 0; i < empresas->contador; i++) {
        fwrite(&empresas->empresa[i], sizeof (Empresa), 1, fp);
    }

    fclose(fp);
}

void pesquisarEmpresas(Empresas *empresas) {

    char nome[MAX_NOME_EMPRESA];
    char localidade[MAX_LOCALIDADE];
    char ramoAtividade[MAX_NOME_RAMO_ATIVIDADE];

    lerString(nome, MAX_NOME_EMPRESA, MSG_OBTER_NOME_EMPRESA);
    lerString(localidade, MAX_LOCALIDADE, MSG_OBTER_LOCALIDADE);
    lerString(ramoAtividade, MAX_NOME_RAMO_ATIVIDADE, MSG_OBTER_RAMO_ATIVIDADE);

    for (int i = 0; i < empresas->contador; i++) {
        if (empresas->empresa[i].estado) {
            if (strcmp(empresas->empresa[i].nomeEmpresa, nome) == 0) {
                printf(EMPRESAS_ENCONTRADAS);
                imprimirEmpresas(empresas->empresa[i]);
                return;
            } else if (strcmp(empresas->empresa[i].localidade, localidade) == 0) {
                printf(EMPRESAS_ENCONTRADAS);
                imprimirEmpresas(empresas->empresa[i]);
                return;
            } else if (strcmp(empresas->empresa[i].ramoAtividade, ramoAtividade) == 0) {
                printf(EMPRESAS_ENCONTRADAS);
                imprimirEmpresas(empresas->empresa[i]);
                return;
            } else {
                puts(CRITERIOS_INVALIDOS);
                return;
            }
        }
    }
}

/**
 * @brief Esta função atualiza o estado do mercado para "Inativo"
 * 
 * @param mercado apontador para a struct Mercado
 */
void removerEmpresa(Empresa *empresa) {
    empresa->estado = 0;
}

/**
 * @brief Verifica se o ID do mercado inserido pelo utilizador existe
 * Se o vendedor tiver comissões associadas o seu estado muda para Inativo(0) (removerMercado())
 * Caso contrário o registo do mercado é removido e o contador descresce por 1
 * 
 * @param mercados apontador para a struct Mercados
 * @param comissões apontador para a struct Comissoes
 */

void removerEmpresas(Empresas *empresas, Comentarios *comentarios) {
    int i, NIF, numero;

    NIF = obterInt(MIN_NIF_EMPRESA, MAX_NIF_EMPRESA, MSG_OBTER_NIF_EMPRESA);

    if (procurarEmpresa(*empresas, NIF) == 1) {
        numero = obterPosicaoEmpresa(NIF, *empresas);
        if (procurarComentarioNomeEmpresa(*comentarios, empresas->empresa[numero].nomeEmpresa) == 0) {
            for (i = numero; i < empresas->contador - 1; i++) {
                empresas->empresa[i] = empresas->empresa[i + 1];
            }

            apagarDadosEmpresas(&empresas->empresa[i]);
            empresas->contador--;
            puts(EMPRESA_REMOVIDA_SUCESSO);
        } else {
            removerEmpresa(&(*empresas).empresa[numero]);
        }
    } else {
        puts(EMPRESA_NAO_EXISTE);
    }
}

/**
 * @brief Cria um novo NIF de Empresa
 * Insere um novo registo em Empresas e o contador aumenta por 1
 * 
 * @param empresas apontador para struct Empresas
 * @return -1 se o NIF já existir ou retorna o número do contador se os dados foram registados com sucesso
 */
int registarComentario(Comentarios *comentarios, Empresas *empresas) {
    char titulo[MAX_TITULO], nomeEmpresa[MAX_NOME_EMPRESA];

    lerString(nomeEmpresa, MAX_NOME_EMPRESA, MSG_OBTER_NOME_EMPRESA);
    lerString(titulo, MAX_TITULO, MSG_OBTER_TITULO_COMENT);

    if (procurarComentario(*comentarios, titulo) == 0 && procurarEmpresaNome(*empresas, nomeEmpresa) == 1) {

        lerString(comentarios->comentario[comentarios->contador].nomeUtilizador, MAX_NOME_UTILIZADOR, MSG_OBTER_NOME_UTILIZADOR);
        lerString(comentarios->comentario[comentarios->contador].email, MAX_EMAIL, MSG_OBTER_EMAIL);
        strcpy(comentarios->comentario[comentarios->contador].nomeEmpresa, nomeEmpresa);
        strcpy(comentarios->comentario[comentarios->contador].titulo, titulo);
        lerString(comentarios->comentario[comentarios->contador].texto, MAX_COMENTARIO, MSG_OBTER_TEXTO);
        comentarios->comentario[comentarios->contador].estado = 1;

        return comentarios->contador++;
    }

    printf(EMPRESA_NAO_EXISTE);
    return -1;
}

/**
 * @brief Verifica se o número do contador e do tamanho são iguais, se sim chama a função expandirComentarios()
 * Caso o contador seja menor que o tamanho verifica-se se o registo do comentário correu bem, caso não corresse retorna -1 e aparece uma mensagem (COMENTARIO_EXISTE)
 * 
 * @param comentarios apontador para a struct Comentarios
 */
void registarComentarios(Comentarios *comentarios, Empresas *empresas) {
    if (comentarios->contador == comentarios->tamanho) {
        expandirComentarios(comentarios);
    }

    if (comentarios->contador < comentarios->tamanho) {
        if (registarComentario(comentarios, empresas) == -1) {
            puts(COMENTARIO_EXISTE);
        } else {
            puts(COMENTARIO_REGISTADO_SUCESSO);
        }
    } else {
        puts(COMENTARIO_LISTA_CHEIA);
    }
}

void classificarEmpresa(Empresas *empresas) {
    char nome[MAX_NOME_EMPRESA];
    lerString(nome, MAX_NOME_EMPRESA, MSG_OBTER_NOME_EMPRESA);
    for (int i = 0; i < empresas->contador; i++) {
        if (strcmp(empresas->empresa[i].nomeEmpresa, nome) == 0 && empresas->empresa[i].estado == 1) {
            int classificacao = obterInt(MIN_CLASSIFICACAO, MAX_CLASSIFICACAO, MSG_OBTER_CLASSIFICACAO);

            if (classificacao >= 0 && classificacao <= 5) {
                empresas->empresa[i].classificacoes[empresas->empresa[i].numClassificacoes] = classificacao;
                empresas->empresa[i].numClassificacoes ++;
                puts(CLASSIFICACAO_REGISTADA);
            } else {
                puts(CLASSIFICACAO_INVALIDA);
            }
            return;
        } 
    }
    puts("Empresa nao encontrada");
}

void relatorioClassificacoes(Empresas *empresas){

    float medias[empresas->contador];
    char nomeEmpresas[empresas->contador][MAX_NOME_EMPRESA];

    //Fazer a media
    for (int i = 0; i < empresas->contador; i++) {
        float soma = 0;
        int totalClassificacoes = 0;


        for(int j = 0; j <empresas->empresa[i].numClassificacoes; j++){
            soma += empresas->empresa[i].classificacoes[j];
            totalClassificacoes++;
        }
        // Verificar se a empresa tem alguma classificação
        if (totalClassificacoes > 0) {
            medias[i] = soma / totalClassificacoes;
        } else {
            medias[i] = -1;
        }
        strcpy(nomeEmpresas[i], empresas->empresa[i].nomeEmpresa);
    }

    //ordenar array ordem decrescente
    for (int i = 0; i < empresas->contador - 1; i++) {
        for (int j = 0; j < empresas->contador - i - 1; j++) {
            if (medias[j] < medias[j + 1]) {
                float temp = medias[j];
                medias[j] = medias[j+1];
                medias[j + 1] = temp; 

                char nomeTemp[MAX_NOME_EMPRESA];
                strcpy(nomeTemp, nomeEmpresas[j]);
                strcpy(nomeEmpresas[j], nomeEmpresas[j+1]);
                strcpy(nomeEmpresas[j+1], nomeTemp);
            }
        }
    }
    //Imprimir a percentagem
    printf("Empresas ordenadas por média de classificações:\n\n");
    for (int i = 0; i < empresas->contador; i++) {
        printf("Empresa %s:\n",nomeEmpresas[i]);
        printf("  Media: %.2f\n",medias[i]);
        printf("  Numero de classificacoes: %d\n\n", empresas->empresa[i].numClassificacoes);
    }
}
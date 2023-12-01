#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define VALOR_INVALIDO "O valor inserido é inválido."

void cleanInputBuffer() {
    char ch;
    while ((ch = getchar()) != '\n' && ch != EOF);
}

int obterInt(int minValor, int maxValor, char *msg) {
    int valor;
    printf(msg);
    while (scanf("%d", &valor) != 1 || valor < minValor || valor > maxValor) {
        puts(VALOR_INVALIDO);
        cleanInputBuffer();
        printf(msg);
    }
    cleanInputBuffer();
    return valor;
}


long int obterLongInt(long int minValor,long int maxValor, char *msg) {
    long int valor;
    printf(msg);
    while (scanf("%d", &valor) != 1 || valor < minValor || valor > maxValor) {
        puts(VALOR_INVALIDO);
        cleanInputBuffer();
        printf(msg);
    }
    cleanInputBuffer();
    return valor;
}


float obterFloat(float minValor, float maxValor, char *msg) {
    float valor;
    printf(msg);
    while (scanf("%f", &valor) != 1 || valor < minValor || valor > maxValor) {
        puts(VALOR_INVALIDO);
        cleanInputBuffer();
        printf(msg);
    }
    cleanInputBuffer();
    return valor;
}

double obterDouble(double minValor, double maxValor, char *msg) {
    double valor;
    printf(msg);
    while (scanf("%lf", &valor) != 1 || valor < minValor || valor > maxValor) {
        puts(VALOR_INVALIDO);
        cleanInputBuffer();
        printf(msg);
    }
    cleanInputBuffer();
    return valor;
}

char obterChar(char *msg) {
    char valor;
    printf(msg);
    valor = getchar();
    cleanInputBuffer();
    return valor;
}

void lerString(char *string, unsigned int tamanho, char *msg) {
    printf(msg);
    if (fgets(string, tamanho, stdin) != NULL) {
        unsigned int len = strlen(string) - 1;
        if (string[len] == '\n') {
            string[len] = '\0';
        } else {
            cleanInputBuffer();
        }
    }
}

int validarEmail( const char * email ){
    char usuario[256], site[256], dominio[256];

    if( sscanf( email, "%[^@ \t\n]@%[^. \t\n].%3[^ \t\n]", usuario, site, dominio ) != 3 )
        return 0;

    return 1;
}

/** @param dia = recebe o dia inserido
* @param mes = recebe o mes inserido
* @param ano = recebe o ano inserido
* @param anoAtual = recebe o ano atual para verificar se a data é válida
* @return 
*/

int verificaData(int dia, int mes, int ano) {
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);

    cleanInputBuffer();

    // Verifica se a data fornecida é posterior ou igual à data atual
    if (ano > (tm.tm_year + 1900) || (ano == (tm.tm_year + 1900) && mes > (tm.tm_mon + 1))
        || (ano == (tm.tm_year + 1900) && mes == (tm.tm_mon + 1) && dia >= tm.tm_mday)) {
        if (ano >= (tm.tm_year + 1900) && ano <= 9999) {
            if (mes >= 1 && mes <= 12) {
                if ((dia >= 1 && dia <= 31) && (mes == 1 || mes == 3 || mes == 5 || mes == 7 || mes == 8 || mes == 10 || mes == 12)) {
                    return 1;
                }
                else if ((dia >= 1 && dia <= 30) && (mes == 4 || mes == 6 || mes == 9 || mes == 11)) {
                    return 1;
                }
                else if ((dia >= 1 && dia <= 28) && (mes == 2)) {
                    return 1;
                }
                else if (dia == 29 && mes == 2 && (ano % 400 == 0 || (ano % 4 == 0 && ano % 100 != 0))) {
                    return 1;
                }
                else {
                    return 0;
                }
            }
            else {
                return 0;
            }
        }
        else {
            return 0;
        }
    }
    else {
        return 0;
    }
}
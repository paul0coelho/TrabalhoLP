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

int validarEmail(char *email) {
    if (strlen(email) == 0) {
        return 0;
    }

    if (email[0] == '.' || email[strlen(email) - 1] == '.') {
        return 0;
    }

    for (int i = 0; email[i] != '\0'; i++) {
        if (email[i] == '.' && email[i + 1] == '.') {
            return 0;
        }
    }

    return 1; 
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

void lerEmail(char *email, unsigned int tamanho, char *msg) {
    do {
        lerString(email, tamanho, msg);

        if (!validarEmail(email)) {
            printf(VALOR_INVALIDO);
        } else {
            break;
        }
    } while (1);
}
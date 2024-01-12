/**
* @file input.h
* @author 8220195 e 8220196 e ESTG
* @date 19-12-2024
*
*
* @brief Header file que declarações de funções utilizadas para obter inputs do utilizador.
*
*/

#ifndef INPUT_H
#define INPUT_H

int obterInt(int minValor, int maxValor, char *msg);

long int obterLongLong(long int minValor, long int maxValor, char *msg);

float obterFloat(float minValor, float maxValor, char *msg);

double obterDouble(double minValor, double maxValor, char *msg);

char obterChar(char *msg);

void lerString(char *string, unsigned int tamanho, char *msg);

int validarEmail(char *email);

void lerEmail(char *email, unsigned int tamanho, char *msg);

#endif /* INPUT_H */


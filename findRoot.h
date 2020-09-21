#include <stdio.h>

/*
    Imprime na tela o resultado de uma iteração.
    11 espaços entre valores, 8 casas decimais de precisão.
*/
void printXk(double (*funcao)(double x), int k, double *x, FILE* pfile);


int bissecao(double (*funcao)(double x), double *x, double x0, double x1, double erro, int maxITER, FILE *pfile);

int newton(double (*funcao)(double x), double (*derivada)(double x), double *x, double x0, double x1, double erro, int maxITER, FILE *pfile);


/*
    Aplica o método das secantes no intervalo [x0, x1], com precisão de "erro" e limite de maxITER iterações. 
    Os resultados são inseridos em um arquivo indicado por pfile (são necessárias permissões de leitura e escrita).
*/
int secantes(double (*funcao)(double x), double *x, double x0, double x1, double erro, int maxITER, FILE *pfile);

/*
    Aplica o método das secantes Regula Falsi no intervalo [x0, x1], com precisão de "erro" e limite de maxITER iterações. 
    Os resultados são inseridos em um arquivo indicado por pfile (são necessárias permissões de leitura e escrita).
*/
int secantesRegulaFalsi(double (*funcao)(double x), double *x, double x0, double x1, double erro, int maxITER, FILE *pfile);
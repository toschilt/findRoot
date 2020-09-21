#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "findRoot.h"

double funcao(double x) {
    double fx = 21*(x*x*x*x) - 11*(x*x*x) + 19*(x*x) - 11*x - 2;
    return fx;
}

double derivada(double x) {
    double fx = 84*(x*x*x) - 33*(x*x) + 38*x - 11;
    return fx;
}

int main() {
    FILE *pfile = fopen("out.txt", "w");
    assert(pfile);

    int MAXITER = 60;
    double x[MAXITER];
    double erro = 0.000001;
    int kraiz1, kraiz2, kraiz3, kraiz4;

    kraiz1 = bissecao(funcao, x, -1, 0, erro, MAXITER, pfile);
    printf("\n");
    kraiz2 = newton(funcao, derivada, x, -1, 0, erro, MAXITER, pfile);
    printf("\n");
    kraiz3 = secantes(funcao, x, -1, 0, erro, MAXITER, pfile);
    printf("\n");
    kraiz4 = secantesRegulaFalsi(funcao, x, -1, 0, erro, MAXITER, pfile);
    printf("\n");

    fclose(pfile);
    return 0;
}
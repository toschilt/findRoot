#include <stdio.h>
#include <stdlib.h>
#include "findRoot.h"

double max(double x, double y) {
    if (x >= y)
        return x;
    else
        return y;
}

double modulo(double x) {
    if(x < 0)
        return (-x);
    else
        return x;
}

void printXk(double (*funcao)(double x), int k, double *x, FILE* pfile) {
    //Imprimindo o número da iteração
    printf("%d         ", k);
    fprintf(pfile, "%d         ", k);
    if(k < 10) {
        printf(" ");
        fprintf(pfile, " ");
    }


    //Imprimindo o valor de xk
    if(x[k] >= 0) {
        printf(" ");
        fprintf(pfile, " ");
    }
    if(x[k] < 10) {
        printf(" ");
        fprintf(pfile, " ");
    }
    printf("%.8f          ", x[k]);
    fprintf(pfile, "%.8f          ", x[k]);
    

    //Imprimindo f(xk)
    if(funcao(x[k]) > 0) {
        printf(" ");
        fprintf(pfile, " ");
    }
    printf("%.8f          ", funcao(x[k]));
    fprintf(pfile, "%.8f          ", funcao(x[k]));
    

    //Imprimindo ek
    if(funcao(x[k]) < 10) {
        printf(" ");
        fprintf(pfile, " ");
    }
    if(k == 0) {
        printf("%.8f\n", 0.0);
        fprintf(pfile, "%.8f\n", 0.0);
    }
    else
    {
        printf("%.8f\n", modulo(x[k] - 0));
        fprintf(pfile, "%.8f\n", modulo(x[k] - 0));
    }
}

int bissecao(double (*funcao)(double x), double *x, double x0, double x1, double erro, int maxITER, FILE *pfile) {
    int k;
    double a, b;

    x[0] = x0;
    x[1] = x1;

    if(funcao(x[0]) == 0)
        return 0;
    if(funcao(x[1]) == 0)
        return 1;

    if (funcao(x[0]) * funcao(x[1]) >= 0) {
        return -2; //x0 e x1 não são ideais (RETORNA ERRO)
    }

    printf("No intervalo [%.1f, %.1f]\n\n", x[0], x[1]);
    printf("k            Xk                   f(Xk)                ek\n");

    fprintf(pfile, "No intervalo [%.1f, ", x[0]);
    fprintf(pfile, "%.1f],\n\n", x[1]);
    fprintf(pfile, "k            Xk                   f(Xk)                ek\n");

    printXk(funcao, 0, x, pfile);
    printXk(funcao, 1, x, pfile);

    a = x0;
    b = x1;

    for (k = 2; k <= maxITER; k++) {
        x[k] = (a + b)/2;
        printXk(funcao, k, x, pfile);
        
        if(funcao(x[k]) == 0 ||
           modulo(x[k] - x[k-1]) < erro*max(1.0, modulo(x[k]))) {
               return k;
           }

        //Escolhendo o intervalo em que a função inverte de sinal para a próxima iteração
        if(funcao(x[k]) * funcao(a) < 0)
            b = x[k];

        if(funcao(x[k]) * funcao(b) < 0)
            a = x[k];
    }

    return -1; //Máximo de iterações atingido (RETORNA ERRO)
}

int newton(double (*funcao)(double x), double (*derivada)(double x), double *x, double x0, double x1, double erro, int maxITER, FILE *pfile) {
    int k;
    x[0] = (x0 + x1)/2;

    printf("No intervalo [%.8f, %.8f]\n\n", x[0], x[1]);
    printf("k            Xk                   f(Xk)                ek\n");

    fprintf(pfile, "No intervalo [%.8f, ", x[0]);
    fprintf(pfile, "%.8f],\n\n", x[1]);
    fprintf(pfile, "k            Xk                   f(Xk)                ek\n");

    printXk(funcao, 0, x, pfile);
    printXk(funcao, 1, x, pfile);

    for (k = 1; k <= maxITER; k++) {
        x[k] = x[k - 1] - (funcao(x[k-1]))/(derivada(x[k-1]));
        printXk(funcao, k, x, pfile);

        if(modulo(x[k] - x[k-1]) < erro * max(1, modulo(x[k])))
            return k;
    }

    return -1; //Máximo de iterações atingido (RETORNA ERRO)
}

int secantes(double (*funcao)(double x), double *x, double x0, double x1, double erro, int maxITER, FILE *pfile) {
    int k;
    x[0] = x0;
    x[1] = x1;

    printf("No intervalo [%.8f, %.8f]\n\n", x[0], x[1]);
    printf("k            Xk                   f(Xk)                ek\n");

    fprintf(pfile, "No intervalo [%.8f, ", x[0]);
    fprintf(pfile, "%.8f],\n\n", x[1]);
    fprintf(pfile, "k            Xk                   f(Xk)                ek\n");

    printXk(funcao, 0, x, pfile);
    printXk(funcao, 1, x, pfile);

    for (k = 2; k <= maxITER; k++) {
        x[k] = (funcao(x[k-1])*x[k-2] - funcao(x[k-2])*x[k-1])/(funcao(x[k-1]) - funcao(x[k-2]));
        printXk(funcao, k, x, pfile);

        if(modulo(x[k] - x[k-1]) < erro * max(1, modulo(x[k])))
            return k;
    }

    return -1; //Máximo de iterações atingido (RETORNA ERRO)
}

int secantesRegulaFalsi(double (*funcao)(double x), double *x, double x0, double x1, double erro, int maxITER, FILE *pfile) {
    int k;
    double s0, s1;
    
    s0 = x0;
    s1 = x1;

    x[0] = x0;
    x[1] = x1;

    if (funcao(x[0]) * funcao(x[1]) >= 0) {
        return -2; //x0 e x1 não são ideais (RETORNA ERRO)
    }

    printf("No intervalo [%.1f, %.1f]\n\n", x[0], x[1]);
    printf("k            Xk                   f(Xk)                ek\n");

    fprintf(pfile, "No intervalo [%.1f, ", x[0]);
    fprintf(pfile, "%.1f],\n\n", x[1]);
    fprintf(pfile, "k            Xk                   f(Xk)                ek\n");

    printXk(funcao, 0, x, pfile);
    printXk(funcao, 1, x, pfile);

    for (k = 2; k <= maxITER; k++) {
        x[k] = (funcao(s1)*s0 - funcao(s0)*s1) / (funcao(s1) - funcao(s0));
        printXk(funcao, k, x, pfile);
        
        if(modulo(x[k] - s0) < erro * max(1, modulo(x[k])) || modulo(x[k] - s1) < erro * max(1, modulo(x[k]))) {
            return k; //Retornando o valor final
        }   

        //Escolhendo o intervalo em que a função inverte de sinal para a próxima iteração
        if(funcao(x[k]) * funcao(s1) < 0) { 
            s0 = s1;
            s1 = x[k];
        }
        else
            s1 = x[k];
    }

    return -1; //Máximo de iterações atingido (RETORNA ERRO)
}
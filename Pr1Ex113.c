//
// Programa per a solucionar equacions polinomiques de segon grau.
//
#include <math.h>
#include <stdio.h>
#define tol 0.000000001
int main() {
    double a, b, c, discr, sqrtdiscr;
    printf("\nIntroduiu les dades a,b,c del polinomi a*x^2+b*x+c:\n");
    while (scanf("%lf %lf %lf", &a, &b, &c) < 3) {
        while (getchar() != '\n') {}
        printf("Les dades no han entrat be....\nTorneu-hi...\n");
    }
    if (fabs(a) < tol) {
        printf("L'equacio no es de segon grau si poseu a=0 .\n");
        printf("La solucio de\n (%g) * x + (%g) =0\nes:\n", b, c);
        printf("x= %.12g\n",-c / b);
    }
    else if (fabs(b) < tol) {
        printf("L'equacó de segon grau té coeficient b=0 .\n");
        printf("Les solucions de\n (%g) * x^2 + (%g) =0\nson:\n", a, c);
        printf("x1= %.12g, x2= %.12g\n",sqrt(-c/a),-sqrt(-c/a));
    }
    else {
        discr = b * b- 4 * a * c;
    if (discr < 0) {
        printf("\nEquacio amb solucions complexes\n");
        printf("(%g)*x^2+(%g)*x+(%g)=0\n", a, b, c);
        printf("x1=%.12g + %.12gi, x2=%.12g - %.12gi\n\n", -b/(2*a), sqrt(4*a*c - b*b)/(2*a), -b/(2*a), sqrt(4*a*c - b*b)/(2*a));
    } 
    else {
        if (discr < tol) {
            printf("\nEquacio amb solucio doble:\n");
            printf("La solucio de l'equacio\n");
            printf("(%g)*x^2+(%g)*x+(%g)=0\n", a, b, c);
            printf("es\n");
            printf("x=%.12g\n",-b / (2 * a));
    }   
        else {
            sqrtdiscr = sqrt(discr);
            printf("\nEquacio amb dues solucions.\n");
            printf("Les solucions de l'equacio\n");
            printf("(%g)*x^2+(%g)*x+(%g)=0\n", a, b, c);
            printf("son\n");
            printf("x=%.12g, x=%.12g\n\n", (-b + sqrtdiscr) / (2 * a),
            (-b-sqrtdiscr) / (2 * a));
    }
    }
    }
    return 0;
}
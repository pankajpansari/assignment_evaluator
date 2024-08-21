#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#define NUMBER 0
#define MAXVAL 100

// FEEDBACK: Consider encapsulating these global variables into a struct for better modularity
int sp = 0;
double val[MAXVAL];

// FEEDBACK: Rename this function to 'push' for better readability
void p(double f) {
    if (sp < MAXVAL)
        val[sp++] = f;
    else
        printf("error: stack full, can't push %g\n", f);
}

// FEEDBACK: Rename this function to 'pop' for better readability
double o() {
    if (sp > 0)
        return val[--sp];
    else {
        printf("error: stack empty\n");
        return 0.0;
    }
}

// FEEDBACK: Break down this long main function into smaller, more focused functions
int main(int a, char *v[]) {
    int t, c;
    double o2, o1, l;
    
    // FEEDBACK: Add input validation for command-line arguments
    while (--a > 0) {
        *++v;
        if (!isdigit(c = **v) && strlen(*v) == 1)
            t = c;
        else
            t = NUMBER;
        
        // FEEDBACK: Consider using a lookup table or function pointers for operations
        switch (t) {
            case NUMBER:
                p(atof(*v));
                break;
            case '+':
                p(o() + o());
                break;
            case '*':
                p(o() * o());
                break;
            case '-':
                o2 = o();
                p(o() - o2);
                break;
            case '/':
                o2 = o();
                if (o2 != 0.0)
                    p(o() / o2);
                else
                    printf("error: zero divisor\n");
                break;
            case '%':
                o2 = o();
                if (o2 != 0.0)
                    p(fmod(o(), o2));
                else
                    printf("error: zero divisor\n");
                break;
            case '^':
                o2 = o();
                o1 = o();
                if (o1 == 0.0 && o2 <= 0)
                    printf("if x = 0.0, y must be greater than 0\n");
                else
                    p(pow(o1, o2));
                break;
            case 'e':
                p(exp(o()));
                break;
            case '~':
                p(sin(o()));
                break;
            default:
                printf("error: unknown command: %c\n", t);
                break;
        }
    }
    
    l = o();
    printf("\t%.8g\n", l);
    return 0;
}

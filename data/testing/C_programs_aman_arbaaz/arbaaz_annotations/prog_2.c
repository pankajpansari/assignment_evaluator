// code here is not readable and should be formatted properly.

// #includes should be sorted 
// ctype.h should also be included to provide the declaration for isdigit
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#define NUMBER 0
#define MAXVAL 100
int sp = 0;
double val[MAXVAL];

// function and parameter names should be more descriptive and the function should be 
// written properly on multiple lines.
void p(double f){if(sp<MAXVAL)val[sp++]=f;else printf("error: stack full, can't push %g\n",f);}
double o(){if(sp>0)return val[--sp];else{printf("error: stack empty\n");return 0.0;}}
// the result of expression *++v is unused and the dereferencing does nothing.
int main(int a,char*v[]){int t,c;double o2,o1,l;while(--a>0){*++v;if(!isdigit(c=**v)&&strlen(*v)==1)t=c;else t=NUMBER;switch(t){case NUMBER:p(atof(*v));break;case'+':p(o()+o());break;case'*':p(o()*o());break;case'-':o2=o();p(o()-o2);break;case'/':o2=o();if(o2!=0.0)p(o()/o2);else printf("error: zero divisor\n");break;case'%':o2=o();if(o2!=0.0)p(fmod(o(),o2));else printf("error: zero divisor\n");break;case'^':o2=o();o1=o();if(o1==0.0&&o2<=0)printf("if x = 0.0, y must be greater than 0\n");else p(pow(o1,o2));break;case'e':p(exp(o()));break;case'~':p(sin(o()));break;default:printf("error: unknown command: %c\n",t);break;}}l=o();printf("\t%.8g\n",l);return 0;}

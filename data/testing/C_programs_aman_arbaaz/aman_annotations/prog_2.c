#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#define NUMBER 0
#define MAXVAL 100 // Define what this is the maximum value for? Or can consider doing dynamic allocation. 
int sp = 0; // Describe what variables represent.
double val[MAXVAL];
void p(double f){if(sp<MAXVAL)val[sp++]=f;else printf("error: stack full, can't push %g\n",f);} // Good practice to include error handling and underflow / overflow errors. 
double o(){if(sp>0)return val[--sp];else{printf("error: stack empty\n");return 0.0;}} 
int main(int a,char*v[]){int t,c;double o2,o1,l;while(--a>0){*++v;if(!isdigit(c=**v)&&strlen(*v)==1)t=c;else t=NUMBER;switch(t){case NUMBER:p(atof(*v));break;case'+':p(o()+o());break;case'*':p(o()*o());break;case'-':o2=o();p(o()-o2);break;case'/':o2=o();if(o2!=0.0)p(o()/o2);else printf("error: zero divisor\n");break;case'%':o2=o();if(o2!=0.0)p(fmod(o(),o2));else printf("error: zero divisor\n");break;case'^':o2=o();o1=o();if(o1==0.0&&o2<=0)printf("if x = 0.0, y must be greater than 0\n");else p(pow(o1,o2));break;case'e':p(exp(o()));break;case'~':p(sin(o()));break;default:printf("error: unknown command: %c\n",t);break;}}l=o();printf("\t%.8g\n",l);return 0;}

// Functions must be well indented and broken down. Single line functions reduce readability considerably. Good error handling for stack and zero division. 
// Variables must be better named or described with comments. 

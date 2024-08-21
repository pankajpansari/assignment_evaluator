#include <stdio.h>
#define M 10
#define I 1
#define O 0
int a[11];int s=I;int n=0;int m(){int c=EOF,i,j;for(i=0;i<=M;++i)a[i]=0;while((c=getchar())!=EOF){++n;if(c==' '||c=='\t'||c=='\n'){s=O;--n;}if(s==O){if(n!=0&&n<=M)++a[n];s=I;n=0;}}for(i=1;i<=M;++i){printf("|%2d| ",i);for(j=0;j<a[i];++j)putchar('*');putchar('\n');}return 0;}

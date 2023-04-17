#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cmath>


using namespace std;
double energia(int s[][100]);
double minimo (double energia, double T);

int main (void)
{
    int i,j;
    double T;
    int N,n,m;
    int s[100][100];
    double e;

    srand(time(NULL));

    cout<<"Introduzca una temperatura entre 0 y 5:";
    cin>>T;
    cout<<"Introduzca el tamaño de la cuadricula:";
    cin>>N;

    for(i=0;i<=N;i++)
        for(j=0;j<=N;j++)
           s[i][j]=(-1)^rand();

//elegir aleatoriamente s(n,m)

  n=rand()% N+1;
  m=rand()% N+1;

  //generar un numero aleatorio entre 0 y 1
  e=(double) rand()/RAND_MAX;

  if(e<minimo(energia(s),T))
      s[n][m]=-s[n][m];

   return 0;
}

double energia (s[100][100])
{
   int n,m;

   if((n=0)&&(m=0)) return 2*s[n][m]*(s[n+1][m]+s[N][m]+s[n][m+1]+s[n][N]);

   if((n=N)&&(m=N)) return 2*s[n][m]*(s[0][m]+s[n-1][m]+s[n][0]+s[n][m-1]);

   if(n=0) return 2*s[n][m]*(s[n+1][m]+s[N][m]+s[n][m+1]+s[n][m-1]);

   if(m=0) return 2*s[n][m]*(s[n+1][m]+s[n-1][m]+s[n][m+1]+s[n][N]);

   if(n=N) return 2*s[n][m]*(s[0][m]+s[n-1][m]+s[n][m+1]+s[n][m-1]);

   if(m=N) return 2*s[n][m]*(s[n+1][m]+s[n-1][m]+s[n][0]+s[n][m-1]);

   else return 2*s[n][m]*(s[n+1][m]+s[n-1][m]+s[n][m+1]+s[n][m-1]);

};

double minimo (energia(s),T)
{

   double cosa;
   
   cosa=exp(-(energia(s))/T);

    if(cosa<1) return cosa;
    else return 1;

};

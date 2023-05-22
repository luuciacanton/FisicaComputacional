#include <iostream>
#include <cmath>
#include <fstream>
#include <ctime>
#include <cstdlib>
#define N 64 //dimension de la red de espines

using namespace std;

int main (void)
{
   double T, energia, cosa, p, epsilon;
   int n,m;
   int i,j,k,l;
   int iter;
   int s[N][N];
   ofstream fich;

   cout<<"Introduzca el valor de la temperatura:";
   cin>>T;

   cout<<"Introduzca el numero de iteraciones: ";
   cin>>iter;

//fichero donde se meteran las matrices 
fich.open("ising_data.dat");

   /*
   for(i=0;i<N;i++)
   {
      for(j=0;j<N;j++)
         {
            s[i][j]=-1;
         }
   }
   */


//se inician los espines aleatoriamente 1 o -1
 srand(time(NULL));
  for(i=0;i<N;i++)
  {
    for(j=0;j<N;j++)
    {
        s[i][j]=pow(-1,rand());    
    }
          
  }

//MODELO DE ISING: METODO DE MONTE CARLO
for (i=0;i<=iter;i++)
{

   for(k=0;k<N;k++)
     {
         for(l=0;l<N-1;l++)
           {
             fich<<s[k][l]<<", ";
           }
             fich<<s[k][N-1]<<endl;        
     }
    fich<<endl;

    for(j=0;j<N*N;j++)
    {

        //elegir aleatoriamente s(n,m)

        n=rand()%(N);
        m=rand()%(N);

  //calcular energia

   if((n==0)&&(m==0)) energia=2*s[n][m]*(s[n+1][m]+s[N-1][m]+s[n][m+1]+s[n][N-1]);
       
   else if((n==N-1)&&(m==N-1)) energia= 2*s[n][m]*(s[0][m]+s[n-1][m]+s[n][0]+s[n][m-1]);

   else if((n==0)&&(m!=N-1)&&(m!=0)) energia= 2*s[n][m]*(s[n+1][m]+s[N-1][m]+s[n][m+1]+s[n][m-1]);

   else if((m==0)&&(n!=N-1)&&(n!=0)) energia= 2*s[n][m]*(s[n+1][m]+s[n-1][m]+s[n][m+1]+s[n][N-1]);

   else if((n==N-1)&&(m!=N-1)&&(m!=0)) energia= 2*s[n][m]*(s[0][m]+s[n-1][m]+s[n][m+1]+s[n][m-1]);

   else if((m==N-1)&&(n!=N-1)&&(n!=0)) energia=2*s[n][m]*(s[n+1][m]+s[n-1][m]+s[n][0]+s[n][m-1]);

   else if((n==0)&&(m==N-1)) energia= 2*s[n][m]*(s[n+1][m]+s[N-1][m]+s[n][0]+s[n][m-1]);

   else if((n==N-1)&&(m==0)) energia= 2*s[n][m]*(s[0][m]+s[n-1][m]+s[n][m+1]+s[n][N-1]);

   else energia=2*s[n][m]*(s[n+1][m]+s[n-1][m]+s[n][m+1]+s[n][m-1]);

    
 cosa=exp(-(energia/T));

//obtener minim0
 if(cosa<1) p=cosa;
 else p=1;

//numero aleatorio entre 0 y 1
 epsilon=(double) rand()/RAND_MAX;

 if(epsilon<p) s[n][m]=-s[n][m];
 
    }

   
}

   fich.close();
      return 0;
}
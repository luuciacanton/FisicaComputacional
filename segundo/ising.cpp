#include <iostream>
#include <cmath>
#include <fstream>
#define N 10

using namespace std;

int main (void)
{
   double T, energia, cosa, p, epsilon;
   int n,m;
   int i,j;
   int iter;
   int s[N][N];
   ofstream fich;

   cout<<"Introduzca el valor de la temperatura:";
   cin>>T;

   cout<<"Introduzca el numero de iteraciones:";
   cin>>iter;

fich.open("matriz.txt");

   /*
   for(i=0;i<N;i++)
   {
      for(j=0;j<N;j++)
         {
            s[i][j]=-1;
         }
   }
   */
//numeros aleatorios

  for(i=0;i<N;i++)
  {
    for(j=0;j<N;j++)
    {
        s[i][j]=pow(-1,rand());
    }
          
  }

for (i=1;i<=iter;i++)
{

   for(i=0;i<N;i++)
           {
               for(j=0;j<N-1;j++)
                 {
                      fich<<s[i][j]<<", ";
                  }
                fich<<s[i][N-1]<<endl;        
           }
    fich<<endl;

    for(j=0;j<N*N;j++)
    {

        //elegir aleatoriamente s(n,m)

        n=rand()% N;
        m=rand()% N;

  //calcular energia

   if((n=0)&&(m=0)) energia=2*s[n][m]*(s[n+1][m]+s[N-1][m]+s[n][m+1]+s[n][N-1]);
       
   else if((n=N-1)&&(m=N-1)) energia= 2*s[n][m]*(s[0][m]+s[n-1][m]+s[n][0]+s[n][m-1]);

   else if(n=0) energia= 2*s[n][m]*(s[n+1][m]+s[N-1][m]+s[n][m+1]+s[n][m-1]);

   else if(m=0) energia= 2*s[n][m]*(s[n+1][m]+s[n-1][m]+s[n][m+1]+s[n][N-1]);

   else if(n=N-1) energia= 2*s[n][m]*(s[0][m]+s[n-1][m]+s[n][m+1]+s[n][m-1]);

   else if(m=N-1) energia=2*s[n][m]*(s[n+1][m]+s[n-1][m]+s[n][0]+s[n][m-1]);

   else if((n=0)&&(m=N-1)) energia= 2*s[n][m]*(s[n+1][m]+s[N-1][m]+s[n][0]+s[n][m-1]);

   else if((n=N-1)&&(m=0)) energia= 2*s[n][m]*(s[0][m]+s[n-1][m]+s[n][m+1]+s[n][N-1]);

   else energia=2*s[n][m]*(s[n+1][m]+s[n-1][m]+s[n][m+1]+s[n][m-1]);

    
 cosa=exp(-(energia/T));

 if(cosa<1) p=cosa;
 else p=1;

 epsilon=(double) rand()/RAND_MAX;

 if(epsilon<p) s[n][m]=-s[n][m];
 
    }

   
}

   fich.close();
      return 0;
}
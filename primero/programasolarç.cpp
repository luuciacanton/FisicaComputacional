# include <iostream>
#include<fstream>
#include <cmath>
using namespace std;
#define MasaSol 1.989e30
#define G 6.67e-11
#define c 1.496e11
#define h 0.1

void pasaravectores (double vector[], string fichero);
void aceleracion  (double a[], double masas[], double pos1[], double pos2[]);
void posiciones (double r[], double w[],double v[], double a[]);
void velocidades (double w[],double a[], double v[]);

int main (void)
{
   int i;
   //vectores donde se van a copiar los datos iniciales
double masas[9], rx[9], vy[9];
//vectores que se inician en 0
double ry[9], vx[9];
double ax[9],ay[9];

pasaravectores ( masas, "masasescaladas.txt");
pasaravectores ( rx, "distanciasolyaescala.txt");
pasaravectores ( vy, "velorb.txt");

/*for (i=0;i<9;i++)
{
   cout<<masas[i]<<endl;
}
cout<<endl;
for (i=0;i<9;i++)
{
   cout<<rx[i]<<endl;
}
cout<<endl;
for (i=0;i<9;i++)
{
   cout<<vy[i]<<endl;
}
*/
for(i=0;i<9;i++)
{
   ry[i]=0.0;
   vx[i]=0.0;
}

aceleracion  ( ax,  masas, rx, ry);
aceleracion  ( ay,  masas, ry, rx);

for (i=0;i<9;i++)
{
   cout<<ax[i]<<","<<ay[i]<<endl;
}


  return 0 ;

}

void pasaravectores (double vector[9], string fichero)
{
    ifstream fich;
    int i;

    fich.open(fichero);

    for(i=0;i<9;i++)
       fich>>vector[i];

fich.close();
   return ;
}


void aceleracion  (double a[], double masas[], double pos1[], double pos2[])
{

   int i,j;
   double suma, norma;

   suma=0.0;
   for(i=0;i<9;i++)
   {
      for(j=0;j<9;j++)
         if(j!=i)
         {
            norma=sqrt((pos1[i]-pos1[j])*(pos1[i]-pos1[j])+(pos2[i]-pos2[j])*(pos2[i]-pos2[j]));
            suma+=masas[j]*((pos1[i]-pos1[j])/pow(norma,3));
         }

         a[i]=-suma;
   }

   return;
}


void posiciones (double r[], double w[],double v[], double a[])
{
    int i;

    for (i=0;i<9;i++)
    {
      r[i]=h*v[i]+h*h*a[i]/2.0;
      w[i]=v[i]+h*a[i]/2.0;
    }

    return;
}

void velocidades (double w[],double a[], double v[])
{
   int i;
   for(i=0;i<9;i++)
   {
      v[i]=w[i] +h*a[i]/2.0;

   }

   return ;
}

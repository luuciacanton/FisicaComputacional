# include <iostream>
#include<fstream>
#include <cmath>
using namespace std;
#define MasaSol 1.989e30
#define G 6.67e-20
#define c 1.496e8
#define h 0.1 //paso del bucle

void pasaravectores (double vector[], string fichero);
void aceleracion  (double a[], double masas[], double pos1[], double pos2[]);
void posicionesyw (double r[], double w[],double v[], double a[]);
void velocidades (double w[],double a[], double v[]);

int main ( )
{
   
   int i;
   //vectores donde se van a copiar los datos iniciales
   double masas[9], rx[9], vy[9];
   //vectores que se inician en 0
   double ry[9], vx[9];
   double ax[9],ay[9];
   double t, tfinal, iter;
   double wx[9], wy[9];
   ofstream fichpos, fichvel, fichacel;

pasaravectores ( masas, "masasescaladas.txt");
pasaravectores ( rx, "distanciasolyaescala.txt");
pasaravectores ( vy, "velorb.txt");


for(i=0;i<9;i++)
{
   ry[i]=0.0;
   vx[i]=0.0;
   ax[i]=0.0;
   ay[i]=0.0;

}

//algoritmo verlet

fichpos.open("planets_data.dat");
fichvel.open("velocidades.txt");
fichacel.open("aceleracion.txt");

for(i=0;i<9;i++)
{
   vy[i]=vy[i]/sqrt(G*MasaSol/c);
}

aceleracion  ( ax,  masas, rx, ry);
aceleracion  ( ay,  masas, ry, rx);


cout<<"Introduzca el tiempo durante el cual se va a ejecutar el programa:";
cin>>tfinal;
//numero iteraciones
iter= tfinal/h;


for (t=0;t<iter;t++)
{

   for(i=0;i<9;i++)
   {
        fichpos<<rx[i]<<", "<<ry[i]<<endl;
   }
  
   fichpos<<endl;

   posicionesyw ( rx, wx, vx,  ax);
   posicionesyw ( ry, wy, vy,  ay);

/*
   for(i=0;i<9;i++)
   {
      ax[i]=0.0;
      ay[i]=0.0;

   }
   */

   aceleracion  ( ax,  masas, rx, ry);
   aceleracion  ( ay,  masas, ry, rx);
   
   velocidades ( wx,ax, vx);
   velocidades ( wy,ay, vy);

   t =t+h;

}

fichpos.close();
fichvel.close();
fichacel.close();

  return 0 ;
 
}

/////////////////////FUNCIONES////////////////////////


//pasar los datos de masas, distancias y velocidades a vectores
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
         if(i!=j) 
         {
            norma=sqrt((pos1[i]-pos1[j])*(pos1[i]-pos1[j])+(pos2[i]-pos2[j])*(pos2[i]-pos2[j]));
            a[i]-=masas[j]*((pos1[i]-pos1[j])/(norma*norma*norma));
         }
         
      //a[i]=suma;   
   }

   return;
}


void posicionesyw (double r[], double w[],double v[], double a[])
{
    int i;

    for (i=0;i<9;i++)
    {
      r[i]=r[i]+h*v[i]+h*h*a[i]/2.0; 
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


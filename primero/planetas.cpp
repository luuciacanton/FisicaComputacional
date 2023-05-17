# include <iostream>
#include<fstream>
#include <cmath>
#define MasaSol 1.99e30 //kg
#define G 6.67e-20 //km^3/kgs
#define c 1.496e8 //km
#define h 0.1 //paso del bucle

using namespace std;

void pasaravectores (double vector[], string fichero);
void aceleracion  (double a[], double masas[], double pos1[], double pos2[]);
void posicionesyw (double r[], double w[],double v[], double a[]);
void velocidades (double w[],double a[], double v[]);
double energia (double pos1[], double pos2[], double vx[], double vy[], double masas[]);

int main (void)
{
   
   int i,j;
   //vectores donde se van a copiar los datos iniciales
   double masas[9], rx[9], vy[9];
   //vectores que se inician en 0
   double ry[9], vx[9], ryanterior[9];
   double ax[9],ay[9];
   //tiempo durante el cual se va a ejecutar el programa del cual sacamos el numero de iteraciones
   double t, tfinal, iter;
   double wx[9], wy[9];
   //ficheros donde se introducen los valores de la posicion, la energia y periodo
   ofstream fichpos, fichenerg, fichper, fichax, fichay;
   int cont[9];

//los planetas saldran todos del eje x con una velocidad perpendicular vy por lo que vx e y inicialmente son 0

//pasamos los datos iniciales a vectores para poder trabajar con ellos
//las masas y las posiciones se encuentran ya reescaldas para no perder precision, ya que trabajamos con valores muy grandes y muy pequeños simultaneamente
pasaravectores ( masas, "masasescaladas.txt");
pasaravectores ( rx, "distanciasolyaescala.txt");
pasaravectores ( vy, "velorb.txt");


//vectores que iniciamos en 0
for(i=0;i<9;i++)
{
   ry[i]=0.0;
   vx[i]=0.0;
   ax[i]=0.0;
   ay[i]=0.0;

}

//algoritmo verlet


fichpos.open("planets_data.dat");
fichenerg.open("energia.txt");
fichper.open("periodo.txt");
fichax.open("ax.txt");
fichay.open("ay.txt");

//tambien hace falta reescalar las velocidades
for(i=0;i<9;i++)
{
   vy[i]=vy[i]/sqrt(G*MasaSol/c);
}

//aceleracion inicial
aceleracion  ( ax,  masas, rx, ry);
aceleracion  ( ay,  masas, ry, rx);


cout<<"Introduzca el tiempo durante el cual se va a ejecutar el programa:";
cin>>tfinal;
//numero iteraciones
iter= (int) tfinal/h;
t=0;

for (i=0;i<=iter;i++)
{
  
//meto en otro vector el valor de la posicion en y para poder calcular despues el periodo 
   for(j=0;j<9;j++)
   {
       ryanterior[j]=ry[j];
   }

   //calculamos la energia y la metemos en su txt
   fichenerg<<t<<"   "<<energia ( rx, ry, vx,  vy, masas)<<endl;

   for(j=0;j<9;j++)
   {
        fichax<<ax[j]<<endl;
   }
   fichax<<endl;

   for(j=0;j<9;j++)
   { 
        fichay<<ay[j]<<endl;
   }
   fichay<<endl;



   for(j=0;j<9;j++)
   {
        fichpos<<rx[j]<<", "<<ry[j]<<endl;
   }
  
   fichpos<<endl;

   posicionesyw ( rx, wx, vx,  ax);
   posicionesyw ( ry, wy, vy,  ay);


   for(j=0;j<9;j++)
   {
      ax[j]=0.0;
      ay[j]=0.0;

   }
   

   aceleracion  ( ax,  masas, rx, ry);
   aceleracion  ( ay,  masas, ry, rx);
   
   velocidades ( wx,ax, vx);
   velocidades ( wy,ay, vy);


 //periodo
 for(j=1;j<9;j++)
   {
       if(cont[j]==0)
       {
         if((ryanterior[j]<0)&&(ry[j]>0))
         {
            cont[j]=1;
            fichper<<j<<"  "<< t*58.1 <<endl; //58.1 es la unidad temporal (reescalamiento)
         }
       }
   }

   t =t+h;

}

fichpos.close();
fichenerg.close();
fichper.close();

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
   double norma;

   for(i=0;i<9;i++)
   {
      for(j=0;j<9;j++)
         if(i!=j) 
         {
            norma=sqrt((pos1[i]-pos1[j])*(pos1[i]-pos1[j])+(pos2[i]-pos2[j])*(pos2[i]-pos2[j]));
            a[i]-=masas[j]*((pos1[i]-pos1[j])/(norma*norma*norma));
         }
         
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

//calculamos la energia mecanica del sistema con la energia cinetica y potencial gravitatoria
double energia (double pos1[], double pos2[], double vx[], double vy[], double masas[])
{
  int i,j;
  double E;
  double norma;
  //E es una sumatoria asique la iniciamos a 0
  E=0;
//emepezamos el bucle en 1 para no meter el sol
  for (i=1;i<9;i++)
  {
      //cinetica
      E+= 0.5*masas[i]*(vx[i]*vx[i]+vy[i]*vy[i]);
      //potencial gravitatorio
      for (j=0;j<9;j++)
      {
         if(i!=j)
         {
            norma=sqrt((pos1[i]-pos1[j])*(pos1[i]-pos1[j])+(pos2[i]-pos2[j])*(pos2[i]-pos2[j]));
            E-=masas[i]*masas[j]/norma;
         }
      }

  }

  return E;

}


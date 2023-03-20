# include <iostream>
#include <fstream>
using namespace std;
void conversionmasas ( masas, masasc );

int main (void)
{

   double masasc[9],masas[9];
   cout<<"HOLA";


}

void conversionmasas ( masas[9], masasc[9] )
{
   ifstream fich;

   fich.open("masas.txt");
   
   double masasc[9],masas[9];
   
   for(i=1;i<=9;i++)
     masasc[i]=masas[i]/19890000e23;

   fich.close();  

    return;

}
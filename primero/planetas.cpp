# include <iostream>
#include <fstream>

using namespace std;

int main (void)
{




}

void conversionmasas ( masas[], masasc[] )
{
   ifstream fich;

   fich.open("masas.txt");
   
   double masasc[9],masas[9];
   
   for(i=1;i<=9;i++)
     masasc[i]=masas[i]/19890000e23;

   fich.close();  

    return;

}
#include <iostream>

double energia(s);
using namespace std;

int main (void)
{
    int i,j;
    int N,T;
    int s[][N];

    cout<<<"Introduzca una temperatura entre 0 y 5:";
    cin>>T;
    cout<<"Introduzca el tamaño de la cuadricula:";
    cin>>N;
    
   return 0;
}

double energia (s[][N])
{
   int n,m;

   return 2*s[n][m]*(s[n+1][m]+s[n-1][m]+s[n][m+1]+s[n][m-1]);

}

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <cmath>

using namespace std;

int main(void)
{   
    bool cambio;
    double psi, psipunto, ppsi, fi, fipunto, pfi, E, k[4][4],t,aux,aux2;
    int i,j, contador;
    string linea;
        vector<double> x1_values;
        vector<double> y1_values;        
        vector<double> x3_values;
        vector<double> y3_values;
        double x1, y1, x2, y2,x11,x22,y11,y22;
        char coma;
        aux=0.;
        contador=0;

    ifstream uno("ang1yv115.dat");
    ifstream tres("ang1yv114.dat");
    ofstream coef("coef.dat");

if (!uno.is_open()) {
    cout << "No se pudo abrir el archivo uno." << endl;
    return 1;
}

if (!tres.is_open()) {
    cout << "No se pudo abrir el archivo tres." << endl;
    return 1;
}
if (uno.is_open()&&tres.is_open()) {
        while (getline(uno, linea)) 
        {
            stringstream ss2(linea);
            ss2 >> x2  >> coma >> y2;
            x1_values.push_back(x2);
            y1_values.push_back(y2);  
        }

        while (getline(tres, linea)) 
        {
            stringstream ss4(linea);
            ss4 >> x22  >> coma >> y22;
            x3_values.push_back(x22);
            y3_values.push_back(y22);
        }

        // Realizar operaciones para encontrar los coeficientes
        for (int i = 0; i < x1_values.size(); ++i) 
        {
            coef << 0.1*i << "    " << log((sqrt(pow(x1_values[i]-x3_values[i],2)+pow(y1_values[i]-y3_values[i],2)))/(sqrt(pow(x1_values[0]-x3_values[0],2)+pow(y1_values[0]-y3_values[0],2)))) << endl;
        }
}   
    return 0;
}

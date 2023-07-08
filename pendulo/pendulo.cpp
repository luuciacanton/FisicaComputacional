#include<iostream>
#include<cmath>
#include<fstream>
/*tenemos un sistema compuesto por dos masas m1 y m2 unidas por 
dos alambres de longitud l1 y l2*/
#define m1 1 
#define m2 1
#define l1 1 
#define l2 1
#define g 9.8
#define tmax 100 //tiempo de ejecucion del programa
#define h 0.1
#define PI 3.1415
double ang1punto(double pang1, double pang2, double ang1, double ang2);
double pang1punto(double pang1, double pang2, double ang1, double ang2);
double ang2punto(double pang1, double pang2, double ang1, double ang2);
double pang2punto(double pang1, double pang2, double ang1, double ang2);
double h1(double pang1, double pang2, double ang1, double ang2);
double h2(double pang1, double pang2, double ang1, double ang2);
using namespace std;


int main (void)
{

double t;
double ang1, ang2;//posiciones
double pang1,pang2;//momentos
double vang1,vang2;
double E;
double k[4][4];
ofstream  posiciones,angulos,angulo1,angulo2,ang1yv1, ang2yv2, coeficientes;

posiciones.open("posiciones.dat");
angulos.open("anguloss.dat");
ang1yv1.open("ang1yv1.dat");
ang2yv2.open("ang2yv2.dat");
coeficientes.open("coeficientes.dat");

//fijamos energia (perdemos un grado de libertad)
//E=1,3,5,10,15
E=5;
ang1=PI/7;
ang2=PI/7;
//como la velocidad angular del segundo angulo es 0, su momento inicial será 0
vang2=0.0;
//a partir de la eenrgia y teniendo en cuenta que el pang2 es 0 podemos sacar el pang1
vang1=sqrt(E-2*g*(1-cos(ang1))-g*(1-cos(ang2)));

//pang1=0.0;
//pang2=0.0;
 pang1=(m1+m2)*l1*l1*vang1+m2*l1*l2*vang2*cos(ang1-ang2);
 pang2=m2*l2*l2*vang2+m2*l1*l2*vang1*cos(ang1-ang2);

for (t = 0; t < tmax; t = t + h)
{
    

    ang1yv1<<ang1<<","<<ang1punto(pang1, pang2, ang1, ang2)<<endl;
    //ang1yv1<<endl;
    ang2yv2<<ang2<<","<<ang2punto(pang1, pang2, ang1, ang2)<<endl;
    //ang2yv2<<endl;
    angulos<<ang1<<","<<ang2<<endl;
    angulos<<endl;
    posiciones << l1 * sin(ang1) << ", " << -l1 * cos(ang1) << endl;
    posiciones << l1 * sin(ang1) + l2 * sin(ang2) << ", " << -l1 * cos(ang1) - l2 * cos(ang2) << endl;
    posiciones << endl;
   
    // fila: superíndice y columna: indica de qué magnitud es: ang1, ang2, pang1 o pang2  
    // k1
    k[0][0] = h * ang1punto(pang1, pang2, ang1, ang2);
    k[0][1] = h * ang2punto(pang1, pang2, ang1, ang2);
    k[0][2] = h * pang1punto(pang1, pang2, ang1, ang2);
    k[0][3] = h * pang2punto(pang1, pang2, ang1, ang2);

    // k2
    k[1][0] = h * ang1punto(pang1 + k[0][2] / 2.0, pang2 + k[0][3] / 2.0, ang1 + k[0][0] / 2.0, ang2 + k[0][1] / 2.0);
    k[1][1] = h * ang2punto(pang1 + k[0][2] / 2.0, pang2 + k[0][3] / 2.0, ang1 + k[0][0] / 2.0, ang2 + k[0][1] / 2.0);
    k[1][2] = h * pang1punto(pang1 + k[0][2] / 2.0, pang2 + k[0][3] / 2.0, ang1 + k[0][0] / 2.0, ang2 + k[0][1] / 2.0);
    k[1][3] = h * pang2punto(pang1 + k[0][2] / 2.0, pang2 + k[0][3] / 2.0, ang1 + k[0][0] / 2.0, ang2 + k[0][1] / 2.0);

    // k3
    k[2][0] = h * ang1punto(pang1 + k[1][2] / 2.0, pang2 + k[1][3] / 2.0, ang1 + k[1][0] / 2.0, ang2 + k[1][1] / 2.0);
    k[2][1] = h * ang2punto(pang1 + k[1][2] / 2.0, pang2 + k[1][3] / 2.0, ang1 + k[1][0] / 2.0, ang2 + k[1][1] / 2.0);
    k[2][2] = h * pang1punto(pang1 + k[1][2] / 2.0, pang2 + k[1][3] / 2.0, ang1 + k[1][0] / 2.0, ang2 + k[1][1] / 2.0);
    k[2][3] = h * pang2punto(pang1 + k[1][2] / 2.0, pang2 + k[1][3] / 2.0, ang1 + k[1][0] / 2.0, ang2 + k[1][1] / 2.0);

    // k4
    k[3][0] = h * ang1punto(pang1 + k[2][2], pang2 + k[2][3], ang1 + k[2][0], ang2 + k[2][1]);
    k[3][1] = h * ang2punto(pang1 + k[2][2], pang2 + k[2][3], ang1 + k[2][0], ang2 + k[2][1]);
    k[3][2] = h * pang1punto(pang1 + k[2][2], pang2 + k[2][3], ang1 + k[2][0], ang2 + k[2][1]);
    k[3][3] = h * pang2punto(pang1 + k[2][2], pang2 + k[2][3], ang1 + k[2][0], ang2 + k[2][1]);

   
    ang1 = ang1 + (k[0][0] + 2.0 * k[1][0] + 2.0 * k[2][0] + k[3][0]) / 6.0;
    ang2 = ang2 + (k[0][1] + 2.0 * k[1][1] + 2.0 * k[2][1] + k[3][1]) / 6.0;
    pang1 = pang1 + (k[0][2] + 2.0 * k[1][2] + 2.0 * k[2][2] + k[3][2]) / 6.0;
    pang2 = pang2 + (k[0][3] + 2.0 * k[1][3] + 2.0 * k[2][3] + k[3][3]) / 6.0;
}

posiciones.close();
angulos.close();
ang1yv1.close();
ang2yv2.close();
coeficientes.close();


return 0;

}

double ang1punto(double pang1, double pang2, double ang1, double ang2)
{
    double ang1punto;

    ang1punto=(l2*pang1-l1*pang2*cos(ang1-ang2))/(l1*l1*l2*(m1+m2*sin(ang1-ang2)*sin(ang1-ang2)));

    return ang1punto;
}

double pang1punto(double pang1, double pang2, double ang1, double ang2)
{
    double pang1punto;

    pang1punto=-(m1+m2)*g*l1*sin(ang1)- h1(pang1, pang2, ang1, ang2)+h2(pang1,pang2,ang1,ang2)*sin(2*(ang1-ang2));

    return pang1punto;
}

double ang2punto(double pang1, double pang2, double ang1, double ang2)
{
    double ang2punto;

    ang2punto = (-m2 * l2 * pang1 * cos(ang1 - ang2) + (m1 + m2) * l1 * pang2) / (m2 * l1 * l2 * l2 * (m1 + m2 * sin(ang1 - ang2) * sin(ang1 - ang2)));

    return ang2punto;
}


double pang2punto(double pang1, double pang2, double ang1, double ang2)
{
    double pang2punto;

    pang2punto=-m2*g*l2*sin(ang2)+h1(pang1, pang2, ang1, ang2)-h2(pang1,pang2,ang1,ang2)*sin(2*(ang1-ang2));

    return pang2punto;
}

double h1(double pang1, double pang2, double ang1, double ang2)
{
    double h1;
    h1 = (pang1 * pang2 * sin(ang1 - ang2)) / (l1 * l2 * (m1 + m2 * sin(ang1 - ang2) * sin(ang1 - ang2)));
    return h1;
}

double h2(double pang1, double pang2, double ang1, double ang2)
{
    double h2;
    h2 = (m2 * l2 * l2 * pang1 * pang1 + (m1 + m2) * l1 * l1 * pang2 * pang2 - 2 * m2 * l1 * l2 * pang1 * pang2 * cos(ang1 - ang2)) /
        (2 * l1 * l1 * l2 * l2 * (m1 + m2 * sin(ang1 - ang2) * sin(ang1 - ang2)) * (m1 + m2 * sin(ang1 - ang2) * sin(ang1 - ang2)));
    return h2;
}

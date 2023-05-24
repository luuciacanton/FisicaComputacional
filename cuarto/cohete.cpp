#include<iostream>
#include<cmath>
#include<fstream>
#define w 2.6617e-6
#define G 6.67e-11
#define Mt 5.9736e24
#define Ml 0.07349e24
#define dtl 3.844e8
#define Rt 6.378160e6
#define Rl 1.7374e6
#define tmax 250000
//550000

using namespace std;

double prpunto(double posc, double phic, double pphi, double t);
double pphipunto(double posc, double phic, double t);

int main(void)
{

    int t;
    double mc, posc, phic, vesc ,theta;//cohete
    double posl, phil;//luna
    double pr,pphi;
    double v,k[4][4];
    ofstream posiciones,Hamiltoniano;

    //masa cohete
    mc=18000;

    //angulo cohete
    theta=0.27;//interacciona con la luna y sigue pero para abajo
    //theta=0.26;//va a la luna y vuelve
   // theta=0.22;//la interaccion es casi nula
    //theta=0.24; //interactua y sigue para arriba con otro angulo
    //theta=0.25; //se desvia aun mas

    // velocidad cohete
   vesc=11200;//esta es la velocidad de escape
   //vesc=11000;//si es por debajo de la velocidad de escape no llega a la luna
   // vesc=11400;//no interacciona con la luna
   // vesc=11300;//intercciona levemente
   //vesc=0;// usada para orbitar el cohete con la luna

    //inicializacion parametros
    posl=dtl;
    phil=0.0;
    //posc=dtl-Rt;//radio cohete para que orbite con la luna
    posc=Rt;//ponemos al cohete en el radio de laz tierra
    phic=0.0;
    v=vesc;//ponemos la velocidad como velocidad de escape

    //reescalamos
    posl=posl/dtl;
    posc=posc/dtl;
    v=v/dtl;

    //momentos
    pr=v*cos(theta);
    pphi=posc*v*sin(theta);

    //abrimos ficheros
    posiciones.open("planets_data.dat");
    Hamiltoniano.open("hamiltoniano.dat");

    for(t=0;t<tmax;t++) 
    {

        //cada 200 pasos escribo las posiciones y el hamiltoniano
        if((t%200)==0)
        {

            posiciones<<"0.0, 0.0"<<endl;
            posiciones<<posc*cos(phic)<<", "<<posc*sin(phic)<<endl;
            posiciones<<posl*cos(w*t*1.0)<<", "<<posl*sin(w*t*1.0)<<endl;
            posiciones<<endl;
            //formula hamiltoniano
            Hamiltoniano<<(pr*pr/2)+(pphi*pphi/(2*posc*posc))-((G/(dtl*dtl*dtl))*((Mt/posc)+(Ml/(sqrt(1+posc*posc-2*posc*cos(phic-1.0*w*t))))))<<endl;
        }

        //evaluo los k (primera coordenada es el superindice y la segunda indica de que magnitud es, r, phi, p_r o p_phi)
        k[0][0]=pr;
        k[0][1]=pphi/(posc*posc);
        k[0][2]=prpunto(posc, phic, pphi, t);
        k[0][3]=pphipunto(posc, phic, t);

        k[1][0]=(pr+k[0][2]/2.0);
        k[1][1]=(pphi+k[0][3]/2.0)/(((posc+k[0][0]/2)*(posc+k[0][0]/2)));
        k[1][2]=prpunto(posc+ k[0][2]/2, phic + k[0][1]/2, pphi+ k[0][3]/2, t);
        k[1][3]=pphipunto(posc+ k[0][0]/2, phic+k[0][1]/2, t);

        k[2][0]=(pr+k[1][2]/2);
        k[2][1]=(pphi+k[1][3]/2)/(((posc+k[1][0]/2)*(posc+k[1][0]/2)));
        k[2][2]=prpunto(posc+ k[1][2]/2, phic + k[1][1]/2, pphi+ k[1][3]/2, t);
        k[2][3]=pphipunto(posc+ k[1][0]/2, phic+k[1][1]/2, t);

        k[3][0]=(pr+k[2][2]); 
        k[3][1]=(pphi+k[2][3])/(((posc+k[2][0])*(posc+k[2][0])));
        k[3][2]=prpunto(posc+ k[2][2], phic + k[2][1], pphi+ k[2][3], t);
        k[3][3]=pphipunto(posc+ k[2][0], phic+k[2][1], t);

        
        pphi+=  (k[0][3]+2*k[1][3]+2*k[2][3]+k[3][3])/6;
        posc+= (k[0][0]+2*k[1][0]+2*k[2][0]+k[3][0])/6;
        phic+=  (k[0][1]+2*k[1][1]+2*k[2][1]+k[3][1])/6;
        pr+= (k[0][2]+2*k[1][2]+2*k[2][2]+k[3][2])/6;
    }

    //cerramos ficheros
    posiciones.close();
    Hamiltoniano.close();

    return 0;
}


double prpunto(double posc, double phic, double pphi, double t)
{

    double prpunto,DELTA, mu,rprima;

    DELTA=G*Mt/(1.0*dtl*dtl*dtl);
    mu=Ml/(1.0*Mt);
    rprima=sqrt(1.0+posc*posc-2.0*posc*cos(phic-1.0*w*t));

    prpunto=pphi*pphi/(posc*posc*posc)-DELTA*(1.0/(posc*posc)+mu/(rprima*rprima*rprima)*(posc-cos(phic-1.0*w*t)));



    return prpunto;
}

double pphipunto(double posc, double phic, double t){


    double pphipunto,DELTA, mu,rprima;

    DELTA=G*Mt/(1.0*dtl*dtl*dtl);
    mu=Ml/(1.0*Mt);
    rprima=sqrt(1.0+posc*posc-2.0*posc*cos(phic-1.0*w*t));

    pphipunto=-DELTA*mu*posc*sin(phic-1.0*w*t)/(rprima*rprima*rprima);

    return pphipunto;
}
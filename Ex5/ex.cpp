#include <cmath>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <TRandom3.h>
#include <TH3F.h>
#include <TCanvas.h>
#include <TApplication.h>
using namespace std;





int main(int argc, char **argv)
{
  if(argc != 2)
    {
      cout<<"Usage: ./ex <NUMBER>"<<endl;
      return -1;
    }
  //create a window
  TApplication theApp("demoApplication",&argc,argv);
  // create a canvas
  TCanvas c1("c1","c1",1,1,1024,768);

  int numbers =atoi(argv[1]);
  TH1F * hist = new TH1F("hist", "hist", 100, 0, 20);


std::cout << "E4.4 Muliply with carry, generator Test" << std::endl;
long m;
double biggest;
long xn, xn0, yn, yn0, cx = 5, cy= 7;
long xnstart = 13;
long ynstart = 17;
long zn;
double chi;
int subdivisions = 10;

int number = 1000;
double random[number];



for (size_t num = 0; num < numbers; num++) {
  xn0 = xnstart;
  yn0 = ynstart;
  for (int i = 0; i < number; i++) {
    m = pow(2,32)-5;

    m = pow(2,16);
    xn =  (18001*xn0 - cx) % m;
    yn = (30903*yn0 - cy) % m;
    zn = xn*pow(2,16) + yn;
    random[i] = zn;
    xn0 = xn;
    yn0 = yn;
  }

  biggest = 0;
  for (int i = 0; i < number; i++) {
    if (random[i] > biggest) {
      biggest = random[i];
    }
  }

  for (int i = 0; i < number; i++) {
    random[i] = random[i]/biggest;
    //std::cout << random[i] << std::endl;
  }


  chi = 0;

long n_sum[subdivisions];
long n_summe = 0;

  for (int k = 0; k < subdivisions; k++) {

    double start = (double) 0 +  k * 1./subdivisions;
    double end = (double) k* 1./subdivisions + 1./subdivisions;
    long hit = 0;
    for (int n = 0; n < number; n++) {
      if (random[n] >= start && random[n] <= end) {
        hit++;
      };
    }
    n_sum[k] = hit;
    n_summe += hit;
  }
  double chi_sum=0;
  for (int k = 0; k < subdivisions; k++) {
    double p = 0.1;
    chi_sum += pow(n_sum[k]-number*p,2)/(number*p);
  }
  chi = chi_sum;
  hist->Fill(chi);
  xnstart++;
  ynstart++;
}







std::cout << "drawing histogram" << std::endl;
hist->Draw();
  //turns off the program with mous clic
  theApp.Connect("TCanvas","Closed()","TApplication",&theApp,"Terminate()");
  //starts the canvas
 theApp.Run();



  return 1;
}


/*
for (int chiss = 0; chiss < numbers; chiss++) {

  xn0 = xnstart;
  yn0 = ynstart;

  for (int i = 0; i < number; i++) {
    m = pow(2,32)-5;

    m = pow(2,16);
    xn =  (18001*xn0 - cx) % m;
    yn = (30903*yn0 - cy) % m;
    zn = xn*pow(2,16) + yn;
    random[i] = zn;
    xn0 = xn;
    yn0 = yn;
  }

  biggest = 0;
  for (int i = 0; i < number; i++) {
    if (random[i] > biggest) {
      biggest = random[i];
    }
  }

  for (int i = 0; i < number; i++) {
    random[i] = random[i]/biggest;
  }

  subdivisions = 100;
  chi = 0;
  for (int k = 0; k < subdivisions; k++) {
    double start = (double) 0 +  k * 1./subdivisions;
    double end = (double) k* 1./subdivisions + 1./subdivisions;
    n_sum = 0;
    for (int n = 0; n < number; n++) {
      if (random[n] > start && random[n] < end) {
        n_sum += random[n];
      };
    }
    double p = end - start;
    for (int n = 0; n < number; n++) {
      if (random[n] > start && random[n] < end) {
        chi += ((random[n] - n_sum*p)*(random[n] - n_sum*p))/(n_sum*p);
      };

    }

  }
  hist->Fill(chi);
  chis[chiss] = chi;
  xnstart++;
  ynstart++;
}
 */

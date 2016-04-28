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
  TH1F * hist = new TH1F("hist", "hist", 100, 0, 2);


std::cout << "E4.4 Muliply with carry, generator Test" << std::endl;
long m;
double biggest;
long xn, xn0, yn, yn0, cx = 5, cy= 7;
long xnstart = 13;
long ynstart = 17;
long zn;

int number = 1000;
double random[number];






for (size_t num = 0; num < numbers; num++) {
  xn0 = xnstart;
  yn0 = ynstart;
  for (int i = 0; i < number; i++) {
    m = pow(2,16);
    xn =  (18001*xn0 - cx) % m;
    yn = (30903*yn0 - cy) % m;
    zn = xn*pow(2,16) + yn;
    random[i] = zn;
    xn0 = xn;
    yn0 = yn;
  }

  biggest = 0;
  for (int n = number; n>1; n--) {
    for (int i = 0; i < n-1; i++) {
      if (random[i] > random[i+1]) {
        double temp = random[i];
        random[i] = random[i+1];
        random[i+1] = temp;
      }
    }
  }

  biggest = random[number-1];
  for (int i = 0; i < number; i++) {
    random[i] = random[i]/biggest;
    //std::cout << random[i] << std::endl;
  }

  double d_negative=0;
  double d_positive=0;

  for (int n = 0; n < number; n++) {
    double temp = (double) (1.*n)/number - random[n];
    if (temp > d_positive) {
      d_positive = temp;
    }
    temp = (double) random[n] - (n-1.)/number;
    if (temp > d_negative) {
      d_negative = temp;
    }
  }
  double d_n;
  if (d_positive > d_negative) {
    d_n = d_positive;
  } else {
    d_n = d_negative;
  }

  hist->Fill(d_n);
  //std::cout << d_n << std::endl;
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

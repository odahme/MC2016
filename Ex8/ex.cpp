#include <cmath>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <TRandom3.h>
#include <TH3F.h>
#include <TH2F.h>
#include <TCanvas.h>
#include <TApplication.h>
#include "TMath.h"
using namespace std;


int main(int argc, char **argv)
{
  if(argc != 2)
    {
      cout<<"Usage: ./ex <NUMBER>"<<endl;
      return -1;
    }
  //create a window
//  TApplication theApp("demoApplication",&argc,argv);
  // create a canvas
//  TCanvas c1("c1","c1",1,1,1024,768);
  TRandom3 *rand = new TRandom3(123);

  int number=atoi(argv[1]);

double x[3] = {0,0,0};


double h[3][4] = {{0.2,0.4,0.1,0.3},{0.3,0.3,0.1,0.3},{0.1,0.2,0.1,0.6}};
double a[3] = {1.5,-1.0,0.7};

for (size_t i = 0; i < number; i++) {
  double q = rand->Uniform(0,1);
  int state = -1;
  double prob = 0;
  while (q > prob) {
    state++;
    prob += 1./3;
  }

  int beforstate = state;
  int startstate = state;
  while (state != 3) {
    double temp = 0;
    beforstate = state;
    for (int i = 0; i < 4; i++) {
      temp += h[state][i];
      double r = rand->Uniform(0,1);
      if (r < temp) {
        state = i;
        break;
      }
    }
  }
  state = beforstate;

   x[startstate] += 3*a[state] / h[state][3];
}

for (size_t i = 0; i < 3; i++) {
  x[i] = x[i]/number;
  std::cout << x[i] << std::endl;
}

  //turns off the program with mous clic
//  theApp.Connect("TCanvas","Closed()","TApplication",&theApp,"Terminate()");
  //starts the canvas
//  theApp.Run();



  return 1;
}

#include <cmath>
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include <TRandom3.h>
#include <TH3F.h>
#include <TCanvas.h>
#include <TApplication.h>
#include <string>

#include "Riostream.h"
#include "TFile.h"
#include "TFoam.h"
#include "TH1.h"
#include "TMath.h"
#include "TFoamIntegrand.h"


using namespace std;


int main(int argc, char **argv)
{
  //create a window
  TApplication theApp("demoApplication",&argc,argv);
  // create a canvas
  TCanvas c1("c1","c1",1,1,1024,768);


  char s[64];
  float moms[1000000];
  fstream f;

  f.open("mom.txt",ios::in);
  int linen = 0;
  while (!f.eof()) {
    f.getline(s,sizeof(s));
    moms[linen] = atof(s);
    linen++;
  }
  f.close();

  double erg =0;
  double variance = 0;
  double sigmar;

for (int i = 0; i < 1000000; i++) {
  erg += (double) moms[i];
}


  erg= erg/sizeof(moms);

for (size_t i = 0; i < 1000000; i++) {
  variance += pow(moms[i] - erg,2);
}
variance = variance/(1000000-1);
sigmar = sqrt(variance)/sqrt(1000000);

  std::cout << "A_fb = " << (erg*3)/2 << std::endl;
  std::cout << "sigma A_fb = " << (sigmar*3)/2 << std::endl;



  erg =0;
  variance = 0;
for (int i = 0; i < 1000000; i++) {
  erg += (double) moms[i]*moms[i];
}
  erg= erg/sizeof(moms);

  for (size_t i = 0; i < 1000000; i++) {
    variance += pow(moms[i]*moms[i] - erg,2);
  }

  variance = variance/(1000000-1);
  sigmar = sqrt(variance)/sqrt(1000000);
  std::cout << "F_h = " << ((erg*2)/15 + 1/5) << std::endl;
  std::cout << "sigma F_h = "<< ((sigmar*2)/15 + 1/5) << std::endl;







  //turns off the program with mous clic
  theApp.Connect("TCanvas","Closed()","TApplication",&theApp,"Terminate()");
  //starts the canvas
  theApp.Run();



  return 1;
}

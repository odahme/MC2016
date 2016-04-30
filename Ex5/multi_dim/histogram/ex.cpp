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
  TH1F * hist = new TH1F("hist", "hist", 100, 0, 500);

int size = 1000;

  char s[64];
  float phi_one[size];
  float phi_two[size];
  fstream f;
  int linen;

  f.open("phi_ones.txt",ios::in);
  linen = 0;
  while (!f.eof()) {
    f.getline(s,sizeof(s));
    phi_one[linen] = atof(s);
    linen++;
  }
  f.close();

  f.open("phi_twos.txt",ios::in);
  linen = 0;
  while (!f.eof()) {
    f.getline(s,sizeof(s));
    phi_two[linen] = atof(s);
    linen++;
  }
  f.close();

double phi;

for (size_t i = 0; i < size; i++) {
  phi = phi_one[i] - phi_two[i];
  hist->Fill(phi);
  //std::cout << phi << std::endl;
}




std::cout << "drawing histogram" << std::endl;
hist->Draw();

  //turns off the program with mous clic
  theApp.Connect("TCanvas","Closed()","TApplication",&theApp,"Terminate()");
  //starts the canvas
  theApp.Run();



  return 1;
}

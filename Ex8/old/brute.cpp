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



double temp = 0;
bool walk = true;
  for (size_t i = 0; i < number;++i) {
    double x;
    int state = 2;
    while (walk) {
      double random = rand->Uniform(0,1);
      //std::cout << random << std::endl;
      if (state == 1) {
        if (random <= 0.2) {
          state = 1;
          continue;
        }
        if (random > 0.2 && random <= 0.6 ) {
          state = 2;
          continue;
        }
        if (random > 0.6 && random <= 0.7 ) {
          state = 3;
          continue;
        }
        if(random > 0.7){
          x = 1.5/0.3;
          walk = false;
        }
        continue;
      }
      if (state == 2) {
        if (random <= 0.3) {
          state = 1;
          continue;
        }
        if (random > 0.3 && random <= 0.6 ) {
          state = 2;
          continue;
        }
        if (random > 0.6 && random <= 0.7 ) {
          state = 3;
          continue;
        }
        if(random > 0.7){
          x = (-1.)/0.3;
          walk = false;
        }
        continue;
      }
      if (state == 3) {
        if (random <= 0.1) {
          state = 1;
          continue;
        }
        if (random > 0.1 && random <= 0.3 ) {
          state = 2;
          continue;
        }
        if (random > 0.3 && random <= 0.4 ) {
          state = 3;
          continue;
        }
        if(random > 0.4){
          x = 0.7/0.6;
          walk = false;
        }
        continue;
      }
      //std::cout << state << std::endl;
    }
    //std::cout << x << std::endl;
    temp += x;
    walk = true;
  }

double calc = (double) temp/number;

std::cout << calc << std::endl;






  //turns off the program with mous clic
//  theApp.Connect("TCanvas","Closed()","TApplication",&theApp,"Terminate()");
  //starts the canvas
//  theApp.Run();



  return 1;
}

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
  
  int number=atoi(argv[1]);
  TRandom3 *rand = new TRandom3(123);
  TH1F * hist = new TH1F("hist", "hist", 100, 0, 10);
  
  for(int i=0;i<number;++i)
    {
      double tmp=rand->Gaus(5,1);
      hist->Fill(tmp);
      
    }
  hist->Draw();

  //turns off the program with mous clic
  theApp.Connect("TCanvas","Closed()","TApplication",&theApp,"Terminate()");
  //starts the canvas
  theApp.Run();
  
  

  return 1;
}

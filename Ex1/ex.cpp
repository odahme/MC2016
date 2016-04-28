#define _USE_MATH_DEFINES


#include <cmath>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <TRandom3.h>
#include <TH3F.h>
#include <TCanvas.h>
#include <TApplication.h>
#include <time.h>
#include <math.h>
#include <TF1.h>


using namespace std;


double One_gaus(double u, double sigma,TRandom3 *rand);


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
  TH1F * hist = new TH1F("hist", "hist", 100, -5, 15);


  int anzahl[4]={100,10000,1000000,100000000};
  int karry = 0;
  for(int x=0;x<4;++x)
  {
    karry = 0;
    for(int i=0;i<anzahl[x];++i)
      {
        int k = 2;
        double n1 = rand-> Uniform(0,1);
        double n2 = rand-> Uniform(0,1);
        while(n2<n1)
    {
      n1 = n2;
      n2 = rand-> Uniform(0,1);
      k++;
    }
        karry += k;
      }
    double e = (double) karry/anzahl[x];
    cout <<"N = "<<anzahl[x]<<"  e = "<< e <<"  Delta = "<< e-2.7182818 <<"  sqrt(N) = "<<1/std::sqrt(anzahl[x])  << std::endl;
  }




  double u = 5;
  double s = 2;
  double erg = 42;
  double x1;
  double x2;
  for(int i=0;i<number;i++)
    {
      erg = One_gaus(u,s,rand);
      hist->Fill(erg);
    }

    hist ->Fit("gaus");
  x1 = hist->FindBin(-1.64*s+u);
  x2 = hist->FindBin(1.64*s+u);
  erg = hist->Integral(x1,x2);
  cout <<"P(1.64) hist = "<< erg/number << std::endl;

  x1 = hist->FindBin(-2.58*s+u);
  x2 = hist->FindBin(2.58*s+u);
  erg = hist->Integral(x1,x2);
  cout <<"P(2.58) hist = "<< erg/number << std::endl;

  x1 = hist->FindBin(-3.29*s+u);
  x2 = hist->FindBin(3.29*s+u);
  erg = hist->Integral(x1,x2);
  cout <<"P(3.29) hist = "<< erg/number << std::endl;


  hist->Draw();

double Norm = 1/(std::sqrt(2*M_PI)*s);

  TF1 *fa1 = new TF1("fa1","gaus(0)",-5,15);

  fa1 ->SetParameter(0,Norm);
  fa1 ->SetParameter(1,u);
  fa1 ->SetParameter(2,s);

  erg = fa1->Integral(-1.64*s+u,1.64*s+u);
  cout <<"P(1.64) TF1 = "<< erg << std::endl;

  erg = fa1->Integral(-2.58*s+u,2.58*s+u);
  cout <<"P(1.64) TF1 = "<< erg << std::endl;

  erg = fa1->Integral(-3.29*s+u,3.29*s+u);
  cout <<"P(1.64) TF1 = "<< erg << std::endl;

//  fa1->Draw();
  //turns off the program with mous clic
  theApp.Connect("TCanvas","Closed()","TApplication",&theApp,"Terminate()");
  //starts the canvas
  theApp.Run();


  return 1;
}

double One_gaus(double u, double sigma,TRandom3 *rand)
{
  double n = 12*sigma*sigma;
  double i = 0;
  double x = 42;
  double g = 0;
  double e = n/2;
  double delta_u = u - e;
  while(i < n)
    {
      x = rand->Uniform(0,1);
      g += x;
      i++;
    }
  return g+delta_u;
}

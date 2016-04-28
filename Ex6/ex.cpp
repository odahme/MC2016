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

int gen_discrete(double rn, double *p){
  int k = 0;
  double sum = p[0];
  while (sum < rn) {
    sum +=p[++k];
  }
  return k;
}

double func_phi(double x, double y){
  double c = 4/TMath::Pi();
  double calc;
  calc = c*sqrt(1-(pow(x,2)+pow(y,2)));
  return calc;
}

double func_f(double x) {
  double calc = sqrt(2/TMath::Pi()) * exp(- pow(x,2)/2);
  return calc;
}

double func_g(double x) {
  double calc = exp(-x);
  return calc;
}

double func_h_one(double x) {
  double calc = exp(-pow(x,2)/2);
  return calc;
}

double func_h_two(double x) {
  double calc = exp(- pow(x-2,2)/2 );
  return calc;
}

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
  TCanvas c2("c2","c2",1,1,1024,768);
  TCanvas c3("c3","c3",1,1,1024,768);
  TCanvas c4("c4","c4",1,1,1024,768);
  TCanvas c5("c5","c5",1,1,1024,768);
  TCanvas c6("c6","c6",1,1,1024,768);

  int number=atoi(argv[1]);
  TRandom3 *rand = new TRandom3(123);
  TH1F * hist1 = new TH1F("hist1", "hist1", 100, 0.9, 2.1);
  TH1F * hist2 = new TH1F("hist2","hist2", 100, -5,5);
  TH1F * hist3 = new TH1F("hist3","hist3", 100,0,11);
  TH2F * hist4 = new TH2F("hist4","hist4", 100,-1,1,100,-1,1);
  TH1F * hist6 = new TH1F("hist6","hist6", 100,0,6);





double a = 1;
double b = 2;
double c = 1/(1/pow(a,2) - 1/pow(b,2));
double calc;

std::cout << "E6.1" << std::endl;
  for(int i=0;i<number;++i)
    {
      double temp=rand->Uniform(0,1);
      calc = sqrt(1/((1/pow(a,2)) - temp/c) );
      hist1->Fill(calc);
    }
  c1.cd();
  hist1->Draw();

std::cout << "E6.2" << std::endl;

double lambda= 1;
double theta = 0;

  for(int i=0;i<number;++i)
    {
      double temp=rand->Uniform(0,1);
      calc = lambda*tan(temp*TMath::Pi()- TMath::Pi()) + theta;
      hist2->Fill(calc);
    }
  c2.cd();
  hist2->Draw();

std::cout << "E6.3" << std::endl;


double p[11];
for (int k = 0; k < 11; k++) {
  p[k] = TMath::Pi()/20 * sin(TMath::Pi()/10. *(k+1./2));
}

for (int i = 0; i < number; i++) {
  double random = rand->Uniform(0,1);
  int temp = gen_discrete(random,p);
  hist3->Fill(temp);
}
c3.cd();
hist3->Draw();

std::cout << "E6.4" << std::endl;

int dim = 2;
double point[dim];
double border;
c = 4/TMath::Pi();
for (long i = 0; i < number;) {
  for (int m = 0; m < dim; m++) {
    point[m] = rand->Uniform(-1,1);
  }

  border = rand->Uniform(0,c);

  if (border < func_phi(point[0],point[1])) {
    hist4->Fill(point[0],point[1]);
    i++;
  }
}

c4.cd();
hist4->Draw("COL");


std::cout << "E6.5" << std::endl;
c5.cd();
//two pads for E6.5
TPad *pad_left5  = new TPad("left hist5","left hist5",0,0,0.6,0.6);
pad_left5->Draw();
TPad *pad_right5  = new TPad("right hist5","right hist5",0.55,0,1,0.6);
pad_right5->Draw();

TH1F *weighted = new TH1F("weighted"," ",100,-10,10);
TH1F *not_weighted = new TH1F("not_weighted"," ",100,-10,10);

double w_max = sqrt(2*TMath::E()/TMath::Pi());

for (int i = 0; i < number;) {
  double random = rand->Uniform(-10,10);
  double u = rand->Uniform(0,1);
  double w = func_f(random)/func_g(random);
  if (w > (w_max*u)) {
    weighted->Fill(random);
    i++;
  }
}

for (int i = 0; i < number;) {
  double random = rand->Uniform(0,1);
  double x = -log(random);
  double u = rand->Uniform(0,w_max);
  if (u*func_g(random) < func_f(x)) {
    not_weighted->Fill(x);
    i++;
  }
}


pad_right5->cd();
weighted->Draw();
pad_left5->cd();
not_weighted->Draw();

std::cout << "E6.6" << std::endl;

double alpha1 = sqrt(2/TMath::Pi());
double alpha2 = sqrt(1/(2*TMath::Pi()));
border = alpha1 /(alpha1+alpha2);


for (int i = 0; i < number;) {
  double random = rand->Uniform(0,1);
  if (random < border ) {
    random = rand->Uniform(0,1);
    double x = random;
    double control = rand->Uniform(0,1);
    if (func_h_one(x) >= control) {
      hist6->Fill(x);
      i++;
    }

  } else {
    random = rand->Uniform(0,1);
    double x = -0.5 * log(1.-random) + 1;
    double control = rand->Uniform(0,1);
    if (func_h_two(x) >= control) {
      hist6->Fill(x);
      i++;
    }
  }
}

c6.cd();
hist6->Fit("gaus");
hist6->Draw();


  //turns off the program with mous clic
  theApp.Connect("TCanvas","Closed()","TApplication",&theApp,"Terminate()");
  //starts the canvas
  theApp.Run();



  return 1;
}

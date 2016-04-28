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


  double l_needle = 1;
  double l_lines = 2.5;
  double y;
  double phi;
  double a;
  double b;
  double x;
  int hit = 0;

  int n[4] = {10000,100000,1000000,10000000};

std::cout << "E2.2" << std::endl;

  for(int j=0;j<4;++j)
  {
    hit = 0;
    x = n[j];
    for(int i=0;i<x;++i)
    {

      y=rand->Uniform(-l_lines,l_lines);
      phi=rand->Uniform(0,M_PI);

      a = y + l_needle*cos(phi);
      b = y - l_needle*cos(phi);

      if(y < 0 )
      {
        if(a > 0 or b < -l_lines)
        {
          hit++;
        }
      }
      if(y > 0)
      {
        if(a > l_lines or b < 0)
        {
          hit++;
        }
      }

      if( y ==0 or y == l_lines or y == -l_lines)
      {
        hit++;
      }

    }
    double p = hit*1.0/x*1.0;
    double pi = (x*2*l_needle)/(hit*l_lines);
    double sigma = 1/(sqrt(x-1)) * sqrt((hit/x)*(1-hit/x));

    std::cout << "pi = "<< pi << std::endl;
    std::cout << "Delta = " << pi - M_PI << std::endl;
    std::cout << "sigma = " << sigma << std::endl;
    std::cout << "---------" << std::endl;
  }




double y_s;
hit = 0;

//hit and miss
  for(int i=0; i<number; ++i)
  {
    x = rand->Uniform(0,1);
    y_s = rand->Uniform(0,1);
    y = (1/sqrt(2*M_PI))*exp(-x*x/2);
    if (y_s <= y)
    {
      hit++;
    }
  }
  std::cout << "E2.3" << std::endl;
  std::cout << "I hit miss func1 = " << hit*1.0/number*1.0 << std::endl;
  std::cout << "sigma func1 = " << 1/(sqrt(number*1.0-1)) * sqrt((hit*1.0/number*1.0)*(1-hit*1.0/number*1.0)) << std::endl;
  std::cout << "---------" << std::endl;

hit =0;
  for(int i=0;i<number;++i)
  {
    double r = rand->Uniform(0,1);
    double r_s = rand->Uniform(0,1);
    double z = M_PI/2 * sqrt(1-r*r)*r;
    if (r_s <= z)
    {
      hit++;
    }
  }
  std::cout << "I hit miss func2 = " << hit*1.0/number*1.0 << std::endl;
  std::cout << "sigma func2 = " << 1/(sqrt(number*1.0-1)) * sqrt((hit*1.0/number*1.0)*(1-hit*1.0/number*1.0)) << std::endl;
  std::cout << "---------" << std::endl;

//crude method

double erg =0;
double variance = 0;
double v1 = 0;
double yrray[number];

for(int i=0; i<number; ++i)
  {
    x = rand->Uniform(0,1);
    y = (1/sqrt(2*M_PI))*exp(-x*x/2);
    yrray[i] = y;
    erg +=y ;

  }

for (int i=0; i<number; ++i)
  {
    v1 += pow(yrray[i] - erg/(number*1.0),2);
  }

  variance = 1/(number*1.0) * 1/(number*1.0-1) * v1;
  std::cout << "I crude func1 = " << erg/(number*1.0) << std::endl;
  std::cout << "sigma func1 = " << sqrt(variance) << std::endl;
  std::cout << "---------" << std::endl;

erg = 0;
variance =0;
v1 =0;
double rarray[number];

for(int i=0;i<number;++i)
{
  double r = rand->Uniform(0,1);
  double z = M_PI/2 * sqrt(1-r*r)*r;
  rarray[i] = z;
  erg += z;
}

for (int i=0; i<number; ++i)
{
  v1 += pow(rarray[i] - erg/(number*1.0),2);
}
variance = 1/(number*1.0) * 1/(number*1.0-1) * v1;
std::cout << "I crude func2 = " << erg/(number*1.0) << std::endl;
std::cout << "sigma func2 = " << sqrt(variance) << std::endl;
std::cout << "---------" << std::endl;


//Stratified Sampling

int w = 5;
int interval = number/w;
double integral = 0;

double y2rray[interval];

for(int j=0;j<w;++j)
{
  erg = 0;
  v1 = 0;
  double start = 0 + (j*1.0)/(w*1.0);
  double end = 1/(w*1.0) + (j*1.0)/(w*1.0);
  for(int i=0; i<interval; ++i)
    {
      x = rand->Uniform(start,end);
      y = (1/sqrt(2*M_PI))*exp(-x*x/2);
      y2rray[i] = y;
      erg +=y ;

    }

  for (int i=0; i<interval; ++i)
    {
      v1 += pow(y2rray[i] - erg/(interval*1.0),2);
    }
  integral += erg;
  variance += 1/(interval*1.0) * 1/(interval*1.0-1) * v1 ;
}

std::cout << "E2.4" << std::endl;
std::cout << "I Stratified func1 = " << integral/ (interval*1.0) /w << std::endl;
std::cout << "sigma = " << sqrt(variance* pow((1/(w*1.0)),2) / (interval*1.0)) << std::endl;
std::cout << "---------" << std::endl;

integral = 0;
variance = 0;

for(int j=0;j<w;++j)
{
  erg = 0;
  v1 = 0;
  double start = 0 + (j*1.0)/(w*1.0);
  double end = 1/(w*1.0) + (j*1.0)/(w*1.0);
  for(int i=0; i<interval; ++i)
    {
      double r = rand->Uniform(start,end);
      double z = M_PI/2 * sqrt(1-r*r)*r;
      rarray[i] = z;
      erg += z;

    }

  for (int i=0; i<interval; ++i)
    {
      v1 += pow(rarray[i] - erg/(interval*1.0),2);
    }
  integral += erg;
  variance += 1/(interval*1.0) * 1/(interval*1.0-1) * v1 ;
}
std::cout << "I Stratified func2 = " << integral/ (interval*1.0) /w << std::endl;
std::cout << "sigma = " << sqrt(variance* pow((1/(w*1.0)),2) / (interval*1.0)) << std::endl;
std::cout << "---------" << std::endl;


  //turns off the program with mous clic
  theApp.Connect("TCanvas","Closed()","TApplication",&theApp,"Terminate()");
  //starts the canvas
  theApp.Run();



  return 1;
}

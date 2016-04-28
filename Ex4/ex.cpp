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
//  TApplication theApp("demoApplication",&argc,argv);
  // create a canvas
//  TCanvas c1("c1","c1",1,1,1024,768);

  int number=atoi(argv[1]);
  TRandom3 *rand = new TRandom3(123);
//  TH1F * hist = new TH1F("hist", "hist", 100, 0, 10);

long x0 = 2045;
long m = 2;
long x1;
long x00;
long x000;


std::cout << "E4.1 Neumann generator" << std::endl;
  for(int i=0;i<number;++i)
    {
      long temp1 = (long) (x0*x0 * pow(10,-m));
      long temp2 = (long) (x0*x0 * pow(10,-3*m));
      x1 = (long) temp1 - temp2*pow(10,2*m);
      std::cout << x1 << std::endl;
      x0 = x1;
    }

std::cout << "E4.2 Marsaglia gnerators" << std::endl;

std::cout << "first" << std::endl;

m = pow(2,32)-5;
std::cout <<"m = "<< m << std::endl;
x0 = 1;
x00 = 2;
x000 = 3;

for (int i = 0; i < number; i++) {
  x1 = (1176*x0 + 1476*x00 + 1776*x000) % m ;
  std::cout << x1 << std::endl;
  long temp1 = x0;
  long temp2 = x00;
  x0 = x1;
  x00 = temp1;
  x000 = temp2;
}

std::cout << "second" << std::endl;
x0 = 1;
x00 = 2;
x000 = 3;

for (int i = 0; i < number; i++) {
  x1 = (pow(2,13) * (x0 + x00 + x000));
  x1 = x1 % m;
  std::cout << x1 << std::endl;
  long temp1 = x0;
  long temp2 = x00;
  x0 = x1;
  x00 = temp1;
  x000 = temp2;
}

std::cout << "third" << std::endl;
x0 = 1;
x00 = 2;
x000 = 3;
m = pow(2,35)*849;

for (int i = 0; i < number; i++) {
  x1 = (1995*x0 + 1998*x00 + 2001*x000) ;
  x1 = x1 % m;
  std::cout << x1 << std::endl;
  long temp1 = x0;
  long temp2 = x00;
  x0 = x1;
  x00 = temp1;
  x000 = temp2;
}

std::cout << "fourth" << std::endl;
x0 = 1;
x00 = 2;
x000 = 3;
m = pow(2,32)*1629;

for (int i = 0; i < number; i++) {
  x1 = (pow(2,19) * (x0 + x00 + x000));
  x1 = x1 % m;
  std::cout << x1 << std::endl;
  long temp1 = x0;
  long temp2 = x00;
  x0 = x1;
  x00 = temp1;
  x000 = temp2;
}


std::cout << "E3.3 Fibonacci generator" << std::endl;
x0 = 1;
x00 = 2;
x000 = 3;
m = 5;
for (int i = 0; i < number; i++) {
  x1 = (x00 * x0) % m;
  std::cout << x1 << std::endl;
  long temp = x0;
  x0 = x1;
  x00 = temp;
}


std::cout << "E4.4 Muliply with carry, generator" << std::endl;


x0 = 7;
x00 = 5;
x000 = 3;
long xn, xn0, yn, yn0, cx, cy;
long zn;
long b[16];
xn0 = 13;
yn0 = 11;
cx = -5;
cy = -7;


for (int i = 0; i < number; i++) {
  m = pow(2,16);
  xn =  (18001*xn0 + cx) % m;
  yn = (30903*yn0 + cy) % m;
  zn = xn*pow(2,16) + yn;
  std::cout << zn << std::endl;
  xn0 = xn;
  yn0 = yn;
}


//  hist->Draw();

  //turns off the program with mous clic
//  theApp.Connect("TCanvas","Closed()","TApplication",&theApp,"Terminate()");
  //starts the canvas
//  theApp.Run();



  return 1;
}

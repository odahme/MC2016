#include <cmath>
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include <TRandom3.h>
#include <TH3F.h>
#include <omp.h>
using namespace std;

int main(int argc, char **argv)
{
  // if(argc != 2)
  //   {
  //     cout<<"Usage: ./ex <NUMBER>"<<endl;
  //     return -1;
  //   }
  // //create a window
// TApplication theApp("demoApplication",&argc,argv);
  // // create a canvas
  // TCanvas c1("c1","c1",1,1,1024,768);

std::cout << "start Programm; created and open file" << std::endl;

ofstream phi_one_file;
phi_one_file.open("phi_ones.txt");
phi_one_file <<"Values for phi one first part of the histogramm \n";

ofstream phi_twos_file;
phi_twos_file.open("phi_twos.txt");
phi_twos_file <<"Values for phi two second part of the histogramm \n";


  int n_phis=100;

//  TH1F * hist = new TH1F("hist", "hist", 100, -2, 20);

  std::cout << "E4.4 multi dimension test" << std::endl;

  int dimstart = 10;
  int dim;
  int subdivisions = 3;
  int number = 1000000;

  //double phismone[n_phis];
  //double phismtwo[n_phis];

  double start, end;
  int hit;




  double calc;

  bool firstphi = true;
for (size_t nphis = 0; nphis < 2; nphis++) {
  if (nphis == 1) {
    firstphi = false;
  }
  dim = dimstart - nphis;

  double hypercube[dim][number];

  int n_subhypercubs = pow(subdivisions,dim);
  int subhypercubesum[n_subhypercubs];
  double starts[dim];
  double ends[dim];
  double startboders[dim][n_subhypercubs];
  double endboders[dim][n_subhypercubs];
  std::cout << "start initialisiation of boders" << std::endl;
    for (int i = 0; i < dim; i++) {
      int wait = pow(subdivisions,i);
      int stand = 0;

      for (int j = 0; j < n_subhypercubs; j++) {
        if (wait >0) {
          calc = (double) (stand % subdivisions)/subdivisions;
          startboders[i][j] = calc;
          endboders[i][j] = calc + 1./subdivisions;
        }
    		else{
          stand++;
          wait = pow(subdivisions,i);
          calc = (double) (stand % subdivisions)/subdivisions;
          startboders[i][j] = calc;
          endboders[i][j] = calc + 1./subdivisions;
        }
    		wait--;
      }
    }
std::cout << "initialisiation of boders completed" << std::endl;

  #pragma omp parallel for
  for (int k = 0; k < n_phis; k++) {
    TRandom3 *rand = new TRandom3(k);

    for (int m = 0; m < dim; m++) {
      for (int i = 0; i < number; i++) {
        hypercube[m][i] = rand->Uniform();
        //std::cout << hypercube[m][i] << std::endl;
      }
    }
    for (int cube = 0; cube < n_subhypercubs; cube++) {

      for (int m = 0; m < dim; m++) {
        starts[m] = startboders[m][cube];
        ends[m] = endboders[m][cube];
      }

      hit = 0;
      int subhit;
      for (int i = 0 ; i < number ; i++) {
        for (int m = 0; m < dim; m++) {
          start = starts[m];
          end = ends[m];

          if (hypercube[m][i] > start && hypercube[m][i] < end) {
            subhit++;
          }
        }
        if (subhit == dim) {
          hit++;
        }
        subhit=0;
      }

      subhypercubesum[cube] = hit;
    }

    double phi = 0;
    for (int i = 0; i < n_subhypercubs; i++) {
      phi += pow(subhypercubesum[i] - (number - dim + 1)/n_subhypercubs,2)/((number - dim + 1) / n_subhypercubs);
    }
//    std::cout << "writing phi " << k << std::endl;

     if (firstphi) {
       phi_one_file << phi << "\n" ;

     }
     else{
       phi_twos_file << phi << "\n" ;
       //std::cout << "second = "<<phi << std::endl;
     }
  }
}

// for (size_t k = 0; k < n_phis; k++) {
//   calc = phismone[k] - phismtwo[k];
//   //std::cout << calc << std::endl;
//   hist->Fill(calc);
// }

double freedom = pow(subdivisions,dimstart) - pow(subdivisions,dimstart-1);

std::cout << "degrees of freedom = "<< freedom << std::endl;


phi_one_file.close();
phi_twos_file.close();

std::cout << "File closed; Programm terminated" << std::endl;

//  hist->Draw();
  //turns off the program with mous clic
//  theApp.Connect("TCanvas","Closed()","TApplication",&theApp,"Terminate()");
  //starts the canvas
//  theApp.Run();



  return 1;
}

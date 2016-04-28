// Demonstrate the TFoam class.
//
//  To run this macro type from CINT command line
//
//  root [0] gSystem->Load("libFoam.so")
//  root [1] .x foam_demo.C+
//Author: Stascek Jadach
//____________________________________________________________________________

#if defined(__CINT__) && !defined(__MAKECINT__)
{
   std::cout << "Using ACliC to run this macro since it uses custom classes" << std::endl;
   TString macroFileName = gSystem->UnixPathName(__FILE__);
   gSystem->CompileMacro(macroFileName, "k");
   foam_demo();
}
#else

#include "Riostream.h"
#include "TFile.h"
#include "TFoam.h"
#include "TH1.h"
#include "TMath.h"
#include "TFoamIntegrand.h"
#include "TRandom3.h"

class TFDISTR: public TFoamIntegrand {
public:
  TFDISTR(){};
  Double_t Density(int nDim, Double_t *Xarg){
  // Integrand for mFOAM
  Double_t x ;
  x= *Xarg;
return TMath::Pi()/2 * sqrt(1-x*x)*x;
}
  ClassDef(TFDISTR,1) //Class of testing functions for FOAM
};
ClassImp(TFDISTR)

Int_t second_integral()
{
  TFile RootFile("foam_demo.root","RECREATE","histograms");
  long   loop;
  Double_t MCresult,MCerror,MCwt;
//=========================================================
  long NevTot   =     50000;   // Total MC statistics
  Int_t  kDim   =         1;   // total dimension
  Int_t  nCells   =     500;   // Number of Cells
  Int_t  nSampl   =     200;   // Number of MC events per cell in build-up
  Int_t  nBin     =       8;   // Number of bins in build-up
  Int_t  OptRej   =       1;   // Wted events for OptRej=0; wt=1 for OptRej=1 (default)
  Int_t  OptDrive =       2;   // (D=2) Option, type of Drive =0,1,2 for TrueVol,Sigma,WtMax
  Int_t  EvPerBin =      25;   // Maximum events (equiv.) per bin in buid-up
  Int_t  Chat     =       1;   // Chat level
//=========================================================
  TRandom *PseRan   = new TRandom3();  // Create random number generator
  TFoam   *FoamX    = new TFoam("FoamX");   // Create Simulator
  TFoamIntegrand    *rho= new TFDISTR();
  PseRan->SetSeed(4357);
//=========================================================
  cout<<"*****   Demonstration Program for Foam version "<<FoamX->GetVersion()<<"    *****"<<endl;
  FoamX->SetkDim(        kDim);      // Mandatory!!!
  FoamX->SetnCells(      nCells);    // optional
  FoamX->SetnSampl(      nSampl);    // optional
  FoamX->SetnBin(        nBin);      // optional
  FoamX->SetOptRej(      OptRej);    // optional
  FoamX->SetOptDrive(    OptDrive);  // optional
  FoamX->SetEvPerBin(    EvPerBin);  // optional
  FoamX->SetChat(        Chat);      // optional
//===============================
  FoamX->SetRho(rho);
  FoamX->SetPseRan(PseRan);
  FoamX->Initialize(); // Initialize simulator
  FoamX->Write("FoamX");     // Writing Foam on the disk, TESTING PERSISTENCY!!!
//===============================
  long nCalls=FoamX->GetnCalls();
  cout << "====== Initialization done, entering MC loop" << endl;
//======================================================================
  //cout<<" About to start MC loop: ";  cin.getline(question,20);
  Double_t *MCvect =new Double_t[kDim]; // vector generated in the MC run
//======================================================================
  TH1D  *hst_Wt = new TH1D("hst_Wt" ,  "Main weight of Foam",25,0,1.25);
  hst_Wt->Sumw2();
//======================================================================
  for(loop=0; loop<NevTot; loop++){
//===============================
    FoamX->MakeEvent();           // generate MC event
//===============================
    FoamX->GetMCvect( MCvect);
    MCwt=FoamX->GetMCwt();
    hst_Wt->Fill(MCwt,1.0);
    if(loop<15){
      cout<<"MCwt= "<<MCwt<<",  ";
      cout<<"MCvect= ";
      for ( Int_t k=0 ; k<kDim ; k++) cout<<MCvect[k]<<" "; cout<< endl;
    }
    if( ((loop)%100000)==0 ){
      cout<<"   loop= "<<loop<<endl;
    }
  }
//======================================================================
//======================================================================
  cout << "====== Events generated, entering Finalize" << endl;

  hst_Wt->Print("all");
  Double_t eps = 0.0005;
  Double_t Effic, WtMax, AveWt, Sigma;
  Double_t IntNorm, Errel;
  FoamX->Finalize(   IntNorm, Errel);     // final printout
  FoamX->GetIntegMC( MCresult, MCerror);  // get MC intnegral
  FoamX->GetWtParams(eps, AveWt, WtMax, Sigma); // get MC wt parameters
  Effic=0; if(WtMax>0) Effic=AveWt/WtMax;
  cout << "================================================================" << endl;
  cout << " MCresult= " << MCresult << " +- " << MCerror << " RelErr= "<< MCerror/MCresult << endl;
  cout << " Dispersion/<wt>= " << Sigma/AveWt << endl;
  cout << "      <wt>/WtMax= " << Effic <<",    for epsilon = "<<eps << endl;
  cout << " nCalls (initialization only) =   " << nCalls << endl;
  cout << "================================================================" << endl;

  delete [] MCvect;
  //
  RootFile.ls();
  RootFile.Write();
  RootFile.Close();
  cout << "***** End of Demonstration Program  *****" << endl;

  return 0;
} // end of Demo

#endif

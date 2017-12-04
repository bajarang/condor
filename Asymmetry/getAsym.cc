#include <iostream>
#include "TH1D.h"
#include "getAsym.h"
using namespace std;

TH1D *getAsym(TH1D* wplus_histo,TH1D* wminus_histo){

  //cout << "Inside getAsym" << endl;
  //CoarserEtaBins
  int nlepEta_ZincNjet_coarserbins(10);
  double lepEta_ZincNjet_coarserbins[11] = {0.0, 0.2, 0.4, 0.6, 0.8, 1.0, 1.2, 1.4, 1.6, 1.85, 2.1};

  TH1D *coarser_histo = new TH1D ("","",nlepEta_ZincNjet_coarserbins, lepEta_ZincNjet_coarserbins);

  //asymhist
  TH1D *asymhist = new TH1D ("asymhist","asymhist",nlepEta_ZincNjet_coarserbins,lepEta_ZincNjet_coarserbins);
 
  //propagate the error

  for(int i=1; i<=wplus_histo->GetNbinsX(); i++){
    double x=0.0, dx=0.0, y=0.0, dy=0.0;
    double z=0.0, dz=0.0;
    x  = wplus_histo->GetBinContent(i);
    dx = wplus_histo->GetBinError(i);
    y  = wminus_histo->GetBinContent(i);
    dy = wminus_histo->GetBinError(i);
    z  = ((x-y)/(x+y));
    dz = 2*sqrt(y*y*dx*dx+x*x*dy*dy)/((x+y)*(x+y)); 
    asymhist->SetBinContent(i,z);
    asymhist->SetBinError(i,dz);
    //cout << z << "\t" << dz << endl;
  }
   

  return asymhist;
}

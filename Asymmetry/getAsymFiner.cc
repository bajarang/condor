#include <iostream>
#include "TH1D.h"
#include "getAsymFiner.h"
using namespace std;

TH1D *getAsymFiner(TH1D* wplus_histo,TH1D* wminus_histo){

  //cout << "Inside getAsym" << endl;
  int nlepEta_ZincNjet_finerbins(46);
  double lepEta_ZincNjet_finerbins[47] = {-2.4, -2.3, -2.2, -2.1, -2, -1.85, -1.75, -1.6, -1.5, -1.4, -1.3, -1.2, -1.1, -1, -0.9, -0.8, -0.7, -0.6, -0.5, -0.4, -0.3, -0.2, -0.1, 0, 0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8, 0.9, 1, 1.1, 1.2, 1.3, 1.4, 1.5, 1.6, 1.75, 1.85, 2, 2.1, 2.2, 2.3, 2.4};

  //asymhist
  TH1D *asymhist = new TH1D ("asymhist","asymhist",nlepEta_ZincNjet_finerbins,lepEta_ZincNjet_finerbins);
 
  //propagate the error

  for(int i=1; i<=wplus_histo->GetNbinsX(); i++){
    double x=0.0, dx=0.0, y=0.0, dy=0.0;
    double z=0.0, dz=0.0;
    x  = wplus_histo->GetBinContent(i);
    dx = wplus_histo->GetBinError(i);
    y  = wminus_histo->GetBinContent(i);
    dy = wminus_histo->GetBinError(i);
    if((x+y)==0){
      z = 0.0;
      dz = 0.0;
    }
    else{
      z  = ((x-y)/(x+y));
      dz = 2*sqrt(y*y*dx*dx+x*x*dy*dy)/((x+y)*(x+y)); 
    }
    asymhist->SetBinContent(i,z);
    asymhist->SetBinError(i,dz);
    //cout << z << "\t" << dz << endl;
  }
   

  return asymhist;
}

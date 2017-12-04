#include <iostream>
#include "TH1D.h"
#include "fold_mside.h"
using namespace std;

TH1D *fold_mside(TH1D* tofold_histo){

  int totbins = 0;
  totbins = tofold_histo->GetNbinsX();
  double mside_bincontent[10] = {0.0};
  double mside_binerr[10]     = {0.0};
  for(int i=1; i<=totbins; i++){
    if(i<=10){
      mside_bincontent[i-1]=tofold_histo->GetBinContent(i);
      mside_binerr[i-1]    =tofold_histo->GetBinError(i);
    }
    else continue;
  }

  //CoarserEtaBins but folded
  int nlepEta_ZincNjet_coarserbins_mside(10);
  double lepEta_ZincNjet_coarserbins_mside[11] = {0.0, 0.2, 0.4, 0.6, 0.8, 1.0, 1.2, 1.4, 1.6, 1.85, 2.1};
  TH1D *mside_hist = new TH1D ("mside_hist","mside_hist", nlepEta_ZincNjet_coarserbins_mside, lepEta_ZincNjet_coarserbins_mside);
  for(int j=0; j<10; j++){
    mside_hist->SetBinContent(j+1,mside_bincontent[9-j]);
    mside_hist->SetBinError(j+1,mside_binerr[9-j]);
  }

  return mside_hist;

}

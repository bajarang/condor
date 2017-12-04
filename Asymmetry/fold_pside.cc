#include <iostream>
#include "TH1D.h"
#include "fold_pside.h"
using namespace std;

TH1D *fold_pside(TH1D* tofold_histo){

  int totbins = 0;
  totbins = tofold_histo->GetNbinsX();
  double pside_bincontent[10] = {0.0};
  double pside_binerr[10] = {0.0};
  for(int i=1; i<=totbins; i++){
    if(i>10){
      pside_bincontent[i-11]=tofold_histo->GetBinContent(i);
      pside_binerr[i-11]    =tofold_histo->GetBinError(i);
    }
    else continue;
  }

  //CoarserEtaBins but folded
  int nlepEta_ZincNjet_coarserbins_pside(10);
  double lepEta_ZincNjet_coarserbins_pside[11] = {0.0, 0.2, 0.4, 0.6, 0.8, 1.0, 1.2, 1.4, 1.6, 1.85, 2.1};
  TH1D *pside_hist = new TH1D ("pside_hist","pside_hist", nlepEta_ZincNjet_coarserbins_pside, lepEta_ZincNjet_coarserbins_pside);
  for(int j=0; j<10; j++){
    pside_hist->SetBinContent(j+1,pside_bincontent[j]);
    pside_hist->SetBinError(j+1,pside_binerr[j]);
  }

  return pside_hist;

}

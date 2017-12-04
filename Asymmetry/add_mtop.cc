#include <iostream>
#include "TH1D.h"
#include "add_mtop.h"
using namespace std;

TH1D *add_mtop(TH1D* histo_to_add){
    int totbins = 0;
    totbins = histo_to_add->GetNbinsX();
    double pside_bincontent[10] = {0.0};
    double pside_binerr[10]     = {0.0};
    double mside_bincontent[10] = {0.0};
    double mside_binerr[10]     = {0.0};
    int nlepEta_ZincNjet_coarserbins_pside(10);
    double lepEta_ZincNjet_coarserbins_pside[11] = {0.0, 0.2, 0.4, 0.6, 0.8, 1.0, 1.2, 1.4, 1.6, 1.85, 2.1};
    TH1D *added_hist = new TH1D ("added_hist","added_hist", nlepEta_ZincNjet_coarserbins_pside, lepEta_ZincNjet_coarserbins_pside);
    for(int i=1; i<=totbins; i++){
        if(i<=10){
            mside_bincontent[i-1] = histo_to_add->GetBinContent(i);
            mside_binerr[i-1]     = histo_to_add->GetBinError(i);
        }
        if(i>10){
            pside_bincontent[i-11] = histo_to_add->GetBinContent(i);
            pside_binerr[i-11]     = histo_to_add->GetBinError(i);
        }
    }
    for(int j=1; j<=totbins/2; j++){
        pside_bincontent[j-1] = pside_bincontent[j-1] + mside_bincontent[10-j];
        pside_binerr[j-1]     = sqrt(pside_binerr[j-1]*pside_binerr[j-1]+mside_binerr[10-j]*mside_binerr[10-j]);
        added_hist->SetBinContent(j,pside_bincontent[j-1]);
        added_hist->SetBinError(j,pside_binerr[j-1]);
    } 
    return added_hist;
}

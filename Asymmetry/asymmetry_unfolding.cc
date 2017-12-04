/*
 *This script is for finding the Muon Charge Asymmetry for different pt ranges
 *
Run it with following command:
g++ rebin_eta_bins_finer_to_coarser_asym_pt_range_specific_8TeV_unfolding.cc -o rebin_eta_bins_finer_to_coarser_asym_pt_range_specific_8TeV_unfolding getAsym.cc fold_mside.cc fold_pside.cc finer_to_coarser_error_prop.cc `root-config --glibs --cflags`
*/


#include <iostream>
#include <fstream>
#include "TApplication.h"
#include "TStyle.h"
#include "TFile.h"
#include "TH1D.h"
#include "TCanvas.h"
#include "TLegend.h"
#include "finer_to_coarser_error_prop.h"
#include "getAsym.h"
#include "fold_mside.h"
#include "fold_pside.h"
#include "add_with_error.h"
#include "sub_with_error.h"
#include "getAsymFiner.h"

using namespace std;

int main(int argc, char* argv[]){

  gStyle->SetOptStat(0);
  //TApplication app("app", &argc, argv);

  //#################################//
 
  string str_pt_low  = "25";
  string str_pt_high = "30";

  //#################################//

  string variable = "lepEta_Zinc0jet";
  if(!str_pt_high.empty()) variable = variable + "_leppt_" + str_pt_low + "_" + str_pt_high;
  cout << "VARIABLE : " << variable << endl;

  //FinerEtaBins
  int nlepEta_ZincNjet_finerbins(46);
  double lepEta_ZincNjet_finerbins[47] = {-2.4, -2.3, -2.2, -2.1, -2, -1.85, -1.75, -1.6, -1.5, -1.4, -1.3, -1.2, -1.1, -1, -0.9, -0.8, -0.7, -0.6, -0.5, -0.4, -0.3, -0.2, -0.1, 0, 0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8, 0.9, 1, 1.1, 1.2, 1.3, 1.4, 1.5, 1.6, 1.75, 1.85, 2, 2.1, 2.2, 2.3, 2.4};

  //CoarserEtaBins
  int nlepEta_ZincNjet_coarserbins(20);
  double lepEta_ZincNjet_coarserbins[21] = {-2.1, -1.85, -1.6, -1.4, -1.2, -1.0, -0.8, -0.6, -0.4, -0.2, 0.0, 0.2, 0.4, 0.6, 0.8, 1.0, 1.2, 1.4, 1.6, 1.85, 2.1};
  //CoarserEtaBins but folded
  //mside
  int nlepEta_ZincNjet_coarserbins_mside(10);
  double lepEta_ZincNjet_coarserbins_mside[11] = {0.0, 0.2, 0.4, 0.6, 0.8, 1.0, 1.2, 1.4, 1.6, 1.85, 2.1};
  //pside
  int nlepEta_ZincNjet_coarserbins_pside(10);
  double lepEta_ZincNjet_coarserbins_pside[11] = {0.0, 0.2, 0.4, 0.6, 0.8, 1.0, 1.2, 1.4, 1.6, 1.85, 2.1};

  //###     muplus    ###//
  //dir
  string muplus_dir;  
  muplus_dir             = "Results/PNGFiles/MySetOfCuts/MuPt25/wplus/FinerBins/Systematics/CENTRAL/FastPlots_30_Syst_0";
  if(!str_pt_low.empty()) muplus_dir = muplus_dir + "_leppt_" + str_pt_low + "_" + str_pt_high;
  muplus_dir             = muplus_dir + "_VarWidth/";
  
  //files
  string mu_unf_file     = "SMu_8TeV_lepEta_Zinc0jet";
  if(!str_pt_low.empty()) mu_unf_file = mu_unf_file + "_leppt_" + str_pt_low + "_" + str_pt_high;
  mu_unf_file = mu_unf_file + "_fastplots_VarWidth.root";
  
  string muplus_unf_file = muplus_dir + mu_unf_file;
  cout << muplus_unf_file << endl;
  
  //tfiles and histos
  TFile *muplus_unf_tfile          = new TFile (muplus_unf_file.c_str(),"READ");
  TH1D  *muplus_unf_finer_histo    = (TH1D*)muplus_unf_tfile->Get("Central");
  TH1D  *muplus_unf_coarser_histo  = new TH1D ("","",nlepEta_ZincNjet_coarserbins, lepEta_ZincNjet_coarserbins);
  muplus_unf_coarser_histo         = finer_to_coarser_error_prop(muplus_unf_finer_histo);
   
  //###     muminus    ###//
  //dir
  string muminus_dir;  
  muminus_dir             = "Results/PNGFiles/MySetOfCuts/MuPt25/wminus/FinerBins/Systematics/CENTRAL/FastPlots_30_Syst_0";
  if(!str_pt_low.empty()) muminus_dir = muminus_dir + "_leppt_" + str_pt_low + "_" + str_pt_high;
  muminus_dir             = muminus_dir + "_VarWidth/";
  //files
  string muminus_unf_file = muminus_dir + mu_unf_file;

  //tfiles and histos
  TFile *muminus_unf_tfile          = new TFile (muminus_unf_file.c_str(),"READ");
  TH1D  *muminus_unf_finer_histo    = (TH1D*)muminus_unf_tfile->Get("Central");
  
  TH1D  *muminus_unf_coarser_histo  = new TH1D ("","",nlepEta_ZincNjet_coarserbins, lepEta_ZincNjet_coarserbins);
  muminus_unf_coarser_histo         = finer_to_coarser_error_prop(muminus_unf_finer_histo);
  
  //####    ASYM   ####//
  TH1D *asym_histo              = new TH1D ("","",nlepEta_ZincNjet_coarserbins,lepEta_ZincNjet_coarserbins);
  asym_histo                    = getAsym(muplus_unf_coarser_histo,muminus_unf_coarser_histo);
  
  //DELETE LATER BELOW
  TH1D *asym_histo_finer        = new TH1D("","",nlepEta_ZincNjet_finerbins,lepEta_ZincNjet_finerbins);
  asym_histo_finer              = getAsymFiner(muplus_unf_finer_histo,muminus_unf_finer_histo);
  for(int kk=1; kk<=asym_histo_finer->GetNbinsX(); kk++){
    cout << kk                                        << "  "
         << lepEta_ZincNjet_finerbins[kk-1]           << "  "
         << lepEta_ZincNjet_finerbins[kk]             << "  "   
         << muplus_unf_finer_histo->GetBinContent(kk)  << "  "
         << muminus_unf_finer_histo->GetBinContent(kk) << "  " 
         << asym_histo_finer->GetBinContent(kk)       << endl;
  }
  //DELETE LATER ABOVE


  //##   FOLD HISTO  ##//
  TH1D *asym_folded_mside_histo = new TH1D ("","",nlepEta_ZincNjet_coarserbins_mside,lepEta_ZincNjet_coarserbins_mside);
  asym_folded_mside_histo       = fold_mside(asym_histo);
  TH1D *asym_folded_pside_histo = new TH1D ("","",nlepEta_ZincNjet_coarserbins_pside,lepEta_ZincNjet_coarserbins_pside);
  asym_folded_pside_histo       = fold_pside(asym_histo);
  
  string histo_title = "";
  if( str_pt_low.empty() &&  str_pt_high.empty()) histo_title = "A_{#eta} ";
  if(!str_pt_low.empty() && !str_pt_high.empty()) histo_title = "A_{#eta} (" + str_pt_low + " < pt_{#mu} < " + str_pt_high + ") ";

  histo_title = histo_title + " [UNFOLDED] with BVeto";
  
  //mycan
  TCanvas *mycan = new TCanvas ("mycan","mycan",800,600);
  mycan->cd();

  //pad1
  TPad *pad1 = new TPad("","",0,0.3,1,1);
  pad1->SetTopMargin(0.11);
  pad1->SetBottomMargin(0);
  pad1->SetRightMargin(0.04);
  pad1->SetTicks();
  pad1->SetGridy();
  pad1->Draw();
  pad1->cd();
  //mside histo
  asym_folded_mside_histo->SetLineColor(kRed);
  asym_folded_mside_histo->SetLineWidth(3.0);
  asym_folded_mside_histo->GetYaxis()->SetTitle("A_{#eta}");
  asym_folded_mside_histo->GetXaxis()->SetTitle("#eta_{#mu}");
  asym_folded_mside_histo->GetYaxis()->SetTitleSize(0.06);
  asym_folded_mside_histo->GetYaxis()->SetTitleOffset(0.75);
  asym_folded_mside_histo->GetYaxis()->SetLabelSize(0.047);
  asym_folded_mside_histo->GetYaxis()->SetLabelOffset(0.004);
  asym_folded_mside_histo->GetYaxis()->SetRangeUser(-0.05,0.4);
  asym_folded_mside_histo->SetTitle(histo_title.c_str());
  asym_folded_mside_histo->Draw("E1");
  //pside histo
  asym_folded_pside_histo->SetLineColor(kBlue);
  asym_folded_pside_histo->SetLineWidth(3.0);
  asym_folded_pside_histo->Draw("Same");    
  //TLegend
  TLegend *leg = new TLegend (0.26,0.63,0.45,0.89);
  leg->SetFillStyle(0);
  leg->SetBorderSize(0);
  leg->SetTextSize(0.04);
  leg->AddEntry(asym_folded_pside_histo, "A_{#eta} (#eta^{+})", "pl");
  leg->AddEntry(asym_folded_mside_histo, "A_{#eta} (#eta^{-})", "pl");
  leg->Draw();
  
  //pad2
  mycan->cd();
  TPad *pad2 = new TPad ("pad2","pad2",0,0,1,0.4);
  pad2->SetTopMargin(0);
  pad2->SetBottomMargin(0.3);
  pad2->SetRightMargin(0.04);
  pad2->SetTicks();
  pad2->SetGridy();
  pad2->Draw();
  pad2->cd();
 
  //## pside/mside ratio ##// 
  TH1D *asym_pside_mside_ratio = new TH1D("asym_pside_mside_ratio","", nlepEta_ZincNjet_coarserbins_mside,lepEta_ZincNjet_coarserbins_mside);
  asym_pside_mside_ratio->Divide(asym_folded_pside_histo,asym_folded_mside_histo);
  asym_pside_mside_ratio->GetXaxis()->SetTickLength(0.03);
  asym_pside_mside_ratio->GetXaxis()->SetTitleSize(0.1);
  asym_pside_mside_ratio->GetXaxis()->SetTitleOffset(1.2);
  asym_pside_mside_ratio->GetXaxis()->SetLabelSize(0.08);
  asym_pside_mside_ratio->GetXaxis()->SetLabelOffset(0.018);
  asym_pside_mside_ratio->GetXaxis()->SetTitle("#eta_{#mu}");
  asym_pside_mside_ratio->GetYaxis()->SetTitle("A_{#eta}(#eta^{+}) / A_{#eta}(#eta^{-})");
  asym_pside_mside_ratio->GetYaxis()->SetTitleSize(0.087);
  asym_pside_mside_ratio->GetYaxis()->SetTitleOffset(0.45);
  asym_pside_mside_ratio->GetYaxis()->SetLabelSize(0.08);
  asym_pside_mside_ratio->GetYaxis()->SetRangeUser(0.9,1.11);
  asym_pside_mside_ratio->GetYaxis()->SetNdivisions(5,5,0);
  asym_pside_mside_ratio->SetMarkerStyle(24);
  asym_pside_mside_ratio->SetMarkerColor(kBlue+1);
  asym_pside_mside_ratio->SetMarkerSize(0.5);
  asym_pside_mside_ratio->SetLineColor(kBlue+2);
  asym_pside_mside_ratio->SetLineWidth(3.0);
  asym_pside_mside_ratio->Draw("");
   
  pad2->Draw(); 

  string output_dir  = "Results/Asym/MySetOfCuts/MuPt25/wplus/FinerBins/Systematics/CENTRAL/unfolded/";
  string create_output_dir = "mkdir -p " + output_dir;
  system(create_output_dir.c_str());
  
  //#### save in text files ####//
  string text_file;
  text_file = "Asym_pt_"+str_pt_low+"_"+str_pt_high+"_RochCorr_NO_SF_YES_8TeV_UNFOLDED_syst_0.txt";
  text_file = output_dir + text_file;
  ofstream op_goes_to_file(text_file.c_str());
  for(int i=1; i<=muplus_unf_coarser_histo->GetNbinsX(); i++){
    
    //goes to the screen
    cout << lepEta_ZincNjet_coarserbins[i-1]             << "\t"
         << lepEta_ZincNjet_coarserbins[i]               << "\t"
         << muplus_unf_coarser_histo->GetBinContent(i)   << "\t"
         << muplus_unf_coarser_histo->GetBinError(i)     << "\t"
         << muminus_unf_coarser_histo->GetBinContent(i)  << "\t"
         << muminus_unf_coarser_histo->GetBinError(i)    << "\t" 
         << asym_histo->GetBinContent(i)                 << "\t"
         << asym_histo->GetBinError(i)                 
         << endl;
    
    //goes to the text file
    op_goes_to_file << lepEta_ZincNjet_coarserbins[i-1]  << ",\t"
         << lepEta_ZincNjet_coarserbins[i]               << ",\t"
         << muplus_unf_coarser_histo->GetBinContent(i)   << ",\t"
         << muplus_unf_coarser_histo->GetBinError(i)     << ",\t"
         << muminus_unf_coarser_histo->GetBinContent(i)  << ",\t"
         << muminus_unf_coarser_histo->GetBinError(i)    << ",\t" 
         << asym_histo->GetBinContent(i)                 << ",\t"
         << asym_histo->GetBinError(i)                   
         << endl;
  }
  //##############################################################################//
  double NPlusEtaPlus[10] = {0.0};
  double NPlusEtaPlusError[10]={0.0};
  double NPlusEtaMinus[10] = {0.0};
  double NPlusEtaMinusError[10]={0.0};

  double NMinusEtaPlus[10]={0.0};
  double NMinusEtaPlusError[10]={0.0};
  double NMinusEtaMinus[10] = {0.0};
  double NMinusEtaMinusError[10]={0.0};

  double NPlusEtaPlusMinus[10]={0.0};
  double NPlusEtaPlusMinusError[10]={0.0};
  double NMinusEtaPlusMinus[10]={0.0};
  double NMinusEtaPlusMinusError[10]={0.0};
  
  double AsymEtaPlus[10] = {0.0};
  double AsymEtaPlusError[10] = {0.0};


  cout << muplus_unf_coarser_histo->GetNbinsX() << "<-- BINS" << endl;
  for(int i=1; i<=muplus_unf_coarser_histo->GetNbinsX(); i++){
    //goes to the screen
    if(i<=10){//negative eta
      NPlusEtaMinus[i-1]        = muplus_unf_coarser_histo->GetBinContent(i);
      NPlusEtaMinusError[i-1]   = muplus_unf_coarser_histo->GetBinError(i); 
      NMinusEtaMinus[i-1]       = muminus_unf_coarser_histo->GetBinContent(i);
      NMinusEtaMinusError[i-1]  = muminus_unf_coarser_histo->GetBinError(i); 
    }
    if(i>10){//positive eta
      NPlusEtaPlus[i-11]        = muplus_unf_coarser_histo->GetBinContent(i);
      NPlusEtaPlusError[i-11]   = muplus_unf_coarser_histo->GetBinError(i); 
      NMinusEtaPlus[i-11]        = muminus_unf_coarser_histo->GetBinContent(i);
      NMinusEtaPlusError[i-11]   = muminus_unf_coarser_histo->GetBinError(i); 
    }
  }

  for(int kk=1; kk<=10; kk++){
    NPlusEtaPlusMinus[kk-1]       = NPlusEtaMinus[10-kk]+NPlusEtaPlus[kk-1];
    NPlusEtaPlusMinusError[kk-1]  = sqrt(NPlusEtaMinusError[10-kk]*NPlusEtaMinusError[10-kk]+NPlusEtaPlusError[kk-1]*NPlusEtaPlusError[kk-1]);
    NMinusEtaPlusMinus[kk-1]      = NMinusEtaMinus[10-kk]+NMinusEtaPlus[kk-1];
    NMinusEtaPlusMinusError[kk-1] = sqrt(NMinusEtaMinusError[10-kk]*NMinusEtaMinusError[10-kk]+NMinusEtaPlusError[kk-1]*NMinusEtaPlusError[kk-1]);

    AsymEtaPlus[kk-1] = (NPlusEtaPlusMinus[kk-1] - NMinusEtaPlusMinus[kk-1]) / (NPlusEtaPlusMinus[kk-1] + NMinusEtaPlusMinus[kk-1]);    
    AsymEtaPlusError[kk-1] = (2/((NPlusEtaPlusMinus[kk-1]+NMinusEtaPlusMinus[kk-1])*(NPlusEtaPlusMinus[kk-1]+NMinusEtaPlusMinus[kk-1])))*sqrt(NMinusEtaPlusMinus[kk-1]*NMinusEtaPlusMinus[kk-1]*NPlusEtaPlusMinusError[kk-1]*NPlusEtaPlusMinusError[kk-1]+NPlusEtaPlusMinus[kk-1]*NPlusEtaPlusMinus[kk-1]*NMinusEtaPlusMinusError[kk-1]*NMinusEtaPlusMinusError[kk-1]);

    //cout << NMinusEtaMinus[kk-1] << "  " << NMinusEtaPlus[10-kk] << "  " << NMinusEtaPlusMinus[kk-1] << endl;
    cout << NPlusEtaPlusMinus[kk-1] << "\t"
         << NPlusEtaPlusMinusError[kk-1] << "\t"
         << NMinusEtaPlusMinus[kk-1] << "\t"
         << NMinusEtaPlusMinusError[kk-1] << "\t"
         << AsymEtaPlus[kk-1] << "\t"
         << AsymEtaPlusError[kk-1] << endl;
  }    
  //##############################################################################//

  //#### save png plots ####//
  string png_file;   
  png_file = "Asym_pt_"+str_pt_low+"_"+str_pt_high+"_RochCorr_NO_SF_YES_8TeV_UNFOLDED_syst_0.png";

  png_file = output_dir + png_file;
  mycan->SaveAs(png_file.c_str());
  
}

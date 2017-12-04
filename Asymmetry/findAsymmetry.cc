/*
 * This script takes three arguements : variable range and closureTest and finds the Muon Charge Asymmetry on Unfolded level 
 * Compile with :
 * $ g++ asymmetry_unfolding.cc -o asymmetry_unfolding validateSystNDirection.cc getAsym.cc getAsymFiner.cc fold_mside.cc fold_pside.cc finer_to_coarser_error_prop.cc add_mtop.cc `root-config --glibs --cflags` 
 * Run with :
 * $ ./asymmetry_unfolding type variable range closureTest systematics direction
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
#include "getAsymFiner.h"
#include "validateSystNDirection.h"
#include "add_mtop.h"
using namespace std;

int main(int argc, char* argv[]){

  ///////////////Check if correct number of args are passed or not/////////////////////////
  if(argc!=7){
    cout << "You passed " << argc << " arguments " << endl;
    cout << "Program expects 6 arguments as explained below." << endl;
    cout << "$ ./asymmetry_unfolding type variable range closureTest systematics direction" << endl;
    cout << "" << endl;
    cout << "Here type can be either : GEN or RECO or DATA or DATA-BKGD or UNF " << endl;
    cout << "Here variable can be : lepEta_Zinc0jet or lepEta_Zinc4jet etc..." << endl;
    cout << "For range, choose from this list : " << endl;
    cout << "  25_above or 25_30 or 30_35 or 35_40 or 40_45 or 45_above" << endl;
    cout << "For closureTest, pass either 0 or 1" << endl;
    cout << "systematics and direction should be as expected, refer to validateSystNDirection code."<< endl;
    exit(0);
  }

  gStyle->SetOptStat(0);

  /////////////////////////////parse arguments/////////////////////////////////
  // 1. parse type
  string type = argv[1];
  cout << "First argument is type : " << type << endl;
  string levelType[5] = {"GEN","RECO","DATA","DATA-BKGD","UNF"};
  bool validType = false;
  for(int i=0; i<5; i++){
    if(levelType[i]==type) validType = true;
  }
  if(!validType) {
    cout << "Provided type is not acceptable, exiting now." << endl;
  }

  // 2. parse variable 
  string variable = argv[2];
  cout << "Second argument variable : " << variable << endl;

  // 3. parse range
  string availableRange[6] = {"25_above", "25_30", "30_35", "35_40", "40_45", "45_above"};
  string range = argv[3];
  bool withinRange = false;
  cout << "Second argument range : " << range << endl;
  for(int ii=0; ii<6; ii++){
    if(availableRange[ii]==range) withinRange=true;
  }
  if(withinRange){
    cout << "Passed range is within accepted ranges, proceeding..." << endl;
  }
  else{
    cout << "passed range is not accepted, exiting now." << endl;
    exit(0);
  }

  // modify variable wrt range
  string str_pt_low;
  string str_pt_high;
  if(range!="25_above"){ 
    variable = variable + "_leppt_" + range;
  }
  cout << "We will process this variable " << variable << endl;

  // 4. parse closureTest
  string closureTest = argv[4];
  if(closureTest!="0" && closureTest!="1") {
    cout << "You passed closureTest : " << closureTest << endl;
    cout << "It can be either 0 or 1, exiting now" << endl;
    exit(0);
  }

  // 5 & 6. parse systematics
  string systematics = argv[5];
  string direction   = argv[6];
  if(!validateSystNDirection(systematics, direction)) {
    cout << "systematics and direction are not within expected list values, exiting now." << endl;
    exit(0);
  }
 
  // 5. for direction, decide append strings
  string strDirection;
  if(direction=="0")      strDirection = "CN";
  else if(direction=="1") strDirection = "UP"; 
  else                    strDirection = "DN"; 

  //////////////////////done parsing//////////////////////////////

  ////////////////////////////Eta bins////////////////////////////
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

  //////////////////////////TFiles and THistos/////////////////////

  //dir
  string mu_dir,  muplus_dir,  muminus_dir;
  string mu_file, muplus_file, muminus_file;
  TFile *muplus_tfile;
  TFile *muminus_tfile;
  TH1D  *muplus_finer_histo;
  TH1D  *muminus_finer_histo;
  if(type=="UNF"){
    //dir
    mu_dir          = "/home/bsutar/t3store2/MuonChargeAsymAnalysis8TeV2012/Results/PNGFiles/Condor/";  
    muplus_dir      = mu_dir + "FastPlots_WP_Syst_" + systematics + "_" + strDirection + "_" + variable;
    muplus_dir      = muplus_dir + "_JetPt_30_VarWidth/";
    muminus_dir     = mu_dir + "FastPlots_WM_Syst_" + systematics + "_" + strDirection + "_" + variable;
    muminus_dir     = muminus_dir + "_JetPt_30_VarWidth/";
    //file
    mu_file         = "SMu_8TeV_" + variable + "_fastplots_VarWidth.root";
    muplus_file     = muplus_dir + mu_file;
    cout << "Visiting for WP :  1. " << muplus_file << endl;
    muminus_file    = muminus_dir + mu_file;
    cout << "Visiting for WM :  2. " << muminus_file << endl;
    //tfile
    muplus_tfile    = new TFile (muplus_file.c_str(),"READ");
    if(!muplus_tfile){
      cout << "Error opening file : " << muplus_file << endl;
      cout << "Exiting now." << endl;
      exit(0);
    }
    muminus_tfile   = new TFile (muminus_file.c_str(),"READ");
    if(!muminus_tfile){
      cout << "Error opening file : " << muminus_file << endl;
      cout << "Exiting now." << endl;
      exit(0);
    }
    //histo
    muplus_finer_histo    = (TH1D*)muplus_tfile->Get("Central");
    muminus_finer_histo   = (TH1D*)muminus_tfile->Get("Central");
  }
  else if(type=="GEN" || type=="RECO" || type=="DATA"){
    if(type!="DATA"){
      //dir
      mu_dir          = "/home/bsutar/t3store2/MuonChargeAsymAnalysis8TeV2012/Results/HistoFiles/Condor/";  
      //file
      muplus_file     = mu_dir + "SMu_8TeV_WJetsALL_MIX_UNFOLDING_dR_5311_WP_EffiCorr_1_TrigCorr_1_Syst_" + systematics + "_" + strDirection + "_JetPtMin_30_VarWidth_BVeto_QCD0_MET15_mT50_Merge.root";
      muminus_file    = mu_dir + "SMu_8TeV_WJetsALL_MIX_UNFOLDING_dR_5311_WM_EffiCorr_1_TrigCorr_1_Syst_" + systematics + "_" + strDirection + "_JetPtMin_30_VarWidth_BVeto_QCD0_MET15_mT50_Merge.root";
      //tfile    
      muplus_tfile    = new TFile (muplus_file.c_str(),"READ");
      if(!muplus_tfile){
        cout << "Error opening file : " << muplus_file << endl;
        cout << "Exiting now." << endl;
        exit(0);
      }
      muminus_tfile   = new TFile (muminus_file.c_str(),"READ");
      if(!muminus_tfile){
        cout << "Error opening file : " << muminus_file << endl;
        cout << "Exiting now." << endl;
        exit(0);
      }
      //histo
      if(type=="GEN") {
        string genVariable;
        genVariable = "gen" + variable;
        muplus_finer_histo    = (TH1D*)muplus_tfile->Get(genVariable.c_str());
        muminus_finer_histo   = (TH1D*)muminus_tfile->Get(genVariable.c_str());
      }
      else {
        muplus_finer_histo    = (TH1D*)muplus_tfile->Get(variable.c_str());
        muminus_finer_histo   = (TH1D*)muminus_tfile->Get(variable.c_str());
      }
    }
    else {
      //dir
      mu_dir          = "/home/bsutar/t3store2/MuonChargeAsymAnalysis8TeV2012/Results/HistoFiles/Condor/";  
      //file
      muplus_file     = mu_dir + "SMu_8TeV_Data_dR_5311_WP_EffiCorr_0_TrigCorr_1_Syst_" + systematics + "_" + strDirection + "_JetPtMin_30_VarWidth_BVeto_QCD0_MET15_mT50_Merge.root";
      muminus_file    = mu_dir + "SMu_8TeV_Data_dR_5311_WM_EffiCorr_0_TrigCorr_1_Syst_" + systematics + "_" + strDirection + "_JetPtMin_30_VarWidth_BVeto_QCD0_MET15_mT50_Merge.root";
      //tfile    
      muplus_tfile    = new TFile (muplus_file.c_str(),"READ");
      if(!muplus_tfile){
        cout << "Error opening file : " << muplus_file << endl;
        cout << "Exiting now." << endl;
        exit(0);
      }
      muminus_tfile   = new TFile (muminus_file.c_str(),"READ");
      if(!muminus_tfile){
        cout << "Error opening file : " << muminus_file << endl;
        cout << "Exiting now." << endl;
        exit(0);
      }
      //histo
      muplus_finer_histo    = (TH1D*)muplus_tfile->Get(variable.c_str());
      muminus_finer_histo   = (TH1D*)muminus_tfile->Get(variable.c_str());
    }
  }
  else if(type=="DATA-BKGD"){
    //dir

    //file

    //tfile    

  }

  TH1D  *muplus_coarser_histo     = new TH1D ("","",nlepEta_ZincNjet_coarserbins, lepEta_ZincNjet_coarserbins);
  muplus_coarser_histo            = finer_to_coarser_error_prop(muplus_finer_histo);
  TH1D  *muminus_coarser_histo    = new TH1D ("","",nlepEta_ZincNjet_coarserbins, lepEta_ZincNjet_coarserbins);
  muminus_coarser_histo           = finer_to_coarser_error_prop(muminus_finer_histo);
   
  //######## Add -ve eta entries with +ve eta entries ########//
  // 1. muplus
  TH1D *mtop_added_muplus_histo   = new TH1D ("","",nlepEta_ZincNjet_coarserbins_pside,lepEta_ZincNjet_coarserbins_pside);
  mtop_added_muplus_histo         = add_mtop(muplus_coarser_histo);
  // 2. muminus
  TH1D *mtop_added_muminus_histo  = new TH1D ("","",nlepEta_ZincNjet_coarserbins_pside,lepEta_ZincNjet_coarserbins_pside);
  mtop_added_muminus_histo        = add_mtop(muminus_coarser_histo);

  //####    ASYM   ####//
  TH1D *asym_histo                = new TH1D ("","",nlepEta_ZincNjet_coarserbins,lepEta_ZincNjet_coarserbins);
  asym_histo                      = getAsym(mtop_added_muplus_histo,mtop_added_muminus_histo);

  for(int i=1; i<=asym_histo->GetNbinsX(); i++){
    cout << lepEta_ZincNjet_coarserbins_pside[i-1]             << "\t"
         << lepEta_ZincNjet_coarserbins_pside[i]               << "\t"
         << mtop_added_muplus_histo->GetBinContent(i)          << "\t"
         << mtop_added_muplus_histo->GetBinError(i)            << "\t"
         << mtop_added_muminus_histo->GetBinContent(i)         << "\t"
         << mtop_added_muminus_histo->GetBinError(i)           << "\t"
         << asym_histo->GetBinContent(i)                       << "\t"
         << asym_histo->GetBinError(i)
         << endl;
  }
  exit(0); 
 
  //DELETE LATER BELOW
  ////TH1D *asym_histo_finer        = new TH1D("","",nlepEta_ZincNjet_finerbins,lepEta_ZincNjet_finerbins);
  ////asym_histo_finer              = getAsymFiner(muplus_finer_histo,muminus_finer_histo);
  ////for(int kk=1; kk<=asym_histo_finer->GetNbinsX(); kk++){
    ////cout << kk                                        << "  "
         ////<< lepEta_ZincNjet_finerbins[kk-1]           << "  "
         ////<< lepEta_ZincNjet_finerbins[kk]             << "  "   
         ////<< muplus_finer_histo->GetBinContent(kk)  << "  "
         ////<< muminus_finer_histo->GetBinContent(kk) << "  " 
         ////<< asym_histo_finer->GetBinContent(kk)       << endl;
  ////}
  //DELETE LATER ABOVE
  

  
}

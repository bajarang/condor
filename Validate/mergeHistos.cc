#include <iostream>
#include <stdio.h>
#include "TFile.h"

using namespace std;

int main(int argc, char* argv[]){

  ///////////////Check if correct number of args are passed or not/////////////////////////
  if(argc!=6){
    cout << "Please provide 5 arguments as explained below." << endl;
    cout << "$ ./mergeHistos charge sample doqcd syst direction" << endl;
    cout << "" << endl;
    cout << "Here charge can be either 1 or -1" << endl;
    cout << "sample can be either Data or SigMC or BkgdMC" << endl;
    cout << "For BkgdMC, you can also provide more targetted sample names from the following list : " << endl;
    cout << "    TTJets, DYJets_10to50, DYJets_MIX, T_s, T_t, T_tW, Tbat_s, Tbar_t, Tbar_tW, WW, WZ, ZZ" << endl;
    cout << "For doqcd, choose either of the following options :" << endl;
    cout << "    0, 1, 2, 3 or 100 (for default)" << endl;
    cout << "For syst, you can choose following options which are based on sample values :" << endl;
    cout << "    Data  : 0, 2 or 100" << endl;
    cout << "    SigMC : 0, 1, 4, 5, 6, 7, 8, 9, 11" << endl;
    cout << "Exiting Now." << endl;
  }

  /////////////////Parse the arguments//////////////////////////
  // 1. parse charge
  stringstream charge;
  charge << argv[2];
  int intCharge = 0;
  charge >> intCharge;
  string strCharge;
  if(intCharge==1) strCharge = "_WP";
  else if (intCharge==-1) strCharge = "_WM";
  else {
    cout << "Please enter either 1 or -1 for charge." << endl;
    cout << "Exiting Now" << endl;
    exit(0);
  }
  // 2. parse sample
  string sample;
  sample = argv[3];
  string listSamples[] = {"Data","SigMC","BkgdMC","TTJets","","","","","",};
  if

  cout << "This script adds the histograms using hadd" << endl;
  cout << "You want to add which sample?" << endl;
  cout << "Enter either of these Data or SigMC or BkgdMC" << endl;
  string whichsample;
  cin  >> whichsample;
  if(whichsample.find("Data")!=string:npos){
    cout << "We will add : " << whichsample << endl;
  }
  else if(whichsample.find("SigMC")!=string:npos){
    cout << "We will add : " << whichsample << endl;
  }
  else if(whichsample.find("BkgdMC")!=string:npos){
    cout << "We will add : " << whichsample << endl;
  }
  else {
    cout << "Please provide the correct input option, exiting now" << endl;
  }

  string command;
  command = "hadd -k ";

  



}

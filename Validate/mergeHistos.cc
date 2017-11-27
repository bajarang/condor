/*
 * Pass these 5 arguments to this executable
 * 1. Charge
 * 2. sample name (for full list, refer to the code)
 * 3. doQCD
 * 4. syst
 * 5. direction
 * Compile the code with : $ g++ mergeHistos.cc -o mergeHistos generateFileNames.cc `root-config --glibs --cflags`
 * Run it with           : $ ./mergeHistos 1 Data 0 0 0 
 */

#include <iostream>
#include <sstream>
#include <stdio.h>
#include <cstdlib>
#include "TFile.h"
#include "generateFileNames.h"

using namespace std;

int main(int argc, char* argv[]){

  ///////////////Check if correct number of args are passed or not/////////////////////////
  if(argc!=6){
    cout << "Please provide 5 arguments as explained below." << endl;
    cout << "$ ./mergeHistos charge sample doqcd syst direction" << endl;
    cout << "" << endl;
    cout << "Here charge can be either 1 or -1" << endl;
    cout << "For sample, choose from this list : " << endl;
    cout << "Data, TTJets, ZZ, WZ, WW, T_s, T_t, T_tW, Tbar_s, Tbar_t, Tbar_tW, DYJets_MIX_UNFOLDING, DYJets_10to50, WJetsALL_MIX_UNFOLDING" << endl;
  }

  // 0. provide path of the input files which we want to add
  string pathDir = "/home/bsutar/t3store2/MuonChargeAsymAnalysis8TeV2012/Results/HistoFiles/Condor/";

  // 1. parse charge
  stringstream charge;
  charge << argv[1];
  int intCharge = 0;
  charge >> intCharge;
  string strCharge;
  bool validCharge = false;
  if(intCharge==1) {
    strCharge = "_WP";
    validCharge = true;
  }
  else if (intCharge==-1) {
    strCharge = "_WM";
    validCharge = true;
  }
  else {
    cout << "Please enter either 1 or -1 for charge." << endl;
    cout << "Exiting Now" << endl;
    exit(0);
  }

  // 2. parse sample
  string sample;
  sample = argv[2];
  string listSamples[14]={};
  listSamples[0]  =                   "Data";
  listSamples[1]  =                 "TTJets";
  listSamples[2]  =                     "ZZ";
  listSamples[3]  =                     "WZ";
  listSamples[4]  =                     "WW";
  listSamples[5]  =            "T_s_channel";
  listSamples[6]  =            "T_t_channel";
  listSamples[7]  =           "T_tW_channel";
  listSamples[8]  =         "Tbar_s_channel";
  listSamples[9]  =         "Tbar_t_channel";
  listSamples[10] =        "Tbar_tW_channel";
  listSamples[11] =          "DYJets_10to50";
  listSamples[12] =   "DYJets_MIX_UNFOLDING";
  listSamples[13] = "WJetsALL_MIX_UNFOLDING";

  int beginRange[14]={0};
  int endRange[14]={0};
  beginRange[0]  =   1; endRange[0]  = 579;  //                      "Data" 
  beginRange[1]  =   1; endRange[1]  =   6;  //                    "TTJets"
  beginRange[2]  =   1; endRange[2]  =   2;  //                        "ZZ"
  beginRange[3]  =   1; endRange[3]  =   4;  //                        "WZ"
  beginRange[4]  =   1; endRange[4]  =   5;  //                        "WW"
  beginRange[5]  =   1; endRange[5]  =   1;  //                       "T_s"
  beginRange[6]  =   1; endRange[6]  =   1;  //                       "T_t"
  beginRange[7]  =   1; endRange[7]  =   1;  //                      "T_tW"
  beginRange[8]  =   1; endRange[8]  =   1;  //                    "Tbar_s"
  beginRange[9]  =   1; endRange[9]  =   1;  //                    "Tbar_t"
  beginRange[10] =   1; endRange[10] =   1;  //                   "Tbar_tW"
  beginRange[11] =   1; endRange[11] =   1;  //             "DYJets_10to50"
  beginRange[12] =   1; endRange[12] =  85;  //      "DYJets_MIX_UNFOLDING" 
  beginRange[13] =   1; endRange[13] = 239;  //    "WJetsALL_MIX_UNFOLDING"


  bool validSample = false;
  int index;
  for(int ii=0; ii<14; ii++){
    if(listSamples[ii].find(sample)!=string::npos){
      validSample = true;
      index = ii;    
    }
  }
  if(!validSample) {
    cout << "Please enter valid sample option" << endl;
    cout << "eg. from this list : " << endl;
    cout << "\tData, SigMC, BkgdMC, TTJets, DYJets_MIX," << endl;
    cout << "\tDYJets_10to50, T_s, T_t, T_tW, Tbar_s,"   << endl;
    cout << "\tTbar_t, Tbar_tW, WW, WZ, ZZ" << endl;
    cout << "Exiting Now." << endl;
    exit(0);
  }

  // 3. parse doqcd
  string doQCD;
  doQCD = argv[3];
  string listDoQCD[5] = {"0","1","2","3","100"};
  bool validDoQCD = false;
  for(int jj=0; jj<5; jj++){ 
    if(listDoQCD[jj].find(doQCD)!=string::npos){
      validDoQCD = true;
    }
  }
  if(!validDoQCD) {
    cout << "Please enter valid doqcd value" << endl;
    cout << "Either 0, 1, 2, 3, 100" << endl;
    cout << "Exiting Now." << endl;
    exit(0);
  }

  // 4. parse syst and direction
  const int NSystData(3);
  short dataSyst[NSystData]  = {0, 2, 2};
  short dataDir[NSystData]   = {0,-1, 1};
  const int NSystWJets(18);
  short wjSyst[NSystWJets]   = {0, 1, 1, 5, 5, 6, 6, 7, 7, 4, 4, 8, 9, 10, 11, 11};
  short wjDir[NSystWJets]    = {0,-1, 1,-1, 1,-1, 1,-1, 1,-1, 1, 1, 1,  1,  1, -1};
  const int NSystBkgd(12);
  short bgSyst[NSystBkgd]    = {0, 1, 1, 3, 3, 5, 5, 6, 6, 7, 7, 8};
  short bgDir[NSystBkgd]     = {0,-1, 1,-1, 1,-1, 1,-1, 1,-1, 1, 1};

  ///////syst///////
  stringstream strStreamSyst;
  strStreamSyst << argv[4];
  int intSyst = -1;
  strStreamSyst >> intSyst;
  string strSyst = strStreamSyst.str();

  ///////dir///////
  stringstream strStreamDir;
  strStreamDir << argv[5];
  int intDirection = -1;
  strStreamDir >> intDirection;
  string strDir = strStreamDir.str();

  bool validSyst = false;
  bool validDirection = false;

  if(sample.find("Data")!=string::npos){ 
    for(int kk=0; kk<NSystData; kk++){
      if(intSyst==dataSyst[kk] || intSyst==100){
        validSyst = true;
        validDirection = true;
      }
      else{
        cout << "Please enter valid syst value (Check the full list inside this code)" << endl;
        cout << "Exiting Now." << endl;
      }
    }
  }

  else if(sample.find("SigMC")!=string::npos){ 
    for(int kk=0; kk<NSystWJets; kk++){
      if(intSyst==wjSyst[kk] || intSyst==100){
        validSyst = true;
        validDirection = true;
      }
    }
  }

  else {
    for(int ll=0; ll<NSystBkgd; ll++){
      if(intSyst==bgSyst[ll] || intSyst==100){
        validSyst = true;
        validDirection = true;
      }
    }
  }

  if(validCharge && validSample && validDoQCD && validSyst && validDirection){
    cout << "Here are the options you entered" << endl;
    cout << "  charge    : " << intCharge << endl;
    cout << "  sample    : " << sample    << endl;
    cout << "  doqcd     : " << doQCD     << endl;
    cout << "  syst      : " << intSyst      << endl;
    cout << "  direction : " << intDirection << endl; 
  }

  stringstream rangeStr;
  ////cout << index << "  " << beginRange[index] << "  " << endRange[index] << endl;
  string mergeIntoThisFile = "";
  mergeIntoThisFile = generateFileNames(strCharge,listSamples[index],doQCD,strSyst,strDir,"Merge");  
  string longStrFileToMerge = "";
  for(int ii=beginRange[index]; ii<=endRange[index]; ii++){
    ////cout << ii << endl;
    rangeStr << ii;

    string rangeStrAppend = "0000" + rangeStr.str();
    int isize = rangeStrAppend.size();
    string subRangeStrAppend = rangeStrAppend.substr(isize-5,5);
    string fileToMerge = "";
    fileToMerge = generateFileNames(strCharge,listSamples[index],doQCD,strSyst,strDir,subRangeStrAppend);
    longStrFileToMerge = longStrFileToMerge + pathDir + fileToMerge + " ";
    ////cout << longStrFileToMerge << endl;
    /////////////clear strings////////////
    rangeStr.str("");
    rangeStrAppend.clear();
    subRangeStrAppend.clear();
    fileToMerge.clear();
  }

  string command = "hadd -k -f ";
  command = command + pathDir + mergeIntoThisFile + " " + longStrFileToMerge;
  ////cout << command << endl;
  system(command.c_str());

  return 0;
}

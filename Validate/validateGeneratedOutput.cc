/* 
 * This code performs following simple tasks :
 * 1. First it checks if the proper arguments are passed or not (its basically a line number)
 * 2. Then it opens and reads that particular line in the Input_DB_Summary.txt file
 * 3. It then generates the names of output histogram files and saves those locally
 * -----------------------------------------------------------------------------
 * compile like this : g++ validateGeneratedOutput.cc -o validateGeneratedOutput
 * Use like this     : ./validateGeneratedOutput 1 
 * -----------------------------------------------------------------------------
 */

#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdlib> 
#include <vector>
#include <algorithm>
#include <stdlib.h>
using namespace std;

int main(int argc, char* argv[]){

  // Part 1.
  //////////////Exit if not correct number of arguments are passed////////////////////
  if(argc!=3){
    cout << "Please provide the charge and the line number to read " << endl;
    cout << "Eg. \n\t $ ./toRead_Input_DB_Summary 1 20" << endl;
    cout << "Exiting Now." << endl;
    exit(0);
  }

  cout << endl;
  cout << "-------------------------------------------" << endl << endl;
  cout << "WCharge      : "    << argv[1] << endl << endl;
  cout << "Line Number : "    << argv[2] << endl << endl;
  cout << "-------------------------------------------" << endl << endl;

  stringstrean strWCharge;
  strWCharge << argv[1]
  int WCharge = 0;
  strWCharge >> WCharge;
  if(abs(WCharge>1)){
    cout << "You entered Charge = "   << WCharge << endl; 
    cout << "It should be equal to either 1 or -1 " << endl;
    cout << "Exiting Now."                 << endl << endl;
    exit(0);
  }

  stringstream strLineNum;
  strLineNum << argv[2];
  int lineNum = 0;
  strLineNum >> lineNum;
  if(lineNum > 929) {
    cout << "You entered Line Number = "   << lineNum << endl; 
    cout << "It should be lesser than or equal to 35 " << endl;
    cout << "Exiting Now."                 << endl << endl;
    exit(0);
  }

  // Part 2.
  //////////////Begin reading the db file///////////////////////////////////////////
  ifstream inputFile("../Input_DB_Summary.txt");
  string strdoWhat, strCI, strTotEvents, strEvents, strPartition, strCurretPar, strFileName;
  vector<string> filePath;
  stringstream strStreamFileName;

  for(int i=1; i<=928; i++){
    inputFile >> strdoWhat >> strCI >> strTotEvents >> strEvents >> strPartition >> strCurretPar >> strFileName;
    if(i==lineNum){
      strStreamFileName << strFileName;
      while(getline(strStreamFileName,strFileName,'/')){  
        filePath.push_back(strFileName);
      }
    }
  }

  int counter = 0;
  counter = filePath.size()-1;
  string fileName = "";
  fileName = filePath.at(counter); 
  
  cout << "--> Reading Input Ntuple file : " << fileName << endl << endl;
  
  // Part 3.
  ////////////////////generate names of the output files/////////////////////// 
 
  // 1. trim the extension .root
  size_t found;
  found = fileName.find(".root");
  string trimmedFileName;
  trimmedFileName = fileName.substr(0,found);
  cout << "trimmedFileName : " << trimmedFileName << endl;
 
  // 2. prepare the string to append 
  stringstream beginAppendString;
  stringstream midAppendString;
  stringstream endAppendString;
  midAppendString << "_JetPtMin_30_VarWidth_BVeto_QCD";
  endAppendString << "_MET15_mT50.root";

  //3a. add Charge
  if(WCharge==1) {
    beginAppendString << "_WP";
  }
  if(WCharge==-1){
    beginAppendString << "_WM";
  }

  // 3. add EffiCorr and TrigCorr based on Data or MC
  if(trimmedFileName.find("_Data_")!=string::npos) {
    beginAppendString << "_EffiCorr_0";
    beginAppendString << "_TrigCorr_1";
  }
  else {
    beginAppendString << "_EffiCorr_1";
    beginAppendString << "_TrigCorr_1";
  }
 
  // 4. add systematics and directions based on Data and BKGDMC and SIGNALMC
  // 4a. Data
  const int NSystData(3);
  const int NSystWJets(18);
  const int NSystBkgd(12);

  short dataSyst[NSystData]  = {0, 2, 2};
  short dataDir[NSystData]   = {0,-1, 1};
  
  short wjSyst[NSystWJets]   = {0, 1, 1, 5, 5, 6, 6, 7, 7, 4, 4, 8, 9, 10, 11, 11};
  short wjDir[NSystWJets]    = {0,-1, 1,-1, 1,-1, 1,-1, 1,-1, 1, 1, 1,  1,  1, -1};

  short bgSyst[NSystBkgd]    = {0, 1, 1, 3, 3, 5, 5, 6, 6, 7, 7, 8};
  short bgDir[NSystBkgd]     = {0,-1, 1,-1, 1,-1, 1,-1, 1,-1, 1, 1};

  /////////////////save the generate histogram filenames in a separate file////////////////
  string strSaveGeneratedFileNames;  
  strSaveGeneratedFileNames = "ExpectedFiles/ExpectedFiles_";

  strSaveGeneratedFileNames = strSaveGeneratedFileNames + strLineNum.str() + ".log"; 
  ofstream outfile(strSaveGeneratedFileNames.c_str());

  if(trimmedFileName.find("_Data_")!=string::npos) {
    for(int i=0; i<NSystData; i++){
      cout << dataSyst[i] << "  " << dataDir[i] << endl;
      for(int j=0; j<4; j++){
        if (dataDir[i] == 0){
          cout    << trimmedFileName << beginAppendString.str() << "_Syst_" << dataSyst[i] << "_CN" << midAppendString.str() << j << endAppendString.str() << endl;
          outfile << trimmedFileName << beginAppendString.str() << "_Syst_" << dataSyst[i] << "_CN" << midAppendString.str() << j << endAppendString.str() << endl;
        }
        else if (dataDir[i] > 0){
          cout    << trimmedFileName << beginAppendString.str() << "_Syst_" << dataSyst[i] << "_UP" << midAppendString.str() << j << endAppendString.str() << endl;
          outfile << trimmedFileName << beginAppendString.str() << "_Syst_" << dataSyst[i] << "_UP" << midAppendString.str() << j << endAppendString.str() << endl;
        }
        else {
          cout    << trimmedFileName << beginAppendString.str() << "_Syst_" << dataSyst[i] << "_DN" << midAppendString.str() << j << endAppendString.str() << endl;
          outfile << trimmedFileName << beginAppendString.str() << "_Syst_" << dataSyst[i] << "_DN" << midAppendString.str() << j << endAppendString.str() << endl;
        }
      }
    }
  }
  else if(trimmedFileName.find("_WJetsALL_")!=string::npos) {
    for(int i=0; i<NSystWJets; i++){
      cout << wjSyst[i] << "  " << wjDir[i] << endl;
      for(int j=0; j<4; j++){
        if (wjDir[i] == 0){
          cout    << trimmedFileName << beginAppendString.str() << "_Syst_" << wjSyst[i] << "_CN" << midAppendString.str() << j << endAppendString.str() << endl;
          outfile << trimmedFileName << beginAppendString.str() << "_Syst_" << wjSyst[i] << "_CN" << midAppendString.str() << j << endAppendString.str() << endl;
        }
        else if (wjDir[i] > 0){
          cout    << trimmedFileName << beginAppendString.str() << "_Syst_" << wjSyst[i] << "_UP" << midAppendString.str() << j << endAppendString.str() << endl;
          outfile << trimmedFileName << beginAppendString.str() << "_Syst_" << wjSyst[i] << "_UP" << midAppendString.str() << j << endAppendString.str() << endl;
        }
        else {
          cout    << trimmedFileName << beginAppendString.str() << "_Syst_" << wjSyst[i] << "_DN" << midAppendString.str() << j << endAppendString.str() << endl;
          outfile << trimmedFileName << beginAppendString.str() << "_Syst_" << wjSyst[i] << "_DN" << midAppendString.str() << j << endAppendString.str() << endl;
        }
      }
    }
  }
  else {
    for(int i=0; i<NSystBkgd; i++){
      cout << bgSyst[i] << "  " << bgDir[i] << endl;
      for(int j=0; j<4; j++){
        if (bgDir[i] == 0){
          cout    << trimmedFileName << beginAppendString.str() << "_Syst_" << bgSyst[i] << "_CN" << midAppendString.str() << j << endAppendString.str() << endl;
          outfile << trimmedFileName << beginAppendString.str() << "_Syst_" << bgSyst[i] << "_CN" << midAppendString.str() << j << endAppendString.str() << endl;
        }
        else if (bgDir[i] > 0){
          cout    << trimmedFileName << beginAppendString.str() << "_Syst_" << bgSyst[i] << "_UP" << midAppendString.str() << j << endAppendString.str() << endl;
          outfile << trimmedFileName << beginAppendString.str() << "_Syst_" << bgSyst[i] << "_UP" << midAppendString.str() << j << endAppendString.str() << endl;
        }
        else {
          cout    << trimmedFileName << beginAppendString.str() << "_Syst_" << bgSyst[i] << "_DN" << midAppendString.str() << j << endAppendString.str() << endl;
          outfile << trimmedFileName << beginAppendString.str() << "_Syst_" << bgSyst[i] << "_DN" << midAppendString.str() << j << endAppendString.str() << endl;
        }
      }
    }
  }
}

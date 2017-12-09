/*
 * We want
 * /home/bsutar/t3store2/MuonChargeAsymAnalysis8TeV2012/Results/HistoFiles/Condor/102/
 * SMu_8TeV_Data_dR_5311_00001_WP_EffiCorr_0_TrigCorr_1_Syst_0_CN_JetPtMin_30_VarWidth_BVeto_QCD0_MET15_mT50.root
 */

#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <sstream>
#include <vector>
#include "generateFileNamesVectors.h"
using namespace std;

void generateFileNamesVectors(string strWCharge, string strSystematics, string strDirection, vector<string>& vectorOfGeneratedFileNames){
  
  string dirPath = "/home/bsutar/t3store2/MuonChargeAsymAnalysis8TeV2012/Results/HistoFiles/Condor/102/";
  //////////////Begin reading the db file///////////////////////
  ifstream inputFile("../Input_DB_Summary.txt");
  string strdoWhat, strCI, strTotEvents, strEvents, strPartition, strCurretPar, strFileName;
  vector<string> filePath;
  stringstream strStreamFileName;

  // decide if systematics match
  stringstream strStreamSystematics;
  strStreamSystematics << strSystematics;
  int intSystematics = 0;
  strStreamSystematics >> intSystematics;

  stringstream strStreamDirection;
  strStreamDirection << strDirection;
  int intDirection = 0;
  strStreamDirection >> intDirection;

  const int NSystData(3);
  short dataSyst[NSystData]  = {0, 2, 2};
  short dataDir[NSystData]   = {0,-1, 1};
  const int NSystWJets(18);
  short wjSyst[NSystWJets]   = {0, 1, 1, 5, 5, 6, 6, 7, 7, 4, 4, 8, 9, 10, 11, 11};
  short wjDir[NSystWJets]    = {0,-1, 1,-1, 1,-1, 1,-1, 1,-1, 1, 1, 1,  1,  1, -1};
  const int NSystBkgd(12);
  short bgSyst[NSystBkgd]    = {0, 1, 1, 3, 3, 5, 5, 6, 6, 7, 7, 8};
  short bgDir[NSystBkgd]     = {0,-1, 1,-1, 1,-1, 1,-1, 1,-1, 1, 1};

  bool validData = false;
  bool validWJets = false;
  bool validBkgd = false;

  for(int ii=0; ii<NSystData; ii++){
    if(dataSyst[ii]==intSystematics && dataDir[ii]==intDirection){
      validData = true;
    }
  }
  for(int jj=0; jj<NSystWJets; jj++){
    if(wjSyst[jj]==intSystematics && wjDir[jj]==intDirection){
      validWJets = true;
    }
  }
  for(int kk=0; kk<NSystBkgd; kk++){
    if(bgSyst[kk]==intSystematics && bgDir[kk]==intDirection){
      validBkgd = true;
    }
  }
 
  cout << "Here : " << validData << "  " << validWJets << "  " << validBkgd << endl;
  if (!validData && !validWJets && ! validBkgd){
    cout << "Passed systematics value is not among the acceptable systematics values list, exiting now." << endl << endl;
    exit(0);
  }
  
  // prepare the string to append 
  stringstream beginAppendString;
  stringstream midAppendString;
  stringstream endAppendString;

  midAppendString << "_JetPtMin_30_VarWidth_BVeto_QCD";
  endAppendString << "_MET15_mT50.root";

  for(int i=1; i<=102; i++){
  //for(int i=1; i<=3; i++){
    inputFile >> strdoWhat >> strCI >> strTotEvents >> strEvents >> strPartition >> strCurretPar >> strFileName;
    strStreamFileName << strFileName;
    while(getline(strStreamFileName,strFileName,'/')){  
      filePath.push_back(strFileName);
    }
    int counter = 0;
    counter = filePath.size()-1;
    string fileName = "";
    fileName = filePath.at(counter); 
    strStreamFileName.str(std::string());
    strStreamFileName.clear();

    ////////////////////generate names of the output files/////////////////////// 
    
    // 1. trim the extension .root
    size_t found;
    found = fileName.find(".root");
    string trimmedFileName;
    trimmedFileName = fileName.substr(0,found);
    //cout << "trimmedFileName : " << trimmedFileName << endl;
    
    // 2. add charge and EffiCorr and TrigCorr based on Data or MC
    if(strWCharge=="1") {
      beginAppendString << "_WP";
    }
    else {
      beginAppendString << "_WM";
    }

    if(trimmedFileName.find("_Data_")!=string::npos) {
      beginAppendString << "_EffiCorr_0";
      beginAppendString << "_TrigCorr_1";
    }
    else {
      beginAppendString << "_EffiCorr_1";
      beginAppendString << "_TrigCorr_1";
    }
 
    //cout << trimmedFileName << endl;
    if(trimmedFileName.find("_Data_")!=string::npos && validData) {
      for(int j=0; j<4; j++){
        if (strDirection == "0"){
          string goesInsideVector="";
          stringstream doQCD;
          doQCD << j;
          vectorOfGeneratedFileNames.push_back(dirPath + trimmedFileName + beginAppendString.str() + "_Syst_" + strSystematics + "_CN" + midAppendString.str() + doQCD.str() + endAppendString.str());
        }
        else if (strDirection == "1"){
          string goesInsideVector="";
          stringstream doQCD;
          doQCD << j;
          vectorOfGeneratedFileNames.push_back(dirPath + trimmedFileName + beginAppendString.str() + "_Syst_" + strSystematics + "_UP" + midAppendString.str() + doQCD.str() + endAppendString.str());
        }
        else {
          string goesInsideVector="";
          stringstream doQCD;
          doQCD << j;
          vectorOfGeneratedFileNames.push_back(dirPath + trimmedFileName + beginAppendString.str() + "_Syst_" + strSystematics + "_DN" + midAppendString.str() + doQCD.str() + endAppendString.str());
        }
      }
    }
    else if(trimmedFileName.find("_WJetsALL_")!=string::npos && validWJets) {
      for(int j=0; j<4; j++){
        if (strDirection == "0"){
          string goesInsideVector="";
          stringstream doQCD;
          doQCD << j;
          vectorOfGeneratedFileNames.push_back(dirPath + trimmedFileName + beginAppendString.str() + "_Syst_" + strSystematics + "_CN" + midAppendString.str() + doQCD.str() + endAppendString.str());
        }
        else if (strDirection > "1"){
          string goesInsideVector="";
          stringstream doQCD;
          doQCD << j;
          vectorOfGeneratedFileNames.push_back(dirPath + trimmedFileName + beginAppendString.str() + "_Syst_" + strSystematics + "_UP" + midAppendString.str() + doQCD.str() + endAppendString.str());
        }
        else {
          string goesInsideVector="";
          stringstream doQCD;
          doQCD << j;
          vectorOfGeneratedFileNames.push_back(dirPath + trimmedFileName + beginAppendString.str() + "_Syst_" + strSystematics + "_DN" + midAppendString.str() + doQCD.str() + endAppendString.str());
        }
      }
    }
    if(trimmedFileName.find("_Data_")==string::npos && trimmedFileName.find("_WJetsALL_")==string::npos){
      if(validBkgd){
        for(int j=0; j<4; j++){
          if (strDirection == "0"){
            string goesInsideVector="";
            stringstream doQCD;
            doQCD << j;
            vectorOfGeneratedFileNames.push_back(dirPath + trimmedFileName + beginAppendString.str() + "_Syst_" + strSystematics + "_CN" + midAppendString.str() + doQCD.str() + endAppendString.str());
          }
          else if (strDirection > "1"){
            string goesInsideVector="";
            stringstream doQCD;
            doQCD << j;
            vectorOfGeneratedFileNames.push_back(dirPath + trimmedFileName + beginAppendString.str() + "_Syst_" + strSystematics + "_UP" + midAppendString.str() + doQCD.str() + endAppendString.str());
          }
          else {
            string goesInsideVector="";
            stringstream doQCD;
            doQCD << j;
            vectorOfGeneratedFileNames.push_back(dirPath + trimmedFileName + beginAppendString.str() + "_Syst_" + strSystematics + "_DN" + midAppendString.str() + doQCD.str() + endAppendString.str());
          }
        }
      }
    }
    beginAppendString.str(std::string());
    beginAppendString.clear();
  }
}

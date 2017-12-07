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
    if(strWCharge=="-1"){
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
    if(trimmedFileName.find("_Data_")!=string::npos) {
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
    else if(trimmedFileName.find("_WJetsALL_")!=string::npos) {
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
    else {
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
    beginAppendString.str(std::string());
    beginAppendString.clear();
  }
}

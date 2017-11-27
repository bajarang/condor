#include <iostream>
#include <string>
#include <sstream>
#include "generateFileNames.h"
using namespace std;

string generateFileNames(string charge, string sample, string doQCD, string syst, string direction, string appendRange){

  //////////////////////////////
  string leptonFlavor = "SMu_";
  string energy = "8TeV_";  
  
  //////////////////////////////
  string effCorr;
  string trigCorr;
  if(sample.find("Data")!=string::npos){
    effCorr = "EffiCorr_0_";
    trigCorr = "TrigCorr_1_";
  }
  else {
    effCorr = "EffiCorr_1_";
    trigCorr = "TrigCorr_1_";
  }

  //////////////////////////////
  string strDirection;
  if(direction=="0"){
    strDirection = "CN_";
  }
  else if (direction=="1"){
    strDirection = "UP_";
  }
  else {
    strDirection = "DN_";
  }

  //////////////////////////////
  /// eg. SMu_8TeV_Data_dR_5311_00001_WP_EffiCorr_0_TrigCorr_1_Syst_0_CN_JetPtMin_30_VarWidth_BVeto_QCD0_MET15_mT50.root
  string fullFileName;
  fullFileName = leptonFlavor + energy + sample + "_dR_5311_" + appendRange  + charge + "_" + effCorr + trigCorr + "Syst_" + syst + "_" + strDirection + "JetPtMin_30_VarWidth_BVeto_QCD" + doQCD + "_MET15_mT50.root";
  cout << "Returning string : " << fullFileName << endl;
  return fullFileName;
}

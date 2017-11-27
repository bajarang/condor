#include <iostream>
#include <string>
#include <sstream>
using namespace std;

string generateFileNames(string charge, string sample, string syst, string direction, string doQCD){

  //////////////////////////////
  string leptonFlavor = "SMu_";
  string energy = "_8TeV_";  
  
  //////////////////////////////
  string effCorr;
  string trigCorr;
  if(sample.find("Data")!=string::npos){
    effCorr = "_EffiCorr_0_";
    trigCorr = "TrigCorr_1_";
  }
  else {
    effCorr = "_EffiCorr_1_";
    trigCorr = "TrigCorr_1_";
  }

  //////////////////////////////
  string strDirection;
  if(direction=="0"){
    strDirection = "CN";
  }
  else if (direction=="1"){
    strDirection = "UP";
  }
  else {
    strDirection = "DN";
  }

  //////////////////////////////
  /// eg. SMu_8TeV_Data_dR_5311_00001_WP_EffiCorr_0_TrigCorr_1_Syst_0_CN_JetPtMin_30_VarWidth_BVeto_QCD0_MET15_mT50.root
  string fullFileName;
  fullFileName = leptonFlavor + energy + sample + charge + effCorr + trigCorr + "Syst_" + syst + strDirection + "_JetPtMin_30_VarWidth_BVeto_QCD" + doQCD + "_MET15_mT50.root";
  cout << "Returning string : " << fullFileName << endl;
  return fullFileName;
}

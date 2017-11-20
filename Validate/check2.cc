/*
 * This code performs three checks
 * 1. 
 * 2. 
 * 3. 
 */

#define  DEBUG 1
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <stdlib.h> 
#include <map>
#include <iterator>
#include "TFile.h"
#include "TH1D.h"
#include "TApplication.h"
#include "TStyle.h"
using namespace std;

int main(int argc, char* argv[]){
  
  ////////////Define path of files////////////
  string pathOfGeneratedFiles="/home/bsutar/t3store/Asym2016-8TeV/Results/HistoFiles/wplus/CENTRAL/trial/";  
                    //this is where the output files are stored

  ////////////Open files containing filenames////////////////
  string pathFilesOfFilenames = "ExpectedFiles/";  //our files containing filenames are here, there are labeled as per the line numbers
                    //change this later to procFiles.log
  
  /*
  ///////////quick test begin////////////////
  TFile *f = new TFile ("/home/bsutar/t3store/Asym2016-8TeV/Results/HistoFiles/wplus/CENTRAL/trial/SMu_8TeV_Data_dR_5311_00001_EffiCorr_0_TrigCorr_1_Syst_0_CN_JetPtMin_30_VarWidth_BVeto_QCD0_MET15_mT50.root","READ");
  TH1D* h = (TH1D*)f->Get("NVtx");
  cout << h->GetEntries() << endl;
  exit(0);
  ///////////quick test over////////////////
  */ 
   
  map <string, int> mapOfSamplesEntries;  //empty map container
  //insert elements in random order
  mapOfSamplesEntries.insert(pair <string, int> ("_Data_",-1));
  mapOfSamplesEntries.insert(pair <string, int> ("_TTJets_",-1));
  mapOfSamplesEntries.insert(pair <string, int> ("_ZZ_",-1));
  mapOfSamplesEntries.insert(pair <string, int> ("_WZ_",-1));
  mapOfSamplesEntries.insert(pair <string, int> ("_WW_",-1));
  mapOfSamplesEntries.insert(pair <string, int> ("_T_s_",-1));
  mapOfSamplesEntries.insert(pair <string, int> ("_T_t_",-1));
  mapOfSamplesEntries.insert(pair <string, int> ("_T_tW_",-1));
  mapOfSamplesEntries.insert(pair <string, int> ("_Tbar_s_",-1));
  mapOfSamplesEntries.insert(pair <string, int> ("_Tbar_t_",-1));
  mapOfSamplesEntries.insert(pair <string, int> ("_Tbar_tW_",-1));
  mapOfSamplesEntries.insert(pair <string, int> ("_DYJets10to50_",-1));
  mapOfSamplesEntries.insert(pair <string, int> ("_WJetsALL_",-1));
  //////////loop for opening each file (containing filenames) here//////////
  for(int fileNum=1; fileNum<=35; fileNum++){ ////UNCOMMENT
                    //change to this full list later
  ////for(int fileNum=1; fileNum<2; fileNum++){
    stringstream strStreamLineNum;
    strStreamLineNum << fileNum;
    string strFileName = pathFilesOfFilenames + "ExpectedFiles_" + strStreamLineNum.str() + ".log";
    //count line numbers in such numbered file, this is needed because we want to run a loop later over it
    string command = "wc -l ";
    string prefixFileName = strFileName + " > counter.txt"; 
    command = command + prefixFileName.c_str();
    system(command.c_str()); 
    ifstream counterFile("counter.txt");
    int lineCounter = 0;
    string lineContent;
    counterFile >> lineCounter >> lineContent; 
    cout << "There are " << lineCounter <<  " lines inside : " << strFileName << endl;
    counterFile.close();
    //now open each file and read filename 
    ifstream infile(strFileName.c_str());
    
    
    //for(int lineNum=1; lineNum<=lineCounter; lineNum++) ////UNCOMMENT
    for(int lineNum=1; lineNum<2; lineNum++){
      string strFullFileName;
      infile >> strFullFileName;
      map <string, int> :: iterator itr;
      
      for(itr = mapOfSamplesEntries.begin(); itr != mapOfSamplesEntries.end(); ++itr){
        if(strFullFileName.find(itr->first)!=string::npos && strFullFileName.find("Syst_0_CN_JetPtMin_30_VarWidth_BVeto_QCD0")!=string::npos){
          strFullFileName = pathOfGeneratedFiles + strFullFileName;
          cout << strFullFileName << endl;
          TFile *inrootfile = new TFile(strFullFileName.c_str(),"READ");
          if(!inrootfile) cout << "Error opening file : " << strFullFileName << endl;
          if(inrootfile){
            if (DEBUG) cout << "Opening File : " << strFullFileName << endl;
            TH1D *h = (TH1D*)inrootfile->Get("NVtx"); 
            if(itr->second == -1 ){
              itr->second = itr->second + h->GetEntries() + 1;
            }
            else{
              itr->second = itr->second + h->GetEntries();
            }
            cout << itr->first << "  " << itr->second << endl;
          }
           
          inrootfile->Close();
        }
      }
      strFullFileName=""; 
    }
     
  }
  
  map <string, int> :: iterator itrOut;
  for(itrOut = mapOfSamplesEntries.begin(); itrOut != mapOfSamplesEntries.end(); ++itrOut){
    cout << "Final Entries in : " << setw(20) << itrOut->first  << "  =  " << setw(10) << itrOut->second << endl;
  }
   
  return 0;
  
}

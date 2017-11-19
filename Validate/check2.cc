/*
 * This code performs three checks
 * 1. Finds out corrupted files (easy check)
 * 2. Finds out empty plots     (easy check)
 * 3. Adds all the events and compares with total (logic needed to add certain set of files)
 */

#define  DEBUG 1
#include <iostream>
#include <fstream>
#include <sstream>
#include <stdlib.h> 
#include "TFile.h"
#include "TH1D.h"
#include "TApplication.h"
#include "TStyle.h"
using namespace std;

int main(int argc, char* argv[]){
  
  // 1. FIND OUT CORRUPTED FILES (EACH CHECK) 
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
  
  //////////loop for opening each file (containing filenames) here//////////
  for(int fileNum=1; fileNum<=35; fileNum++){
                    //change to this full list later
  ////for(int fileNum=1; fileNum<2; fileNum++){
    stringstream strStreamLineNum;
    strStreamLineNum << fileNum;
    string strFileName = pathFilesOfFilenames + "ExpectedFiles_" + strStreamLineNum.str() + ".log";
    //count line numbers in such numbered file, this is needed because we want to run a loop later over it
    string command = "wc -l ";
    string prefixFileName = strFileName + " > counter.txt"; 
    command = command + prefixFileName.c_str();
    system(command.c_str() ); 
    ifstream counterFile("counter.txt");
    int lineCounter = 0;
    string lineContent;
    counterFile >> lineCounter >> lineContent; 
    cout << "There are "<< lineCounter <<  " lines inside : " << strFileName << endl;
    counterFile.close();
    //now open each file and read filename 
    ifstream infile(strFileName.c_str());
    
    for(int lineNum=1; lineNum<=lineCounter; lineNum++){
    ////for(int lineNum=1; lineNum<2; lineNum++){
      string strFullFileName;
      infile >> strFullFileName;
      if(strFullFileName.find("Syst_0_CN_JetPtMin_30_VarWidth_BVeto_QCD0")!=string::npos){
        strFullFileName = pathOfGeneratedFiles + strFullFileName;
        cout << strFullFileName << endl;
        TFile *inrootfile = new TFile(strFullFileName.c_str(),"READ");
        if(!inrootfile) cout << "Error opening file : " << strFullFileName << endl;
        if(inrootfile){
          if (DEBUG) cout << "Opening File : " << strFullFileName << endl;
          TH1D *h = (TH1D*)inrootfile->Get("NVtx"); 
          double entries=0.0;
          entries = h->GetEntries();
          cout << entries << endl;
        } 
        inrootfile->Close();
      }
    } 
  } 
  
 
  // 2. ADDS ALL THE EVENTS AND COMPARES WITH TOTAL (LOGIC NEEDED TO ADD CERTAIN SET OF FILES)
  ////////////Explain logic here////////////////
  // As we have split the ntuples we will have to add up the respective  
  // nentries histogram for smaller 
  
  return 0;

}

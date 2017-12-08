/*
 * Pass three arguments to this code and then if performs three checks
 * 1. Splits which files are unprocessed and halts from further processing
 * 2. Tells whether the generated root files are not corrupt, if yes then halts
 * 3. Counts the number of events, if does not match from expected then halts
 * Compile with : $ g++ check2.cc -o check2 `root-config --glibs --cflags`
 * Run     with : $ ./check2 systematics direction
 * ************  WARNING USE LATEST VERSION OF ROOT ************ 
 */

#define  DEBUG 1
#define  quickTest 0
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <stdlib.h> 
#include <map>
#include <iterator>
#include <sys/stat.h>
#include <ctime>
#include "generateFileNamesVectors.h" 
#include "TFile.h"
#include "TH1D.h"
#include "TApplication.h"
#include "TStyle.h"

using namespace std;

int main(int argc, char* argv[]){
  
  
  // 0a. Checks if correct arguments are passed or not
  if(argc!=4){
    cout << "Please provide the charge, systematics and direction values as arguments" << endl;
    cout << "Eg. \n\t $ ./check2 1 0 0" << endl;
    cout << "Whether those values are within bound or not, this code will tell" << endl;
    cout << "Exiting Now." << endl;
    exit(0);
  }

  // 0b. Check if charge value is valid
  string strWCharge = argv[1];
  if(strWCharge!="1" && strWCharge!="-1"){
    cout << "Please pass either 1 or -1 for charge, exiting now." << endl;
    exit(0);
  }

  // 0c. Check if systematics and direction values are valid 
  bool validSyst = false;
  string strSystematics;
  strSystematics = argv[2];
  stringstream strStreamSystematics;
  strStreamSystematics << strSystematics;
  int intSystematics;
  strStreamSystematics >> intSystematics;

  bool validDir = false;
  string strDirection;
  strDirection = argv[3];
  stringstream strStreamDirection;
  strStreamDirection << strDirection;
  int intDirection;
  strStreamDirection >> intDirection;

  const int nPossibleSyst(20);
  short possibleSystList[nPossibleSyst] = {0, 1, 1, 2, 2, 3, 3, 4, 4, 5, 5, 6, 6, 7, 7, 8, 9, 10, 11, 11};
  short possibleDirList[nPossibleSyst]  = {0,-1, 1,-1, 1,-1, 1,-1, 1,-1, 1,-1, 1,-1, 1, 1, 1,  1,  1, -1};

  for(int ii=0; ii<nPossibleSyst; ii++){
    if(possibleSystList[ii]==intSystematics && possibleDirList[ii]==intDirection){
      validSyst = true; validDir = true;
    }
    if (validSyst && validDir) continue; 
  }
  if (!validSyst && !validDir){
    cout << "Passed systematics value is not among the acceptable systematics values list, exiting now." << endl << endl;
    exit(0);
  }

  // 1. Splits which files are unprocessed and halts from further checks
  // 1a. Begin generating filenames, make use of Input_DB_Summary file
  // 1ai. Based on the values of charge, systematics and direction, generate filenames
  vector<string> vectorOfGeneratedFileNames;
  generateFileNamesVectors(strWCharge, strSystematics, strDirection, vectorOfGeneratedFileNames);

  string storeUnpFiles = "UnprocessedFiles/UnprocessedFiles.txt";
  ofstream unpFiles;
  unpFiles.open(storeUnpFiles.c_str(), std::ios_base::app); //append this file
  //generate time stamp
  time_t rawtime;
  struct tm *timeinfo;
  char buffer[80];
  time (&rawtime);
  timeinfo = localtime(&rawtime);
  strftime(buffer,sizeof(buffer),"%d-%m-%Y %I:%M:%S",timeinfo);
  std::string str(buffer);
  unpFiles << str << endl; 
  bool unpProcessedFilesExist = false;
  for(int ii=0; ii<vectorOfGeneratedFileNames.size(); ii++){ 
    string filename;
    filename = vectorOfGeneratedFileNames.at(ii);
    struct stat buf;
    if (stat(filename.c_str(), &buf) != -1){
      //cout << filename << " --> file exists." << endl;
    }
    else{
      cout << filename << " --> file does not exist." << endl;
      unpFiles << filename << endl; //store the unprocessed filenames
      unpProcessedFilesExist = true;
    }
  }
  
  if(unpProcessedFilesExist) {
    cout << "Unprocessed file(s) exist, please visit " <<  storeUnpFiles << " for more details, check the time-stamp" << endl;
    cout << "Exiting now." << endl;
    exit(0);
  } 
   
  
  // 2. Tells whether the generated root files are not corrupt and count events
  string sampleList[14]    = {"_Data_","_TTJets_","_ZZ_","_WZ_","_WW_","_T_s_","_T_t_","_T_tW_","_Tbar_s_",
                              "_Tbar_t_","_Tbar_tW_","_DYJets10to50_","_DYJets_MIX","_WJetsALL_"};

  int sampleListEvents[4][14] = {{0}};

  for(int ii=0; ii<vectorOfGeneratedFileNames.size(); ii++){ 
    string filename;
    filename = vectorOfGeneratedFileNames.at(ii);
    TFile *inrootfile = new TFile (filename.c_str(),"READ");
    if(!inrootfile) cout << "Error opening file : " << filename << endl;
    else{
      for(int jj=0; jj<14; jj++){
        for(int kk=0; kk<4; kk++){
          string strDoQCD="QCD";
          stringstream strStreamDoQCD;
          strStreamDoQCD << strDoQCD;
          strStreamDoQCD << kk;
          strDoQCD = strStreamDoQCD.str();
          if(filename.find(sampleList[jj])!=string::npos && filename.find(strDoQCD)!=string::npos){
            //TH1D *h = (TH1D*)inrootfile->Get("nentries"); 
            TH1D *h = (TH1D*)inrootfile->Get("lepEta_Zinc0jet"); 
            sampleListEvents[kk][jj] = sampleListEvents[kk][jj] + h->GetEntries();         
          }
        }
      }
    }
    inrootfile->Close();
  }
  
  // 3. Counts the number of events, if does not match from expected then halts
  double nentries[14] = {115698277,1069869,253413,640592,991539,18887,269558,71509,10279,146031,70718,120533,16804803,47601882};
  for(int kk=0; kk<4; kk++){
    string strDoQCD="QCD";
    stringstream strStreamDoQCD;
    strStreamDoQCD << strDoQCD;
    strStreamDoQCD << kk;
    strDoQCD = strStreamDoQCD.str();
    cout << "*******************************************************" << endl;
    cout << "                    " << strDoQCD << "                 " << endl; 
    cout << "-------------------------------------------------------" << endl;
    cout << setw(20) << left << "Sample" << setw(20) << left << "Obtained" << setw(20) << left << "Expected" << endl;
    cout << "-------------------------------------------------------" << endl;
    for(int jj=0; jj<14; jj++){
      cout << fixed << setprecision(0) << setw(20) << left << sampleList[jj] << setw(20) << left << sampleListEvents[kk][jj] << setw(20) << left << nentries[jj] << endl;
    }
    cout << "-------------------------------------------------------" << endl;
  }
  cout << endl;
  cout << "Please visit this file to see if any jobs have failed or not, check the time-stamp --> " << endl;
  cout << storeUnpFiles << endl;
  cout << endl;
  return 0;
  
}

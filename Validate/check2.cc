/*
 * Pass three arguments to this code and then if performs three checks
 * 1. Splits which files are unprocessed and halts from further processing
 * 2. Tells whether the generated root files are not corrupt, if yes then halts
 * 3. Counts the number of events, if does not match from expected then halts
 * Compile with : $ g++ check2.cc -o check2 `root-config --glibs --cflags`
 * Run     with : $ ./check2 systematics direction
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
      cout << filename << " --> file exists." << endl;
    }
    else{
      cout << filename << " --> file does not exist." << endl;
      unpFiles << filename << endl; //store the unprocessed filenames
      unpProcessedFilesExist = true;
    }
  }
  if(unpProcessedFilesExist) {
    cout << "Unprocessed file(s) exist, please visit " << unpFiles << " for more details, check the time-stamp" << endl;
    cout << "Exiting now." << endl;
    exit(0);
  } 

  // 2. Tells whether the generated root files are not corrupt, if yes then halts



  // 3. Counts the number of events, if does not match from expected then halts
  
  /*
  string dirOfOutputFiles="/home/bsutar/t3store/Asym2016-8TeV/Results/HistoFiles/wplus/CENTRAL/102/";  
  
  if(quickTest) {
    TFile *f = new TFile ("/home/bsutar/t3store/Asym2016-8TeV/Results/HistoFiles/wplus/CENTRAL/trial/SMu_8TeV_Data_dR_5311_00001_EffiCorr_0_TrigCorr_1_Syst_0_CN_JetPtMin_30_VarWidth_BVeto_QCD0_MET15_mT50.root","READ");
    TH1D* h = (TH1D*)f->Get("NVtx");
    cout << h->GetEntries() << endl;
    exit(0);
  }


  /////////////////later//////////////////  
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
            //TH1D *h = (TH1D*)inrootfile->Get("NVtx"); 
            TH1D *h = (TH1D*)inrootfile->Get("nentries"); 
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
  
  int counter = 0;
  double nentries[14] = {60000,60000,60000,60000,60000,60000,60000,60000,60000,60000,60000,60000,60000,60000};
  map <string, int> :: iterator itrOut;
  for(itrOut = mapOfSamplesEntries.begin(); itrOut != mapOfSamplesEntries.end(); ++itrOut){
    cout << "Final Entries in : " << setw(20) << itrOut->first  << "  =  " << setw(10) << itrOut->second << " Original nentries : " << nentries[counter] << endl;
    counter++;
  }
  */   
  return 0;
  
}

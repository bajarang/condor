#include "TROOT.h"
#include "TFile.h"
#include <iostream>
#include <string>
#include <vector>
#include "TH1F.h"
#include "TFile.h"
#include "TStyle.h"
#include "TCanvas.h"
#include "TLegend.h"
#include "TMath.h"

//*** Very Important: Please make sure to invoke ROOT version >=6.05 
//*** for executing the following macro. It DOES NOT work for ROOT version 5.x
//Method 1: This method require root version 6.06 onward and managed by python script given by ROOT
//Please note: a) "tree" in source file is in directory tree ("tree/tree")
//             b) In the destination file tree is written after creating this directory

//If you don't like this then follow Method 2
//For Method 2; comment out Method 1 (Lines 68-158) and uncomment Method 2: Lines 160-197

void split_02() { 
  int  doWhatType[14];
  int  idivision = 200000; 

  string input_path, output_path;
  string input_file[14], output_file;
  string extn1, extn2, fin, fout;
  char   temp_in[300], temp_out[300];

  extn1 = ".root";  extn2= "_00001";
  input_path  = "/home/bsutar/t3store2/Asym8TeV/DataW/";
  output_path = "/home/bsutar/t3store2/Asym8TeV/DataW/split_root_files/";

  input_file[0]  = "SMu_8TeV_Data_dR_5311";                       //Data Sample
  input_file[1]  = "SMu_8TeV_TTJets_dR_5311";
  input_file[2]  = "SMu_8TeV_ZZ_dR_5311";
  input_file[3]  = "SMu_8TeV_WZ_dR_5311";
  input_file[4]  = "SMu_8TeV_WW_dR_5311";
  input_file[5]  = "SMu_8TeV_T_s_channel_dR_5311";
  input_file[6]  = "SMu_8TeV_T_t_channel_dR_5311";
  input_file[7]  = "SMu_8TeV_T_tW_channel_dR_5311";
  input_file[8]  = "SMu_8TeV_Tbar_s_channel_dR_5311";
  input_file[9]  = "SMu_8TeV_Tbar_t_channel_dR_5311";
  input_file[10] = "SMu_8TeV_Tbar_tW_channel_dR_5311";
  input_file[11] = "SMu_8TeV_DYJets10to50_dR_5311";
  input_file[12] = "SMu_8TeV_DYJets_MIX_UNFOLDING_dR_5311_Inf3";
  input_file[13] = "SMu_8TeV_WJetsALL_MIX_UNFOLDING_dR_5311";      //Signal MC Sample

  doWhatType[0]  = 0; //Collision Data
  doWhatType[1]  = 1; //Backround MC Data
  doWhatType[2]  = 1; //Backround MC Data
  doWhatType[3]  = 1; //Backround MC Data
  doWhatType[4]  = 1; //Backround MC Data
  doWhatType[5]  = 1; //Backround MC Data
  doWhatType[6]  = 1; //Backround MC Data
  doWhatType[7]  = 1; //Backround MC Data
  doWhatType[8]  = 1; //Backround MC Data
  doWhatType[9]  = 1; //Backround MC Data
  doWhatType[10] = 1; //Backround MC Data
  doWhatType[11] = 1; //Backround MC Data
  doWhatType[12] = 2; //DY_MIX MC Data
  doWhatType[13] = 3; //Signal MC Data (This file contains generator level data as well)

  ofstream ofs("Input_DB_Summary.txt");


  //Method 1: First method to split root file. Use Method 2 is 
  //there are any problems with this method
  int iCount_T=0;
  for(int iFile=0; iFile<14; iFile++){

    int iDoWhat = doWhatType[iFile];

    std::stringstream idw;  idw  << iDoWhat;
    string a3 = "0000" + idw.str();
    int isize3 = a3.size();
    string b3 = a3.substr(isize3-5, 5) + "   ";

    fin  = input_path  + input_file[iFile] + extn1;
    strcpy(temp_in,  fin.c_str());

    TFile *input_rfile = new TFile(temp_in);
    TTree *tree = (TTree*)input_rfile->Get("tree/tree");

    int iTotal = tree->GetEntries();
    int iSplit = iTotal/idivision +1;
    cout << iTotal << "   iSplit=" << iSplit << endl;
    input_rfile->Close();

    std::stringstream iTEvt;  iTEvt << iTotal;
    string a4 = "0000000000" + iTEvt.str();
    int isize4 = a4.size();
    string b4 = a4.substr(isize4-10, 10) + "   ";

    std::stringstream iTSplit;  iTSplit << iSplit;
    string a5 = "00000" + iTSplit.str();
    int isize5 = a5.size();
    string b5 = a5.substr(isize5-5, 5) + "   ";

    //////for(int i=1; (i<iSplit+1 && i<4); i++){
    for(int i=1; i<(iSplit+1); i++){
      int i1 = (i-1)*idivision + 1;
      int i2 = i1 + idivision - 1;
      if(i2>iTotal){i2=iTotal-1;}

      std::stringstream ss1; ss1 << i1;
      std::stringstream ss2; ss2 << i2;

      std::stringstream ss;  ss  << i;
      string a1 = "0000" + ss.str();
      int isize = a1.size();
      string b1 = a1.substr(isize-5, 5);
      
      iCount_T++;
      std::stringstream ss3;  ss3<<iCount_T;
      string a2 = "0000" + ss3.str();
      int isize2 = a2.size();
      string b2 = a2.substr(isize2-5, 5) + "   ";

      
      extn2 = "_" + b1;
      fout = output_path + input_file[iFile] + extn2 + extn1;

      //First create the directory and then copy tree in that directory
      string fout1 = fout + ":tree";
      string tmp1 = "rootmkdir " + fout1;
      gSystem->Exec(tmp1.c_str());
      string cmd1 = "rooteventselector --first " + ss1.str() + " --last " + ss2.str() + " " + fin + ":tree/tree " + fout1;
      gSystem->Exec(cmd1.c_str());
      cout << cmd1 << endl;


      std::stringstream ss4;  ss4<<idivision;
      string a6 = "0000" + ss4.str();
      int isize6 = a6.size();
      string b6 = a6.substr(isize6-6, 6) + "   ";
      cout << isize6 << endl;

      //b3=doWhat
      //b2=Current Cumulative File Count over all input files
      //b4=Total number of events in a given input file
      //b6=Number of events per partition (fragmented file)
      //b5=Total number of Split files for a given input file
      //b1=Current Split file Count for a given input file

      string cmd2 = b3 + b2 + b4+ b6 + b5 + b1 + "  " + fout;
      ofs  << cmd2 << endl;
      cout << cmd2 << endl;

      //Directly copy tree without any directory structure
      //string cmd2 = "rooteventselector --first " + ss1.str() + " --last " + ss2.str() + " " + fin + ":tree/tree " + fout;
      //gSystem->Exec(cmd2.c_str());
      //cout << cmd2 << endl;

    } //Split Loop
  }  //Input File Loop

  ofs.close();

/*
  //Method 2: Second method to split root file if Method 1 does not work

  TFile *input_rfile = new TFile(temp_in);
  TTree *tree = (TTree*)input_rfile->Get("tree/tree");
  int iTotal = tree->GetEntries();
  int iSplit = iTotal/idivision +1;
  cout << iTotal << "   iSplit=" << iSplit << endl;
  input_rfile->Close();

  fout = output_path + input_file + extn2 + extn1;
  strcpy(temp_out, fout.c_str());
  TFile *output_rfile = new TFile(temp_out, "RECREATE");
  TTree *outTree      = (TTree*)tree->CloneTree(0); 

  int icnt=1;
  for(int i=0; (i<iTotal && i<21000); i++){
    tree->GetEntry(i);
    outTree->Fill();
    int idx = i%idivision;
    if(idx==0 && i>0){
     output_rfile->Write();   output_rfile->Close();
     icnt++;
     std::stringstream ss; ss << icnt;
     string a1 = "0000" + ss.str();
     int isize = a1.size();
     extn2 = "_" + a1.substr(isize-5, 5);
     fout = output_path + input_file + extn2 + extn1;
     strcpy(temp_out, fout.c_str());
     output_rfile = new TFile(temp_out, "RECREATE");
     outTree      = (TTree*)tree->CloneTree(0);
     cout << temp_out << endl;
    }
  }
  input_rfile->Close();
  output_rfile->Write();   output_rfile->Close();
  cout << iTotal << endl;
*/

  exit(0);

  //TFile * origin = new TFile("origin.root");
  //TTree *tree = (TTree*)origin->Get("myMiniTreeProducer/MyTree");
  //tree->Print();

}

/*
  The eos path to all these files is : /eos/cms/store/group/phys_smp/WPlusJets/NtuplesTomislavNEW/
   1.    32G  SMu_8TeV_Data_dR_5311.root
   2.   899M  SMu_8TeV_TTJets_dR_5311.root
   3.   173M  SMu_8TeV_ZZ_dR_5311.root
   4.   408M  SMu_8TeV_WZ_dR_5311.root
   5.   622M  SMu_8TeV_WW_dR_5311.root
   6.    14M  SMu_8TeV_T_s_channel_dR_5311.root
   7.   185M  SMu_8TeV_T_t_channel_dR_5311.root
   8.    54M  SMu_8TeV_T_tW_channel_dR_5311.root
   9.   7.4M  SMu_8TeV_Tbar_s_channel_dR_5311.root
  10.   101M  SMu_8TeV_Tbar_t_channel_dR_5311.root
  11.    54M  SMu_8TeV_Tbar_tW_channel_dR_5311.root
  12.    69M  SMu_8TeV_DYJets10to50_dR_5311.root
  13.    16M  SMu_8TeV_DYJets_MIX_UNFOLDING_dR_5311_Inf3.root
  14.    32G  SMu_8TeV_WJetsALL_MIX_UNFOLDING_dR_5311.root

  Download these files with the command :
  $ voms-proxy-init --voms cms 
  $ xrdcp root://cms-xrd-global.cern.ch:///eos/cms/store/group/phys_smp/WPlusJets/NtuplesTomislavNEW/filename .
*/

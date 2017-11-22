# Validation Codes  


###---   Validating whether all the condor jobs are run successfully   ---###

We perform two steps check as described below.  

0. In this 0th step (which is to be performed only once) we create the expected filenames.  
   Code    : condor/Validate/validateGeneratedOutput.cc  
   Compile : g++ validateGeneratedOutput.cc -o validateGeneratedOutput  
   Run     : ./validateGeneratedOutput 1  
             here 1 is the argument passed which is basically a line number of the Input_DB_Summary.txt  
   Flow    : a. First we check if the argument (which is a line number) is passed or not.  
             b. Then we open Input_DB_Summary and assign the filname inside it to a variable  
             c. Based on the substring of the filename, we generate expected filenames for all the possibilities  
   Eg.     : a. If this substring exists "_Data_", it will generate 12 expected filenames,   
                4 for Syst_0_CN with doQCD=0..3  
                4 for Syst_2_UP with doQCD=0..3  
                4 for Syst_2_DN with doQCD=0..3  
             b. If this substring exists "_WJetsALL_", it will generate 72 expected filenames,  
                4 for Syst_0_CN with doQCD=0..3  
                and 18 other possibilities for systematics  
             c. And for all the other cases (bkgd MC), it will generate 48 expected filenames  
   Output  : Output filenames are stored in ExpectedFiles/ExpectedFiles_N.log where N=1..35  
  
  
1. In this first check, we see if all the files with desired names are present or not.  
   Code    : condor/Validate/getUnProcNtuples.py  
   Run     : python getUnProcNtuples.py  
   Flow    : We pass two input files  
             a. Any one file from ExpectedFiles/ExpectedFiles_N.log and  
             b. procprocNtuples_N.log (which we obtain by ls and redirection inside the folder where all the   
                root files are produced)  
             This code then compares the two strings inside those two files and it outputs the one not matching  
             and stores it inside unProcNtuples_N.log file. We re-generate these jobs once again using condor.  
            
  
2. In this second step we check if the condor-generated files are not corrupted and also if the summation  
   of nentries histogram add up to the total entries.  
   Code    : condor/Validate/check2.cc  
   Compile : g++ check2.cc -o check2 `root-config --glibs --cflags`  
   Run     : ./check2  
   Flow    : a. First we define a c++ map of strings and ints (14 strings for identifying which sample it is  
                and 14 integers which will be updated later with the summation of all the GetEntries of the  
                respective histograms)  
             b. Open all the ExpectedFiles/ExpectedFiles_N.log (N=1..35) where each of these files have the expected  
                filenames  
                We count the line numbers of each of these ExpectedFiles_N.log files  
                There are 12 lines for _Data_.._00001, 12 for _Data_.._00002 etc.  
                There are 48 lines for all the bkgd MCs  
                and there are 72 lines for all the Signal MCs  
             c. We then read the content of ExpectedFiles_N.log file (which is basically the root filenames)  
                We open those read files, if there is problem in opening the rootfiles, it prints error and exits.  
                When all the file open errors are resolved we go on to add the nentries of the nentries histogram  
                We update the corresponding value term of the c++ map  
             d. Finally we print the added nentries for all the small ouput histogram files and also the total nentries  
                This way we come to know if we have processed correct number of events with our condor framework.  

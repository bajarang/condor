# Validation Codes  


1. First we generate the filenames that we must expect condor to create  
   This is performed by the code  
   validateGeneratedOutput.cc  
   Compile this code like this :
   $ g++ validateGeneratedOutput.cc -o validateGeneratedOutput  
   And run like this :  
   $ ./validateGeneratedOutput 1  
   This will create a directory  ExpectedFiles/ inside of which the files listing the  
   expected filenames    

2. Then we check if we condor has generated all the required files or not with this code  
   getUnProcNtuples.py
   Run it like this  
   $ python getUnProcNtuples.py  
   There are two input files required for this code  
   a. procNtuples.log and b. ExpectedFiles/ExpectedFiles_N.log (N=1,2,...,35)  
   where procNtuples.log is obtained by doing ls in output directory of histograms  
   and ExpectedFiles/ExpectedFiles_N.log are generated in the first step above  
   
   

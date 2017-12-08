# Validation Codes  


###---   Validating whether all the condor jobs are run successfully   ---###

We perform the check whether  
  1. all the condor jobs were successful (by looking at the generated files)  
  2. the generated files are not corrupted  
  3. and counting the nentries integral expecting to match with the expectec number  
of events   
by using this code --> check2.cc    
This code expects three arguments, charge, systematics and direction value  

Compile it with :  
$ g++ check2.cc -o check2 generateFileNamesVectors.cc `root-config --glibs --cflags`  

Run it with :  
$ ./check2 1 0 0   (for w+, sytematics 0 and no direction) 
or  
$ ./check2 -1 1 -1  (for w-, systematics 1 and down direction)  etc...  

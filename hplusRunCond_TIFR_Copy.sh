#!/bin/bash
#REFERENCE
#https://github.com/florez/CONDOR

#//////////////////////////////////////
#                                     #
# hplusCond.sub runs hplusAnalyzer_TIFR.sh #
# hplusAnalyzer_TIFR.sh runs runMe.sh      #
# runMe.sh runs hplusAnalyzer.C       #
#                                     #
#//////////////////////////////////////

#------------------------------------------------
#create a directory where all the outputs will be
#stored, for different merged ntuple input files
#------------------------------------------------
ntupleT2Paths=$1




#------------------------------------------------
#read the file, where paths of ntuples are stored
#do not put empty lines in mergedNtupleT2.txt
#------------------------------------------------
count=0
cat $ntupleT2Paths | while read ntupleT2Path
do
  #----------------------------------------------
  #print T2Paths of ntuple, on terminal
  #split the T2Paths of ntuples, into an array
  #get the  second last entry of the array
  #remove .root, from the input ntuple
  #----------------------------------------------
  ((count++))
  echo -e "input ntuple=" $count": " $ntupleT2Path
  IFS='/ ' read -r -a array <<< "$ntupleT2Path"
  len=${#array[@]}
  #sec_last=`expr $len - 1`
  sec_last=`expr $len`
  ntuple=${array[$sec_last]}
  echo $ntuple
  iFile=${ntuple/.root/""}
 
  
done

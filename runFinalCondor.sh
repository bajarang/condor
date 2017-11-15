#!/bin/bash

###//////////////////////////////////////////###
###                                          ###
###  Script to run the condor jobs in one go ###
###                                          ###
###//////////////////////////////////////////###

###--- variable to store Input_DB_Summary.txt ---###
Input_DB_Summary_File="Input_DB_Summary.txt" # variable for DB file
totalLineNum=($(cat $Input_DB_Summary_File | wc -l))                      # count the total number of lines in DB file
echo "Total Number of Lines in " $Input_DB_Summary_File " = " $totalLineNum

###--- parse the command line arguments ---###
lineNum=$1
doQCD=$2
systematics=$3
direction=$4

###--- if illegal number of parameters are passed, exit with message ---###
if [ "$#" -ne 1 ] && [ "$#" -ne 2 ] && [ "$#" -ne 3 ] && [ "$#" -ne 4 ]
then
  echo "Illegal number of parameters"
  echo "Pass at least 2 or 3 or 4 parameters to this script"
  echo "Exiting Now."
  return 0 
fi

###--- some default parameters ---###
allSystematics="100"
allDirection="100"

###--- If incorrect line number is entered, exit with message ---###
echo "You entered Line Number = " $lineNum
if [ $lineNum -gt $totalLineNum ]   
then
  echo "It should be lesser than " $totalLineNum 
  echo "Exiting Now. "
  return 0 
fi

###--- If incorrect doQCD number is entered, exit with message ---###
echo "You entered doQCD = " $doQCD
if [ -z "$doQCD" ] 
then
  echo "You did not enter doQCD, we are running for all the doQCD options"
else
  if [ $doQCD -gt 3 ]
  then
    echo "It should be lesser than 3"  
    echo "Exiting Now. "
    return 0 
  fi
fi

###--- check systematics and direction values, take decisions accordingly ---###
echo "You entered systematics = " $systematics "  and direction = " $direction
if [ -z "$systematics" ] && [ -z "$direction" ]
then
  echo "You did not enter systematics and direction, we are running for default full systematics and both directions"
elif [ -z "$direction" ]
then
  echo "You did not enter direction, we are running for default Up and Down directions"
else 
  echo 
fi

source /cvmfs/cms.cern.ch/cmsset_default.sh
eval `scram runtime -sh`
###voms-proxy-init --voms cms   ###UNCOMMENT THIS
###cp /tmp/x509up_u51603 ~/     ###UNCOMMENT THIS

#--- create log directory ---#
log="log_"
logDir=$log${Input_DB_Summary_File/.txt/""}
baseDir="/home/bsutar/t3store2/condor/condor_log/" # provide base path for log directory 
mkdir $baseDir$logDir               # make a proper log directory 
outcond="$baseDir$logDir"           # assign a variable to log directory
echo "Visit this log directory : " $outcond
#--- copy related files to log directory for future reference ---#
runCond="runCond.sub"
cp $runCond $outcond             # 1. cond submit script
cp runAnalysis.sh $outcond          # 2. script where we pass our parameters on the command line 
cp $Input_DB_Summary_File $outcond  # 3. Input_DB_Summary.txt file 
cd $outcond                         # we are inside log directory now

######------ WE ARE INSIDE LOG DIRECTORY NOW ------######
###--- read Input_DB_Summary.txt ---###
count=0                             # line counter

cat $Input_DB_Summary_File | while read ntupleT2Path
do
  #----------------------------------------------
  # 1. print T2Paths of ntuple, on terminal
  # 2. split the T2Paths of ntuples, into an array
  # 3. get the last entry of the array
  # 4. remove .root, from the input ntuple
  #----------------------------------------------
  ((count++))
  #echo -e "input ntuple=" $count": " $ntupleT2Path
  IFS=' ' read -r -a array <<< "$ntupleT2Path"  # neglect the spaces within entries
  len=${#array[@]}                  # must be 6 as of now
  var1=`expr 0 `                    # dowhat (do not be bothered)
  var2=`expr 1 `                    # serial number (of interest)
  var3=`expr 2 `                    # total number of events (dnbb)
  var4=`expr 3 `                    # number of events (dnbb)
  var5=`expr 4 `                    # partitions (dnbb)
  var6=`expr 5 `                    # Current partition number (dnbb)
  var7=`expr 6 `                    # path to the ntuples (this if of interest)
  col1=${array[$var1]}  
  col2=${array[$var2]}
  col3=${array[$var3]}
  col4=${array[$var4]}
  col5=${array[$var5]}
  col6=${array[$var6]}
  col7=${array[$var7]}
  if [ $col2 -ne $lineNum ]
  then
    continue
  else
    #echo -e "input ntuple=" $count": " $ntupleT2Path
    #echo $col1 $col2 $col3 $col4 $col5 $col6 $col7
    IFS='/' read -r -a array2 <<< "$col7"  # trim the path to the ntuples
    len2=${#array2[@]}                # must be --
    last=`expr $len2 - 1`             # number of last element of the array 
    ntuple=${array2[$last]}           # ntuple name
    iFile=${ntuple/.root/""}          # trim root from ntuple name
 
    #----------------------------------------------
    #copy condor scripts to each input ntuple dir
    #replace runCond.sub arguments, as per input
    #submit the condor jobs, for each ntuple
    #----------------------------------------------
  
    mkdir -p $iFile                   # iFile = directory with trimmed ntuple names
    cp $runCond $iFile                # copy cond submit script to iFile
    cp runAnalysis.sh $iFile          # pass the argument script (for LineNumber, doQC, syst and dir) 
    cd $iFile                         # cd to iFile
    sed -i "s:LINENUM:$lineNum:g" $runCond   # dictate which file to process
    ##sed -i "s:DOQCD:$doQCD:g" $runCond   # passed doQCD 
    if [ -z "$doQCD" ] && [ -z "$systematics" ] && [ -z "$direction" ]
    then
      for ii in {0..3}
      do
        echo $ii
        runCondCopy=$runCond/.sub/""
        runCondCopy=$runcCondCopy"_Copy.sub"
        cp $runCond $runCondCopy
        sed -i "s:DOQCD:$ii:g" $runCond   # passed doQCD 
        sed -i "s:SYSTEMATICS:$allSystematics:g" $runCond
        sed -i "s:DIRECTION:$allDirection:g" $runCond 
        runCondStripped=${runCond/.sub/""}
        runCondSpecific=$runCondStripped"_"$ii".sub" 
        cp $runCond $runCondSpecific
        echo "condor submit stage 1"
        condor_submit $runCondSpecific ###this is already properly indented
        cp $runCondCopy $runCond
      done
    elif [ -z "$systematics" ] && [ -z "$direction" ]
    then
      sed -i "s:DOQCD:$doQCD:g" $runCond   # passed doQCD 
      sed -i "s:SYSTEMATICS:$allSystematics:g" $runCond
      sed -i "s:DIRECTION:$allDirection:g"     $runCond
      runCondStripped=${runCond/.sub/""}
      runCondSpecific=$runCondStripped"_"$doQCD".sub" 
      mv $runCond $runCondSpecific
      echo "condor submit stage 1"
      condor_submit $runCondSpecific ###this is already properly indented
    elif [ -z "$direction" ] 
    then
      sed -i "s:DOQCD:$doQCD:g" $runCond   # passed doQCD 
      sed -i "s:SYSTEMATICS:$systematics:g"    $runCond
      sed -i "s:DIRECTION:$allDirection:g"     $runCond
      runCondStripped=${runCond/.sub/""}
      runCondSpecific=$runCondStripped"_"$doQCD".sub" 
      mv $runCond $runCondSpecific
      echo "condor submit stage 2"
      condor_submit $runCondSpecific ###this is already properly indented
    else
      # FOCUSING ON THIS RIGHT NOW
      sed -i "s:DOQCD:$doQCD:g" $runCond   # passed doQCD 
      sed -i "s:SYSTEMATICS:$systematics:g"    $runCond
      sed -i "s:DIRECTION:$direction:g"        $runCond
      runCondStripped=${runCond/.sub/""}
      runCondSpecific=$runCondStripped"_"$doQCD".sub" 
      mv $runCond $runCondSpecific
      echo "condor submit stage 3"
      condor_submit $runCondSpecific ###this is already properly indented
    fi
    cd ../
  fi
done

#!/bin/bash

###////////////////////////////////////////////////////////////////###
###                                                                ###
###  Script to run the Unfolding condor jobs in one go             ###
###  $ source runUnfFinalCondor.sh  1 lepEta_Zinc0jet 30-35 1 0  0 ###
###////////////////////////////////////////////////////////////////###


###--- parse the command line arguments ---###
WCharge=$1
Variable=$2
Range=$3
CT=$4
systematics=$5
direction=$6

###--- if illegal number of parameters are passed, exit with message ---###
if [ "$#" -ne 6 ]
then
  echo "Illegal number of parameters"
  echo "Pass 6 parameters to this script"
  echo "Here is a list (in that order)"
  echo "charge variable range CT systematics direction"
  echo "Eg : 1. $ ./runUnfFinalCondor.sh  1 lepEta_Zinc0jet 25-30 1 0  0"
  echo "Eg : 2. $ ./runUnfFinalCondor.sh -1 lepEta_Zexc2jet 40-45 0 1 -1"
  echo "Exiting Now."
  return 0 
fi

###--- If incorrect WCharge is entered, exit with message ---###
echo "You entered WCharge = " $WCharge
if [ $WCharge -ne 1 ] && [ $WCharge -ne -1 ]
then
  echo "It should be either 1 or -1"
  echo "Exiting Now."
  return 
fi

if [ $WCharge -eq 1 ]
then
  strWCharge="WP"
else
  strWCharge="WM"
fi

###--- If incorrect Range is entered, exit with message ---###
rangeArray=('25-above' '25-30' '30-35' '35-40' '40-45' '45-above')
withinRange=false
for ii in {0..5}
do 
  if [ ${rangeArray[ii]} == $Range ]
  then
    withinRange=true
  fi
done

if [ "$withinRange" == true ]
then
  echo "provided range " $Range " is correct, continuing..."
else
  echo "Please provide correct range, exiting now."
  return 
fi

####--- check systematics and direction values, take decisions accordingly ---###
rangeSystematics=('0'  '1'  '1'  '2'  '2'  '3'  '3'  '4'  '5'  '5'  '6'  '6'  '7'  '7'  '8'  '9'  '10'  '11'  '11')
rangeDirection=('0'   '-1'  '1' '-1'  '1' '-1'  '1'  '1' '-1'  '1'  '1' '-1' '-1'  '1'  '1'  '1'   '1'  '-1'   '1')
validSystematicsNDirections=false
for jj in {0..18}
do
  if [ ${rangeSystematics[jj]} == $systematics ] && [ ${rangeDirection[jj]} == $direction ]
  then
    validSystematicsNDirections=true
  fi
done

if [ "$validSystematicsNDirections" == true ]
then
  echo "provided systematics " $systematics " and " $direction " are correct, continuing..."
else
  echo "Please provide correct systematics and direction values, exiting now."
  return 0
fi

source /cvmfs/cms.cern.ch/cmsset_default.sh
eval `scram runtime -sh`
##voms-proxy-init --voms cms   ###UNCOMMENT THIS
cp /tmp/x509up_u51603 ~/     ###UNCOMMENT THIS

##--- create log directory ---#
logDir="logUnfold"
baseDir="/home/bsutar/t3store2/condor/condor_log/" # provide base path for log directory 
mkdir -p $baseDir$logDir                # make a proper log directory 
outcond="$baseDir$logDir"               # assign a variable to log directory
echo "Visit this log directory : " $outcond

##--- copy related files to log directory for future reference ---#
runUnfCond="runUnfCond.sub"
cp $runUnfCond $outcond                # 1. cond submit script
cp runUnfAnalysis.sh $outcond          # 2. script where we pass our parameters on the command line 
cd $outcond                         # we are inside log directory now

#######------ WE ARE INSIDE LOG DIRECTORY NOW ------######
 
#----------------------------------------------
#copy condor scripts to each input ntuple dir
#replace runUnfCond.sub arguments, as per input
#----------------------------------------------
prefix="unf_"
iDir=$prefix$strWCharge"_"$Variable
mkdir -p $iDir                          # iDir = directory where condor info will be saved based on the passed args
echo "Created " $iDir
cp $runUnfCond $iDir                    # copy cond submit script to iDir
cp runUnfAnalysis.sh $iDir              # pass the argument script (for WCharge, Variable, Range, CT, systematics, direction) 
cd $iDir                                # cd to iDir
runUnfCondCopy=${runUnfCond/.sub/""}
runUnfCondCopy=$runUnfCondCopy"_Copy.sub" 
cp $runUnfCond $runUnfCondCopy
sed -i "s:WCHARGE:$WCharge:g"         $runUnfCond
sed -i "s:VARIABLE:$Variable:g"       $runUnfCond  
sed -i "s:RANGE:$Range:g"             $runUnfCond 
sed -i "s:CLOSURETEST:$CT:g"                   $runUnfCond 
sed -i "s:SYSTEMATICS:$systematics:g" $runUnfCond 
sed -i "s:DIRECTION:$direction:g"     $runUnfCond 
runUnfCondStripped=${runUnfCond/.sub/""}
runUnfCondSpecific=$runUnfCondStripped"_"$strWCharge"_"$Variable"_"$Range"_"$CT"_"$systematics"_"$direction".sub" 
cp $runUnfCond $runUnfCondSpecific
echo "condor submit stage 1"
#####condor_submit $runUnfCondSpecific
cp $runUnfCondCopy $runUnfCond
cd /home/bsutar/t3store2/condor/Unfolding 

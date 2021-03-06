#!/bin/bash

#--- pass the arguments to pass_LineNum_doQCD_Syst_Dir_runDYJets_named1.sh ---# 
WCharge=$1
LineNum=$2
doQCD=$3
systematics=$4
direction=$5

date

#--- this script runs on some remote condor machine ---#
echo "CONDOR DIR: $_CONDOR_SCRATCH_DIR"
cd ${_CONDOR_SCRATCH_DIR}                                # we are inside the remote machine now
cp -r /home/bsutar/t3store/Asym2016-8TeV/CMSSW_5_3_11 .  # copy out framework to remove machine

#--- set env on remove machine  ---#
#cd CMSSW_5_3_11/src/TreeAnalysis2012/WJetsp_CENTRAL_QCD0 
cd CMSSW_5_3_11/src/TreeAnalysis2012/MuonChargeAsymAnalysis8TeV2012 #this setup is on git now 
source /cvmfs/cms.cern.ch/cmsset_default.sh
eval `scram runtime -sh`

#--- run the script ---#
./pass_LineNum_doQCD_Syst_Dir_runDYJets_named1.sh $WCharge $LineNum $doQCD $systematics $direction

cd ${_CONDOR_SCRATCH_DIR}
rm -rf CMSSW_5_3_11

echo "DONE"
date


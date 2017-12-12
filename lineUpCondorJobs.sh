#for ii in {1..579}   #data
#for ii in {580..689} #BkgdMC (including DYJets_MIX_UNFOLDING)
#for ii in {690..928} #signalMC
#for ii in {605..689} #Only DYJets_MIX_UNFOLDING
for ii in {1..102}   #full
#for ii in {70..78}    #Only DYJets_MIX_UNFOLDING 
do
  for jj in {0..3}
  do
    # ./runFinalCondor.sh WCHARGE LINENUM DOQCD SYSTEMATICS DIRECTION 
    #./runFinalCondor.sh  1 $ii $jj 0  0  
    #./runFinalCondor.sh -1 $ii $jj 0  0  
    # 1
    #./runFinalCondor.sh  1 $ii $jj 1 -1  
    #./runFinalCondor.sh  1 $ii $jj 1  1  
    #./runFinalCondor.sh -1 $ii $jj 1 -1
    #./runFinalCondor.sh -1 $ii $jj 1  1
    # 2
    #./runFinalCondor.sh  1 $ii $jj 2 -1  
    #./runFinalCondor.sh  1 $ii $jj 2  1  
    #./runFinalCondor.sh -1 $ii $jj 2 -1
    #./runFinalCondor.sh -1 $ii $jj 2  1
    # 3
    #./runFinalCondor.sh  1 $ii $jj 3 -1  
    #./runFinalCondor.sh  1 $ii $jj 3  1  
    #./runFinalCondor.sh -1 $ii $jj 3 -1
    #./runFinalCondor.sh -1 $ii $jj 3  1
    # 4
    #./runFinalCondor.sh  1 $ii $jj 4 -1  
    #./runFinalCondor.sh  1 $ii $jj 4  1  
    #./runFinalCondor.sh -1 $ii $jj 4 -1
    #./runFinalCondor.sh -1 $ii $jj 4  1
    # 5
    ./runFinalCondor.sh  1 $ii $jj 5 -1  
    ./runFinalCondor.sh  1 $ii $jj 5  1  
    ./runFinalCondor.sh -1 $ii $jj 5 -1
    ./runFinalCondor.sh -1 $ii $jj 5  1
  done
done
#./runFinalCondor.sh 2
#./runFinalCondor.sh 3
#./runFinalCondor.sh 1 0 0 0
#./runFinalCondor.sh 1 1 0 0
#./runFinalCondor.sh 1 2 0 0

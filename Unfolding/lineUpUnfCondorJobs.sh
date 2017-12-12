#Provide proper arguments in the same order
#Here is a list of arguments,
# CHARGE      : 1 or -1
# VARIABLE    : lepEta_Zinc2jet, lepEta_Zexc1jet etc
# CLOSURETEST : 0 or 1
# SYSTEMATICS : 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11
# DIRECTION   : 0 or 1 or -1
# RANGE       : 25-above, 25-30, 30-35, 35-40, 40-45, 45-above
declare -a Range=('25_above' '25_30' '30_35' '35_40' '40_45' '45_above')
Variable='lepEta_Z'
for jj in {0..5}
do
  for ii in {0..4}
  do
    myIncVariable=$Variable'inc'$ii'jet'
    myExcVariable=$Variable'exc'$ii'jet'
    # w+
    ## 1 down
    ###./runUnfFinalCondor.sh   1 $myIncVariable 0 1 -1 ${Range[jj]}
    ###./runUnfFinalCondor.sh   1 $myExcVariable 0 1 -1 ${Range[jj]}
    ## 1 up
    ###./runUnfFinalCondor.sh   1 $myIncVariable 0 1  1 ${Range[jj]}
    ###./runUnfFinalCondor.sh   1 $myExcVariable 0 1  1 ${Range[jj]}
    ## 2 down
    ###./runUnfFinalCondor.sh   1 $myIncVariable 0 2 -1 ${Range[jj]}
    ###./runUnfFinalCondor.sh   1 $myExcVariable 0 2 -1 ${Range[jj]}
    ## 2 up
    ###./runUnfFinalCondor.sh   1 $myIncVariable 0 2  1 ${Range[jj]}
    ###./runUnfFinalCondor.sh   1 $myExcVariable 0 2  1 ${Range[jj]}
    ## 3 down
    ./runUnfFinalCondor.sh   1 $myIncVariable 0 3 -1 ${Range[jj]}
    ./runUnfFinalCondor.sh   1 $myExcVariable 0 3 -1 ${Range[jj]}
    ## 3 up
    ./runUnfFinalCondor.sh   1 $myIncVariable 0 3  1 ${Range[jj]}
    ./runUnfFinalCondor.sh   1 $myExcVariable 0 3  1 ${Range[jj]}
    # w-
    ## 1 down
    ###./runUnfFinalCondor.sh  -1 $myIncVariable 0 1 -1 ${Range[jj]}
    ###./runUnfFinalCondor.sh  -1 $myExcVariable 0 1 -1 ${Range[jj]}
    ## 1 up
    ###./runUnfFinalCondor.sh  -1 $myIncVariable 0 1  1 ${Range[jj]}
    ###./runUnfFinalCondor.sh  -1 $myExcVariable 0 1  1 ${Range[jj]}
    ## 2 down
    ###./runUnfFinalCondor.sh  -1 $myIncVariable 0 2 -1 ${Range[jj]}
    ###./runUnfFinalCondor.sh  -1 $myExcVariable 0 2 -1 ${Range[jj]}
    ## 2 up
    ###./runUnfFinalCondor.sh  -1 $myIncVariable 0 2  1 ${Range[jj]}
    ###./runUnfFinalCondor.sh  -1 $myExcVariable 0 2  1 ${Range[jj]}
    ## 3 down
    ./runUnfFinalCondor.sh  -1 $myIncVariable 0 3 -1 ${Range[jj]}
    ./runUnfFinalCondor.sh  -1 $myExcVariable 0 3 -1 ${Range[jj]}
    ## 3 up
    ./runUnfFinalCondor.sh  -1 $myIncVariable 0 3  1 ${Range[jj]}
    ./runUnfFinalCondor.sh  -1 $myExcVariable 0 3  1 ${Range[jj]}
    myIncVariable=$Variable
    myExcVariable=$Variable
  done
  myIncVariable=$Variable
  myExcVariable=$Variable
done

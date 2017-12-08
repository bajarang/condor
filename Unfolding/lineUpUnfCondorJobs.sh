#Provide proper arguments in the same order
#Here is a list of arguments,
# CHARGE      : 1 or -1
# VARIABLE    : lepEta_Zinc2jet, lepEta_Zexc1jet etc
# RANGE       : 25-above, 25-30, 30-35, 35-40, 40-45, 45-above
# CLOSURETEST : 0 or 1
# SYSTEMATICS : 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11
# DIRECTION   : 0 or 1 or -1

###--- wplus ---###
##-- Inc --##
#- 0jet -#
source runUnfFinalCondor.sh   1 lepEta_Zinc0jet 0 0  0 25_above
source runUnfFinalCondor.sh   1 lepEta_Zinc0jet 0 0  0 25_30
source runUnfFinalCondor.sh   1 lepEta_Zinc0jet 0 0  0 30_35
source runUnfFinalCondor.sh   1 lepEta_Zinc0jet 0 0  0 35_40
source runUnfFinalCondor.sh   1 lepEta_Zinc0jet 0 0  0 40_45
source runUnfFinalCondor.sh   1 lepEta_Zinc0jet 0 0  0 45_above
#- 1jet -#
source runUnfFinalCondor.sh   1 lepEta_Zinc1jet 0 0  0 25_above
source runUnfFinalCondor.sh   1 lepEta_Zinc1jet 0 0  0 25_30
source runUnfFinalCondor.sh   1 lepEta_Zinc1jet 0 0  0 30_35
source runUnfFinalCondor.sh   1 lepEta_Zinc1jet 0 0  0 35_40
source runUnfFinalCondor.sh   1 lepEta_Zinc1jet 0 0  0 40_45
source runUnfFinalCondor.sh   1 lepEta_Zinc1jet 0 0  0 45_above
#- 2jet -#
source runUnfFinalCondor.sh   1 lepEta_Zinc2jet 0 0  0 25_above
source runUnfFinalCondor.sh   1 lepEta_Zinc2jet 0 0  0 25_30
source runUnfFinalCondor.sh   1 lepEta_Zinc2jet 0 0  0 30_35
source runUnfFinalCondor.sh   1 lepEta_Zinc2jet 0 0  0 35_40
source runUnfFinalCondor.sh   1 lepEta_Zinc2jet 0 0  0 40_45
source runUnfFinalCondor.sh   1 lepEta_Zinc2jet 0 0  0 45_above
#- 3jet -#
source runUnfFinalCondor.sh   1 lepEta_Zinc3jet 0 0  0 25_above
source runUnfFinalCondor.sh   1 lepEta_Zinc3jet 0 0  0 25_30
source runUnfFinalCondor.sh   1 lepEta_Zinc3jet 0 0  0 30_35
source runUnfFinalCondor.sh   1 lepEta_Zinc3jet 0 0  0 35_40
source runUnfFinalCondor.sh   1 lepEta_Zinc3jet 0 0  0 40_45
source runUnfFinalCondor.sh   1 lepEta_Zinc3jet 0 0  0 45_above
#- 4jet -#
source runUnfFinalCondor.sh   1 lepEta_Zinc4jet 0 0  0 25_above
source runUnfFinalCondor.sh   1 lepEta_Zinc4jet 0 0  0 25_30
source runUnfFinalCondor.sh   1 lepEta_Zinc4jet 0 0  0 30_35
source runUnfFinalCondor.sh   1 lepEta_Zinc4jet 0 0  0 35_40
source runUnfFinalCondor.sh   1 lepEta_Zinc4jet 0 0  0 40_45
source runUnfFinalCondor.sh   1 lepEta_Zinc4jet 0 0  0 45_above
##-- Exc --##
#- 0jet -#
source runUnfFinalCondor.sh   1 lepEta_Zexc0jet 0 0  0 25_above
source runUnfFinalCondor.sh   1 lepEta_Zexc0jet 0 0  0 25_30
source runUnfFinalCondor.sh   1 lepEta_Zexc0jet 0 0  0 30_35
source runUnfFinalCondor.sh   1 lepEta_Zexc0jet 0 0  0 35_40
source runUnfFinalCondor.sh   1 lepEta_Zexc0jet 0 0  0 40_45
source runUnfFinalCondor.sh   1 lepEta_Zexc0jet 0 0  0 45_above
#- 1jet -#
source runUnfFinalCondor.sh   1 lepEta_Zexc1jet 0 0  0 25_above
source runUnfFinalCondor.sh   1 lepEta_Zexc1jet 0 0  0 25_30
source runUnfFinalCondor.sh   1 lepEta_Zexc1jet 0 0  0 30_35
source runUnfFinalCondor.sh   1 lepEta_Zexc1jet 0 0  0 35_40
source runUnfFinalCondor.sh   1 lepEta_Zexc1jet 0 0  0 40_45
source runUnfFinalCondor.sh   1 lepEta_Zexc1jet 0 0  0 45_above
#- 2jet -#
source runUnfFinalCondor.sh   1 lepEta_Zexc2jet 0 0  0 25_above
source runUnfFinalCondor.sh   1 lepEta_Zexc2jet 0 0  0 25_30
source runUnfFinalCondor.sh   1 lepEta_Zexc2jet 0 0  0 30_35
source runUnfFinalCondor.sh   1 lepEta_Zexc2jet 0 0  0 35_40
source runUnfFinalCondor.sh   1 lepEta_Zexc2jet 0 0  0 40_45
source runUnfFinalCondor.sh   1 lepEta_Zexc2jet 0 0  0 45_above
#- 3jet -#
source runUnfFinalCondor.sh   1 lepEta_Zexc3jet 0 0  0 25_above
source runUnfFinalCondor.sh   1 lepEta_Zexc3jet 0 0  0 25_30
source runUnfFinalCondor.sh   1 lepEta_Zexc3jet 0 0  0 30_35
source runUnfFinalCondor.sh   1 lepEta_Zexc3jet 0 0  0 35_40
source runUnfFinalCondor.sh   1 lepEta_Zexc3jet 0 0  0 40_45
source runUnfFinalCondor.sh   1 lepEta_Zexc3jet 0 0  0 45_above
#- 4jet -#
source runUnfFinalCondor.sh   1 lepEta_Zexc4jet 0 0  0 25_above
source runUnfFinalCondor.sh   1 lepEta_Zexc4jet 0 0  0 25_30
source runUnfFinalCondor.sh   1 lepEta_Zexc4jet 0 0  0 30_35
source runUnfFinalCondor.sh   1 lepEta_Zexc4jet 0 0  0 35_40
source runUnfFinalCondor.sh   1 lepEta_Zexc4jet 0 0  0 40_45
source runUnfFinalCondor.sh   1 lepEta_Zexc4jet 0 0  0 45_above

###--- wminus ---###
##-- Inc --##
#- 0jet -#
source runUnfFinalCondor.sh  -1 lepEta_Zinc0jet 0 0  0 25_above
source runUnfFinalCondor.sh  -1 lepEta_Zinc0jet 0 0  0 25_30
source runUnfFinalCondor.sh  -1 lepEta_Zinc0jet 0 0  0 30_35
source runUnfFinalCondor.sh  -1 lepEta_Zinc0jet 0 0  0 35_40
source runUnfFinalCondor.sh  -1 lepEta_Zinc0jet 0 0  0 40_45
source runUnfFinalCondor.sh  -1 lepEta_Zinc0jet 0 0  0 45_above
#- 1jet -#
source runUnfFinalCondor.sh  -1 lepEta_Zinc1jet 0 0  0 25_above
source runUnfFinalCondor.sh  -1 lepEta_Zinc1jet 0 0  0 25_30
source runUnfFinalCondor.sh  -1 lepEta_Zinc1jet 0 0  0 30_35
source runUnfFinalCondor.sh  -1 lepEta_Zinc1jet 0 0  0 35_40
source runUnfFinalCondor.sh  -1 lepEta_Zinc1jet 0 0  0 40_45
source runUnfFinalCondor.sh  -1 lepEta_Zinc1jet 0 0  0 45_above
#- 2jet -#
source runUnfFinalCondor.sh  -1 lepEta_Zinc2jet 0 0  0 25_above
source runUnfFinalCondor.sh  -1 lepEta_Zinc2jet 0 0  0 25_30
source runUnfFinalCondor.sh  -1 lepEta_Zinc2jet 0 0  0 30_35
source runUnfFinalCondor.sh  -1 lepEta_Zinc2jet 0 0  0 35_40
source runUnfFinalCondor.sh  -1 lepEta_Zinc2jet 0 0  0 40_45
source runUnfFinalCondor.sh  -1 lepEta_Zinc2jet 0 0  0 45_above
#- 3jet -#
source runUnfFinalCondor.sh  -1 lepEta_Zinc3jet 0 0  0 25_above
source runUnfFinalCondor.sh  -1 lepEta_Zinc3jet 0 0  0 25_30
source runUnfFinalCondor.sh  -1 lepEta_Zinc3jet 0 0  0 30_35
source runUnfFinalCondor.sh  -1 lepEta_Zinc3jet 0 0  0 35_40
source runUnfFinalCondor.sh  -1 lepEta_Zinc3jet 0 0  0 40_45
source runUnfFinalCondor.sh  -1 lepEta_Zinc3jet 0 0  0 45_above
#- 4jet -#
source runUnfFinalCondor.sh  -1 lepEta_Zinc4jet 0 0  0 25_above
source runUnfFinalCondor.sh  -1 lepEta_Zinc4jet 0 0  0 25_30
source runUnfFinalCondor.sh  -1 lepEta_Zinc4jet 0 0  0 30_35
source runUnfFinalCondor.sh  -1 lepEta_Zinc4jet 0 0  0 35_40
source runUnfFinalCondor.sh  -1 lepEta_Zinc4jet 0 0  0 40_45
source runUnfFinalCondor.sh  -1 lepEta_Zinc4jet 0 0  0 45_above
##-- Exc --##
#- 0jet -#
source runUnfFinalCondor.sh  -1 lepEta_Zexc0jet 0 0  0 25_above
source runUnfFinalCondor.sh  -1 lepEta_Zexc0jet 0 0  0 25_30
source runUnfFinalCondor.sh  -1 lepEta_Zexc0jet 0 0  0 30_35
source runUnfFinalCondor.sh  -1 lepEta_Zexc0jet 0 0  0 35_40
source runUnfFinalCondor.sh  -1 lepEta_Zexc0jet 0 0  0 40_45
source runUnfFinalCondor.sh  -1 lepEta_Zexc0jet 0 0  0 45_above
#- 1jet -#
source runUnfFinalCondor.sh  -1 lepEta_Zexc1jet 0 0  0 25_above
source runUnfFinalCondor.sh  -1 lepEta_Zexc1jet 0 0  0 25_30
source runUnfFinalCondor.sh  -1 lepEta_Zexc1jet 0 0  0 30_35
source runUnfFinalCondor.sh  -1 lepEta_Zexc1jet 0 0  0 35_40
source runUnfFinalCondor.sh  -1 lepEta_Zexc1jet 0 0  0 40_45
source runUnfFinalCondor.sh  -1 lepEta_Zexc1jet 0 0  0 45_above
#- 2jet -#
source runUnfFinalCondor.sh  -1 lepEta_Zexc2jet 0 0  0 25_above
source runUnfFinalCondor.sh  -1 lepEta_Zexc2jet 0 0  0 25_30
source runUnfFinalCondor.sh  -1 lepEta_Zexc2jet 0 0  0 30_35
source runUnfFinalCondor.sh  -1 lepEta_Zexc2jet 0 0  0 35_40
source runUnfFinalCondor.sh  -1 lepEta_Zexc2jet 0 0  0 40_45
source runUnfFinalCondor.sh  -1 lepEta_Zexc2jet 0 0  0 45_above
#- 3jet -#
source runUnfFinalCondor.sh  -1 lepEta_Zexc3jet 0 0  0 25_above
source runUnfFinalCondor.sh  -1 lepEta_Zexc3jet 0 0  0 25_30
source runUnfFinalCondor.sh  -1 lepEta_Zexc3jet 0 0  0 30_35
source runUnfFinalCondor.sh  -1 lepEta_Zexc3jet 0 0  0 35_40
source runUnfFinalCondor.sh  -1 lepEta_Zexc3jet 0 0  0 40_45
source runUnfFinalCondor.sh  -1 lepEta_Zexc3jet 0 0  0 45_above
#- 4jet -#
source runUnfFinalCondor.sh  -1 lepEta_Zexc4jet 0 0  0 25_above
source runUnfFinalCondor.sh  -1 lepEta_Zexc4jet 0 0  0 25_30
source runUnfFinalCondor.sh  -1 lepEta_Zexc4jet 0 0  0 30_35
source runUnfFinalCondor.sh  -1 lepEta_Zexc4jet 0 0  0 35_40
source runUnfFinalCondor.sh  -1 lepEta_Zexc4jet 0 0  0 40_45
source runUnfFinalCondor.sh  -1 lepEta_Zexc4jet 0 0  0 45_above

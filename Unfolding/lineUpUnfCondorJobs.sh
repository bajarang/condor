#Provide proper arguments in the same order
#Here is a list of arguments,
# CHARGE      : 1 or -1
# VARIABLE    : lepEta_Zinc2jet, lepEta_Zexc1jet etc
# RANGE       : 25-above, 25-30, 30-35, 35-40, 40-45, 45-above
# CLOSURETEST : 0 or 1
# SYSTEMATICS : 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11
# DIRECTION   : 0 or 1 or -1

source runUnfFinalCondor.sh  -1 lepEta_Zinc0jet 30-35 1 0  0


#////////////////////////////////////////////////////////
#                                                       #
# Compare Generated/processed files with Expected files #
#                                                       #
#////////////////////////////////////////////////////////


import os
import sys
import datetime


##------------------------------------------------
# compare the two files, output the unmatched lines
# and save it in unProcNtuples.log
##------------------------------------------------
def compare(File1,File2):
    with open(File1,'r') as f:
        d=set(f.readlines())

    with open(File2,'r') as f:
        e=set(f.readlines())

    open('unProcNtuples_1.log','w').close() #Create the file
    with open('unProcNtuples_1.log','a') as f:
        for line in list(d-e):
           f.write(line)
	   print line

compare("ExpectedFiles/ExpectedFiles_1.log", "procNtuples_1.log")



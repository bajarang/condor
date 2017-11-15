# condor

Steps to setup this condor framework ---

1. Go to your home directory
   $ cd ~/.

2. Copy this framework
   $ git clone master https://git.github.com/bsutar/condor

3. There are 4 main files of our interest
   a. runFinalCondor.sh
   b. runCond.sub
   c. runAnalysis.sh
   d. Input_DB_Summary.txt
   
4. We pass arguments runFinalCondor.sh to run the condor jobs.
   There are following ways by which we submit the jobs.
   a. $ ./runFinalCondor.sh 1
        Here the first option 1 is the line number from Input_DB_Summary.txt
        This way we are submitting default doQCD, systematics and direction
        where default doQCD means for values 0, 1, 2 and 3 
        default systematics means for all the systematics sequentially
        and default direction means for all the possible respective variations 
   b. $ ./runFinalCondor.sh 1 0
        Here the first option 1 is the line number from Input_DB_Summary.txt
        and the second option 0 is for doQCD value
        systematics and direction are kept default, aka for all
   c. $ ./runFinalCondor.sh 1 0 2
        Here the first option 1 is the line number from Input_DB_Summary.txt
        and the second option 0 is for doQCD value
        and the third option 2 is for the particular systematics that we want to carry out
        direction is default
   d. $ ./runFinalCondor.sh 1 0 2 1
        Here the first option 1 is the line number from Input_DB_Summary.txt
        and the second option 0 is for doQCD value
        and the third option 2 is for the particular systematics that we want to carry out
        direction is provided by us in this case
      

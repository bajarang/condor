###################################
# COMPILE mergeHistos.cc FIRST #
###################################

declare -a Sample=('Data' 'TTJets' 'ZZ' 'WZ' 'WW' 'T_s_channel' 'T_t_channel' 'T_tW_channel' 'Tbar_s_channel' 'Tbar_t_channel' 'Tbar_tW_channel' 'DYJets10to50' 'DYJets_MIX_UNFOLDING' 'WJetsALL_MIX_UNFOLDING')
#for jj in {0..13}
for jj in {1..12}
#jj=0
do
  for ii in {0..3}
  do
    # 0
    #./mergeHistos  1 ${Sample[jj]} $ii 0 0
    #./mergeHistos -1 ${Sample[jj]} $ii 0 0
    # 1
    #./mergeHistos  1 ${Sample[jj]} $ii 1  1
    #./mergeHistos  1 ${Sample[jj]} $ii 1 -1
    #./mergeHistos -1 ${Sample[jj]} $ii 1  1
    #./mergeHistos -1 ${Sample[jj]} $ii 1 -1
    # 2
    #./mergeHistos  1 ${Sample[jj]} $ii 2  1
    #./mergeHistos  1 ${Sample[jj]} $ii 2 -1
    #./mergeHistos -1 ${Sample[jj]} $ii 2  1
    #./mergeHistos -1 ${Sample[jj]} $ii 2 -1
    # 3
    ./mergeHistos  1 ${Sample[jj]} $ii 3  1
    ./mergeHistos  1 ${Sample[jj]} $ii 3 -1
    ./mergeHistos -1 ${Sample[jj]} $ii 3  1
    ./mergeHistos -1 ${Sample[jj]} $ii 3 -1
  done
done

###################################
# COMPILE mergeHistos.cc FIRST #
###################################

declare -a Sample=('Data' 'TTJets' 'ZZ' 'WZ' 'WW' 'T_s_channel' 'T_t_channel' 'T_tW_channel' 'Tbar_s_channel' 'Tbar_t_channel' 'Tbar_tW_channel' 'DYJets10to50' 'DYJets_MIX_UNFOLDING' 'WJetsALL_MIX_UNFOLDING')
jj=12
#for jj in {0..13}
#do
  for ii in {0..3}
  do
    ./mergeHistos  1 ${Sample[jj]} $ii 0 0
    ./mergeHistos -1 ${Sample[jj]} $ii 0 0
  done
#done

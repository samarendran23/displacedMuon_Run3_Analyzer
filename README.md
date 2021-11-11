# displacedMuon_Run3_Analyzer
cmsrel CMSSW_12_1_0_pre4
cd CMSSW_12_1_0_pre4/src
scram b -j 8
cmsenv
cmsRun step3_RAW2DIGI_L1Reco_RECO_RECOSIM_EI_PAT_VALIDATION_DQM.py

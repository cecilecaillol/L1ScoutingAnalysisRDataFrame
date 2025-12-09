Reproducing EXO-25-010
======================

Step 1: Signal generation
-------------------------

Follow the instructions below to generate locally a small signal sample. The checkout modifies CMSSW to store earlier and later bmtfDigis. It is crucial to use the dedicated customise function when running the GENSIM step (--customise SimG4Core/CustomPhysics/Exotica\_HSCP\_SIM\_cfi.customise), otherwise the HSCPs wont be simulated in the detector.

```
cmsrel CMSSW_14_0_18
 cd CMSSW_14_0_18/src/
 cmsenv
 git cms-init
 git cms-checkout-topic -u cecilecaillol:hscp_simulate
 cd ../..
 cp /afs/cern.ch/work/c/ccaillol/public/HSCP_simulation_2024/* .
 sh do_Zprime2600.sh
```

In the GENSIM step, just before the Path and EndPath definitions, add the following lines to improve the tracking for slow particles in Geant4:
```
TimeCut = cms.double(10000000000.0)
process.common_maximum_time.MaxTrackTime = TimeCut
process.g4SimHits.Generator.MaxTrackTime = TimeCut
process.g4SimHits.StackingAction.MaxTrackTime = TimeCut
process.g4SimHits.SteppingAction.MaxNumberOfSteps = cms.int32(1000000)
process.g4SimHits.SteppingAction.MaxTrackTime = TimeCut
process.g4SimHits.Physics.MaxTrackTime = TimeCut
process.g4SimHits.Physics.DefaultCutValue = 0.01
```

Step 2: Rerun the kBMTF algorithm from stubs in different BXs
-------------------------------------------------------------

This step takes the RECO files from step 1, reruns the kBMTF algorithm with stubs from different BXs, and produces ntuples with information about L1 Muons, default kBMTF tracks, and modified kBMTF tracks. For modified kBMTF tracks, information about individual stubs, like their respective BX, is stored.

The checkout below modifies the code for the kBMTF algorithm to consider stubs that belong within a customizable range of bunch crossings. 
The algorithm is otherwise unchanged and the timing information is not used. The curvature is stored for the pT to be recomputed offline. 

```
mkdir reKBMTF
cd reKBMTF
cmsrel CMSSW_14_0_12
cd CMSSW_14_0_12/src/
cmsenv
git cms-init
git cms-checkout-topic -u cecilecaillol:hscp_kbmtf 
scram b -j 8
cd L1TriggerScouting/Utilities/python
```

Run MC locally:
```
cmsRun kbmtFlatTableProducerSimulation_cfg.py inputFiles=file:input.root
```
Submit MC to condor:
```
sh do_condor_signal1DHSCP.sh
```

Run data locally:
```
cmsRun kbmtFlatTableProducer_cfg.py inputFiles=file:input.root
```
Submit data to crab:
```
crab submit crabConfigData
```
or split by run ranges:
```
crab submit crabConfigDataRunRange.py
```

Step 3: Skim the ntuples
------------------------

This step runs on the ntuples from step 2 using RDataFrame to compute higher-level quantities (like the BX pattern for each track, whether the BX is colliding, ...) for a subset of the events (those with at least one track across more than 1 BX). For the MC, all the events are kept without filtering since the samples are small. 

```
mkdir HSCPanalysis
cd HSCPanalysis
cmsrel CMSSW_14_0_12
cd CMSSW_14_0_12/src/
cmsenv
git cms-init
git clone https://github.com/cecilecaillol/L1ScoutingAnalysisRDataFrame.git
scram b -j 8
cd L1ScoutingAnalysisRDataFrame/NtupleAnalyzer/scripts
```

Data skimming can be run with:
```
python3 FinalSelection_SlowData.py input.root output.root
```
To submit the skimming to lxbatch for a set of files stored in a directory (edit the sh file to change the location):
```
python3 lxbatch_slowSkim.py
```
Some tracks are duplicated. To remove the overlap, use:
```
./Make.sh RemoveDuplicate.cc
./RemoveDuplicate.exe input.root output.root
```
or to lxbatch:
```
python3 lxbatch_cleaning.py
```

MC skimming can be run with:
```
python3 FinalSelection_SlowNoFilter.py input.root output.root
```
For example, to run locally over signal samples stored in eos:
```
sh do_slow.sh
```

Hadd all the cleaned files:
```
sh do_skim_hadd.sh
```

Step 4: Analyze the ntuples and write the datacards
----------------------------------------------------

To apply the selection, build the categories, and write datacard-like ROOT files for each process:

```
./Make.sh SlowAnalysis_classification.cc
./SlowAnalysis_classification.exe input.root output.root name
```

The whole workflow running on data and signal MC, deriving the background histogram, and producing the final datacard to be used with Combine, can be run with (change the locations of the input and output files):
```
sh do_datacard.sh
```


Extra step: Drell-Yan control region
-------------------------------------

Select dimuon events built from modified kBMTF tracks and make ntuples for further analysis.

Run:
```
python3 FinalSelection_ZmumuKBMTF.py input.root output.root 
```

or to lxbatch for data:
```
python3 lxbatch_zmumuKBMTFSkim.py
```


./Make.sh SlowAnalysis_classification.cc
./SlowAnalysis_classification.exe /eos/cms/store/group/cmst3/group/slowmuons/Cleaned_SlowSkims/Scouting_2024G_part1.root out_2024G_part1.root data_obs
./SlowAnalysis_classification.exe /eos/cms/store/group/cmst3/group/slowmuons/Cleaned_SlowSkims/Scouting_2024G_part2.root out_2024G_part2.root data_obs
./SlowAnalysis_classification.exe /eos/cms/store/group/cmst3/group/slowmuons/Cleaned_SlowSkims/Scouting_2024G_part3.root out_2024G_part3.root data_obs
./SlowAnalysis_classification.exe /eos/cms/store/group/cmst3/group/slowmuons/Cleaned_SlowSkims/Scouting_2024G_part4.root out_2024G_part4.root data_obs
./SlowAnalysis_classification.exe /eos/cms/store/group/cmst3/group/slowmuons/Cleaned_SlowSkims/Scouting_2024G_part5.root out_2024G_part5.root data_obs
./SlowAnalysis_classification.exe /eos/cms/store/group/cmst3/group/slowmuons/Cleaned_SlowSkims/Scouting_2024G_part6.root out_2024G_part6.root data_obs
./SlowAnalysis_classification.exe /eos/cms/store/group/cmst3/group/slowmuons/Cleaned_SlowSkims/Scouting_2024H.root out_2024H.root data_obs
./SlowAnalysis_classification.exe /eos/cms/store/group/cmst3/group/slowmuons/Cleaned_SlowSkims/Scouting_2024I_part1.root out_2024I_part1.root data_obs
./SlowAnalysis_classification.exe /eos/cms/store/group/cmst3/group/slowmuons/Cleaned_SlowSkims/Scouting_2024I_part2.root out_2024I_part2.root data_obs
hadd -f out_data.root out_2024G_part1.root out_2024G_part2.root out_2024G_part3.root out_2024G_part4.root out_2024G_part5.root out_2024G_part6.root out_2024H.root out_2024I_part1.root out_2024I_part2.root
#hadd -f out_data.root out_2024H.root
./SlowAnalysis_classification.exe slow_Jian_91188_45600.root out_Jian.root Jian
./SlowAnalysis_classification.exe slow_HSCP2600.root out_HSCP2600.root HSCP2600
./SlowAnalysis_classification.exe slow_HSCP3000.root out_HSCP3000.root HSCP3000
./SlowAnalysis_classification.exe slow_HSCP3500.root out_HSCP3500.root HSCP3500
./SlowAnalysis_classification.exe slow_HSCP4000.root out_HSCP4000.root HSCP4000
./SlowAnalysis_classification.exe slow_HSCP4500.root out_HSCP4500.root HSCP4500
./SlowAnalysis_classification.exe slow_HSCP5000.root out_HSCP5000.root HSCP5000
./SlowAnalysis_classification.exe slow_HSCP5500.root out_HSCP5500.root HSCP5500
./SlowAnalysis_classification.exe slow_HSCP6000.root out_HSCP6000.root HSCP6000
hadd -f out_signal.root out_Jian.root out_HSCP2600.root out_HSCP3000.root out_HSCP3500.root out_HSCP4000.root out_HSCP4500.root out_HSCP5000.root out_HSCP5500.root out_HSCP6000.root
python3 Create_fake.py 
hadd -f datacard.root out_data.root out_fake.root out_signal.root 
python3 Draw_SR.py 

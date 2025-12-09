#python3 Histo_Zmumu.py mmumu DY
#python3 Histo_Zmumu.py mmumu Scouting_2024H
#./Make.sh ZmumuAnalysis.cc 
#./ZmumuAnalysis.exe testL1Mu_DY.root output_Zmumu/DY.root DY L1Mu
#./ZmumuAnalysis.exe testL1Mu_Scouting_2024H.root output_Zmumu/Scouting_2024H.root data_obs L1Mu
#python3 Create_fake_Zmumu.py --selection="Zmumu"
#hadd -f datacard_Zmumu.root output_Zmumu/DY.root output_Zmumu/Scouting_2024H.root output_Zmumu/Fake.root
#python3 Draw_Zmumu.py --selection="Zmumu"


./Make.sh ZmumuAnalysis.cc
#./ZmumuAnalysis.exe Zmumu_DY.root output_Zmumu/DY.root DY Zmumu
./ZmumuAnalysis.exe Zmumu_DYMM.root output_Zmumu/DY.root DY Zmumu
./ZmumuAnalysis.exe Zmumu_DYMM.root output_Zmumu/DYall.root DYall Zmumu
./ZmumuAnalysis.exe /eos/cms/store/group/cmst3/group/slowmuons/ZmumuSkims/Scouting_2024G_part1.root output_Zmumu/Scouting_2024G_part1.root data_obs Zmumu
./ZmumuAnalysis.exe /eos/cms/store/group/cmst3/group/slowmuons/ZmumuSkims/Scouting_2024G_part2.root output_Zmumu/Scouting_2024G_part2.root data_obs Zmumu
./ZmumuAnalysis.exe /eos/cms/store/group/cmst3/group/slowmuons/ZmumuSkims/Scouting_2024G_part3.root output_Zmumu/Scouting_2024G_part3.root data_obs Zmumu
./ZmumuAnalysis.exe /eos/cms/store/group/cmst3/group/slowmuons/ZmumuSkims/Scouting_2024G_part4.root output_Zmumu/Scouting_2024G_part4.root data_obs Zmumu
./ZmumuAnalysis.exe /eos/cms/store/group/cmst3/group/slowmuons/ZmumuSkims/Scouting_2024G_part5.root output_Zmumu/Scouting_2024G_part5.root data_obs Zmumu
./ZmumuAnalysis.exe /eos/cms/store/group/cmst3/group/slowmuons/ZmumuSkims/Scouting_2024G_part6.root output_Zmumu/Scouting_2024G_part6.root data_obs Zmumu
./ZmumuAnalysis.exe /eos/cms/store/group/cmst3/group/slowmuons/ZmumuSkims/Scouting_2024H.root output_Zmumu/Scouting_2024H.root data_obs Zmumu
./ZmumuAnalysis.exe /eos/cms/store/group/cmst3/group/slowmuons/ZmumuSkims/Scouting_2024I_part1.root output_Zmumu/Scouting_2024I_part1.root data_obs Zmumu
./ZmumuAnalysis.exe /eos/cms/store/group/cmst3/group/slowmuons/ZmumuSkims/Scouting_2024I_part2.root output_Zmumu/Scouting_2024I_part2.root data_obs Zmumu
hadd -f  output_Zmumu/Scouting_2024.root output_Zmumu/Scouting_2024G_part1.root output_Zmumu/Scouting_2024G_part2.root output_Zmumu/Scouting_2024G_part3.root output_Zmumu/Scouting_2024G_part4.root output_Zmumu/Scouting_2024G_part5.root output_Zmumu/Scouting_2024G_part6.root output_Zmumu/Scouting_2024H.root output_Zmumu/Scouting_2024I_part1.root output_Zmumu/Scouting_2024I_part2.root
#hadd -f  output_Zmumu/Scouting_2024.root output_Zmumu/Scouting_2024H.root
#hadd -f  output_Zmumu/Scouting_2024.root output_Zmumu/Scouting_2024I_part1.root output_Zmumu/Scouting_2024I_part2.root
#hadd -f  output_Zmumu/Scouting_2024.root output_Zmumu/Scouting_2024G_part1.root output_Zmumu/Scouting_2024G_part2.root output_Zmumu/Scouting_2024G_part3.root output_Zmumu/Scouting_2024G_part4.root output_Zmumu/Scouting_2024G_part5.root output_Zmumu/Scouting_2024G_part6.root
python3 Create_fake_Zmumu.py --selection="Zmumu"
hadd -f datacard_Zmumu.root output_Zmumu/DY.root output_Zmumu/DYall.root output_Zmumu/Scouting_2024.root output_Zmumu/Fake.root
python3 Draw_Zmumu.py --selection="Zmumu"


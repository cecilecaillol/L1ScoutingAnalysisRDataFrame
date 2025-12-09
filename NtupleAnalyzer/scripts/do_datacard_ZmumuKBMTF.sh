#python3 Histo_ZmumuKBMTF.py mmumu DY
#python3 Histo_ZmumuKBMTF.py mmumu Scouting_2024H
#python3 Create_fake_Zmumu.py --selection="ZmumuKBMTF"
#hadd -f datacard_ZmumuKBMTF.root output_ZmumuKBMTF/DY.root output_ZmumuKBMTF/Scouting_2024H.root output_ZmumuKBMTF/Fake.root
#python3 Draw_Zmumu.py --selection="ZmumuKBMTF"

#./Make.sh ZmumuAnalysis.cc
#./ZmumuAnalysis.exe ZmumuKBMTF_DY.root output_ZmumuKBMTF/DY.root DY KBMTF
#./ZmumuAnalysis.exe ZmumuKBMTF_Scouting_2024H.root output_ZmumuKBMTF/Scouting_2024H.root data_obs KBMTF
#python3 Create_fake_Zmumu.py --selection="ZmumuKBMTF"
#hadd -f datacard_ZmumuKBMTF.root output_ZmumuKBMTF/DY.root output_ZmumuKBMTF/Scouting_2024H.root output_ZmumuKBMTF/Fake.root
#python3 Draw_Zmumu.py --selection="ZmumuKBMTF"

./Make.sh ZmumuAnalysis.cc
#./ZmumuAnalysis.exe ZmumuKBMTF_DY.root output_ZmumuKBMTF/DY.root DY KBMTF
./ZmumuAnalysis.exe ZmumuKBMTF_DYMM.root output_ZmumuKBMTF/DY.root DY KBMTF
./ZmumuAnalysis.exe ZmumuKBMTF_DYMM.root output_ZmumuKBMTF/DYall.root DYall KBMTF
./ZmumuAnalysis.exe /eos/cms/store/group/cmst3/group/slowmuons/ZmumuKBMTFSkims/Scouting_2024G_part1.root output_ZmumuKBMTF/Scouting_2024G_part1.root data_obs KBMTF
./ZmumuAnalysis.exe /eos/cms/store/group/cmst3/group/slowmuons/ZmumuKBMTFSkims/Scouting_2024G_part2.root output_ZmumuKBMTF/Scouting_2024G_part2.root data_obs KBMTF
./ZmumuAnalysis.exe /eos/cms/store/group/cmst3/group/slowmuons/ZmumuKBMTFSkims/Scouting_2024G_part3.root output_ZmumuKBMTF/Scouting_2024G_part3.root data_obs KBMTF
./ZmumuAnalysis.exe /eos/cms/store/group/cmst3/group/slowmuons/ZmumuKBMTFSkims/Scouting_2024G_part4.root output_ZmumuKBMTF/Scouting_2024G_part4.root data_obs KBMTF
./ZmumuAnalysis.exe /eos/cms/store/group/cmst3/group/slowmuons/ZmumuKBMTFSkims/Scouting_2024G_part5.root output_ZmumuKBMTF/Scouting_2024G_part5.root data_obs KBMTF
./ZmumuAnalysis.exe /eos/cms/store/group/cmst3/group/slowmuons/ZmumuKBMTFSkims/Scouting_2024G_part6.root output_ZmumuKBMTF/Scouting_2024G_part6.root data_obs KBMTF
./ZmumuAnalysis.exe /eos/cms/store/group/cmst3/group/slowmuons/ZmumuKBMTFSkims/Scouting_2024H.root output_ZmumuKBMTF/Scouting_2024H.root data_obs KBMTF
./ZmumuAnalysis.exe /eos/cms/store/group/cmst3/group/slowmuons/ZmumuKBMTFSkims/Scouting_2024I_part1.root output_ZmumuKBMTF/Scouting_2024I_part1.root data_obs KBMTF
./ZmumuAnalysis.exe /eos/cms/store/group/cmst3/group/slowmuons/ZmumuKBMTFSkims/Scouting_2024I_part2.root output_ZmumuKBMTF/Scouting_2024I_part2.root data_obs KBMTF
hadd -f  output_ZmumuKBMTF/Scouting_2024.root output_ZmumuKBMTF/Scouting_2024G_part1.root output_ZmumuKBMTF/Scouting_2024G_part2.root output_ZmumuKBMTF/Scouting_2024G_part3.root output_ZmumuKBMTF/Scouting_2024G_part4.root output_ZmumuKBMTF/Scouting_2024G_part5.root output_ZmumuKBMTF/Scouting_2024G_part6.root output_ZmumuKBMTF/Scouting_2024H.root output_ZmumuKBMTF/Scouting_2024I_part1.root output_ZmumuKBMTF/Scouting_2024I_part2.root
python3 Create_fake_Zmumu.py --selection="ZmumuKBMTF"
hadd -f datacard_ZmumuKBMTF.root output_ZmumuKBMTF/DY.root output_ZmumuKBMTF/DYall.root output_ZmumuKBMTF/Scouting_2024.root output_ZmumuKBMTF/Fake.root
python3 Draw_Zmumu.py --selection="ZmumuKBMTF"


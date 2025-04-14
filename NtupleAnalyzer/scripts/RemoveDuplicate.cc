#include <TFile.h>
#include <TTree.h>
#include "tr_Tree.h"
#include <iostream>

using namespace std;

int main(int argc, char** argv) {

    std::string input = *(argv + 1);
    std::string output = *(argv + 2);

    TFile *inFile = new TFile(input.c_str());
    cout<<"XXXXXXXXXXXXX "<<input.c_str()<<" XXXXXXXXXXXX"<<endl;
    TTree *oldTree = (TTree*) inFile->Get("Events");
    
    // Get the branch of interest
    unsigned int run;
    unsigned int luminosityBlock;
    unsigned int bunchCrossing;
    unsigned int orbitNumber;
    oldTree->SetBranchAddress("run", &run);
    oldTree->SetBranchAddress("luminosityBlock", &luminosityBlock);
    oldTree->SetBranchAddress("bunchCrossing", &bunchCrossing);
    oldTree->SetBranchAddress("orbitNumber", &orbitNumber);
    oldTree->SetBranchAddress("eta1", &eta1);
    oldTree->SetBranchAddress("nstub1", &nstub1);
    oldTree->SetBranchAddress("bxspread1", &bxspread1);

    // Create output file and clone tree structure
    TFile *outFile = new TFile(output.c_str(), "RECREATE");
    TTree *newTree = oldTree->CloneTree(0); // Create an empty tree with the same structure

    unsigned int prev_run = 0; 
    unsigned int prev_luminosityBlock = 0;
    unsigned int prev_bunchCrossing = 0;
    unsigned int prev_orbitNumber = 0;
    float prev_eta1 = 100;
    int max_value = 0;
    Long64_t max_entry = -1;

    // Loop over entries
    Long64_t nentries = oldTree->GetEntries();
    for (Long64_t i = 0; i < nentries; i++) {
       oldTree->GetEntry(i);
       if (i % 100000 == 0) fprintf(stdout, "\r  Processed events: %8d of %8d ", i, nentries);
       fflush(stdout);
		
       bool is_same_track = (run==prev_run and luminosityBlock==prev_luminosityBlock and orbitNumber==prev_orbitNumber and fabs(bunchCrossing-prev_bunchCrossing)<5 and fabs(eta1-prev_eta1)<0.1);
       if (i == 0 || !is_same_track) {
            // If it's a new group, process the previous one
            if (i > 0 && max_entry >= 0) {
                oldTree->GetEntry(max_entry);
                newTree->Fill();
		oldTree->GetEntry(i);
            }

            // Start a new group
            max_value = nstub1;
            max_entry = i;
        } else {
            // If still in the same group, update the max if needed
            if (nstub1 > max_value) {
                max_value = nstub1;
                max_entry = i;
            }
        }

        prev_run = run;
        prev_luminosityBlock = luminosityBlock;
        prev_orbitNumber = orbitNumber;
        prev_bunchCrossing = bunchCrossing;
        prev_eta1 = eta1;
    }

    // Handle last group
    if (max_entry >= 0) {
        oldTree->GetEntry(max_entry);
        newTree->Fill();
    }

    // Save and clean up
    newTree->Write();
    outFile->Close();
    inFile->Close();
    
    delete inFile;
    delete outFile;
    //delete oldTree;
    //delete newTree;
}


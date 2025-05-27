// Load your file and tree
TFile *file = TFile::Open("your_file.root");
TTree *tree = (TTree*)file->Get("Events");

// Set up branches
int runNumber, bunchCrossing;
tree->SetBranchAddress("runNumber", &runNumber);
tree->SetBranchAddress("bunchCrossing", &bunchCrossing);

// Example mappings (fill these with your real data)
std::map<int, std::string> runToScheme = {
    {12345, "SchemeA"},
    {12346, "SchemeB"}
};

std::map<std::string, std::vector<int>> schemeToBX = {
    {"SchemeA", {1, 2, 3, 5, 7}},
    {"SchemeB", {10, 11, 12, 15}}
};

// Loop through entries
Long64_t nEntries = tree->GetEntries();
for (Long64_t i = 0; i < nEntries; ++i) {
    tree->GetEntry(i);

    auto schemeIt = runToScheme.find(runNumber);
    if (schemeIt == runToScheme.end()) {
        std::cerr << "Unknown run number: " << runNumber << std::endl;
        continue;
    }

    const std::string &scheme = schemeIt->second;
    const std::vector<int> &bxList = schemeToBX[scheme];

    // Efficient check using binary search if bxList is sorted
    bool found = std::binary_search(bxList.begin(), bxList.end(), bunchCrossing);

    if (found) {
        std::cout << "Event " << i << ": BX " << bunchCrossing
                  << " is in scheme " << scheme << std::endl;
    } else {
        std::cout << "Event " << i << ": BX " << bunchCrossing
                  << " NOT in scheme " << scheme << std::endl;
    }
}


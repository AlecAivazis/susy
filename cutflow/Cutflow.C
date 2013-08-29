// C++
#include <vector>
#include <set>
#include <iostream>

// ROOT
#include "TDirectory.h"
#include "TTreeCache.h"
#include "Math/VectorUtil.h"

// header
#include "Cutflow.h"

using namespace std;

void Cutflow::draw(TChain* chainZ, int numFiles){

    TChain *chain = new TChain("Events");

    TObjArray *listOfFiles = chainZ->GetListOfFiles();
    TIter fileIter(listOfFiles);
    TFile *currentFile = 0;

    int fileCounter = 0;
  
    while ( (currentFile = (TFile*)fileIter.Next()) ) {

        fileCounter++;
    
        if (fileCounter > numFiles && numFiles !=0) {
            break;
        }
        
        cout << "looking at file " <<currentFile->GetTitle() << endl;

        chain->Add(currentFile->GetTitle());

    }
    
    cout << "Source: " << chain->GetEntries() << endl;

    

}

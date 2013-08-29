// C++
#include <vector>
#include <set>
#include <iostream>

// ROOT
#include "TDirectory.h"
#include "TTreeCache.h"
#include "Math/VectorUtil.h"
#include "TCut.h"

// CMS2
#include "CMS2.h"

// header
#include "Cutflow.h"

using namespace std;
using namespace tas;

void Cutflow::draw(TChain* chainZ, int numFiles){
    
    // create chain containing the files
    TChain *chain = new TChain("Events");

    TH1F *histo = new TH1F("", "", 60, 0, 300);

    TObjArray *listOfFiles = chainZ->GetListOfFiles();
    TIter fileIter(listOfFiles);
    TFile *currentFile = 0;

    int fileCounter = 0;
  
    while ( (currentFile = (TFile*)fileIter.Next()) ) {

        fileCounter++;
    
        if (fileCounter > numFiles && numFiles !=0) {
            break;
        }

        /*

        TFile f( currentFile->GetTitle());
        TTree *tree = (TTree*)f.Get("Events");
        TTreeCache::SetLearnEntries(10);
        tree->SetCacheSize(128*1024*1024);
        
        cms2.Init(tree);

        unsigned int nEventsTree = tree->GetEntriesFast();
        
        for (unsigned int event =0; event < nEventsTree; ++event){
            
            tree->LoadTree(event);
            cms2.GetEntry(event);

            float maxPt = -1;
            int index = -1;

            for (unsigned int i = 0; i< hyp_p4().size(); i++){

                float sumPt = hyp_lt_p4().at(i).pt() + hyp_ll_p4().at(i).pt();

                if (sumPt > maxPt){
                    maxPt = sumPt;
                    index = i;
                }
            }
            
            cout << index << endl;


        }

        */
        chain->Add(currentFile->GetTitle());

    }

    
    

    
    TCut weight("evt_scale1fb * 19.5");
    TCut weight_tt("evt_scale1fb * (numEvents / 3465) * 19.5");
    TCut None("hyp_p4.size()>1");


    cout << "Source: " << chain->GetEntries() << endl;

    chain->Draw("hyp_ll_p4.at(0).pt()>>histo", None); 
    std::cout<<"Source v2 - " << histo->GetEntries() << std::endl;
    

}

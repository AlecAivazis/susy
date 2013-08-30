// C++
#include <iostream>
#include <vector>
#include <set>

// ROOT
#include "TDirectory.h"
#include "TTreeCache.h"
#include "Math/VectorUtil.h"

// CMS2
#include "CMS2.h"

#include "/home/users/aaivazis/CORE/muonSelections.h"
#include "/home/users/aaivazis/CORE/electronSelections.h"
#include "/home/users/aaivazis/CORE/ssSelections.h"

// header
#include "ScanChain.h"

using namespace std;
using namespace tas;


void babyMaker::ScanChain(TChain* chain, std::string baby_name, unsigned int numEvent){

    if (numEvent != 0 ){
        cout << "Processing the first " << numEvent << " file(s)" << endl;
    }

  MakeBabyNtuple( Form("/home/users/aaivazis/susy/babymaker/minis%s.root", baby_name.c_str()) );

  // File Loop
  int nEvents = chain->GetEntries();
  unsigned int nEventsTotal = 0;
  TObjArray *listOfFiles = chain->GetListOfFiles();
  TIter fileIter(listOfFiles);
  TFile *currentFile = 0;
  int nEventsMini = 0;

  unsigned int fileCounter = 0;

  int oppositeChargedCounter =0;
  int ll_Pt20Counter = 0;
  int lt_Pt20Counter = 0;
  int typeCounter = 0;
  int ll_etaCounter = 0;
  int lt_etaCounter = 0;
  int isoCounter = 0;
  
  while ( (currentFile = (TFile*)fileIter.Next()) ) {

      fileCounter++;
    
      if (fileCounter > numEvent && numEvent !=0) {
          break;
      }

    
      // Get File Content
      TFile f( currentFile->GetTitle() );
      TTree *tree = (TTree*)f.Get("Events");
      TTreeCache::SetLearnEntries(10);
      tree->SetCacheSize(128*1024*1024);
      cms2.Init(tree);
    
    
      // Event Loop
      unsigned int nEventsTree = tree->GetEntriesFast();

      nEventsMini = nEventsMini + nEventsTree;

      for(unsigned int event = 0; event < nEventsTree; ++event) {
    

          // Get Event Content
          tree->LoadTree(event);
          cms2.GetEntry(event);
          ++nEventsTotal;




          // cut flow counters

          int counter = 0;
      


          // only grab the hypothesis with the biggest pt
          for (unsigned int i = 0; i< hyp_p4().size(); i++){
         
              if (hyp_ll_charge().at(i)*hyp_lt_charge().at(i) < 0)  continue;
          
              /*
                if (hyp_ll_p4().at(i).pt() < 20) continue;
                if (hyp_lt_p4().at(i).pt() < 20) continue;
                if (hyp_type().at(i) == 3) continue;
                if (hyp_ll_p4().at(i).eta() > 2.4) continue;
                if (hyp_lt_p4().at(i).eta() > 2.4) continue;
                if (!samesign2011::isNumeratorHypothesis(i)) continue;
              */
      
              counter ++;
        
          }
      
          if (counter < hyp_p4().size()) {
              oppositeChargedCounter++;
          }

     
      
      }

  }
  cout << "Source: " << nEventsMini << endl;
  cout << "Oppositely Charged: " << oppositeChargedCounter << endl;
  
  return;
}

// C++
#include <iostream>
#include <vector>
#include <set>
#include <fstream>

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


void babyMaker::ScanChain(TChain* chain, std::string sample_name, unsigned int numEvent){

    if (numEvent != 0 ){
        cout << "Processing the first " << numEvent << " file(s)" << endl;
    }


  // File Loop
  unsigned int nEventsTotal = 0;
  TObjArray *listOfFiles = chain->GetListOfFiles();
  TIter fileIter(listOfFiles);
  TFile *currentFile = 0;
  int nEventsMini = 0;

  unsigned int fileCounter = 0;

  int goodCounter =0;
  int osCounter = 0;
  int bTagsCounter = 0;
  int typeCounter = 0;
  int ptCounter =0;
  
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

          // int counter = hyp_p4().size();
          int _osCounter =0; 
          int _goodCounter = 0;
          int _typeCounter = 0;

          int jetCounter = 0;
          
          float looseDiscriminant = .244;
          
          float maxPt = -1;

          for (unsigned int i = 0; i< hyp_p4().size(); i++){
         
              if (!samesign2011::isNumeratorHypothesis(i)) continue;
              if (hyp_ll_p4().at(i).pt() < 20) continue;
              if (hyp_lt_p4().at(i).pt() < 20) continue;
              if (abs(hyp_ll_p4().at(i).eta()) > 2.4) continue;
              if (abs(hyp_lt_p4().at(i).eta()) > 2.4) continue;
              _goodCounter++;
              
              if (hyp_ll_charge().at(i)*hyp_lt_charge().at(i) > 0)  continue;
              _osCounter++;
              
              if (hyp_type().at(i) == 3) continue;
              _typeCounter++;

              maxPt = (min(hyp_ll_p4().at(i).pt(), hyp_lt_p4().at(i).pt()) > maxPt) ? min(hyp_ll_p4().at(i).pt(), hyp_lt_p4().at(i).pt()) : maxPt;
              
          }
          

          if (_goodCounter > 0) goodCounter++;
          else continue;

          if (_osCounter > 0) osCounter++;
          else continue;
          
          if (maxPt == -1) continue;
      
          if (_typeCounter == 0 ) continue;
          typeCounter++;
              
          for (unsigned int k = 0; k < pfjets_p4().size(); k++){

              if (pfjets_p4().at(k).pt() < 20) continue;
              if (abs(pfjets_p4().at(k).eta()) > 2.4) continue;
                  
              float _bTag = pfjets_combinedSecondaryVertexBJetTag().at(k);
              if (_bTag > looseDiscriminant){
                  jetCounter++;
              }
          }
          if (jetCounter >= 2) bTagsCounter++;
          else continue;
  
          
          if (maxPt > 40) ptCounter++;
          else continue;
          
      }
  }
  
  ofstream stream;
  stream.open("cutflow.txt", ios::app);

  stream << sample_name << ": " << endl;
  stream << Form("Source: %d", nEventsMini) << endl;
  stream << Form("'Good' Hypothesis (ID/Isolation/eta/Pt): %d (%.2f)", goodCounter, double(goodCounter/nEventsMini)) << endl;
  stream << Form("Oppositely Charged: %d (%.2f)", osCounter, double(osCounter/nEventsMini)) << endl;
  stream << Form("Ignoring ee events: %d (%.2f)", typeCounter, double(typeCounter/nEventsMini)) << endl;
  stream << Form("nBtags > 2: %d (%.2f)", bTagsCounter, double(bTagsCounter/nEventsMini)) << endl;
  stream << Form("Hypothesis Pt > 40: %d (%.2f)", ptCounter, double(ptCounter/nEventsMini)) << endl;
  stream << "--------------------------------" << endl;

  stream.close();
  
  return;
}

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


void babyMaker::ScanChain(TChain* chain, std::string sample_name, unsigned int numEvent, bool showControlRegions){

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

  double goodCounter =0;
  double osCounter = 0;
  double bTagsCounter = 0;
  double typeCounter = 0;
  double ptCounter =0;
  double CR1counter =0;
  double CR2counter =0;
  double CR3counter =0;
  
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

          int index = 0;

          int jetCounter = 0;
          
          float looseDiscriminant = .244;
          
          float maxPt = -1;

          float avgM = 0 ; 
          float deltaM = 999;
        

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
              
              float maxPtOld = maxPt;
              maxPt = (hyp_ll_p4().at(i) + hyp_lt_p4().at(i)).pt() > maxPt ? (hyp_ll_p4().at(i) + hyp_lt_p4().at(i)).pt() : maxPt;

              
              if (maxPt > maxPtOld){
                  index = i;
              }
              
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
              if (_bTag >= looseDiscriminant){
                  jetCounter++;

                  if (!showControlRegions) continue;
                  
                  float val1 = (hyp_ll_p4().at(index) + pfjets_p4().at(k)).mass();

                  for (unsigned int j = 0; j < pfjets_p4().size(); j++){
                      
                      if (pfjets_p4().at(j).pt() < 20) continue;
                      if (abs(pfjets_p4().at(j).eta()) > 2.4) continue;
                  
                      float l_bTag = pfjets_combinedSecondaryVertexBJetTag().at(j);
                      if (l_bTag >= looseDiscriminant){
                          
                          float val2 =  (hyp_ll_p4().at(index) + pfjets_p4().at(j)).mass();
                          
                          float deltaMOld = deltaM;
                          deltaM = (val2-val1)/2 < deltaM ? (val2-val1)/2 : deltaM; 
                          
                          if (deltaM < deltaMOld){
                              avgM = (val1+val2)/2;
                          }
                      }
                  }
              }
          }

          if (jetCounter >= 2) bTagsCounter++;
          else continue;
  
          
          if (maxPt > 40) ptCounter++;
          else continue;
                  
          if (!showControlRegions) continue;

          if ((avgM >= 50 && avgM <= 350) && (deltaM > -150 && deltaM < 150)) CR1counter++;
          if ((avgM >= 100 && avgM <= 300) && (deltaM > -100 && deltaM < 100)) CR2counter++;
          if ((avgM >= 150 && avgM <= 250) && (deltaM > -50 && deltaM < 50)) CR3counter++;
          
      }
  }
  
  ofstream stream;
  stream.open("cutflow.txt", ios::app);

  stream << sample_name << ": " << endl;
  stream << Form("Source: %d", nEventsMini) << endl;
  stream << Form("'Good' Hypothesis (ID/Isolation/eta/Pt): %.0f (%.2f)", goodCounter, goodCounter/nEventsMini * 100) << endl;
  stream << Form("Oppositely Charged: %.0f (%.2f)", osCounter, osCounter/nEventsMini * 100) << endl;
  stream << Form("Ignoring ee events: %.0f (%.2f)", typeCounter, typeCounter/nEventsMini * 100) << endl;
  stream << Form("nBtags > 2: %.0f (%.2f)", bTagsCounter, bTagsCounter/nEventsMini * 100) << endl;
  stream << Form("Hypothesis Pt > 40: %.0f (%.2f)", ptCounter, ptCounter/nEventsMini * 100) << endl;
  stream << "--------------------------------" << endl;

  if (showControlRegions){

      stream << Form("Control Region 1: %.1f", (CR1counter/nEventsMini) * 100 ) <<  " " << CR1counter/9 << endl; 
      stream << Form("Control Region 2: %.1f", (CR2counter/nEventsMini) * 100 ) << " " << CR2counter/4 << endl; 
      stream << Form("Control Region 3: %.1f", (CR3counter/nEventsMini) * 100 ) << " " << CR3counter/1 << endl; 
      stream << "--------------------------------" << endl;
  }

  stream.close();
  
  return;
}

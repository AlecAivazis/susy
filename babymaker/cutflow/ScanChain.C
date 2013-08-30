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

  int oppositeChargedCounter =0;
  int ptCounter = 0;
  int typeCounter = 0;
  int etaCounter = 0;
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

          // int counter = hyp_p4().size();
          int counter =0; 

          for (unsigned int i = 0; i< hyp_p4().size(); i++){
         
              if (hyp_ll_charge().at(i)*hyp_lt_charge().at(i) > 0)  continue;
      
              counter++;
        
          }
      
          if (counter > 0) {
              oppositeChargedCounter++;
          }
      }
      
      for(unsigned int event = 0; event < nEventsTree; ++event) {
    

          // Get Event Content
          tree->LoadTree(event);
          cms2.GetEntry(event);
          ++nEventsTotal;

          // int counter = hyp_p4().size();
          int counter =0; 

          for (unsigned int i = 0; i< hyp_p4().size(); i++){
         
              if (hyp_ll_charge().at(i)*hyp_lt_charge().at(i) > 0)  continue;
              if (hyp_ll_p4().at(i).pt() < 20) continue;
              if (hyp_lt_p4().at(i).pt() < 20) continue;
      
              counter++;
        
          }
      
          if (counter > 0) {
              ptCounter++;
          }
      }
      for(unsigned int event = 0; event < nEventsTree; ++event) {
    

          // Get Event Content
          tree->LoadTree(event);
          cms2.GetEntry(event);
          ++nEventsTotal;

          // int counter = hyp_p4().size();
          int counter =0; 

          for (unsigned int i = 0; i< hyp_p4().size(); i++){
         
              if (hyp_ll_charge().at(i)*hyp_lt_charge().at(i) > 0)  continue;
              
              if (hyp_ll_p4().at(i).pt() < 20) continue;
              if (hyp_lt_p4().at(i).pt() < 20) continue;
              if (hyp_type().at(i) == 3) continue;
      
              counter++;
        
          }
      
          if (counter > 0) {
              typeCounter++;
          }
      }

      for(unsigned int event = 0; event < nEventsTree; ++event) {
    

          // Get Event Content
          tree->LoadTree(event);
          cms2.GetEntry(event);
          ++nEventsTotal;

          // int counter = hyp_p4().size();
          int counter =0; 

          for (unsigned int i = 0; i< hyp_p4().size(); i++){
         
              if (hyp_ll_charge().at(i)*hyp_lt_charge().at(i) > 0)  continue;
              
              if (hyp_ll_p4().at(i).pt() < 20) continue;
              if (hyp_lt_p4().at(i).pt() < 20) continue;
              if (hyp_type().at(i) == 3) continue;
              
              if (hyp_ll_p4().at(i).eta() > 2.4) continue;
              if (hyp_lt_p4().at(i).eta() > 2.4) continue;
      
              counter++;
        
          }
      
          if (counter > 0) {
              etaCounter++;
          }
      }
      for(unsigned int event = 0; event < nEventsTree; ++event) {
    

          // Get Event Content
          tree->LoadTree(event);
          cms2.GetEntry(event);
          ++nEventsTotal;

          // int counter = hyp_p4().size();
          int counter =0; 

          for (unsigned int i = 0; i< hyp_p4().size(); i++){
         
              if (hyp_ll_charge().at(i)*hyp_lt_charge().at(i) > 0)  continue;
              
              if (hyp_ll_p4().at(i).pt() < 20) continue;
              if (hyp_lt_p4().at(i).pt() < 20) continue;
              if (hyp_type().at(i) == 3) continue;
              
                if (hyp_ll_p4().at(i).eta() > 2.4) continue;
                if (hyp_lt_p4().at(i).eta() > 2.4) continue;
                if (!samesign2011::isNumeratorHypothesis(i)) continue;
              
      
              counter++;
        
          }
      
          if (counter > 0) {
              isoCounter++;
          }
      }
  }
  
  ofstream stream;
  stream.open("cutflow.txt");

  stream << sample_name << ": " << endl;
  stream << "Source: " << nEventsMini << endl;
  stream << "Oppositely Charged: " << oppositeChargedCounter << endl;
  stream << "Hyp pt > 20: " << ptCounter << endl;
  stream << "Ignoring ee events: " << typeCounter << endl;
  stream << "Eta > 2.4: " << etaCounter << endl;
  stream << "ID/Isolation requirements: " << isoCounter << endl;
  stream << "--------------------------------" << endl;

  stream.close();
  
  return;
}

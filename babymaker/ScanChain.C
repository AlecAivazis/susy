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

// header
#include "ScanChain.h"

using namespace std;
using namespace tas;

void babyMaker::ScanChain(TChain* chain, std::string baby_name){

  MakeBabyNtuple( Form("%s.root", baby_name.c_str()) );

  // File Loop
  int nDuplicates = 0;
  int nEvents = chain->GetEntries();
  unsigned int nEventsChain = nEvents;
  unsigned int nEventsTotal = 0;
  TObjArray *listOfFiles = chain->GetListOfFiles();
  TIter fileIter(listOfFiles);
  TFile *currentFile = 0;
  while ( (currentFile = (TFile*)fileIter.Next()) ) {

    // Get File Content
    TFile f( currentFile->GetTitle() );
    TTree *tree = (TTree*)f.Get("Events");
    TTreeCache::SetLearnEntries(10);
    tree->SetCacheSize(128*1024*1024);
    cms2.Init(tree);
    
    // Event Loop
    unsigned int nEventsTree = tree->GetEntriesFast();


    for( unsigned int event = 0; event < nEventsTree; ++event) {
    

      // Get Event Content
      tree->LoadTree(event);
      cms2.GetEntry(event);
      ++nEventsTotal;

      float maxPt = 0;
      int index = -1;


      // only grab the hypothesis with the biggest pt
      for (unsigned int i = 0; i< hyp_p4().size(); i++){

          int lt_id_ = hyp_lt_id().at(i);
          int lt_idx = hyp_lt_index().at(i);
          int ll_id_ = hyp_ll_id().at(i);
          int ll_idx = hyp_ll_index().at(i);	
          if (hyp_ll_charge().at(i)*hyp_lt_charge().at(i) > 0) continue;

          if (hyp_ll_p4().at(i).pt() < 20) continue;
          if (hyp_lt_p4().at(i).pt() < 20) continue;
          if (hyp_ll_p4().at(i).eta() > 2.4) continue;
          if (hyp_lt_p4().at(i).eta() > 2.4) continue;

       
          if (hyp_type().at(i) != 0) continue;

          float sumPt = hyp_lt_p4().at(i).pt() + hyp_ll_p4().at(i).pt();

          if (sumPt > maxPt){
              maxPt = sumPt;
              index = i;
          }
      }

      if (index == -1) continue;


    
      // Progress
      CMS2::progress( nEventsTotal, nEventsChain );

      InitBabyNtuple();

      //analysis

      met = evt_pfmet();
      jets_p4 = pfjets_p4();
      type = hyp_type().at(index);

      ll_p4 = hyp_ll_p4().at(index);
      ll_id = hyp_ll_id().at(index);
      total_p4 = hyp_p4().at(index);
      ll_charge = hyp_ll_charge().at(index);
      ll_index = hyp_ll_index().at(index);

      lt_p4 = hyp_lt_p4().at(index);
      lt_charge = hyp_lt_charge().at(index);
      lt_id = hyp_lt_id().at(index);
      lt_index = hyp_lt_index().at(index);
      btagDiscriminant = pfjets_combinedSecondaryVertexBJetTag();
      scale_1fb = evt_scale1fb();
      //jets_p4 = pfjets_p4().at(index);

      float looseDiscriminant = .244;
      float mediumDiscriminant = .679;
      float tightDiscriminant = .89;


      int _nJetsPt20Loose = 0;
      int _nJetsPt30Loose = 0;
      int _nJetsPt40Loose = 0;
      
      
      int _nJetsPt20Medium = 0;
      int _nJetsPt30Medium = 0;
      int _nJetsPt40Medium = 0;
      
      int _nJetsPt20Tight = 0;
      int _nJetsPt30Tight = 0;
      int _nJetsPt40Tight = 0;
      int _nJets = 0;
      
      std::vector<LorentzVector> _jets_p4_min ;
     
      for(unsigned int k = 0; k < pfjets_p4().size(); k++) {

          
                
          float dR_lt = ROOT::Math::VectorUtil::DeltaR(pfjets_p4().at(k), hyp_lt_p4().at(index));
          float dR_ll = ROOT::Math::VectorUtil::DeltaR(pfjets_p4().at(k), hyp_ll_p4().at(index));
                    
          if (dR_ll < 0.4) continue;
          if (dR_lt < 0.4) continue;

          _nJets++ ;


          // count the number of jets for a variety of mass points
          if (pfjets_p4().at(k).pt() > 20){
              if (pfjets_combinedSecondaryVertexBJetTag().at(k) > looseDiscriminant){
                  _nJetsPt20Loose++ ;

                  _jets_p4_min.push_back(pfjets_p4().at(k));

              } 
              if (pfjets_combinedSecondaryVertexBJetTag().at(k) > mediumDiscriminant){
                  _nJetsPt20Medium++ ;
              }
              if (pfjets_combinedSecondaryVertexBJetTag().at(k) > tightDiscriminant){
                  _nJetsPt20Tight++ ;
              }
          }

          if (pfjets_p4().at(k).pt() > 30){
              if (pfjets_combinedSecondaryVertexBJetTag().at(k) > looseDiscriminant){
                  _nJetsPt30Loose++ ;
              } 
              if (pfjets_combinedSecondaryVertexBJetTag().at(k) > mediumDiscriminant){
                  _nJetsPt30Medium++ ;
              }
              if (pfjets_combinedSecondaryVertexBJetTag().at(k) > tightDiscriminant){
                  _nJetsPt30Tight++ ;
              }
          }

          if (pfjets_p4().at(k).pt() > 40){
              if (pfjets_combinedSecondaryVertexBJetTag().at(k) > looseDiscriminant){
                  _nJetsPt40Loose++ ;
              } 
              if (pfjets_combinedSecondaryVertexBJetTag().at(k) > mediumDiscriminant){
                  _nJetsPt40Medium++ ;
              }
              if (pfjets_combinedSecondaryVertexBJetTag().at(k) > tightDiscriminant){
                  _nJetsPt40Tight++ ;
              }
          }
      }
      nJetsPt20Loose = _nJetsPt20Loose;
      nJetsPt30Loose = _nJetsPt30Loose;
      nJetsPt40Loose = _nJetsPt40Loose;
      
      nJetsPt20Medium = _nJetsPt20Medium;
      nJetsPt30Medium = _nJetsPt30Medium;
      nJetsPt40Medium = _nJetsPt40Medium;
     
      nJetsPt20Tight = _nJetsPt20Tight;
      nJetsPt30Tight = _nJetsPt30Tight;
      nJetsPt40Tight = _nJetsPt40Tight;

      nJets = _nJets;
      

      jets_p4_min = _jets_p4_min;
      

      FillBabyNtuple();
    }//end loop on events in a file
  
    
    delete tree;
    f.Close();
  }//end loop on files
  
  if ( nEventsChain != nEventsTotal ) {
    std::cout << "ERROR: number of events from files is not equal to total number of events" << std::endl;
  }

  cout << nDuplicates << " duplicate events were skipped." << endl;

  CloseBabyNtuple();

  return;
}

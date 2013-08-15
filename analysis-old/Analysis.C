// Usage:
// > root -b doAll.C

// C++
 
#include <iostream>
#include <vector>
// ROOT
#include "TBenchmark.h"
#include "TChain.h"
#include "TDirectory.h"
#include "TFile.h"
#include "TROOT.h"
#include "TTreeCache.h"
#include "TMath.h"
#include "THStack.h"
#include "Math/VectorUtil.h"
#include "Math/Vector4D.h"
#include "TH2F.h"

// CMS2
#include "CMS2.h"

// File Numbers
// 0 = signal
// 

using namespace std;
using namespace tas;
using namespace ROOT::Math;
int Analysis( TChain* chain, bool fast = true, int nEvents = -1, string skimFilePrefix = "test") {

  // Benchmark
  TBenchmark *bmark = new TBenchmark();
  bmark->Start("benchmark");

  // susy Histograms
  TH1F *susy_met = new TH1F("susy_met", "susy", 200,0,200);
  TH1F *susy_njets = new TH1F("susy_njets", "susy", 200,0,200);
  TH1F *susy_ll_pt = new TH1F("susy_ll_pt", "susy", 200,0,200);
  TH1F *susy_lt_pt = new TH1F("susy_lt_pt", "susy", 200,0,200);
  TH1F *susy_stop_pt = new TH1F("susy_stop_pt", "susy", 200,0,200);
  TH1F *susy_mu_mass = new TH1F("susy_mu_mass", "susy", 200,0,200);

  susy_met->SetFillColor(kBlue);
  susy_njets->SetFillColor(kBlue);
  susy_ll_pt->SetFillColor(kBlue);
  susy_lt_pt->SetFillColor(kBlue);
  susy_stop_pt->SetFillColor(kBlue);
  susy_mu_mass->SetFillColor(kBlue);
  
  
  // tt Histograms
  TH1F *tt_met = new TH1F("tt_met", "susy", 200,0,200);
  TH1F *tt_njets = new TH1F("tt_njets", "susy", 200,0,200);
  TH1F *tt_ll_pt = new TH1F("tt_ll_pt", "susy", 200,0,200);
  TH1F *tt_lt_pt = new TH1F("tt_lt_pt", "susy", 200,0,200);
  TH1F *tt_stop_pt = new TH1F("tt_stop_pt", "susy", 200,0,200);
  TH1F *tt_mu_mass = new TH1F("tt_mu_mass", "susy", 200,0,200);

  tt_met->SetFillColor(kYellow);
  tt_njets->SetFillColor(kYellow);
  tt_ll_pt->SetFillColor(kYellow);
  tt_lt_pt->SetFillColor(kYellow);
  tt_stop_pt->SetFillColor(kYellow);
  tt_mu_mass->SetFillColor(kYellow);
 

  // tt Histograms
  TH1F *dy_met = new TH1F("dy_met", "susy", 200,0,200);
  TH1F *dy_njets = new TH1F("dy_njets", "susy", 200,0,200);
  TH1F *dy_ll_pt = new TH1F("dy_ll_pt", "susy", 200,0,200);
  TH1F *dy_lt_pt = new TH1F("dy_lt_pt", "susy", 200,0,200);
  TH1F *dy_stop_pt = new TH1F("dy_stop_pt", "susy", 200,0,200);
  TH1F *dy_mu_mass = new TH1F("dy_mu_mass", "susy", 200,0,200);

  dy_met->SetFillColor(kRed);
  dy_njets->SetFillColor(kRed);
  dy_ll_pt->SetFillColor(kRed);
  dy_lt_pt->SetFillColor(kRed);
  dy_stop_pt->SetFillColor(kRed);
  dy_mu_mass->SetFillColor(kRed);


  // Loop over events to Analyze 
  float lumi = 20.0;
  unsigned int nEventsTotal = 0;
  unsigned int nEventsChain = chain->GetEntries();
  if( nEvents >= 0 ) nEventsChain = nEvents;
  TObjArray *listOfFiles = chain->GetListOfFiles();
  TIter fileIter(listOfFiles);
  TFile *currentFile = 0;

  // File Loop
  while ( (currentFile = (TFile*)fileIter.Next()) ) {

    int fileNumber = listOfFiles->IndexOf(currentFile);
    
    // Get File Content
    TFile *file = new TFile( currentFile->GetTitle() );
    TTree *tree = (TTree*)file->Get("tree");
    if(fast) TTreeCache::SetLearnEntries(10);
    if(fast) tree->SetCacheSize(128*1024*1024);
    cms2.Init(tree);
    
    // Loop over Events in current file
    if( nEventsTotal >= nEventsChain ) continue;
    unsigned int nEventsTree = tree->GetEntries();
    for( unsigned int event = 0; event < nEventsTree; ++event) {
    
      // Get Event Content
      if( nEventsTotal >= nEventsChain ) continue;
      if(fast) tree->LoadTree(event);
      cms2.GetEntry(event);
      ++nEventsTotal;
    
      // Progress
      CMS2::progress( nEventsTotal, nEventsChain );

      // Analysis Code
      int numJets = 0;
      float maxPt = 0;
      int index = -1;
      float minDiscriminant = .679;

      // this need to be hyp_p4().size() but i'm too tired to add the branch to the baby
      for(unsigned int i=0; i< total_p4().size(); i++) {
          int lt_id_ = lt_id().at(i);
          int lt_idx = lt_index().at(i);
          int ll_id_ = ll_id().at(i);
          int ll_idx = ll_index().at(i);	
          if (ll_charge().at(i)*lt_charge().at(i) > 0) continue;

          if (ll_p4().at(i).pt() < 20) continue;
          if (lt_p4().at(i).pt() < 20) continue;
          if (ll_p4().at(i).eta() > 2.4) continue;
          if (lt_p4().at(i).eta() > 2.4) continue;

          // should this be a cut like all of the others?
          // to limit the events we're analyzing to only those with muons
          // is this only define for the event as a whole? how do you do electron and muon
          
          if (type().at(i) != 0) continue;

  
          float sumPt = lt_p4().at(i).pt() +  ll_p4().at(i).pt();
          if (sumPt > maxPt){
              maxPt = sumPt;
              index = i;
          }
      }

  

      if (index > -1){

          for(unsigned int k = 0; k < jets_p4().size(); k++) {
                
              float dR_lt = VectorUtil::DeltaR(jets_p4().at(k), lt_p4().at(index));
              float dR_ll = VectorUtil::DeltaR(jets_p4().at(k), ll_p4().at(index));
                    
              if (dR_ll < 0.4) continue;
              if (dR_lt < 0.4) continue;
              if (jets_p4().at(k).pt() < 30) continue;
              if (btag().at(k) < minDiscriminant) continue;             

              numJets++;

          }

          if (fileNumber == 0){
              susy_met->Fill(met(), lumi* scale_1fb());
              susy_njets->Fill(numJets, lumi*scale_1fb());
              susy_ll_pt->Fill(ll_p4().at(index).pt(), lumi*scale_1fb());
              susy_lt_pt->Fill(lt_p4().at(index).pt(), lumi*scale_1fb());
              susy_stop_pt->Fill(total_p4().at(index).pt(), lumi*scale_1fb());
              susy_mu_mass->Fill(total_p4().at(index).mass(), lumi*scale_1fb());
              
          } else if (fileNumber == 1){
              tt_met->Fill(met(), lumi* scale_1fb());
              tt_njets->Fill(numJets, lumi*scale_1fb());
              tt_ll_pt->Fill(ll_p4().at(index).pt(), lumi*scale_1fb());
              tt_lt_pt->Fill(lt_p4().at(index).pt(), lumi*scale_1fb());
              tt_stop_pt->Fill(total_p4().at(index).pt(), lumi*scale_1fb());
              tt_mu_mass->Fill(total_p4().at(index).mass(), lumi*scale_1fb());
          
          } else if (fileNumber == 2){
              dy_met->Fill(met(), lumi* scale_1fb());
              dy_njets->Fill(numJets, lumi*scale_1fb());
              dy_ll_pt->Fill(ll_p4().at(index).pt(), lumi*scale_1fb());
              dy_lt_pt->Fill(lt_p4().at(index).pt(), lumi*scale_1fb());
              dy_stop_pt->Fill(total_p4().at(index).pt(), lumi*scale_1fb());
              dy_mu_mass->Fill(total_p4().at(index).mass(), lumi*scale_1fb());
          } 
                
      }   
    }
  
    // Clean Up
    delete tree;
    file->Close();
    delete file;
  }
  if ( nEventsChain != nEventsTotal ) {
    cout << Form( "ERROR: number of events from files (%d) is not equal to total number of events (%d)", nEventsChain, nEventsTotal ) << endl;
  }

  // Example Histograms
  susy_met->Draw();
  
  // return
  bmark->Stop("benchmark");
  cout << endl;
  cout << nEventsTotal << " Events Processed" << endl;
  cout << "------------------------------" << endl;
  cout << "CPU  Time:	" << Form( "%.01f", bmark->GetCpuTime("benchmark")  ) << endl;
  cout << "Real Time:	" << Form( "%.01f", bmark->GetRealTime("benchmark") ) << endl;
  cout << endl;
  delete bmark;
  return 0;
}

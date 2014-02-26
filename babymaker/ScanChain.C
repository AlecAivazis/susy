// C++
#include <iostream>
#include <vector>
#include <set>
#include <fstream>

// ROOT
#include "TDirectory.h"
#include "TTreeCache.h"
#include "Math/VectorUtil.h"
#include "Math/LorentzVector.h"

// CMS2
#include "CMS2.h"
#include "/home/users/aaivazis/CORE/electronSelections.h"
#include "/home/users/aaivazis/CORE/muonSelections.h"
#include "/home/users/aaivazis/CORE/ssSelections.h"
#include "/home/users/aaivazis/CORE/trackSelections.h"
#include "/home/users/aaivazis/CORE/eventSelections.h"
#include "/home/users/aaivazis/CORE/susySelections.h"

// header
#include "ScanChain.h"

typedef ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > LorentzVector;

using namespace std;
using namespace tas;
using namespace ROOT::Math::VectorUtil;

bool isValidPair(int hypIndex, int jetIndex){

    // require the generated pair to be either mu- b or mu+ bbar
    // 
 
    // if(genps_id().at(hypIndex) * genps_id().at(jetIndex) ) return false;
    
    // muons have id = 13
    // b's have id = 5
    // i need bbar and muon (or opposite)
    return genps_id().at(hypIndex) * genps_id().at(jetIndex) == -65;

}

void babyMaker::ScanChain(TChain* chain, std::string baby_name, unsigned int numEvent){


    if (numEvent != 0 ){
        cout << "Processing the first " << numEvent << " file(s)" << endl;
    }

  MakeBabyNtuple( Form("babies/%s.root", baby_name.c_str()) );

  // File Loop
  int nDuplicates = 0;
  int nEvents = chain->GetEntries();
  unsigned int nEventsChain = nEvents;
  unsigned int nEventsTotal = 0;
  TObjArray *listOfFiles = chain->GetListOfFiles();
  TIter fileIter(listOfFiles);
  TFile *currentFile = 0;
  int nEventsMini = 0;

  unsigned int fileCounter = 0;

  double _hypPt20Counter = 0;
  double _osCounter = 0;
  double _typeCounter = 0;
  double _etaCounter = 0;
  double _muonIdCounter = 0;
  double _muonIsoCounter = 0;
  double _electronIdCounter = 0;
  double _electronIsoCounter = 0;
  double _eventsCounter = 0;
  double _muonCounter = 0;

  double hypCounter = 0;
  double eventHypCounter = 0;

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
      
      // Progress
      CMS2::progress( nEventsTotal, nEventsChain );

      int index = -1;
      float _maxPt = 0.0;

      // count number of hypotheses
      if (hyp_p4().size() != 0) eventHypCounter++;

      hypCounter = hypCounter + hyp_p4().size();
      
      // apply cuts to hypotheses
      for (unsigned int i = 0; i< hyp_p4().size(); i++){

          if (hyp_ll_p4().at(i).pt() < 20) continue;
          if (hyp_lt_p4().at(i).pt() < 20) continue;
          _hypPt20Counter++;
          
          // oppositely charged leptons - NOTE: NOT WHAT ALEX DOES (uses id voodoo hoodoo)
          if (hyp_ll_charge().at(i)*hyp_lt_charge().at(i) > 0) continue;
          _osCounter++;

          // require one muon
          if (abs(hyp_ll_id().at(i)) != 13 || abs(hyp_lt_id().at(i)) != 13) continue;
          _typeCounter++;

          // eta < 2.4
          if (fabs(hyp_ll_p4().at(i).eta()) > 2.4) continue;
          if (fabs(hyp_lt_p4().at(i).eta()) > 2.4) continue;
          _etaCounter++;

          // count number of muons before ID/iso
          if (abs(hyp_ll_id().at(i)) == 13 && abs(hyp_lt_id().at(i)) == 13) {
	      _muonCounter++;
          }

          /* This iso is too tight. Saving in case they change their mind....
             if(!isGoodLepton(hyp_lt_id().at(i), hyp_lt_index().at(i))) continue;
             if(!isGoodLepton(hyp_ll_id().at(i), hyp_ll_index().at(i))) continue;
          */

          // electron id
          if (abs(hyp_ll_id().at(i) == 11) && !passElectronSelection_ZMet2012_v3_Iso(hyp_ll_index().at(i))) continue;
          if (abs(hyp_lt_id().at(i) == 11) && !passElectronSelection_ZMet2012_v3_Iso(hyp_lt_index().at(i))) continue;
          _electronIdCounter++;

          // muon id
          if (abs(hyp_ll_id().at(i)) == 13 && !muonId(hyp_ll_index().at(i), ZMet2012_v1)) continue;
          if (abs(hyp_lt_id().at(i)) == 13 && !muonId(hyp_lt_index().at(i), ZMet2012_v1)) continue;
          _muonIdCounter++;

          // isolation - variables
          double chiso_ll = mus_isoR03_pf_ChargedHadronPt().at(hyp_ll_index().at(i));
          double nhiso_ll = mus_isoR03_pf_NeutralHadronEt().at(hyp_ll_index().at(i));
          double emiso_ll = mus_isoR03_pf_PhotonEt().at(hyp_ll_index().at(i));
          double dbeta_ll = mus_isoR03_pf_PUPt().at(hyp_ll_index().at(i));
          double iso_ll = (chiso_ll + max(0.0, nhiso_ll + emiso_ll - 0.5 * dbeta_ll)) / hyp_ll_p4().at(i).pt();

          double chiso_lt = mus_isoR03_pf_ChargedHadronPt().at(hyp_lt_index().at(i));
          double nhiso_lt = mus_isoR03_pf_NeutralHadronEt().at(hyp_lt_index().at(i));
          double emiso_lt = mus_isoR03_pf_PhotonEt().at(hyp_lt_index().at(i));
          double dbeta_lt = mus_isoR03_pf_PUPt().at(hyp_lt_index().at(i));
          double iso_lt = (chiso_lt + max(0.0, nhiso_lt + emiso_lt - 0.5 * dbeta_lt)) / hyp_lt_p4().at(i).pt();
         
          // isolation - cuts
          if (abs(hyp_ll_id().at(i)) == 11 && iso_ll > 0.15) continue;
          if (abs(hyp_lt_id().at(i)) == 11 && iso_lt > 0.15) continue;
          if (abs(hyp_ll_id().at(i)) == 13 && iso_ll > 0.2) continue;
          if (abs(hyp_lt_id().at(i)) == 13 && iso_lt > 0.2) continue;

          // count the number of electrons and muons that pass
          // if it's not a mu/mu then it's an e/mu
          if (abs(hyp_lt_id().at(i)) == 13 && abs(hyp_ll_id().at(i)) == 13){
              _muonIsoCounter++;
          } else {
              _electronIsoCounter++;
          }

          // select the highest pt hypothesis
          float sumPt = hyp_lt_p4().at(i).pt() + hyp_ll_p4().at(i).pt();
         
          if (sumPt > _maxPt){
              _maxPt = sumPt;
              index = i;
          }
          
      }

      if (index == -1) continue;
      _eventsCounter++;

      /*
      now that we've selected a hypothesis, loop over the generated p4
      and find the matching particle, store its index and value
      float generatedVal1 = -1;
      float generatedVal2 = -1;
      int llGenerated = -1;
      int ltGenerated = -1;
      int jetllGenerated = -1;
      int jetltGenerated =-1;

      float ll_dRmin = 1001;
      float lt_dRmin = 1001;
      float llJet_dRmin = 1001;
      float ltJet_dRmin = 1001;

      for ( int i = 0; i < genps_p4().size(); i++ ){

          float deltaR = DeltaR(genps_p4().at(i), hyp_ll_p4().at(index));
          
          if (deltaR < ll_dRmin) {
              ll_dRmin = deltaR;
              llGenerated = i;
          }
      }
      
      for ( int i = 0; i < genps_p4().size(); i++ ){

          if (i == llGenerated) continue;

          float deltaR = DeltaR(genps_p4().at(i), hyp_lt_p4().at(index));
          
          if (deltaR < lt_dRmin) {
              lt_dRmin = deltaR;
              ltGenerated = i;
          }
      }

      for ( int i = 0; i < genps_p4().size(); i++ ){

          if (i == llGenerated || i == ltGenerated) continue;

          float deltaR = DeltaR(genps_p4().at(i), pfjets_p4().at(jetllIndex));
          
          if (deltaR < llJet_dRmin) {
              llJet_dRmin = deltaR;
              jetllGenerated = i;
          }
      }
  
      for ( int i = 0; i < genps_p4().size(); i++ ){

          if (i == llGenerated || i == ltGenerated || i == jetllGenerated) continue;

          float deltaR = DeltaR(genps_p4().at(i), pfjets_p4().at(jetltIndex));
          
          if (deltaR < ltJet_dRmin) {
              ltJet_dRmin = deltaR;
              jetltGenerated = i;
          }
      }    

      if (llGenerated != -1 && ltGenerated != -1 && jetllGenerated != -1 && jetltGenerated != -1){

          if (isValidPair(llGenerated, jetllGenerated))
              generatedVal1 = (genps_p4().at(llGenerated) + genps_p4().at(jetllGenerated)).mass();


          if (isValidPair(ltGenerated, jetltGenerated))
              generatedVal2 = (genps_p4().at(ltGenerated) + genps_p4().at(jetltGenerated)).mass();
     
      }

      */


      // create the ntuple
      InitBabyNtuple();

      // set the branch values
      met = evt_pfmet_type1cor();

      jets_p4 = pfjets_p4();
      jets_p4Correction = pfjets_corL1FastL2L3();

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
      numEvents = tree->GetEntries();
      file = Form("%s", currentFile->GetTitle());

      eventNumber = evt_event();
      runNumber = evt_run();
      lumiBlock = evt_lumiBlock();

      /*
      if (generatedVal2 != -1 && generatedVal1 != -1){
          generatedAvgMass = (generatedVal2 + generatedVal1)/2;
          generatedDeltaMass = (generatedVal2 - generatedVal1)/2;
      }
      */

      // fill that sucker
      FillBabyNtuple();


    } // end of loop over events in file

    delete tree;
    f.Close();

  } // end of loop over files

  if (nEventsChain != nEventsTotal){
      cout << "WARNING: The number of events added is not equal to the total number of events!" << endl;
  }


  cout << nDuplicates << " duplicate events were skipped." << endl;

  CloseBabyNtuple();

  ofstream stream;
  stream.open("cutflow.txt", ios::app);

  stream << baby_name << ": " << endl;
  stream << Form("Source (Events): %.0d", nEventsMini) << endl;
  stream << Form("Events with Hypothesis: %.0f (%.2f)", eventHypCounter, eventHypCounter/nEventsMini * 100) << endl;
  stream << Form("Source (Hypotheses): %.0f", hypCounter) << endl;
  stream << Form("Hypothesis Pt > 20: %.0f (%.2f, %.2f)",_hypPt20Counter, _hypPt20Counter/hypCounter * 100, 1-(_hypPt20Counter/hypCounter)) << endl;
  stream << Form("Oppositely Charged: %.0f (%.2f, %.2f)",_osCounter, _osCounter/hypCounter * 100, 1-(_osCounter/_hypPt20Counter)) << endl;
  stream << Form("Requiring one muon: %.0f (%.2f, %.2f)",_typeCounter, _typeCounter/hypCounter * 100, 1-(_typeCounter/_osCounter)) << endl;
  stream << Form("Eta < 2.4: %.0f (%.2f, %.2f)",_etaCounter, _etaCounter/hypCounter * 100, 1-(_etaCounter/_typeCounter)) << endl;
  stream << "Electron Id/Iso-" << endl; 
  stream << Form("e/mu passing ID: %.0f (%.2f, %.2f)", _electronIdCounter, _electronIdCounter/hypCounter * 100, 1-(_electronIdCounter/_etaCounter)) << endl;
  stream << Form("e/mu passing ISO: %.0f (%.2f, %.2f)",_electronIsoCounter, _electronIsoCounter/hypCounter * 100, 1-(_electronIsoCounter/_electronIdCounter)) << endl;
  stream << "Muon Id/Iso-" << endl; 
  stream << Form("# of muons : %.0f (%.2f)",_muonCounter, _muonCounter/hypCounter * 100) << endl;
  stream << Form("# muons passing ID: %.0f (%.2f, %.2f)",_muonIdCounter, _muonIdCounter/hypCounter * 100, 1-(_muonIdCounter/_etaCounter)) << endl;
  stream << Form("# muons passing ISO: %.0f (%.2f, %.2f)",_muonIsoCounter, _muonIsoCounter/hypCounter * 100, 1-(_muonIsoCounter/_muonIdCounter)) << endl;
  stream << "-" << endl;
  stream << Form("# of hypothesis passing ID/ISO: %.0f (%.2f)",(_muonIsoCounter + _electronIsoCounter), (_muonIsoCounter + _electronIsoCounter)/hypCounter * 100) << endl;
  stream << Form("# of events passing ID/ISO: %.0f (%.2f)",(_eventsCounter), (_eventsCounter)/eventHypCounter * 100) << endl;
//stream << Form("Muon Events: %.0f (%.2f)", muonCounter, muonCounter/nEventsMini * 100) << endl;
  stream << "--------------------------------" << endl;

  /*
    if (showControlRegions){v

    stream << Form("Control Region 1: %.1f", (CR1counter/nEventsMini) * 100 ) <<  " " << CR1counter/9 << endl; 
    stream << Form("Control Region 2: %.1f", (CR2counter/nEventsMini) * 100 ) << " " << CR2counter/4 << endl; 
    stream << Form("Control Region 3: %.1f", (CR3counter/nEventsMini) * 100 ) << " " << CR3counter/1 << endl; 
    stream << "--------------------------------" << endl;
    }
  */
  stream.close();
  

  return;
}


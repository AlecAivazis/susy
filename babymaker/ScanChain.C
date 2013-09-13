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
using namespace ROOT::Math::VectorUtil;

/*

enum IsolationType { DET_ISO, TIGHT_DET_ISO, COR_DET_ISO };


bool isIsolatedLepton(int id, int idx, enum IsolationType iso_type)
{
    // electrons
    if (abs(id) == 11) {
        if (iso_type == DET_ISO)
            return (pass_electronSelection(idx, electronSelection_ssV6_iso));
        else if (iso_type == COR_DET_ISO)
            return (electronIsolation_cor_rel_v1(idx, true) < 0.10);
        else if (iso_type == TIGHT_DET_ISO)
            return (electronIsolation_rel_v1(idx, true) < 0.10);
    }

    // muons
    if (abs(id) == 13) {
        if (iso_type == DET_ISO)
            return (muonIsoValue(idx, false) < 0.15);
        else if (iso_type == COR_DET_ISO)
            return (muonCorIsoValue(idx, false) < 0.10);
        else if (iso_type == TIGHT_DET_ISO)
            return (muonIsoValue(idx, false) < 0.10);
    }

    return false;
}

bool isNumeratorLepton(int id, int idx, enum IsolationType iso_type)
{
    return (samesign2011::isGoodLepton(id, idx) && isIsolatedLepton(id, idx, iso_type));
}

bool isNumeratorHypothesis(int idx, enum IsolationType iso_type = DET_ISO)
{
    if (!isNumeratorLepton(cms2.hyp_lt_id().at(idx), cms2.hyp_lt_index().at(idx), iso_type))
        return false;
    if (!isNumeratorLepton(cms2.hyp_ll_id().at(idx), cms2.hyp_ll_index().at(idx), iso_type))
        return false;

    return true;
}

*/

void babyMaker::ScanChain(TChain* chain, std::string baby_name, unsigned int numEvent){

    if (numEvent != 0 ){
        cout << "Processing the first " << numEvent << " file(s)" << endl;
    }

  MakeBabyNtuple( Form("minis/%s.root", baby_name.c_str()) );

  // File Loop
  int nDuplicates = 0;
  int nEvents = chain->GetEntries();
  unsigned int nEventsChain = nEvents;
  unsigned int nEventsTotal = 0;
  TObjArray *listOfFiles = chain->GetListOfFiles();
  TIter fileIter(listOfFiles);
  TFile *currentFile = 0;

  unsigned int fileCounter = 0;

  cout << "NumEvents : "<<  numEvent << endl;
  
  while ( (currentFile = (TFile*)fileIter.Next()) ) {

    fileCounter++;
    
    cout << "filecounter : "<< fileCounter <<endl;
    
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

    /*
    // if numEvents has been set and it would actually do something
    if (numEvents != 0 && nEventsTree > numEvents){
        nEventsTree = numEvents;
    }
    */


    for(unsigned int event = 0; event < nEventsTree; ++event) {
    

      // Get Event Content
      tree->LoadTree(event);
      cms2.GetEntry(event);
      ++nEventsTotal;

      // float maxPt = 0;
      int index = -1;
      float _maxPt = 0.0;
      float looseDiscriminant = .244;
      // float mediumDiscriminant = .679;
      // float tightDiscriminant = .89;

      std::vector<LorentzVector> _jets_p4_min ;
      std::vector<float> _jets_p4_minCorrection ;

      
      vector<float> _deltaM;
      vector<float> _avgM;
      vector<float> _minJetPt;
      
      float deltaMin40 = 1000;
      float _avgM40 = 0;


      // only grab the hypothesis with the biggest pt
      for (unsigned int i = 0; i< hyp_p4().size(); i++){
      
          // good hypothesis
          if (!samesign2011::isNumeratorHypothesis(i)) continue;

          if (hyp_ll_p4().at(i).pt() < 20) continue;
          if (hyp_lt_p4().at(i).pt() < 20) continue;
          
          
          if (hyp_ll_p4().at(i).eta() > 2.4) continue;
          if (hyp_lt_p4().at(i).eta() > 2.4) continue;
          
          // oppositely charged leptons
          if (hyp_ll_charge().at(i)*hyp_lt_charge().at(i) > 0) continue;
          
          // ignore ee events
          if (hyp_type().at(i) == 3) continue;

          // select the highest pt hypothesis
          float sumPt = hyp_lt_p4().at(i).pt() + hyp_ll_p4().at(i).pt();

          if (sumPt > _maxPt){
              _maxPt = sumPt;
              index = i;
          }
      }

      if (index == -1) continue;
      
      int _nBtags = 0;
      int jetllIndex = 0;
      int jetltIndex = 0;

      // now that we have one hyp from each event, loop over the jets, count them and find the 
      // best delta_m pair and store those jets
      for(unsigned int k = 0; k < pfjets_p4().size(); k++) {

          // cuts on k
          float jetPt = pfjets_p4().at(k).pt() * pfjets_corL1FastL2L3().at(k);
          if (jetPt < 20) continue; 
                
          float dR_lt = DeltaR(pfjets_p4().at(k), hyp_lt_p4().at(index));
          float dR_ll = DeltaR(pfjets_p4().at(k), hyp_ll_p4().at(index));
                    
          if (dR_ll < 0.4) continue;
          if (dR_lt < 0.4) continue;
              
          // minimum loose bTag discriminant
          float _bTag = pfjets_combinedSecondaryVertexBJetTag().at(k);

          if (_bTag < looseDiscriminant) continue;
          // save the
          _jets_p4_min.push_back(pfjets_p4().at(k));
          _jets_p4_minCorrection.push_back(pfjets_corL1FastL2L3().at(k));


          _nBtags++;


          float val1 = (hyp_ll_p4().at(index) + pfjets_p4().at(k)).mass();

          if (jetPt < 40) continue;

          float _deltaM40 = 0;

          float val140 = (hyp_ll_p4().at(index) + pfjets_p4().at(k)).mass();



              
          for (unsigned int l = 0; l< pfjets_p4().size(); l++){
                  
              // cuts on l loop
              if (l == k) continue;
              float l_jetPt = pfjets_p4().at(l).pt() * pfjets_corL1FastL2L3().at(l);
              if (l_jetPt < 20) continue; 
                
              float l_dR_lt = DeltaR(pfjets_p4().at(l), hyp_lt_p4().at(index));
              float l_dR_ll = DeltaR(pfjets_p4().at(l), hyp_ll_p4().at(index));
                    
              if (l_dR_ll < 0.4) continue;
              if (l_dR_lt < 0.4) continue;
              
              float l_bTag = pfjets_combinedSecondaryVertexBJetTag().at(l);

              if (l_bTag < looseDiscriminant) continue;    
              
              float val2 = (hyp_lt_p4().at(index) + pfjets_p4().at(l)).mass();

              _deltaM.push_back((val2-val1)/2);
              _avgM.push_back((val2+val1)/2);
              _minJetPt.push_back(min(jetPt,l_jetPt));

              if (l_jetPt < 40) continue;

              float val240 = (hyp_lt_p4().at(index) + pfjets_p4().at(l)).mass();
    
              _deltaM40 = val240 - val140;
              if (_deltaM40 <= deltaMin40) {
                  deltaMin40 = _deltaM40;
                  _avgM40 = (val140 + val240)/2; 
                  jetltIndex = l;
                  jetllIndex = k;
              }
          }
      }


      // now that we've selected a hypothesis, loop over the generated p4
      // and find the matching particle
      LorentzVector llGenerated;
      LorentzVector ltGenerated;
      LorentzVector jetllGenerated;
      LorentzVector jetltGenerated;

      for (int i = 0; i < genps_p4().size(); i++ ){

          if (matches(genps_p4().at(i), hyp_ll_p4().at(index))){
              llGenerated = genps_p4().at(i);
              continue;
          }
          
          if (matches(genps_p4().at(i), hyp_lt_p4().at(index))){
              ltGenerated = genps_p4().at(i);
              continue;
          }
          
          if (matches(genps_p4().at(i), pfjet_p4().at(jetltIndex))){
              jetltGenerated = genps_p4().at(i);
              continue;
          }
          
          if (matches(genps_p4().at(i), pfjet_p4().at(jetllIndex)))
              jetllGenerated = genps_p4().at(i);
      }

      float generateVal1 = 0;
      float generatedVal2 = 0;

      if (isValidPair(llGenerated, jetllGenerated))
          generatedVal1 = (llGenerated + jetllGenerated).mass();


      if (isValidPair(ltGenerated, jetltGenerated))
          generatedVal2 = (ltGenerated + jetltGenerated).mass();
     

      // Progress
      CMS2::progress( nEventsTotal, nEventsChain );

      InitBabyNtuple();

      //analysis
      met = evt_pfmet_type1cor();;

      nBtags = _nBtags;

      maxPt = _maxPt;

      jets_p4 = pfjets_p4();
      jets_p4Correction = pfjets_corL1FastL2L3();
      
      jets_p4_min = _jets_p4_min;
      jets_p4_minCorrection = _jets_p4_minCorrection;

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
    
      deltaM = _deltaM;
      avgM = _avgM;
      minJetPt = _minJetPt;
      deltaM40 = deltaMin40;
      avgM40 = _avgM40;

      eventNumber = evt_event();
      runNumber = evt_run();
      lumiBlock = evt_lumiBlock();

      
      if (abs(lt_id) == 13) lt_iso = muonIsoValuePF2012_deltaBeta(hyp_lt_index().at(index));
      if (abs(ll_id) == 13) ll_iso = muonIsoValuePF2012_deltaBeta(hyp_ll_index().at(index));

      // signal needs to be run through an up-to-date CMS2 in order to use these branches. Save it as 0.0 for now. 

      if (abs(lt_id) == 11) lt_iso = 0.0 ; // electronIsoValuePF2012_FastJetEffArea_v3(hyp_lt_index().at(index), .4);
      if (abs(ll_id) == 11) ll_iso =  0.0 ; //electronIsoValuePF2012_FastJetEffArea_v3(hyp_ll_index().at(index), .4);

      FillBabyNtuple();
    }//end loop on events in a file
  
    
    delete tree;
    f.Close();
  }//end loop on files
  
  if ( nEventsChain != nEventsTotal ) {
    std::cout << "WARNING: The number of events added is not equal to the total number of events in the file." << std::endl;
  }

  cout << nDuplicates << " duplicate events were skipped." << endl;

  CloseBabyNtuple();

  return;
}

bool matches(LorentzVector a, LoretzVector b){
    return ROOT::Math::VectorUtil::DeltaR(a ,b) < 0.1;
}

bool isValidPair(int hypIndex, int jetIndex){

    if 

}

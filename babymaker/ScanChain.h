#ifndef ScanChain_h
#define ScanChain_h

// C++ includes
#include <string>
#include <vector>

// ROOT includes
#include "TROOT.h"
#include "TFile.h"
#include "TChain.h"
#include "TTree.h"
#include "TH1F.h"
#include "Math/VectorUtil.h"
#include "Math/Vector4D.h"

#include "/home/users/aaivazis/CORE/ssSelections.h"
#include "/home/users/aaivazis/CORE/muonSelections.h"

typedef ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > LorentzVector;

class babyMaker {

 public:

  babyMaker() {};
  ~babyMaker() {
    delete BabyFile_;
    delete BabyTree_;
  };

  void ScanChain(TChain* chain, std::string baby_name = "testSample", unsigned int numEvents = 0);

  void MakeBabyNtuple(const char *);
  void InitBabyNtuple();
  void FillBabyNtuple();
  void CloseBabyNtuple();

 private:

  TFile *BabyFile_;
  TTree *BabyTree_;

  //baby ntuple variables
  float met;

  //std::vector<LorentzVector> jets_p4;
  std::vector<ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > > jets_p4;
  std::vector<float> jets_p4Correction;

  int type;

  LorentzVector ll_p4;
  LorentzVector lt_p4;
  LorentzVector total_p4;

  int ll_id;
  int lt_id;
  int ll_charge;
  int lt_charge;
  int ll_index;
  int lt_index;
  

  float scale_1fb;
  std::vector<float> btagDiscriminant;
  
  int numEvents;

  int eventNumber;
  int runNumber;
  int lumiBlock;

  string file;

  float generatedAvgMass;
  float generatedDeltaMass;
};

#endif

void babyMaker::MakeBabyNtuple(const char *BabyFilename){

  //
  TDirectory *rootdir = gDirectory->GetDirectory("Rint:");
  rootdir->cd();
  BabyFile_ = new TFile(Form("%s", BabyFilename), "RECREATE");
  BabyFile_->cd();
  BabyTree_ = new TTree("tree", "A Baby Ntuple");

  BabyTree_->Branch("met", &met );
  BabyTree_->Branch("jets_p4", &jets_p4 );
  BabyTree_->Branch("jets_p4Correction", &jets_p4Correction );
  BabyTree_->Branch("type", &type);

  BabyTree_->Branch("ll_p4", &ll_p4);
  BabyTree_->Branch("lt_p4", &lt_p4);
  BabyTree_->Branch("total_p4", &total_p4);

  BabyTree_->Branch("ll_id", &ll_id);
  BabyTree_->Branch("lt_id", &lt_id);
  BabyTree_->Branch("ll_charge" , &ll_charge);
  BabyTree_->Branch("lt_charge", &lt_charge);
  BabyTree_->Branch("ll_index", &ll_index);
  BabyTree_->Branch("lt_index", &lt_index);
  
  BabyTree_->Branch("eventNumber", &eventNumber);
  BabyTree_->Branch("runNumber", &runNumber);
  BabyTree_->Branch("lumiBlock", &lumiBlock);
  
  BabyTree_->Branch("scale_1fb", &scale_1fb);
  BabyTree_->Branch("btagDiscriminant", &btagDiscriminant);

  BabyTree_->Branch("generatedDeltaMass", &generatedDeltaMass);
  BabyTree_->Branch("generatedAvgMass", &generatedAvgMass);
  
  BabyTree_->Branch("numEvents", &numEvents);


  BabyTree_->Branch("file", &file);

  return;
}

void babyMaker::InitBabyNtuple () {

  met = -999.0;

  type = -1;

  ll_id = -1;
  lt_id = -1;
  ll_charge = -999;
  lt_charge = -999;
  ll_index = -1;
  lt_index = -1;

  scale_1fb = 1;

  eventNumber = -1;
  runNumber = -1;
  lumiBlock = 1;

  numEvents = 0;

  generatedDeltaMass = 999;
  generatedAvgMass = 0;

  return;
}

void babyMaker::FillBabyNtuple(){
  BabyTree_->Fill();
  return;
}

void babyMaker::CloseBabyNtuple(){
  BabyFile_->cd();
  BabyTree_->Write();
  BabyFile_->Close();
  return;
}


#ifndef RPVAnalysis_h
#define RPVAnalysis_h

// C++
#include <fstream>
#include <set>

// root
#include "TChain.h"
#include "TFile.h"
#include "THStack.h"
#include "TLegend.h"
#include "TCanvas.h"
#include "TROOT.h"
#include "Math/VectorUtil.h"


// CMS2
#include "RPV.h"

using namespace hak;
using namespace std;

typedef ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > LorentzVector;

class RPVAnalysis {

 public:

    // run the analysis
    void run();

 private: 
    
    // fill the plots associated with a given signal
    void fillPlots(TChain* samples, map<string, TH1F*> sample, bool useJetCorrection = false);
    // draw an individual plot
    void makePlot(vector<TH1F*> plots, TH1F* overlay=0);
    // check if the given jetIndex represents a "good" jet
    bool isGoodJet(int index);
    // check if the generated pair is valid
    bool isValidPair(int hypIndex, int jetIndex);
    // fill the sample histograms
    void createHistograms();
    // give the histograms color, overflow, etc. 
    void prepareHistograms();
    // draw the histograms associated with the analysis
    void plotHistograms();
    // set the bin located at {overflowValue} to the overflow of the histograms
    void overflow(TH1F *histo, float overflowValue);
    //find the index that matches to generated value
    int getMatchingGeneratedIndex(LorentzVector candidate, set<int> indices);

    // save the various one dimensional plots in maps for each signal
    map<string, TH1F*> signal600;
    map<string, TH1F*> signal600Before;
    map<string, TH1F*> ttjets;
    map<string, TH1F*> dy;
    map<string, TH1F*> zz;
    // store the analysis luminosity
    const static float lumi = 19.5;
};
#endif

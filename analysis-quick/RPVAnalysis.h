#ifndef RPVAnalysis_h
#define RPVAnalysis_h

// C++
#include <fstream>

// root
#include "TChain.h"
#include "TFile.h"
#include "TROOT.h"
#include "Math/VectorUtil.h"

// CMS2
#include "RPV.h"

using namespace hak;
using namespace std;

class RPVAnalysis {

 public:

    // run the analysis
    void run();

 private: 
    
    // fill the plots associated with a given signal
    void fillPlots(TChain* samples, map<string, TH1F*> sample, bool useJetCorrection = true);
    // check if the given jetIndex represents a "good" jet
    bool isGoodJet(int index);
    // fill the sample histograms
    void createHistograms();
    // give the histograms color, overflow, etc. 
    void prepareHistograms();
    // set the bin located at {overflowValue} to the overflow of the histograms
    void overflow(TH1F *histo, float overflowValue);

    // save the various one dimensional plots in maps for each signal
    map<string, TH1F*> signal200;
    map<string, TH1F*> signal200Before;
    // store the analysis luminosity
    const static float lumi = 19.5;
};
#endif

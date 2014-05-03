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
    RPVAnalysis(float lum){
        lumi = lum;
    };


    RPVAnalysis(){
        lumi = 19.5;
    };

    // run the analysis
    void run();

 private: 
    
    // fill the plots associated with a given signal
    void fillPlot(TChain* samples, TH1F* plot, bool useJetCorrection = false);
    // check if the given jetIndex represents a "good" jet
    bool isGoodJet(int index);

    // save the various one dimensional plots in maps for each signal
    map<string, TH1F*> signal200;
    // store the analysis luminosity
    float lumi;
};
#endif

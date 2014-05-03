{
    // load the necessary files
    gROOT->ProcessLine(".L /home/users/aaivazis/susy/analysis-quick/RPV.cc+");
    gROOT->ProcessLine(".L RPVAnalysis.C+");
  
    gStyle->SetOptStat("em");
  
    // set lumi to 19.5
    RPVAnalysis *analysis = new RPVAnalysis();

    analysis->run(); 
}


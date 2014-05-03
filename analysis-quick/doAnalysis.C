{
  gROOT->ProcessLine(".L /home/users/aaivazis/susy/analysis/RPV.cc+");
  gROOT->ProcessLine(".L analysis.C+");
  gROOT->ProcessLine("performAnalysis()");
}


{

  gROOT->ProcessLine(".L CMS2.cc++");
  gROOT->ProcessLine(".L Analysis.C++");
  TChain *ch = new TChain("tree"); 
  ch->Add("../signal200.root");
  ch->Add("../ttjets.root");
  ch->Add("../dy.root");
  Analysis(ch); 
}

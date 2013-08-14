{
  gSystem->AddIncludePath(Form("-I%s/CORE", gSystem->Getenv("HOME")));
  // gSystem->Load(Form("%s/CORE/libCMS2NtupleMacrosCORE.so", gSystem->Getenv("HOME")));
  gSystem->Load("/home/users/cgeorge/CORE/libCMS2NtupleMacrosCORE.so");
  gROOT->ProcessLine(".L ScanChain.C+");

  babyMaker *looper = new babyMaker();
  
  /*
  TChain *signal = new TChain("Events"); 
  signal->Add("../signal200RAW.root");

  looper->ScanChain(signal, "signal200"); 
  */

  TChain *dy = new TChain("Events"); 
  dy->Add("/hadoop/cms/store/group/snt/papers2012/Summer12_53X_MC/DY1JetsToLL_M-50_TuneZ2Star_8TeV-madgraph_Summer12_DR53X-PU_S10_START53_V7A-v1/V05-03-25/*.root");
  dy->Add("/hadoop/cms/store/group/snt/papers2012/Summer12_53X_MC/DY2JetsToLL_M-50_TuneZ2Star_8TeV-madgraph_Summer12_DR53X-PU_S10_START53_V7C-v1/V05-03-25/*.root");
  dy->Add("/hadoop/cms/store/group/snt/papers2012/Summer12_53X_MC/DY3JetsToLL_M-50_TuneZ2Star_8TeV-madgraph_Summer12_DR53X-PU_S10_START53_V7A-v1/V05-03-25/*.root");  
  dy->Add("/hadoop/cms/store/group/snt/papers2012/Summer12_53X_MC/DY4JetsToLL_M-50_TuneZ2Star_8TeV-madgraph_Summer12_DR53X-PU_S10_START53_V7A-v1/V05-03-23/*.root"); 
  looper->ScanChain(dy, "dy"); 

  TChain *ttjets = new TChain("Events"); 
  ttjets->Add("/hadoop/cms/store/group/snt/papers2012/Summer12_53X_MC/TTJets_MassiveBinDECAY_TuneZ2star_8TeV-madgraph-tauola_Summer12_DR53X-PU_S10_START53_V7A-v1/V05-03-23/*.root");
  looper->ScanChain(ttjets, "ttjets"); 
}

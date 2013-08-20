doTTbar(int numEvents = 0)
{
  gSystem->AddIncludePath(Form("-I%s/CORE", gSystem->Getenv("HOME")));
  // gSystem->Load(Form("%s/CORE/libCMS2NtupleMacrosCORE.so", gSystem->Getenv("HOME")));
  gSystem->Load("/home/users/cgeorge/CORE/libCMS2NtupleMacrosCORE.so");
  gROOT->ProcessLine(".L ScanChain.C+");

  babyMaker *looper = new babyMaker();

  TChain *ttjets = new TChain("Events"); 
  ttjets->Add("/hadoop/cms/store/group/snt/papers2012/Summer12_53X_MC/TTJets_MassiveBinDECAY_TuneZ2star_8TeV-madgraph-tauola_Summer12_DR53X-PU_S10_START53_V7A-v1/V05-03-23/*.root");
  looper->ScanChain(ttjets, "ttjets", numEvents); 
}

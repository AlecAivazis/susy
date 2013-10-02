doDY(std::string file_name="dy", int numEvents = 0)
{
  gSystem->AddIncludePath(Form("-I%s/CORE", gSystem->Getenv("HOME")));
  // gSystem->Load(Form("%s/CORE/libCMS2NtupleMacrosCORE.so", gSystem->Getenv("HOME")));
   gSystem->Load(Form("%s/CORE/libCMS2NtupleMacrosCORE.so", gSystem->Getenv("HOME")));
  gROOT->ProcessLine(".L ScanChain.C+");

  babyMaker *looper = new babyMaker();
 
  TChain *dy = new TChain("Events"); 
  
  
  dy->Add("/hadoop/cms/store/group/snt/papers2012/Summer12_53X_MC/DY1JetsToLL_M-50_TuneZ2Star_8TeV-madgraph_Summer12_DR53X-PU_S10_START53_V7A-v1/V05-03-25/*.root");
  /*
  dy->Add("/hadoop/cms/store/group/snt/papers2012/Summer12_53X_MC/DY2JetsToLL_M-50_TuneZ2Star_8TeV-madgraph_Summer12_DR53X-PU_S10_START53_V7C-v1/V05-03-25/*.root");
  dy->Add("/hadoop/cms/store/group/snt/papers2012/Summer12_53X_MC/DY3JetsToLL_M-50_TuneZ2Star_8TeV-madgraph_Summer12_DR53X-PU_S10_START53_V7A-v1/V05-03-25/*.root");  
  dy->Add("/hadoop/cms/store/group/snt/papers2012/Summer12_53X_MC/DY4JetsToLL_M-50_TuneZ2Star_8TeV-madgraph_Summer12_DR53X-PU_S10_START53_V7A-v1/V05-03-23/*.root"); 
  */

  //dy->Add("/hadoop/cms/store/group/snt/papers2012/Summer12_53X_MC/DYJetsToLL_M-50_TuneZ2Star_8TeV-madgraph-tarball_Summer12_DR53X-PU_S10_START53_V7A-v1/*.root");

  looper->ScanChain(dy, file_name, numEvents); 
}

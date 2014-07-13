doDY(int numEvents = -1, std::string file_name="dy")
{
  gSystem->Load("/home/users/cgeorge/macros/MiniFWLite/libMiniFWLite.so");
  gSystem->AddIncludePath(Form("-I%s/CORE", gSystem->Getenv("HOME")));
  // gSystem->Load(Form("%s/CORE/libCMS2NtupleMacrosCORE.so", gSystem->Getenv("HOME")));
   gSystem->Load(Form("CORE/libCMS2NtupleMacrosCORE.so", gSystem->Getenv("HOME")));
  gROOT->ProcessLine(".L ScanChain.C+");

  babyMaker *looper = new babyMaker();
 
  TChain *dy = new TChain("Events"); 
  
  dy->Add("/hadoop/cms/store/group/snt/papers2012/Summer12_53X_MC/DYJetsToLL_M-50_TuneZ2Star_8TeV-madgraph-tarball_Summer12_DR53X-PU_S10_START53_V7A-v1/V05-03-23/*.root");

  looper->ScanChain(dy, file_name + "_M50", numEvents/2); 

  TChain *dy = new TChain("Events"); 
  dy->Add("/hadoop/cms/store/group/snt/papers2012/Summer12_53X_MC/DYJetsToLL_M-10To50filter_8TeV-madgraph_Summer12_DR53X-PU_S10_START53_V7A-v1/V05-03-13_slim/*.root");

  looper->ScanChain(dy, file_name + "_M10to50", numEvents/2); 
}

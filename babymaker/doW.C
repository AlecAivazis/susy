doW(int numFiles = -1, std::string file_name="w")
{
  gSystem->AddIncludePath(Form("-I%s/CORE", gSystem->Getenv("HOME")));
  gSystem->Load(Form("%s/CORE/libCMS2NtupleMacrosCORE.so", gSystem->Getenv("HOME")));
  //gSystem->Load("/home/users/cgeorge/CORE/libCMS2NtupleMacrosCORE.so");
  gROOT->ProcessLine(".L ScanChain.C++");

  babyMaker *looper = new babyMaker();
 
  TChain *w = new TChain("Events"); 
  w->Add("/hadoop/cms/store/group/snt/papers2012/Summer12_53X_MC/WZJetsTo2L2Q_TuneZ2star_8TeV-madgraph-tauola_Summer12_DR53X-PU_S10_START53_V7A-v1/V05-03-23/*.root");
  looper->ScanChain(w, file_name + "zjets", numFiles); 

  TChain *w = new TChain("Events"); 
  w->Add("/hadoop/cms/store/group/snt/papers2012/Summer12_53X_MC/WZ_TuneZ2star_8TeV_pythia6_tauola_Summer12_DR53X-PU_S10_START53_V7A-v1/V05-03-13_slim/*.root");
  looper->ScanChain(w, file_name + "z", numFiles); 

  zz = new TChain("Events");
  zz->Add("/hadoop/cms/store/group/snt/papers2012/Summer12_53X_MC/WW_DoubleScattering_8TeV-pythia8_Summer12_DR53X-PU_S10_START53_V7A-v1/V05-03-23/*.root");
  looper->ScanChain(w, file_name + "w", numFiles); 
}

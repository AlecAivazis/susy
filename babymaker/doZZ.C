doZZ(int numEvents = -1, std::string file_name="zz")
{
  gSystem->Load("/home/users/cgeorge/macros/MiniFWLite/libMiniFWLite.so");
  gSystem->AddIncludePath(Form("-I%s/CORE", gSystem->Getenv("HOME")));
  gSystem->Load(Form("%s/CORE/libCMS2NtupleMacrosCORE.so", gSystem->Getenv("HOME")));
  //gSystem->Load("/home/users/cgeorge/CORE/libCMS2NtupleMacrosCORE.so");
  gROOT->ProcessLine(".L ScanChain.C++");

  babyMaker *looper = new babyMaker();
 
  TChain *zz = new TChain("Events"); 
  zz->Add("/hadoop/cms/store/group/snt/papers2012/Summer12_53X_MC/ZZJetsTo4L_TuneZ2star_8TeV-madgraph-tauola_Summer12_DR53X-PU_S10_START53_V7A-v1/V05-03-23/*.root");
  looper->ScanChain(zz, file_name + "_4l", numEvents); 

  zz = new TChain("Events");
  zz->Add("/hadoop/cms/store/group/snt/papers2012/Summer12_53X_MC/ZZJetsTo2L2Nu_TuneZ2star_8TeV-madgraph-tauola_Summer12_DR53X-PU_S10_START53_V7A-v3/V05-03-23/*.root");
  looper->ScanChain(zz, file_name + "_2l2n", numEvents); 

  zz = new TChain("Events");
  zz->Add("/hadoop/cms/store/group/snt/papers2012/Summer12_53X_MC/ZZJetsTo2L2Q_TuneZ2star_8TeV-madgraph-tauola_Summer12_DR53X-PU_S10_START53_V7A-v1/V05-03-23/*.root");
  looper->ScanChain(zz, file_name + "_2l2q", numEvents); 
}

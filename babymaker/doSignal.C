doSignal(int numEvents= -1, std::string suffix ="")
{

  gSystem->AddIncludePath(Form("-I%s/CORE", gSystem->Getenv("HOME")));
   gSystem->Load(Form("%s/CORE/libCMS2NtupleMacrosCORE.so", gSystem->Getenv("HOME")));
  //gSystem->Load("/home/users/cgeorge/CORE/libCMS2NtupleMacrosCORE.so");
  gROOT->ProcessLine(".L ScanChain.C++");

  babyMaker *looper = new babyMaker();
  

  // cross sections in pb
  // 200 - 18.5245
  // 600 - 0.0248009
  // 800 - 0.00289588

  // number of events in LHE file (use macro to generate)
  // 200 - 42140
  // 600 - 40262
  // 800 - 40403
  
  TChain *signal200 = new TChain("Events"); 
  signal200->Add("/hadoop/cms/store/user/jgran/forUndergrads/signals/raw/200/*.root");
  looper->ScanChain(signal200, "signal200" + suffix, numEvents, 18500.0/42140.0); 

  TChain *signal600 = new TChain("Events"); 
  signal600->Add("/hadoop/cms/store/user/jgran/forUndergrads/signals/raw/600/*.root");
  looper->ScanChain(signal600, "signal600" + suffix, numEvents, 25.0/40262.0); 
  
  TChain *signal800 = new TChain("Events"); 
  signal800->Add("/hadoop/cms/store/user/jgran/forUndergrads/signals/raw/800/*.root");
  looper->ScanChain(signal800, "signal800" + suffix, numEvents, 2.896/40403.0); 
  
  TChain *signal1000 = new TChain("Events"); 
  signal1000->Add("/hadoop/cms/store/user/jgran/forUndergrads/signals/raw/1000/*.root");
  looper->ScanChain(signal1000, "signal1000" + suffix, numEvents, 0.416/100000.0); 

}

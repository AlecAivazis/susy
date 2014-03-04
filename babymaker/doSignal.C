doSignal(int numEvents=0, std::string suffix ="")
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

  // number of events in LHE file (use macro)
  // 200 - 42140
  // 600 - 40262
  // 800 - 40403

  TChain *signal200 = new TChain("Events"); 
  signal200->Add("/home/users/aaivazis/susy/signals/raw/200/*.root");
  looper->ScanChain(signal200, "signal200" + suffix, numEvents, 18500.0/42140.0); 

  TChain *signal600 = new TChain("Events"); 
  signal600->Add("/home/users/aaivazis/susy/signals/raw/600/*.root");
  looper->ScanChain(signal600, "signal600" + suffix, numEvents, 25.0/40262.0); 
}

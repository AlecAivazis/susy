doSignal(std::string suffix ="", int numEvents=0)
{

  gSystem->AddIncludePath(Form("-I%s/CORE", gSystem->Getenv("HOME")));
   gSystem->Load(Form("%s/CORE/libCMS2NtupleMacrosCORE.so", gSystem->Getenv("HOME")));
  //gSystem->Load("/home/users/cgeorge/CORE/libCMS2NtupleMacrosCORE.so");
  gROOT->ProcessLine(".L ScanChain.C++");

  babyMaker *looper = new babyMaker();
  
  TChain *signal = new TChain("Events"); 
  signal->Add("/home/users/aaivazis/susy/signals/raw/signal200.root");
  looper->ScanChain(signal, "signal200" + suffix, numEvents); 

  TChain *signal = new TChain("Events"); 
  signal->Add("/home/users/aaivazis/susy/signals/raw/signal600.root");
  looper->ScanChain(signal, "signal600" + suffix, numEvents); 
}

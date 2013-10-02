doSignal(std::string file_name ="signal200", int numEvents=0)
{
  gSystem->AddIncludePath(Form("-I%s/CORE", gSystem->Getenv("HOME")));
  gSystem->Load(Form("%s/CORE/libCMS2NtupleMacrosCORE.so", gSystem->Getenv("HOME")));
  gROOT->ProcessLine(".L ScanChain.C+");

  babyMaker *looper = new babyMaker();
  
  TChain *signal = new TChain("Events"); 
  signal->Add("/home/users/aaivazis/susy/signal200RAW.root");

  looper->ScanChain(signal, file_name, numEvents, true); 
}

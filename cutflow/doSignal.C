doSignal(int numFiles=0)
{

  gSystem->AddIncludePath(Form("-I%s/CORE", gSystem->Getenv("HOME")));
  // gSystem->Load(Form("%s/CORE/libCMS2NtupleMacrosCORE.so", gSystem->Getenv("HOME")));
  gSystem->Load("/home/users/cgeorge/CORE/libCMS2NtupleMacrosCORE.so");
  gROOT->ProcessLine(".L Cutflow.C+");

  table = new Cutflow();
  
  TChain *signal = new TChain("Events"); 
  signal->Add("/home/users/aaivazis/susy/signal200RAW.root");

  table->draw(signal, numFiles); 

}

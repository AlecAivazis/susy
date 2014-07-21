doSignal(int numEvents= -1, std::string suffix ="")
{
  gSystem->Load("/home/users/cgeorge/macros/MiniFWLite/libMiniFWLite.so");
  gSystem->AddIncludePath(Form("-I%s/CORE", gSystem->Getenv("HOME")));
  gSystem->Load(Form("CORE/libCMS2NtupleMacrosCORE.so", gSystem->Getenv("HOME")));
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
  signal200->Add("/hadoop/cms/store/user/aaivazis/embryos/200/ntuple*");
  looper->ScanChain(signal200, "signal200" + suffix, numEvents, 18524.5/100000.0); 

  TChain *signal250 = new TChain("Events"); 
  signal250->Add("/hadoop/cms/store/user/aaivazis/embryos/250/ntuple*");
  looper->ScanChain(signal250, "signal250" + suffix, numEvents, 5576.0/100000.0); 

  TChain *signal300 = new TChain("Events"); 
  signal300->Add("/hadoop/cms/store/user/aaivazis/embryos/300/ntuple*");
  looper->ScanChain(signal300, "signal300" + suffix, numEvents, 1996.1/100000.0); 

  TChain *signal350 = new TChain("Events"); 
  signal350->Add("/hadoop/cms/store/user/aaivazis/embryos/350/ntuple*");
  looper->ScanChain(signal350, "signal350" + suffix, numEvents, 807.3/100000.0); 

  TChain *signal400 = new TChain("Events"); 
  signal400->Add("/hadoop/cms/store/user/aaivazis/embryos/400/ntuple*");
  looper->ScanChain(signal400, "signal400" + suffix, numEvents, 356.8/100000.0); 

  TChain *signal450 = new TChain("Events"); 
  signal450->Add("/hadoop/cms/store/user/aaivazis/embryos/450/ntuple*");
  looper->ScanChain(signal450, "signal450" + suffix, numEvents, 169.7/100000.0); 

  TChain *signal500 = new TChain("Events"); 
  signal500->Add("/hadoop/cms/store/user/aaivazis/embryos/500/ntuple*");
  looper->ScanChain(signal500, "signal500" + suffix, numEvents, 85.6/100000.0); 

  TChain *signal550 = new TChain("Events"); 
  signal550->Add("/hadoop/cms/store/user/aaivazis/embryos/550/ntuple*");
  looper->ScanChain(signal550, "signal550" + suffix, numEvents, 45.2/100000.0); 

  TChain *signal600 = new TChain("Events"); 
  signal600->Add("/hadoop/cms/store/user/aaivazis/embryos/600/ntuple*");
  looper->ScanChain(signal600, "signal600" + suffix, numEvents, 24.8/100000.0); 
  
  TChain *signal650 = new TChain("Events"); 
  signal650->Add("/hadoop/cms/store/user/aaivazis/embryos/650/ntuple*");
  looper->ScanChain(signal650, "signal650" + suffix, numEvents, 14.0/100000.0); 

  TChain *signal700 = new TChain("Events"); 
  signal700->Add("/hadoop/cms/store/user/aaivazis/embryos/700/ntuple*");
  looper->ScanChain(signal700, "signal700" + suffix, numEvents, 8.1/100000.0); 

  TChain *signal750 = new TChain("Events"); 
  signal750->Add("/hadoop/cms/store/user/aaivazis/embryos/750/ntuple*");
  looper->ScanChain(signal750, "signal750" + suffix, numEvents, 4.8/100000.0); 

  TChain *signal800 = new TChain("Events"); 
  signal800->Add("/hadoop/cms/store/user/aaivazis/embryos/800/ntuple*");
  looper->ScanChain(signal800, "signal800" + suffix, numEvents, 2.896/100000.0); 
  
}

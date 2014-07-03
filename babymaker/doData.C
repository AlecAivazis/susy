doData(int numFiles = -1, std::string file_name = "data")
{
  gSystem->Load("/home/users/cgeorge/macros/MiniFWLite/libMiniFWLite.so");
  gSystem->AddIncludePath(Form("-I%s/CORE", gSystem->Getenv("HOME")));
  gSystem->Load(Form("%s/CORE/libCMS2NtupleMacrosCORE.so", gSystem->Getenv("HOME")));
  //gSystem->Load("/home/users/cgeorge/CORE/libCMS2NtupleMacrosCORE.so");
  gROOT->ProcessLine(".L ScanChain.C+");

  babyMaker *looper = new babyMaker();

  TChain *data = new TChain("Events"); 

  data->Add("/hadoop/cms/store/group/snt/papers2012/Data2012/CMSSW_5_3_2_patch4_V05-03-24/DoubleMu_Run2012A-13Jul2012-v1_AOD/merged/*.root");
  data->Add("/hadoop/cms/store/group/snt/papers2012/Data2012/CMSSW_5_3_2_patch4_V05-03-24/DoubleMu_Run2012A-recover-06Aug2012-v1_AOD/merged/*.root");
  data->Add("/hadoop/cms/store/group/snt/papers2012/Data2012/CMSSW_5_3_2_patch4_V05-03-24/DoubleMu_Run2012B-13Jul2012-v4_AOD/merged/*.root");
  //  data->Add("/hadoop/cms/store/group/snt/papers2012/Data2012/CMSSW_5_3_2_patch4_V05-03-24/DoubleMu_Run2012C-24Aug2012-v1_AOD/merged/*.root");
  //  data->Add("/hadoop/cms/store/group/snt/papers2012/Data2012/CMSSW_5_3_2_patch4_V05-03-24/DoubleMu_Run2012D-16Jan2013-v2_AOD/merged/*.root*);

  data->Add("/hadoop/cms/store/group/snt/papers2012/Data2012/CMSSW_5_3_2_patch4_V05-03-24/MuEG_Run2012A-13Jul2012-v1_AOD/merged/*.root");
  data->Add("/hadoop/cms/store/group/snt/papers2012/Data2012/CMSSW_5_3_2_patch4_V05-03-24/MuEG_Run2012A-recover-06Aug2012-v1_AOD/merged/*.root");
  data->Add("/hadoop/cms/store/group/snt/papers2012/Data2012/CMSSW_5_3_2_patch4_V05-03-24/MuEG_Run2012B-13Jul2012-v1_AOD/merged/*.root");
  //data->Add("/hadoop/cms/store/group/snt/papers2012/Data2012/CMSSW_5_3_2_patch4_V05-03-24/MuEG_Run2012C-24Aug2012-v1_AOD/merged/*.root");
  //data->Add("/hadoop/cms/store/group/snt/papers2012/Data2012/CMSSW_5_3_2_patch4_V05-03-24/MuEG_Run2012D-16Jan2013-v2_AOD/merged/*.root");

  data->Add("/hadoop/cms/store/group/snt/papers2012/Data2012/CMSSW_5_3_2_patch4_V05-03-24/DoubleElectron_Run2012A-13Jul2012-v1_AOD/merged/*.root");
  data->Add("/hadoop/cms/store/group/snt/papers2012/Data2012/CMSSW_5_3_2_patch4_V05-03-24/DoubleElectron_Run2012A-recover-06Aug2012-v1_AOD/merged/*.root");
  data->Add("/hadoop/cms/store/group/snt/papers2012/Data2012/CMSSW_5_3_2_patch4_V05-03-24/DoubleElectron_Run2012B-13Jul2012-v1_AOD/merged/*.root");
  looper->ScanChain(data, file_name, numFiles, 1/5.2, true); 
}

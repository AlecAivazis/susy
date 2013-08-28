analysis(){


    
  //Path
  char* path = "/home/users/aaivazis/susy/babymaker/minis";

  //Chains
  TChain *dy   = new TChain("tree");
  TChain *signal   = new TChain("tree");
  TChain *tt   = new TChain("tree");

  //Files
  dy->Add(Form("%s/dy-mini.root",path));
  signal->Add(Form("%s/signal200-mini.root",path));
  tt->Add(Form("%s/tt-mini.root",path));



  // these are particular to babymaker/minis-before
  // nEvents_signal = 30689;
  // nEvents_tt = 4884;
  // nEvents_dy = 31005;


  //Weight
  TCut weight_tt("scale_1fb * (numEvents / 3465) * 19.5");
  TCut weight_signal(".060608 * 19.5");
  TCut weight_dy("scale_1fb * (numEvents / 3748) * 19.5");

  //Cuts
  TCut None("");
  TCut Twobtags("nJetsPt20>=2");
  TCut Met("met<80");
  TCut ll_Pt40("ll_p4.pt() > 40");
  TCut lt_Pt40("lt_p4.pt() > 40");

  TCut cut = Twobtags; //+ ll_Pt40 + lt_Pt40;


  // Signal Plots
  TH1F *signal_met = new TH1F("signal_met", "signal MET", 200, 0, 200);
  TH1F *signal_nJets = new TH1F("signal_nJets", "signal nJets", 10, 0, 10);
  TH1F *signal_nJetsPt20 = new TH1F("signal_nJetsPt20", "signal nJetsPt20", 10, 0, 10);
  TH1F *signal_nJetsPt30 = new TH1F("signal_nJetsPt30", "signal nJetsPt30", 10, 0, 10);
  TH1F *signal_nJetsPt40 = new TH1F("signal_nJetsPt40", "signal nJetsPt40", 10, 0, 10);
  TH1F *signal_nJetsPt50 = new TH1F("signal_nJetsPt50", "signal nJetsPt50", 10, 0, 10);
  TH1F *signal_nJetsPt60 = new TH1F("signal_nJetsPt60", "signal nJetsPt60", 10, 0, 10);
  TH1F *signal_ll_pt = new TH1F("signal_ll_pt", "signal ll_pt", 280, 20, 300);
  TH1F *signal_lt_pt = new TH1F("signal_lt_pt", "signal lt_pt", 280, 20, 300);
  TH1F *signal_total_pt = new TH1F("signal_total_pt", "signal total_pt", 260, 40, 300);
  TH1F *signal_total_mass = new TH1F("signal_total_mass", "signal total_mass", 200, 0, 200);
  
  
  // dy Plots
  TH1F *dy_met = new TH1F("dy_met", "dy MET", 200, 0, 200);
  TH1F *dy_nJets = new TH1F("dy_nJets", "dy nJets", 10, 0, 10);
  TH1F *dy_nJetsPt20 = new TH1F("dy_nJetsPt20", "dy nJetsPt20", 10, 0, 10);
  TH1F *dy_nJetsPt30 = new TH1F("dy_nJetsPt30", "dy nJetsPt30", 10, 0, 10);
  TH1F *dy_nJetsPt40 = new TH1F("dy_nJetsPt40", "dy nJetsPt40", 10, 0, 10);
  TH1F *dy_nJetsPt50 = new TH1F("dy_nJetsPt50", "dy nJetsPt50", 10, 0, 10);
  TH1F *dy_nJetsPt60 = new TH1F("dy_nJetsPt60", "dy nJetsPt60", 10, 0, 10);
  TH1F *dy_ll_pt = new TH1F("dy_ll_pt", "dy ll_pt", 280, 20, 300);
  TH1F *dy_lt_pt = new TH1F("dy_lt_pt", "dy lt_pt", 260, 40, 300);
  TH1F *dy_total_pt = new TH1F("dy_total_pt", "dy total_pt", 260, 40, 300);
  TH1F *dy_total_mass = new TH1F("dy_total_mass", "dy total_mass", 200, 0, 200);
  

  // tt Plots
  TH1F *tt_met = new TH1F("tt_met", "tt MET", 200, 0, 200);
  TH1F *tt_nJets = new TH1F("tt_nJets", "tt nJets", 10, 0, 10);
  TH1F *tt_nJetsPt20 = new TH1F("tt_nJetsPt20", "tt nJetsPt20", 10, 0, 10);
  TH1F *tt_nJetsPt30 = new TH1F("tt_nJetsPt30", "tt nJetsPt30", 10, 0, 10);
  TH1F *tt_nJetsPt40 = new TH1F("tt_nJetsPt40", "tt nJetsPt40", 10, 0, 10);
  TH1F *tt_nJetsPt50 = new TH1F("tt_nJetsPt50", "tt nJetsPt50", 10, 0, 10);
  TH1F *tt_nJetsPt60 = new TH1F("tt_nJetsPt60", "tt nJetsPt60", 10, 0, 10);
  TH1F *tt_ll_pt = new TH1F("tt_ll_pt", "tt ll_pt", 280, 20, 300);
  TH1F *tt_lt_pt = new TH1F("tt_lt_pt", "tt lt_pt", 260, 40, 300);
  TH1F *tt_total_pt = new TH1F("tt_total_pt", "tt total_pt", 260, 40, 300);
  TH1F *tt_total_mass = new TH1F("tt_total_mass", "tt total_mass", 200, 0, 200);


  

  //Fill signal plots
  signal->Draw("met>>signal_met", weight_signal*cut); 
  signal->Draw("nJets>>signal_nJets", weight_signal*cut); 
  signal->Draw("nJetsPt20>>signal_nJetsPt20", weight_signal*cut);
  signal->Draw("nJetsPt30>>signal_nJetsPt30", weight_signal*cut);
  signal->Draw("nJetsPt40>>signal_nJetsPt40", weight_signal*cut);
  signal->Draw("nJetsPt50>>signal_nJetsPt50", weight_signal*cut);
  signal->Draw("nJetsPt60>>signal_nJetsPt60", weight_signal*cut);
  signal->Draw("ll_p4.pt()>>signal_ll_pt", weight_signal*cut); 
  signal->Draw("lt_p4.pt()>>signal_lt_pt", weight_signal*cut); 
  signal->Draw("total_p4.pt()>>signal_total_pt", weight_signal*cut); 
  signal->Draw("total_p4.mass()>>signal_total_mass", weight_signal*cut); 



  
  // Fill dy plots
  dy->Draw("met>>dy_met", weight_dy*cut); 
  dy->Draw("nJets>>dy_nJets", weight_dy*cut); 
  dy->Draw("nJetsPt20>>dy_nJetsPt20", weight_dy*cut);
  dy->Draw("nJetsPt30>>dy_nJetsPt30", weight_dy*cut);
  dy->Draw("nJetsPt40>>dy_nJetsPt40", weight_dy*cut);
  dy->Draw("nJetsPt50>>dy_nJetsPt50", weight_dy*cut);
  dy->Draw("nJetsPt60>>dy_nJetsPt60", weight_dy*cut);
  dy->Draw("ll_p4.pt()>>dy_ll_pt", weight_dy*cut); 
  dy->Draw("lt_p4.pt()>>dy_lt_pt", weight_dy*cut); 
  dy->Draw("total_p4.pt()>>dy_total_pt", weight_dy*cut); 
  dy->Draw("total_p4.mass()>>dy_total_mass", weight_dy*cut); 


  // Fill tt plots
  tt->Draw("met>>tt_met", weight_tt*cut); 
  tt->Draw("nJets>>tt_nJets", weight_tt*cut); 
  tt->Draw("nJetsPt20>>tt_nJetsPt20", weight_tt*cut);
  tt->Draw("nJetsPt30>>tt_nJetsPt30", weight_tt*cut);
  tt->Draw("nJetsPt40>>tt_nJetsPt40", weight_tt*cut);
  tt->Draw("nJetsPt50>>tt_nJetsPt50", weight_tt*cut);
  tt->Draw("nJetsPt60>>tt_nJetsPt60", weight_tt*cut);
  tt->Draw("ll_p4.pt()>>tt_ll_pt", weight_tt*cut); 
  tt->Draw("lt_p4.pt()>>tt_lt_pt", weight_tt*cut); 
  tt->Draw("total_p4.pt()>>tt_total_pt", weight_tt*cut); 
  tt->Draw("total_p4.mass()>>tt_total_mass", weight_tt*cut); 


  std::cout << "Cut Flow Table:" <<std::endl;
  std::cout << "SIGNAL:" <<std::endl;
  signal->Draw("ll_p4.pt()>>signal_ll_pt", weight_signal*None); 
  std::cout<<"Baby - " << signal_ll_pt->GetEntries() << std::endl;
  signal->Draw("ll_p4.pt()>>signal_ll_pt", weight_signal*Twobtags); 
  std::cout<< "TwoBTags - " << signal_ll_pt->GetEntries() << std::endl;
  signal->Draw("ll_p4.pt()>>signal_ll_pt", weight_signal*(Twobtags+ll_Pt40)); 
  std::cout<< "ll_Pt40 - " << signal_ll_pt->GetEntries() << std::endl; 
  signal->Draw("ll_p4.pt()>>signal_ll_pt", weight_signal*(Twobtags+ll_Pt40+lt_Pt40)); 
  std::cout<< "lt_Pt40 - " << signal_ll_pt->GetEntries() << std::endl; 

  std::cout<< "TT: " << std::endl;
  tt->Draw("ll_p4.pt()>>tt_ll_pt", weight_tt*None); 
  std::cout<< "Baby - " << tt_ll_pt->GetEntries() << std::endl;
  tt->Draw("ll_p4.pt()>>tt_ll_pt", weight_tt*Twobtags); 
  std::cout<< "TwoBTags - " << tt_ll_pt->GetEntries() << std::endl;
  tt->Draw("ll_p4.pt()>>tt_ll_pt", weight_tt*(Twobtags+ll_Pt40)); 
  std::cout<< "ll_Pt40 - " << tt_ll_pt->GetEntries() << std::endl; 
  tt->Draw("ll_p4.pt()>>tt_ll_pt", weight_tt*(Twobtags+ll_Pt40+lt_Pt40)); 
  std::cout<< "lt_Pt40 - " << tt_ll_pt->GetEntries() << std::endl; 
  
  std::cout<< "DY: " << std::endl;
  dy->Draw("ll_p4.pt()>>dy_ll_pt", weight_dy*None); 
  std::cout<< "Baby - " << dy_ll_pt->GetEntries() << std::endl;
  dy->Draw("ll_p4.pt()>>dy_ll_pt", weight_dy*Twobtags); 
  std::cout<< "TwoBTags - " << dy_ll_pt->GetEntries() << std::endl;
  dy->Draw("ll_p4.pt()>>dy_ll_pt", weight_dy*(Twobtags+ll_Pt40)); 
  std::cout<< "ll_Pt40 - " << dy_ll_pt->GetEntries() << std::endl; 
  dy->Draw("ll_p4.pt()>>dy_ll_pt", weight_dy*(Twobtags+ll_Pt40+lt_Pt40)); 
  std::cout<< "lt_Pt40 - " << dy_ll_pt->GetEntries() << std::endl; 

  //Merged Plot
  THStack *stack = new THStack("stack", "");

  // color the stacked plots
   dy_ll_pt->SetFillColor(9);
   //signal_met->SetFillColor(1);
   tt_ll_pt->SetFillColor(8);

  // create overflow bins
    float overflowValue = 299.0;
   overflow(dy_ll_pt, overflowValue);
  overflow(tt_ll_pt, overflowValue);
   overflow(signal_ll_pt, overflowValue);

  // add plots to stack
  stack->Add(dy_ll_pt);
  stack->Add(tt_ll_pt);
  stack->Draw();
  signal_ll_pt->Draw("same");
  signal_ll_pt->SetLineStyle(7);
  signal_ll_pt->SetLineWidth(3);
  signal_ll_pt->SetLineColor(1);
  // add legend on x-axis
  stack->GetXaxis()->SetTitle("GeV");

  // create legend
  TLegend *leg = new TLegend(.75,.85,.90,.55);
  leg->AddEntry(dy_ll_pt, "dy", "f");
  leg->AddEntry(tt_ll_pt, "ttbar", "f");
  leg->AddEntry(signal_ll_pt, "signal", "f");
  leg->SetFillStyle(0);
  leg->SetBorderSize(0);
  leg->SetTextSize(0.04);
  leg->Draw();
  
}

string convertFloat(float number){
    stringstream ss;
    ss << number << endl;
    return ss.str();
}

void overflow(TH1F *histo, int overflowValue){
 histo->SetBinContent(histo->GetXaxis()->FindBin(overflowValue), histo->GetBinContent((histo->GetXaxis()->FindBin(overflowValue)))+histo->GetBinContent((histo->GetXaxis()->FindBin(overflowValue))+1));
}

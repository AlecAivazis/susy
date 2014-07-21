#include "RPVAnalysis.h"

// run the analysis
void RPVAnalysis::run(){

    // add the files to their respective chains
    TChain* signal600Chain = new TChain("tree");
    signal600Chain->Add("/hadoop/cms/store/user/aaivazis/samples/signal/signal200.root");

    // add the files to their respective chains
    //TChain* signal800Chain = new TChain("tree");
    //signal800Chain->Add("/hadoop/cms/store/user/aaivazis/samples/signal/signal800.root");

    // add the files to their respective chains
    //TChain* signal1000Chain = new TChain("tree");
    //signal1000Chain->Add("/hadoop/cms/store/user/aaivazis/samples/signal/signal1000.root");

    // add the data file to a chain
    TChain* dataChain = new TChain("tree");
    dataChain->Add("/hadoop/cms/store/user/aaivazis/samples/data/data.root");

    // add the ttjets file to a chain
    TChain* ttjetsChain = new TChain("tree");
    ttjetsChain->Add("/hadoop/cms/store/user/aaivazis/samples/tt/ttjets.root");
    
    // add the dy (Mass 10 to 50) file to a chain
    TChain* dy_M10to50Chain = new TChain("tree");
    dy_M10to50Chain->Add("/hadoop/cms/store/user/aaivazis/samples/dy/dy_M10to50.root");
    
    // add the dy (Mass greater than 50) file to a chain
    TChain* dy_M50Chain = new TChain("tree");
    dy_M50Chain->Add("/hadoop/cms/store/user/aaivazis/samples/dy/dy_M50.root");
    
    // add the zz_2l2q file to a chain
    TChain* zz_2l2qChain = new TChain("tree");
    zz_2l2qChain->Add("/hadoop/cms/store/user/aaivazis/samples/zz/zz_2l2q.root");
    
    // add the zz_2l2n file to a chain
    TChain* zz_2l2nChain = new TChain("tree");
    zz_2l2nChain->Add("/hadoop/cms/store/user/aaivazis/samples/zz/zz_2l2n.root");
    
    // add the zz_4l file to a chain
    TChain* zz_4lChain = new TChain("tree");
    zz_4lChain->Add("/hadoop/cms/store/user/aaivazis/samples/zz/zz_4l.root");
    
    // add the ww file to a chain
    TChain* wwChain = new TChain("tree");
    wwChain->Add("/hadoop/cms/store/user/aaivazis/samples/w/ww.root");

    // add the wz_2l2q file to a chain
    TChain* wz_2l2qChain = new TChain("tree");
    wz_2l2qChain->Add("/hadoop/cms/store/user/aaivazis/samples/w/wz_2l2q.root");

    // add the wz_3ln file to a chain
    TChain* wz_3lnChain = new TChain("tree");
    wz_3lnChain->Add("/hadoop/cms/store/user/aaivazis/samples/w/wz_3ln.root");

    // fill the dictionaries with empty histograms
    createHistograms();

    // use the jet correction for this sample
    fillPlots(signal600Chain, signal600, signalDel600);
    //fillPlots(signal800Chain, signal800, signalDel800);
    //fillPlots(signal1000Chain, signal1000, signalDel1000);
    // fill the data plots
    fillPlots(dataChain, data, dataDel);
    // fill the tt plots
    fillPlots(ttjetsChain, ttjets, ttDel);
    // fill the dy plots
    fillPlots(dy_M10to50Chain, dy_M10to50, dy_M10to50Del);
    // fill the dy plots
    fillPlots(dy_M50Chain, dy_M50, dy_M50Del);
    // fill the zz plots
    fillPlots(zz_2l2qChain, zz_2l2q, zz_2l2qDel);
    // fill the zz plots
    fillPlots(zz_2l2nChain, zz_2l2n, zz_2l2nDel);
    // fill the zz plots
    fillPlots(zz_4lChain, zz_4l, zz_4lDel);
    // fill the ww plots
    fillPlots(wwChain, ww, wwDel);
    // fill the wz plots
    fillPlots(wz_2l2qChain, wz_2l2q, wwDel);
    // fill the wz plots
    fillPlots(wz_3lnChain, wz_3ln, wwDel);

    // draw the histograms
    //plotHistograms();
}

// fill the given dictionary with the important quantities
void RPVAnalysis::fillPlots(TChain* chain, map<string, TH1F*> sample, TH2F* plot){

    float stopMass = 200.0;

    // get the list of files from the chain
    TObjArray* files = chain->GetListOfFiles();
    // create an iterator over the fiels
    TIter fileIter(files);
    // store the current file data
    TFile* currentFile = 0;

    // stream to write the event list    
    ofstream stream;

    // definitions for signal region calc
    int mets[6]= {20, 40, 60, 80, 100, 1000};
    int jets[4] = {0, 1, 2, 3};

    int counters[6][4] = {0};
    int metnumber = sizeof(mets)/sizeof(mets[0]);
    int jetnumber = sizeof(jets)/sizeof(jets[0]);

    float lumi = 5.2;

    // loop over the files to fill plots
    while(( currentFile = (TFile*)fileIter.Next() )) {
        
        // get the file content
        TFile* file = new TFile(currentFile->GetTitle());
        TTree* tree = (TTree*)file->Get("tree");
        // tell cms2 about the tree
        cms2.Init(tree);

        // declare mumu and emu counters
        int mumuCounter = 0;
        int emuCounter = 0;

        // loop over events in the tree
        for (unsigned int event = 0; event < tree->GetEntriesFast(); ++event) {

            // load the event into the branches
            cms2.GetEntry(event);

            // save the delta mass between jet/lepton combos (minimized)
            float deltaMass = 9999;
            // save the average mass of the same pair
            float avgMass = 0;
            // counter for btags
            float nBtags = 0;
            // counter for jets 
            float nJets = 0;
            
            // store the indices of the jets that minimize deltaMass
            int jetllIndex;
            int jetltIndex;

            // counters and indices for the gen_ps loop
            float generatedMass1 = -1;
            float generatedMass2 = -1;
            int llGenerated = -1;
            int ltGenerated = -1;
            int jetllGenerated = -1;
            int jetltGenerated =-1;
            int ll_mother = -1;
            int lt_mother = -1;
            // store the list of known good indices for the gen_ps loop
            set<int> indices;
            // save if the mass pair is valid
            bool genMassGood = true;

            // loop over the jets to compute delta mass
            for (unsigned int j=0; j<jets_p4().size() ; j++) {

                // check that the jet is "good"
                if (! isGoodJet(j)) continue; 
                nJets++;
                // count number of Btags
                if (btagDiscriminant().at(j) < 0.244) continue;
                nBtags++;

                // save the combined masses from the two jet loops to 
                // calculate average and delta mass
                float mass1 = 0;
                float mass2 = 0;

                // loop over jets to find pairs
                for (unsigned int k = 0; k<jets_p4().size() - 1 ; k++){
                    // ignore the jet from the first loop
                    if (k == j) continue;
                    // make sure the second jet is good too
                    if (! isGoodJet(k)) continue;

                    mass1 = (ll_p4() + jets_p4().at(j)).M();
                    mass2 = (lt_p4() + jets_p4().at(k)).M();

                    // minimize the delta mass
                    if (fabs(mass2-mass1) < fabs(deltaMass)){
                        // save the delta and average mass of the minimized pair
                        deltaMass = mass2-mass1;
                        avgMass = (mass1+mass2)/2;
                        // save the indices of the jets that minimized delta mass
                        jetllIndex = j;
                        jetltIndex = k;
                    }
                }
            }

            // perform cuts
            if (type() == 3) continue;
            //if (type() != 0) continue; 

            if (/*type() == 0 && */ fabs((ll_p4()+lt_p4()).M() - 91) < 15) continue; 

            if (nBtags < 1) continue; 
            
            // cuts that define the control region
            if (fabs(deltaMass) > 100) continue; 
            if (fabs(avgMass - stopMass) > 50) continue; 

            // build the sigma matrix
            for (int i =0; i < metnumber; i++){
                // cout << "minimum met: " << mets.at(i) << endl;
                for (int k = 0; k < jetnumber; k++){
                    // cout << "minimum nJets: " << jets.at(k) << endl;
                    if (met() <= mets[i] && nJets >= jets[k]){  
                        counters[i][k]++;
                    }
                }
            }

            if (/*type() ==0 &&*/ met() > 60) continue; 
            if (nJets < 2) continue;
            // find the gen_ps particles corresponding to our p4s
            llGenerated = getMatchingGeneratedIndex(ll_p4(), indices);
            indices.insert(llGenerated);

            ltGenerated = getMatchingGeneratedIndex(lt_p4(), indices);
            indices.insert(ltGenerated);

            jetllGenerated = getMatchingGeneratedIndex(jets_p4().at(jetllIndex) , indices);
            indices.insert(jetllGenerated);

            jetltGenerated = getMatchingGeneratedIndex(jets_p4().at(jetltIndex) , indices);

            /*
            //look at mother of generated lepton
            if (llGenerated != -1 && ltGenerated != -1) {

                ll_mother = generated_mother_id().at(llGenerated);
                lt_mother = generated_mother_id().at(ltGenerated);

                if (fabs(ll_mother) != 24 || fabs(lt_mother) != 24) 
                    cout << ll_mother << ", " << lt_mother << endl; 
            }
            */

            // calculate the combined mass of the two pairs
            if (llGenerated != -1
                && ltGenerated != -1
                && jetllGenerated != -1
                && jetltGenerated != -1){

                if (isValidPair(llGenerated, jetllGenerated))
                    generatedMass1 = (generated_p4().at(llGenerated)
                                      + generated_p4().at(jetllGenerated)).M();
                else
                    genMassGood = false;

                if (isValidPair(ltGenerated, jetltGenerated))
                    generatedMass2 = (generated_p4().at(ltGenerated)
                                      + generated_p4().at(jetltGenerated)).M();
                else
                    genMassGood = false;
            }
            
            stream.open("eventlist.txt", ios::app);
            stream << event << endl;
            stream.close();
            
            // fill the appopriate plots
            sample["met"]->Fill(met(), scale_1fb());
            
            // fill the 2d plot if it was given
            if (plot) plot->Fill(avgMass, deltaMass, scale_1fb());

            // increment eventCounters
            if (type() == 0) mumuCounter++;
            if (type() == 1 || type() == 2) emuCounter++;

            /*
            stream.open("eventList.txt", ios::app);
            stream << event << endl;
            stream.close();
            */
        }
        
        // print the event counters
        cout << "number of mumu events: " << mumuCounter * lumi * scale_1fb() << ", unweighted: " << mumuCounter << endl;
        cout << "number of emu events: " << emuCounter * lumi * scale_1fb() << ", unweighted: " << emuCounter << endl;

        float weightedCounter = sqrt(mumuCounter + emuCounter) * scale_1fb() * lumi;
        if ( weightedCounter == 0){
            weightedCounter = scale_1fb() * lumi;
        }

        cout << "error: " << weightedCounter << endl;
        cout << " " << endl;
    }

    stream.open("signalregion.txt", ios::app);
    for (int i = 0; i< metnumber; i++){
        for (int k =0; k < jetnumber; k++){
            stream << counters[i][k] * lumi * scale_1fb() << " ";
        }
    }
    stream << endl;
    stream.close();

    return;
}

// utility/background functions

// check if the requested jet is "good"
bool RPVAnalysis::isGoodJet(int index) {
    // pt > 30
    if (jets_p4().at(index).pt() < 30) return false;
    // eta < 2.5
    if (fabs(jets_p4().at(index).eta()) > 2.5)  return false;
    // dR > 0.4
    if (ROOT::Math::VectorUtil::DeltaR(jets_p4().at(index), ll_p4()) < 0.4) return false;
    if (ROOT::Math::VectorUtil::DeltaR(jets_p4().at(index), lt_p4()) < 0.4) return false;

    return true;
}

bool RPVAnalysis::isValidPair(int hypIndex, int jetIndex){

    // require the generated pair to be either mu- b or mu+ bbar
 
    // muons have id = 13
    // b's have id = 5
    // i need bbar and muon (or opposite)
    return generated_id().at(hypIndex) * generated_id().at(jetIndex) == -65;
}

int RPVAnalysis::getMatchingGeneratedIndex(const LorentzVector candidate, set<int> indices){

    float deltaMin = 9999;
    int index = -1;

    for( int i = 0; i < generated_p4().size(); ++i){
        
        // check if i is in indices
        if ( indices.find(i) != indices.end() ) continue;

        // compute deltaR
        float deltaR = ROOT::Math::VectorUtil::DeltaR(generated_p4().at(i), candidate);

        // deltaR  has to be <= 0.1
        if (fabs(deltaR) > 0.1) continue; 

        // grab the minimum
        if (deltaR < deltaMin )  {
            index = i;
            deltaMin = deltaR;
        }
    }  

    // return the index that minimized the deltaR
    return index;
}


// fill the sample dictionaries 
void RPVAnalysis::createHistograms() {
   
    // create signal200 plots
    signal600["avgMass"] = new TH1F("signal600_avgMass", "signal 600 Avg Mass", 240, 0, 1200);
    signal600["met"] = new TH1F("signal600_met", "signal 600 met", 50, 10, 50);

    signalDel600 = new TH2F("signal600", "zz", 100, 0, 1200, 100, -200, 200);
    signalDel800 = new TH2F("signal800", "zz", 100, 0, 1200, 100, -200, 200);
    signalDel1000 = new TH2F("signal1000", "zz", 100, 0, 1200, 100, -200, 200);
    zz_2l2qDel = new TH2F("zz_2l2q", "zz_2l2q", 100, 0, 1200, 100, -200, 200);
    zz_2l2nDel = new TH2F("zz_2l2n", "zz_2l2n", 100, 0, 1200, 100, -200, 200);
    zz_4lDel = new TH2F("zz_4l", "zz_4l", 100, 0, 1200, 100, -200, 200);
    wwDel = new TH2F("ww", "ww", 100, 0, 1200, 100, -200, 200);
    wz_2l2qDel = new TH2F("wz_2l2q", "wz_2l2q", 100, 0, 1200, 100, -200, 200);
    wz_3lnDel = new TH2F("wz_3ln", "wz_3ln", 100, 0, 1200, 100, -200, 200);
    dy_M50Del = new TH2F("dy_M50", "zz", 100, 0, 1200, 100, -200, 200);
    dy_M10to50Del = new TH2F("dy_M10to50", "zz", 100, 0, 1200, 100, -200, 200);
    ttDel = new TH2F("tt", "zz", 100, 0, 1200, 100, -200, 200);
    dataDel = new TH2F("data", "zz", 100, 0, 1200, 100, -200, 200);

    // create ttjets plots
    ttjets["avgMass"] = new TH1F("ttjets_avgMass", "ttjets Avg Mass", 240, 0, 1200);
    ttjets["met"] = new TH1F("ttjets_met", "tt jets met", 80, 0, 300);

    // create dy plots
    dy_M50["avgMass"] = new TH1F("dy_M50_avgMass", "dy_M50 Avg Mass", 240, 0, 1200);
    dy_M50["met"] = new TH1F("dy_M50_met", "dy_M50 met", 80, 0, 300);

    dy_M10to50["avgMass"] = new TH1F("dy_M10to50_avgMass", "dy_M10to50 Avg Mass", 240, 0, 1200);
    dy_M10to50["met"] = new TH1F("dy_M10to50_met", "dy_M10to50 met", 80, 0, 300);

    // create zz plots
    zz_2l2q["avgMass"] = new TH1F("zz_2l2q_avgMass", "zz_2l2q Avg Mass", 240, 0, 1200);
    zz_2l2q["met"] = new TH1F("zz_2l2q_met", "zz_2l2q met", 80, 0, 300);

    zz_2l2n["avgMass"] = new TH1F("zz_2l2n_avgMass", "zz_2l2n Avg Mass", 240, 0, 1200);
    zz_2l2n["met"] = new TH1F("zz_2l2n_met", "zz_2l2n met", 80, 0, 300);

    zz_4l["avgMass"] = new TH1F("zz_4l_avgMass", "zz_4l Avg Mass", 240, 0, 1200);
    zz_4l["met"] = new TH1F("zz__4l_met", "zz_4l met", 80, 0, 300);

    // create w plots
    ww["avgMass"] = new TH1F("ww_avgMass", "ww Avg Mass", 240, 0, 1200);
    ww["met"] = new TH1F("ww_met", "ww met", 80, 0, 300);

    wz_2l2q["avgMass"] = new TH1F("wz_2l2q_avgMass", "wz_2l2q Avg Mass", 240, 0, 1200);
    wz_2l2q["met"] = new TH1F("wz_2l2q_met", "wz_2l2q met", 80, 0, 300);

    wz_3ln["avgMass"] = new TH1F("wz_3ln_avgMass", "wz_3ln Avg Mass", 240, 0, 1200);
    wz_3ln["met"] = new TH1F("wz_3ln_met", "wz_3ln met", 80, 0, 300);

    // create data plots
    data["avgMass"] = new TH1F("data_avgMass", "data Avg Mass", 240, 0, 1200);
    data["met"] = new TH1F("data_met", "data met", 80, 0, 300);

    // create sample plots
    data["avgMass"] = new TH1F("data_avgMass", "data Avg Mass", 240, 0, 1200);
    data["genMinusReco"] = new TH1F("data_genMinusReco", "data generated - reco mass", 100, -75, 75);

    return;
}

// give the histograms color,overflow, etc.
void RPVAnalysis::prepareHistograms(){


    // color the histograms
    signal600["avgMass"]->SetLineColor(kBlack);
    signal600["met"]->SetLineColor(kBlack);
    ttjets["met"]->SetFillColor(kBlue);
    dy_M50["met"]->SetFillColor(kMagenta);
    dy_M10to50["met"]->SetFillColor(kMagenta);
    zz_2l2q["met"]->SetFillColor(kGreen);
    zz_2l2n["met"]->SetFillColor(kGreen+1);
    zz_4l["met"]->SetFillColor(kGreen+2);
    ww["met"]->SetFillColor(kRed);
    wz_2l2q["met"]->SetFillColor(kRed+1);
    wz_3ln["met"]->SetFillColor(kRed-4);
    data["met"]->SetMarkerStyle(kFullDotLarge);
    ttjets["avgMass"]->SetLineColor(kRed);
    //  signal600before["genMinusReco"]->SetLineColor(kRed);

    signalDel600->SetFillColor(kBlack);
    signalDel800->SetFillColor(kBlack);
    signalDel1000->SetFillColor(kBlack);
    dy_M50Del->SetFillColor(kRed);
    dy_M10to50Del->SetFillColor(kRed);
    zz_2l2qDel->SetFillColor(kRed);
    zz_2l2nDel->SetFillColor(kRed);
    zz_4lDel->SetFillColor(kRed);
    wwDel->SetFillColor(kRed);
    wz_2l2qDel->SetFillColor(kRed);
    wz_3lnDel->SetFillColor(kRed);
    ttDel->SetFillColor(kRed);
    
    // set the overflow bins
    overflow(signal600["avgMass"], 1200);

    return;
}

// set the bin corresponding to {overflowValue} as the histograms overflow bin
void RPVAnalysis::overflow(TH1F *histo, float overflowValue){
    return histo->SetBinContent(histo->GetXaxis()->FindBin(overflowValue), histo->GetBinContent((histo->GetXaxis()->FindBin(overflowValue)))+histo->GetBinContent((histo->GetXaxis()->FindBin(overflowValue))+1));
}

void RPVAnalysis::plotHistograms(){

    // set up canvas and legend 
    TCanvas *c1 = new TCanvas("c1","Graph Example",200,10,700,500);
    //c1->SetLogy();
    
    // create the legend
    TLegend *leg = new TLegend(.73,.9,.89,.6);

    /*
    // add entries to the legend
    leg->AddEntry(ttjets["avgMass"], "ttbar", "f");
    leg->AddEntry(dy["avgMass"] , "dy", "f");
    leg->AddEntry(zz_2l2q["avgMass"], "zz_2l2q", "f");
    leg->AddEntry(signal600["avgMass"], "signal600", "l");
    */

    // style the legend
    leg->SetFillStyle(0);
    leg->SetBorderSize(0);
    leg->SetTextSize(0.04);

    // prepare the histograms
    prepareHistograms();
    
    signalDel600->GetYaxis()->SetTitle("Delta Mass (GeV)");
    signalDel600->GetXaxis()->SetTitle("Average Mass (GeV)");

    signalDel600->Draw("box");
    signalDel800->Draw("samebox");
    signalDel1000->Draw("samebox");
    dy_M50Del->Draw("samebox");
    dy_M10to50Del->Draw("samebox");
    zz_2l2qDel->Draw("samebox");
    zz_2l2nDel->Draw("samebox");
    zz_4lDel->Draw("samebox");
    wwDel->Draw("samebox");
    wz_2l2qDel->Draw("samebox");
    wz_3lnDel->Draw("samebox");
    ttDel->Draw("samebox");
    

    c1->SaveAs("DelVsAvgMass.png");
    
    /*
    // stacked plots 
    THStack *stack = new THStack("stack","");

    
    c1 = new TCanvas("c1","Graph Example",200,10,700,500);
    //c1->SetLogy();
    leg = new TLegend(.73,.9,.89,.6);
    
    leg->AddEntry(ww["met"], "ww_2l2n", "f");
    leg->AddEntry(zz_2l2n["met"], "zz_2l2n", "f");
    leg->AddEntry(zz_4l["met"], "zz_4l", "f");
    leg->AddEntry(wz_3ln["met"], "wz_3ln", "f");
    leg->AddEntry(wz_2l2q["met"], "wz_2l2q", "f");
    leg->AddEntry(zz_2l2q["met"], "zz_2l2q", "f");
    leg->AddEntry(dy_M50["met"], "DY", "f");
    leg->AddEntry(ttjets["met"], "TT", "f");
    leg->AddEntry(data["met"], "data", "p");
    leg->AddEntry(signal600["met"], "signal", "l");

    stack->Add(ww["met"]);
    stack->Add(zz_2l2n["met"]);
    stack->Add(zz_4l["met"]);
    stack->Add(wz_3ln["met"]);
    stack->Add(wz_2l2q["met"]);
    stack->Add(zz_2l2q["met"]);
    stack->Add(dy_M50["met"]);
    stack->Add(dy_M10to50["met"]);
    stack->Add(ttjets["met"]);

    signal600["met"]->GetXaxis()->SetTitle("Average Mass (GeV)");

    stack->Draw();
    data["met"]->Draw("sameP");
    signal600["met"]->Draw("same");
    leg->Draw("same");
    c1->SaveAs("met.png");
    */
}

    

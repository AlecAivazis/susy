#include "RPVAnalysis.h"

// run the analysis
void RPVAnalysis::run(){

    // add the files to their respective chains
    TChain* signal600Chain = new TChain("tree");
    signal600Chain->Add("/hadoop/cms/store/user/jgran/forUndergrads/babies/signal600.root");

    // add the ttjets file to a chain
    TChain* ttjetsChain = new TChain("tree");
    ttjetsChain->Add("/hadoop/cms/store/user/jgran/forUndergrads/babies/ttjets.root");
    
    // add the dy file to a chain
    TChain* dyChain = new TChain("tree");
    dyChain->Add("/hadoop/cms/store/user/jgran/forUndergrads/babies/dy.root");
    
    // add the dy file to a chain
    TChain* zzChain = new TChain("tree");
    zzChain->Add("/hadoop/cms/store/user/jgran/forUndergrads/babies/zz.root");
    
    // fill the dictionaries with empty histograms
    createHistograms();
    
    // use the jet correction for this sample
    fillPlots(signal600Chain, signal600, true);
    // fill the tt plots
    //fillPlots(ttjetsChain, ttjets);
    // fill the dy plots
    //fillPlots(dyChain, dy);

    // fill the zz plots
    // fillPlots(zzChain, zz);

    // draw the histograms
    plotHistograms();
}

// fill the given dictionary with the important quantities
void RPVAnalysis::fillPlots(TChain* samples, map<string, TH1F*> sample, bool useJetCorrection){

    // get the list of files from the chain
    TObjArray* files = samples->GetListOfFiles();
    // create an iterator over the fiels
    TIter fileIter(files);
    // store the current file data
    TFile* currentFile = 0;

    // stream to write the event list    
    ofstream eventList;
    // open the eventList stream

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
            // counter for nJets 
            float nJets = 0;
            
            // default jet correction = 0
            float alphaMin = 0;
            float betaMin = 0;

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

                // save the combined masses from the two jet loops to calculate average and delta mass
                float mass1 = 0;
                float mass2 = 0;


                // if it is, loop over the other jets,
                for (unsigned int k = 0; k<jets_p4().size() - 1 ; k++){
                    // ignore the jet from the first loop
                    if (k == j) continue;
                    // make sure the second jet is good too
                    if (! isGoodJet(k)) continue;

                    // default jet correction is 0
                    float alpha = 0;
                    float beta = 0;

                    // should we use the jet correction?
                    if (useJetCorrection){
                    
                        // if so, compute the corrections from the system of equation
                    
                        // Ex = alpha*ja_x + beta*jb_x
                        // Ey = alpha*ja_y + beta*jb_y
                    
                        // save values that are used for the jet met correction
                        float metx = met()*cos(metPhi());
                        float mety = met()*sin(metPhi());
                        float ja_x = jets_p4().at(j).X();
                        float ja_y = jets_p4().at(j).Y();
                        float jb_x = jets_p4().at(k).X();
                        float jb_y = jets_p4().at(k).Y();

                        // save the corrected values (solution was found using Mathematica).
                        alpha = (mety*jb_x - metx*jb_y) / (ja_y*jb_x - ja_x*jb_y);  
                        beta = (mety*ja_x - metx*ja_y) / (ja_x*jb_y - ja_y*jb_x); 
                    }

                    // compute the corrected masses
                    mass1 = (ll_p4()+( (1+alpha)*jets_p4().at(j) )).M();
                    mass2 = (lt_p4()+( (1+beta)*jets_p4().at(k) )).M();

                    // minimize the delta mass
                    if (fabs(mass1-mass2) < fabs(deltaMass)){
                        // save the delta and average mass of the minimized pair
                        deltaMass = mass1-mass2;
                        avgMass = (mass1+mass2)/2;
                        // save the minimized alpha and beta
                        alphaMin = alpha;
                        betaMin = beta;
                        // save the indices of the jets that minimized delta mass
                        jetllIndex = j;
                        jetltIndex = k;
                    }
                }
            }

            // perform cuts
            if (type() == 3) continue;   // ignoring ee
            if (met() < 60) continue; // mumu only
            if (type() == 0 &&  fabs((ll_p4()+lt_p4()).M() - 91) < 15) continue; // mumu only z-veto
            if (nBtags < 1) continue; 
            if (nJets < 2) continue;
            if (fabs(deltaMass) > 50) continue; 
            
            // increment eventCounters
            if (type() == 0) mumuCounter++;
            if (type() == 1 || type() == 2) emuCounter++;


            // find the gen_ps particles corresponding to our p4s
            llGenerated = getMatchingGeneratedIndex(ll_p4(), indices);
            indices.insert(llGenerated);

            ltGenerated = getMatchingGeneratedIndex(lt_p4(), indices);
            indices.insert(ltGenerated);

            jetllGenerated = getMatchingGeneratedIndex(jets_p4().at(jetllIndex) , indices);
            indices.insert(jetllGenerated);

            jetltGenerated = getMatchingGeneratedIndex(jets_p4().at(jetltIndex) , indices);

            // calculate the combined mass of the two pairs
            if (llGenerated != -1 && ltGenerated != -1 && jetllGenerated != -1 && jetltGenerated != -1){
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

            // calculate the generated average mass
            float genMass = (generatedMass2 + generatedMass1)/2;

            // make eventList
            eventList.open("eventList.txt", ios::app);
            eventList << runNumber() << " " << lumiBlock() << " " <<  eventNumber() << endl;
            eventList.close();

            
            // fill the appopriate plots
            sample["avgMass"]->Fill(avgMass);

            if (useJetCorrection) {
                sample["alpha"]->Fill(alphaMin);
                sample["beta"]->Fill(betaMin);
            }

            if (genMassGood) sample["genMinusReco"]->Fill(genMass - avgMass);


        }

        // print the event counters
        cout << "number of mumu events: " << mumuCounter << endl;
        cout << "number of emu events: " << emuCounter << endl;

    }
    
    return;
}


// utility/background functions

// check if the requested jet is "good"
bool RPVAnalysis::isGoodJet(int index) {
    // pt > 30
    if (jets_p4().at(index).pt() < 30) return false;
    // btagged (loose)
    if (btagDiscriminant().at(index) < .244) return false;
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
        // grab the minimum
        if (deltaR < deltaMin )  {
            index = i;
            deltaMin = deltaR;
        }
    }  

    // return the index of the generated particle that matches
    return index;
}

// fill the sample dictionaries 
void RPVAnalysis::createHistograms() {
   
    // create signal200 plots
    signal600["avgMass"] = new TH1F("signal600_avgMass", "signal 600 Avg Mass", 240, 0, 1200);
    signal600["genMinusReco"] = new TH1F("signal600_genMinusReco", "generated - reco mass", 100, -75, 75);
    signal600["alpha"] = new TH1F("signal600_alpha", "signal 600 Correction Coefficients", 100, -1, 1);
    signal600["beta"] = new TH1F("signal600_beta", "signal 600 Correction Coefficients", 100, -1, 1);

    // create ttjets plots
    ttjets["avgMass"] = new TH1F("ttjets_avgMass", "ttjets Avg Mass", 240, 0, 1200);
    ttjets["genMinusReco"] = new TH1F("ttjets_genMinusReco", "ttjets generated - reco mass", 100, -75, 75);

    // create data plots
    dy["avgMass"] = new TH1F("dy_avgMass", "dy Avg Mass", 240, 0, 1200);
    dy["genMinusReco"] = new TH1F("dy_genMinusReco", "dy generated - reco mass", 100, -75, 75);


    return;
}

// do this with a vector and get the names dynamically instead of using a map
void RPVAnalysis::makePlot(vector<TH1F*> plots, TH1F* overlay){

    /*
    // create a TStack for the plots
    THStack* stack = new THStack("stack", "");
    // and a legend
    TLegend* legend = new TLegend(.73,.9,.89,.6);

    // create a typedef for the iterator
    typedef map<string, TH1F*>::iterator iter;
    //iterate over the map
    for (iter iterator = plots.begin(); iterator != plots.end(); iterator++) {
        
        string name = iterator->first;
        TH1F * plot = iterator->second;

        // add the plot to the legend
        //  legend->AddEntry(plot, name, "f") ;
        // and to the stack
        stack->Add(plot);
    }
    

    // if we were asked to plot the stack, do so
    stack->Draw();
    // if we were given an overlay, draw it
    if (overlay) overlay->Draw("same");

    // draw the legend
    legend->Draw("same");
    */
}


// give the histograms color,overflow, etc.
void RPVAnalysis::prepareHistograms(){


    // color the histograms
    signal600["avgMass"]->SetLineColor(kBlack);
    signal600["genMinusReco"]->SetLineColor(kBlack);
    signal600["alpha"]->SetLineColor(kBlack);
    signal600["beta"]->SetLineColor(kRed);
    
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
    leg->AddEntry(zz["avgMass"], "zz", "f");
    leg->AddEntry(signal600["avgMass"], "signal600", "l");
    */
    leg->AddEntry(signal600["alpha"], "alpha", "l");
    leg->AddEntry(signal600["beta"], "beta", "l");

    // style the legend
    leg->SetFillStyle(0);
    leg->SetBorderSize(0);
    leg->SetTextSize(0.04);

    // prepare the histograms
    prepareHistograms();

    /* stacked plots */
    THStack *stack = new THStack("stack","");

    signal600["alpha"]->Draw();
    signal600["beta"]->Draw("same");

    leg->Draw("same");
}

    

#include "RPVAnalysis.h"


void RPVAnalysis::fillPlot(TChain* samples, TH1F* plot, bool useJetCorrection){

    // get the list of files from the chain
    TObjArray* files = samples->GetListOfFiles();
    // create an iterator over the fiels
    TIter fileIter(files);
    // store the current file data
    TFile* currentFile = 0;

    // stream to write the event list    
    ofstream stream;

    // loop over the files to fill plots
    while(( currentFile = (TFile*)fileIter.Next() )) {
        
        // get the file content
        TFile* file = new TFile(currentFile->GetTitle());
        TTree* tree = (TTree*)file->Get("tree");
        // tell cms2 about the tree
        cms2.Init(tree);

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

                    // default jet correction = 0
                    float alpha =0;
                    float beta = 0;

                    // is {useJetCorrection} set to true?
                    if (useJetCorrection){
                    
                        // if it is, compute the corrections from the system of equation
                    
                        // Ex = alpha*ja_x + beta*jb_x
                        // Ey = alpha*ja_y + beta*jb_y
                    
                        // save values that are used for the jet met correction
                        float metx = met()*cos(metPhi());
                        float mety = met()*sin(metPhi());
                        float ja_x = jets_p4().at(j).X()*jets_p4Correction().at(j);
                        float ja_y = jets_p4().at(j).Y()*jets_p4Correction().at(j);
                        float jb_x = jets_p4().at(k).X()*jets_p4Correction().at(k);
                        float jb_y = jets_p4().at(k).Y()*jets_p4Correction().at(k);

                        // save the corrected values (solution was found using Mathematica).
                        alpha = (mety*jb_x - metx*jb_y) / (ja_y*jb_x - ja_x*jb_y);  
                        beta = (mety*ja_x - metx*ja_y) / (ja_x*jb_y - ja_y*jb_x); 
                    }

                    // compute the corrected masses
                    mass1 = (ll_p4()+( (1+alpha)*jets_p4().at(j)*jets_p4Correction().at(j) )).M();
                    mass2 = (lt_p4()+( (1+beta)*jets_p4().at(k)*jets_p4Correction().at(k) )).M();


                    // minimize the delta mass
                    if (fabs(mass1-mass2) < fabs(deltaMass)){
                        // save the delta and average mass of the minimized pair
                        deltaMass = mass1-mass2;
                        avgMass = (mass1+mass2)/2;
                    }
                }
            }
            
            // perform cuts
            if (type() == 3) continue;
            if (type == 0 && met() < 60) continue;
            if (type == 0 && fabs((ll_p4()+lt_p4()).M() - 91) < 15) continue;
            if (nBtags < 1) continue; 
            if (nJets < 2) continue;
            if (deltaMass > fabs(50)) continue; 

            // make eventList
            stream.open("eventList.txt", ios::app);
            stream << runNumber() << " " << lumiBlock() << " " <<  eventNumber() << endl;
            stream.close();

            // fill the given plot with average mass
            plot->Fill(avgMass);
        }
    }
    
    return ;
}

// check if the requested jet is "good"
bool RPVAnalysis::isGoodJet(int index) {
    // pt > 30
    if (jets_p4().at(index).pt()*jets_p4Correction().at(index) < 30) return false;
    // btagged (loose)
    if (btagDiscriminant().at(index) < .244) return false;
    // eta < 2.5
    if (fabs(jets_p4().at(index).eta()) > 2.5)  return false;
    // dR > 0.4
    if (ROOT::Math::VectorUtil::DeltaR(jets_p4().at(index), ll_p4()) < 0.4) return false;
    if (ROOT::Math::VectorUtil::DeltaR(jets_p4().at(index), lt_p4()) < 0.4) return false;

    return true;
}

// run the analysis
void RPVAnalysis::run(){

    // add the files to their respective chains
    TChain* signal = new TChain("tree");
    signal->Add("/home/users/aaivazis/susy/babymaker/babies/signal600.root");
    
    // create the histograms to fill
    TH1F* before = new TH1F("before", "signal 600 Avg Mass (Before Correction)", 240, 0, 1200);
    TH1F* after = new TH1F("after", "signal 600 Avg Mass (After Correction)", 240, 0, 1200);

    // use the jet correction
    fillPlot(signal, after, true);
    // dont
    fillPlot(signal, before, false);

    // draw the histograms on the same canvas
    after->Draw();
    before->Draw("same");
}

// -*- C++ -*-
#ifndef RPV_H
#define RPV_H
#include "Math/LorentzVector.h"
#include "Math/Point3D.h"
#include "TMath.h"
#include "TBranch.h"
#include "TTree.h"
#include "TH1F.h"
#include "TFile.h"
#include "TBits.h"
#include <vector> 
typedef ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > LorentzVector;

#define PARANOIA

using namespace std; 
class RPV {
private: 
protected: 
	unsigned int index;
	float	met_;
	TBranch *met_branch;
	bool met_isLoaded;
	float	metPhi_;
	TBranch *metPhi_branch;
	bool metPhi_isLoaded;
	vector<ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > > *jets_p4_;
	TBranch *jets_p4_branch;
	bool jets_p4_isLoaded;
	vector<float> *jets_p4Correction_;
	TBranch *jets_p4Correction_branch;
	bool jets_p4Correction_isLoaded;
	int	type_;
	TBranch *type_branch;
	bool type_isLoaded;
	ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > *ll_p4_;
	TBranch *ll_p4_branch;
	bool ll_p4_isLoaded;
	ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > *lt_p4_;
	TBranch *lt_p4_branch;
	bool lt_p4_isLoaded;
	ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > *total_p4_;
	TBranch *total_p4_branch;
	bool total_p4_isLoaded;
	int	ll_id_;
	TBranch *ll_id_branch;
	bool ll_id_isLoaded;
	int	lt_id_;
	TBranch *lt_id_branch;
	bool lt_id_isLoaded;
	int	ll_charge_;
	TBranch *ll_charge_branch;
	bool ll_charge_isLoaded;
	int	lt_charge_;
	TBranch *lt_charge_branch;
	bool lt_charge_isLoaded;
	int	ll_index_;
	TBranch *ll_index_branch;
	bool ll_index_isLoaded;
	int	lt_index_;
	TBranch *lt_index_branch;
	bool lt_index_isLoaded;
	int	eventNumber_;
	TBranch *eventNumber_branch;
	bool eventNumber_isLoaded;
	int	runNumber_;
	TBranch *runNumber_branch;
	bool runNumber_isLoaded;
	int	lumiBlock_;
	TBranch *lumiBlock_branch;
	bool lumiBlock_isLoaded;
	float	scale_1fb_;
	TBranch *scale_1fb_branch;
	bool scale_1fb_isLoaded;
	vector<float> *btagDiscriminant_;
	TBranch *btagDiscriminant_branch;
	bool btagDiscriminant_isLoaded;
	float	generatedDeltaMass_;
	TBranch *generatedDeltaMass_branch;
	bool generatedDeltaMass_isLoaded;
	float	generatedAvgMass_;
	TBranch *generatedAvgMass_branch;
	bool generatedAvgMass_isLoaded;
	int	numEvents_;
	TBranch *numEvents_branch;
	bool numEvents_isLoaded;
public: 
void Init(TTree *tree) {
	jets_p4_branch = 0;
	if (tree->GetBranch("jets_p4") != 0) {
		jets_p4_branch = tree->GetBranch("jets_p4");
		if (jets_p4_branch) {jets_p4_branch->SetAddress(&jets_p4_);}
	}
	ll_p4_branch = 0;
	if (tree->GetBranch("ll_p4") != 0) {
		ll_p4_branch = tree->GetBranch("ll_p4");
		if (ll_p4_branch) {ll_p4_branch->SetAddress(&ll_p4_);}
	}
	lt_p4_branch = 0;
	if (tree->GetBranch("lt_p4") != 0) {
		lt_p4_branch = tree->GetBranch("lt_p4");
		if (lt_p4_branch) {lt_p4_branch->SetAddress(&lt_p4_);}
	}
	total_p4_branch = 0;
	if (tree->GetBranch("total_p4") != 0) {
		total_p4_branch = tree->GetBranch("total_p4");
		if (total_p4_branch) {total_p4_branch->SetAddress(&total_p4_);}
	}
  tree->SetMakeClass(1);
	met_branch = 0;
	if (tree->GetBranch("met") != 0) {
		met_branch = tree->GetBranch("met");
		if (met_branch) {met_branch->SetAddress(&met_);}
	}
	metPhi_branch = 0;
	if (tree->GetBranch("metPhi") != 0) {
		metPhi_branch = tree->GetBranch("metPhi");
		if (metPhi_branch) {metPhi_branch->SetAddress(&metPhi_);}
	}
	jets_p4Correction_branch = 0;
	if (tree->GetBranch("jets_p4Correction") != 0) {
		jets_p4Correction_branch = tree->GetBranch("jets_p4Correction");
		if (jets_p4Correction_branch) {jets_p4Correction_branch->SetAddress(&jets_p4Correction_);}
	}
	type_branch = 0;
	if (tree->GetBranch("type") != 0) {
		type_branch = tree->GetBranch("type");
		if (type_branch) {type_branch->SetAddress(&type_);}
	}
	ll_id_branch = 0;
	if (tree->GetBranch("ll_id") != 0) {
		ll_id_branch = tree->GetBranch("ll_id");
		if (ll_id_branch) {ll_id_branch->SetAddress(&ll_id_);}
	}
	lt_id_branch = 0;
	if (tree->GetBranch("lt_id") != 0) {
		lt_id_branch = tree->GetBranch("lt_id");
		if (lt_id_branch) {lt_id_branch->SetAddress(&lt_id_);}
	}
	ll_charge_branch = 0;
	if (tree->GetBranch("ll_charge") != 0) {
		ll_charge_branch = tree->GetBranch("ll_charge");
		if (ll_charge_branch) {ll_charge_branch->SetAddress(&ll_charge_);}
	}
	lt_charge_branch = 0;
	if (tree->GetBranch("lt_charge") != 0) {
		lt_charge_branch = tree->GetBranch("lt_charge");
		if (lt_charge_branch) {lt_charge_branch->SetAddress(&lt_charge_);}
	}
	ll_index_branch = 0;
	if (tree->GetBranch("ll_index") != 0) {
		ll_index_branch = tree->GetBranch("ll_index");
		if (ll_index_branch) {ll_index_branch->SetAddress(&ll_index_);}
	}
	lt_index_branch = 0;
	if (tree->GetBranch("lt_index") != 0) {
		lt_index_branch = tree->GetBranch("lt_index");
		if (lt_index_branch) {lt_index_branch->SetAddress(&lt_index_);}
	}
	eventNumber_branch = 0;
	if (tree->GetBranch("eventNumber") != 0) {
		eventNumber_branch = tree->GetBranch("eventNumber");
		if (eventNumber_branch) {eventNumber_branch->SetAddress(&eventNumber_);}
	}
	runNumber_branch = 0;
	if (tree->GetBranch("runNumber") != 0) {
		runNumber_branch = tree->GetBranch("runNumber");
		if (runNumber_branch) {runNumber_branch->SetAddress(&runNumber_);}
	}
	lumiBlock_branch = 0;
	if (tree->GetBranch("lumiBlock") != 0) {
		lumiBlock_branch = tree->GetBranch("lumiBlock");
		if (lumiBlock_branch) {lumiBlock_branch->SetAddress(&lumiBlock_);}
	}
	scale_1fb_branch = 0;
	if (tree->GetBranch("scale_1fb") != 0) {
		scale_1fb_branch = tree->GetBranch("scale_1fb");
		if (scale_1fb_branch) {scale_1fb_branch->SetAddress(&scale_1fb_);}
	}
	btagDiscriminant_branch = 0;
	if (tree->GetBranch("btagDiscriminant") != 0) {
		btagDiscriminant_branch = tree->GetBranch("btagDiscriminant");
		if (btagDiscriminant_branch) {btagDiscriminant_branch->SetAddress(&btagDiscriminant_);}
	}
	generatedDeltaMass_branch = 0;
	if (tree->GetBranch("generatedDeltaMass") != 0) {
		generatedDeltaMass_branch = tree->GetBranch("generatedDeltaMass");
		if (generatedDeltaMass_branch) {generatedDeltaMass_branch->SetAddress(&generatedDeltaMass_);}
	}
	generatedAvgMass_branch = 0;
	if (tree->GetBranch("generatedAvgMass") != 0) {
		generatedAvgMass_branch = tree->GetBranch("generatedAvgMass");
		if (generatedAvgMass_branch) {generatedAvgMass_branch->SetAddress(&generatedAvgMass_);}
	}
	numEvents_branch = 0;
	if (tree->GetBranch("numEvents") != 0) {
		numEvents_branch = tree->GetBranch("numEvents");
		if (numEvents_branch) {numEvents_branch->SetAddress(&numEvents_);}
	}
  tree->SetMakeClass(0);
}
void GetEntry(unsigned int idx) 
	// this only marks branches as not loaded, saving a lot of time
	{
		index = idx;
		met_isLoaded = false;
		metPhi_isLoaded = false;
		jets_p4_isLoaded = false;
		jets_p4Correction_isLoaded = false;
		type_isLoaded = false;
		ll_p4_isLoaded = false;
		lt_p4_isLoaded = false;
		total_p4_isLoaded = false;
		ll_id_isLoaded = false;
		lt_id_isLoaded = false;
		ll_charge_isLoaded = false;
		lt_charge_isLoaded = false;
		ll_index_isLoaded = false;
		lt_index_isLoaded = false;
		eventNumber_isLoaded = false;
		runNumber_isLoaded = false;
		lumiBlock_isLoaded = false;
		scale_1fb_isLoaded = false;
		btagDiscriminant_isLoaded = false;
		generatedDeltaMass_isLoaded = false;
		generatedAvgMass_isLoaded = false;
		numEvents_isLoaded = false;
	}

void LoadAllBranches() 
	// load all branches
{
	if (met_branch != 0) met();
	if (metPhi_branch != 0) metPhi();
	if (jets_p4_branch != 0) jets_p4();
	if (jets_p4Correction_branch != 0) jets_p4Correction();
	if (type_branch != 0) type();
	if (ll_p4_branch != 0) ll_p4();
	if (lt_p4_branch != 0) lt_p4();
	if (total_p4_branch != 0) total_p4();
	if (ll_id_branch != 0) ll_id();
	if (lt_id_branch != 0) lt_id();
	if (ll_charge_branch != 0) ll_charge();
	if (lt_charge_branch != 0) lt_charge();
	if (ll_index_branch != 0) ll_index();
	if (lt_index_branch != 0) lt_index();
	if (eventNumber_branch != 0) eventNumber();
	if (runNumber_branch != 0) runNumber();
	if (lumiBlock_branch != 0) lumiBlock();
	if (scale_1fb_branch != 0) scale_1fb();
	if (btagDiscriminant_branch != 0) btagDiscriminant();
	if (generatedDeltaMass_branch != 0) generatedDeltaMass();
	if (generatedAvgMass_branch != 0) generatedAvgMass();
	if (numEvents_branch != 0) numEvents();
}

	float &met()
	{
		if (not met_isLoaded) {
			if (met_branch != 0) {
				met_branch->GetEntry(index);
				#ifdef PARANOIA
				#endif // #ifdef PARANOIA
			} else { 
				printf("branch met_branch does not exist!\n");
				exit(1);
			}
			met_isLoaded = true;
		}
		return met_;
	}
	float &metPhi()
	{
		if (not metPhi_isLoaded) {
			if (metPhi_branch != 0) {
				metPhi_branch->GetEntry(index);
				#ifdef PARANOIA
				#endif // #ifdef PARANOIA
			} else { 
				printf("branch metPhi_branch does not exist!\n");
				exit(1);
			}
			metPhi_isLoaded = true;
		}
		return metPhi_;
	}
	const vector<ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > > &jets_p4()
	{
		if (not jets_p4_isLoaded) {
			if (jets_p4_branch != 0) {
				jets_p4_branch->GetEntry(index);
				#ifdef PARANOIA
				for (vector<ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > >::const_iterator i = jets_p4_->begin(); i != jets_p4_->end(); ++i) {
					int e;
					frexp(i->pt(), &e);
					if (not isfinite(i->pt()) || e > 30) {
						printf("branch jets_p4_branch contains a bad float: %f\n", i->pt());
						exit(1);
					}
				}
				#endif // #ifdef PARANOIA
			} else { 
				printf("branch jets_p4_branch does not exist!\n");
				exit(1);
			}
			jets_p4_isLoaded = true;
		}
		return *jets_p4_;
	}
	const vector<float> &jets_p4Correction()
	{
		if (not jets_p4Correction_isLoaded) {
			if (jets_p4Correction_branch != 0) {
				jets_p4Correction_branch->GetEntry(index);
				#ifdef PARANOIA
				for (vector<float>::const_iterator i = jets_p4Correction_->begin(); i != jets_p4Correction_->end(); ++i) {
					if (not isfinite(*i)) {
						printf("branch jets_p4Correction_branch contains a bad float: %f\n", *i);
						exit(1);
					}
				}
				#endif // #ifdef PARANOIA
			} else { 
				printf("branch jets_p4Correction_branch does not exist!\n");
				exit(1);
			}
			jets_p4Correction_isLoaded = true;
		}
		return *jets_p4Correction_;
	}
	int &type()
	{
		if (not type_isLoaded) {
			if (type_branch != 0) {
				type_branch->GetEntry(index);
				#ifdef PARANOIA
				#endif // #ifdef PARANOIA
			} else { 
				printf("branch type_branch does not exist!\n");
				exit(1);
			}
			type_isLoaded = true;
		}
		return type_;
	}
	ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > &ll_p4()
	{
		if (not ll_p4_isLoaded) {
			if (ll_p4_branch != 0) {
				ll_p4_branch->GetEntry(index);
				#ifdef PARANOIA
				int e;
				frexp(ll_p4_->pt(), &e);
				if (not isfinite(ll_p4_->pt()) || e > 30) {
					printf("branch ll_p4_branch contains a bad float: %f\n", ll_p4_->pt());
					exit(1);
				}
				#endif // #ifdef PARANOIA
			} else { 
				printf("branch ll_p4_branch does not exist!\n");
				exit(1);
			}
			ll_p4_isLoaded = true;
		}
		return *ll_p4_;
	}
	ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > &lt_p4()
	{
		if (not lt_p4_isLoaded) {
			if (lt_p4_branch != 0) {
				lt_p4_branch->GetEntry(index);
				#ifdef PARANOIA
				int e;
				frexp(lt_p4_->pt(), &e);
				if (not isfinite(lt_p4_->pt()) || e > 30) {
					printf("branch lt_p4_branch contains a bad float: %f\n", lt_p4_->pt());
					exit(1);
				}
				#endif // #ifdef PARANOIA
			} else { 
				printf("branch lt_p4_branch does not exist!\n");
				exit(1);
			}
			lt_p4_isLoaded = true;
		}
		return *lt_p4_;
	}
	ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > &total_p4()
	{
		if (not total_p4_isLoaded) {
			if (total_p4_branch != 0) {
				total_p4_branch->GetEntry(index);
				#ifdef PARANOIA
				int e;
				frexp(total_p4_->pt(), &e);
				if (not isfinite(total_p4_->pt()) || e > 30) {
					printf("branch total_p4_branch contains a bad float: %f\n", total_p4_->pt());
					exit(1);
				}
				#endif // #ifdef PARANOIA
			} else { 
				printf("branch total_p4_branch does not exist!\n");
				exit(1);
			}
			total_p4_isLoaded = true;
		}
		return *total_p4_;
	}
	int &ll_id()
	{
		if (not ll_id_isLoaded) {
			if (ll_id_branch != 0) {
				ll_id_branch->GetEntry(index);
				#ifdef PARANOIA
				#endif // #ifdef PARANOIA
			} else { 
				printf("branch ll_id_branch does not exist!\n");
				exit(1);
			}
			ll_id_isLoaded = true;
		}
		return ll_id_;
	}
	int &lt_id()
	{
		if (not lt_id_isLoaded) {
			if (lt_id_branch != 0) {
				lt_id_branch->GetEntry(index);
				#ifdef PARANOIA
				#endif // #ifdef PARANOIA
			} else { 
				printf("branch lt_id_branch does not exist!\n");
				exit(1);
			}
			lt_id_isLoaded = true;
		}
		return lt_id_;
	}
	int &ll_charge()
	{
		if (not ll_charge_isLoaded) {
			if (ll_charge_branch != 0) {
				ll_charge_branch->GetEntry(index);
				#ifdef PARANOIA
				#endif // #ifdef PARANOIA
			} else { 
				printf("branch ll_charge_branch does not exist!\n");
				exit(1);
			}
			ll_charge_isLoaded = true;
		}
		return ll_charge_;
	}
	int &lt_charge()
	{
		if (not lt_charge_isLoaded) {
			if (lt_charge_branch != 0) {
				lt_charge_branch->GetEntry(index);
				#ifdef PARANOIA
				#endif // #ifdef PARANOIA
			} else { 
				printf("branch lt_charge_branch does not exist!\n");
				exit(1);
			}
			lt_charge_isLoaded = true;
		}
		return lt_charge_;
	}
	int &ll_index()
	{
		if (not ll_index_isLoaded) {
			if (ll_index_branch != 0) {
				ll_index_branch->GetEntry(index);
				#ifdef PARANOIA
				#endif // #ifdef PARANOIA
			} else { 
				printf("branch ll_index_branch does not exist!\n");
				exit(1);
			}
			ll_index_isLoaded = true;
		}
		return ll_index_;
	}
	int &lt_index()
	{
		if (not lt_index_isLoaded) {
			if (lt_index_branch != 0) {
				lt_index_branch->GetEntry(index);
				#ifdef PARANOIA
				#endif // #ifdef PARANOIA
			} else { 
				printf("branch lt_index_branch does not exist!\n");
				exit(1);
			}
			lt_index_isLoaded = true;
		}
		return lt_index_;
	}
	int &eventNumber()
	{
		if (not eventNumber_isLoaded) {
			if (eventNumber_branch != 0) {
				eventNumber_branch->GetEntry(index);
				#ifdef PARANOIA
				#endif // #ifdef PARANOIA
			} else { 
				printf("branch eventNumber_branch does not exist!\n");
				exit(1);
			}
			eventNumber_isLoaded = true;
		}
		return eventNumber_;
	}
	int &runNumber()
	{
		if (not runNumber_isLoaded) {
			if (runNumber_branch != 0) {
				runNumber_branch->GetEntry(index);
				#ifdef PARANOIA
				#endif // #ifdef PARANOIA
			} else { 
				printf("branch runNumber_branch does not exist!\n");
				exit(1);
			}
			runNumber_isLoaded = true;
		}
		return runNumber_;
	}
	int &lumiBlock()
	{
		if (not lumiBlock_isLoaded) {
			if (lumiBlock_branch != 0) {
				lumiBlock_branch->GetEntry(index);
				#ifdef PARANOIA
				#endif // #ifdef PARANOIA
			} else { 
				printf("branch lumiBlock_branch does not exist!\n");
				exit(1);
			}
			lumiBlock_isLoaded = true;
		}
		return lumiBlock_;
	}
	float &scale_1fb()
	{
		if (not scale_1fb_isLoaded) {
			if (scale_1fb_branch != 0) {
				scale_1fb_branch->GetEntry(index);
				#ifdef PARANOIA
				#endif // #ifdef PARANOIA
			} else { 
				printf("branch scale_1fb_branch does not exist!\n");
				exit(1);
			}
			scale_1fb_isLoaded = true;
		}
		return scale_1fb_;
	}
	const vector<float> &btagDiscriminant()
	{
		if (not btagDiscriminant_isLoaded) {
			if (btagDiscriminant_branch != 0) {
				btagDiscriminant_branch->GetEntry(index);
				#ifdef PARANOIA
				for (vector<float>::const_iterator i = btagDiscriminant_->begin(); i != btagDiscriminant_->end(); ++i) {
					if (not isfinite(*i)) {
						printf("branch btagDiscriminant_branch contains a bad float: %f\n", *i);
						exit(1);
					}
				}
				#endif // #ifdef PARANOIA
			} else { 
				printf("branch btagDiscriminant_branch does not exist!\n");
				exit(1);
			}
			btagDiscriminant_isLoaded = true;
		}
		return *btagDiscriminant_;
	}
	float &generatedDeltaMass()
	{
		if (not generatedDeltaMass_isLoaded) {
			if (generatedDeltaMass_branch != 0) {
				generatedDeltaMass_branch->GetEntry(index);
				#ifdef PARANOIA
				#endif // #ifdef PARANOIA
			} else { 
				printf("branch generatedDeltaMass_branch does not exist!\n");
				exit(1);
			}
			generatedDeltaMass_isLoaded = true;
		}
		return generatedDeltaMass_;
	}
	float &generatedAvgMass()
	{
		if (not generatedAvgMass_isLoaded) {
			if (generatedAvgMass_branch != 0) {
				generatedAvgMass_branch->GetEntry(index);
				#ifdef PARANOIA
				#endif // #ifdef PARANOIA
			} else { 
				printf("branch generatedAvgMass_branch does not exist!\n");
				exit(1);
			}
			generatedAvgMass_isLoaded = true;
		}
		return generatedAvgMass_;
	}
	int &numEvents()
	{
		if (not numEvents_isLoaded) {
			if (numEvents_branch != 0) {
				numEvents_branch->GetEntry(index);
				#ifdef PARANOIA
				#endif // #ifdef PARANOIA
			} else { 
				printf("branch numEvents_branch does not exist!\n");
				exit(1);
			}
			numEvents_isLoaded = true;
		}
		return numEvents_;
	}

  static void progress( int nEventsTotal, int nEventsChain ){
    int period = 1000;
    if(nEventsTotal%1000 == 0) {
      // xterm magic from L. Vacavant and A. Cerri
      if (isatty(1)) {
        if( ( nEventsChain - nEventsTotal ) > period ){
          float frac = (float)nEventsTotal/(nEventsChain*0.01);
          printf("\015\033[32m ---> \033[1m\033[31m%4.1f%%"
               "\033[0m\033[32m <---\033[0m\015", frac);
          fflush(stdout);
        }
        else {
          printf("\015\033[32m ---> \033[1m\033[31m%4.1f%%"
                 "\033[0m\033[32m <---\033[0m\015", 100.);
          cout << endl;
        }
      }
    }
  }
  
};

#ifndef __CINT__
extern RPV cms2;
#endif

namespace hak {
	const float &met();
	const float &metPhi();
	const vector<ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > > &jets_p4();
	const vector<float> &jets_p4Correction();
	const int &type();
	const ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > &ll_p4();
	const ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > &lt_p4();
	const ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > &total_p4();
	const int &ll_id();
	const int &lt_id();
	const int &ll_charge();
	const int &lt_charge();
	const int &ll_index();
	const int &lt_index();
	const int &eventNumber();
	const int &runNumber();
	const int &lumiBlock();
	const float &scale_1fb();
	const vector<float> &btagDiscriminant();
	const float &generatedDeltaMass();
	const float &generatedAvgMass();
	const int &numEvents();
}
#endif

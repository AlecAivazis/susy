// -*- C++ -*-
#ifndef CMS2_H
#define CMS2_H
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
class CMS2 {
private: 
protected: 
	unsigned int index;
	float	met_;
	TBranch *met_branch;
	bool met_isLoaded;
	vector<ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > > *jets_p4_;
	TBranch *jets_p4_branch;
	bool jets_p4_isLoaded;
	vector<int> *type_;
	TBranch *type_branch;
	bool type_isLoaded;
	vector<ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > > *ll_p4_;
	TBranch *ll_p4_branch;
	bool ll_p4_isLoaded;
	vector<ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > > *lt_p4_;
	TBranch *lt_p4_branch;
	bool lt_p4_isLoaded;
	vector<ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > > *total_p4_;
	TBranch *total_p4_branch;
	bool total_p4_isLoaded;
	vector<int> *ll_id_;
	TBranch *ll_id_branch;
	bool ll_id_isLoaded;
	vector<int> *lt_id_;
	TBranch *lt_id_branch;
	bool lt_id_isLoaded;
	vector<int> *ll_charge_;
	TBranch *ll_charge_branch;
	bool ll_charge_isLoaded;
	vector<int> *lt_charge_;
	TBranch *lt_charge_branch;
	bool lt_charge_isLoaded;
	vector<int> *ll_index_;
	TBranch *ll_index_branch;
	bool ll_index_isLoaded;
	vector<int> *lt_index_;
	TBranch *lt_index_branch;
	bool lt_index_isLoaded;
	float	scale_1fb_;
	TBranch *scale_1fb_branch;
	bool scale_1fb_isLoaded;
	vector<float> *btag_;
	TBranch *btag_branch;
	bool btag_isLoaded;
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
	scale_1fb_branch = 0;
	if (tree->GetBranch("scale_1fb") != 0) {
		scale_1fb_branch = tree->GetBranch("scale_1fb");
		if (scale_1fb_branch) {scale_1fb_branch->SetAddress(&scale_1fb_);}
	}
	btag_branch = 0;
	if (tree->GetBranch("btag") != 0) {
		btag_branch = tree->GetBranch("btag");
		if (btag_branch) {btag_branch->SetAddress(&btag_);}
	}
  tree->SetMakeClass(0);
}
void GetEntry(unsigned int idx) 
	// this only marks branches as not loaded, saving a lot of time
	{
		index = idx;
		met_isLoaded = false;
		jets_p4_isLoaded = false;
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
		scale_1fb_isLoaded = false;
		btag_isLoaded = false;
	}

void LoadAllBranches() 
	// load all branches
{
	if (met_branch != 0) met();
	if (jets_p4_branch != 0) jets_p4();
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
	if (scale_1fb_branch != 0) scale_1fb();
	if (btag_branch != 0) btag();
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
	const vector<int> &type()
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
		return *type_;
	}
	const vector<ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > > &ll_p4()
	{
		if (not ll_p4_isLoaded) {
			if (ll_p4_branch != 0) {
				ll_p4_branch->GetEntry(index);
				#ifdef PARANOIA
				for (vector<ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > >::const_iterator i = ll_p4_->begin(); i != ll_p4_->end(); ++i) {
					int e;
					frexp(i->pt(), &e);
					if (not isfinite(i->pt()) || e > 30) {
						printf("branch ll_p4_branch contains a bad float: %f\n", i->pt());
						exit(1);
					}
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
	const vector<ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > > &lt_p4()
	{
		if (not lt_p4_isLoaded) {
			if (lt_p4_branch != 0) {
				lt_p4_branch->GetEntry(index);
				#ifdef PARANOIA
				for (vector<ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > >::const_iterator i = lt_p4_->begin(); i != lt_p4_->end(); ++i) {
					int e;
					frexp(i->pt(), &e);
					if (not isfinite(i->pt()) || e > 30) {
						printf("branch lt_p4_branch contains a bad float: %f\n", i->pt());
						exit(1);
					}
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
	const vector<ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > > &total_p4()
	{
		if (not total_p4_isLoaded) {
			if (total_p4_branch != 0) {
				total_p4_branch->GetEntry(index);
				#ifdef PARANOIA
				for (vector<ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > >::const_iterator i = total_p4_->begin(); i != total_p4_->end(); ++i) {
					int e;
					frexp(i->pt(), &e);
					if (not isfinite(i->pt()) || e > 30) {
						printf("branch total_p4_branch contains a bad float: %f\n", i->pt());
						exit(1);
					}
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
	const vector<int> &ll_id()
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
		return *ll_id_;
	}
	const vector<int> &lt_id()
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
		return *lt_id_;
	}
	const vector<int> &ll_charge()
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
		return *ll_charge_;
	}
	const vector<int> &lt_charge()
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
		return *lt_charge_;
	}
	const vector<int> &ll_index()
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
		return *ll_index_;
	}
	const vector<int> &lt_index()
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
		return *lt_index_;
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
	const vector<float> &btag()
	{
		if (not btag_isLoaded) {
			if (btag_branch != 0) {
				btag_branch->GetEntry(index);
				#ifdef PARANOIA
				for (vector<float>::const_iterator i = btag_->begin(); i != btag_->end(); ++i) {
					if (not isfinite(*i)) {
						printf("branch btag_branch contains a bad float: %f\n", *i);
						exit(1);
					}
				}
				#endif // #ifdef PARANOIA
			} else { 
				printf("branch btag_branch does not exist!\n");
				exit(1);
			}
			btag_isLoaded = true;
		}
		return *btag_;
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
extern CMS2 cms2;
#endif

namespace tas {
	const float &met();
	const vector<ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > > &jets_p4();
	const vector<int> &type();
	const vector<ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > > &ll_p4();
	const vector<ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > > &lt_p4();
	const vector<ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > > &total_p4();
	const vector<int> &ll_id();
	const vector<int> &lt_id();
	const vector<int> &ll_charge();
	const vector<int> &lt_charge();
	const vector<int> &ll_index();
	const vector<int> &lt_index();
	const float &scale_1fb();
	const vector<float> &btag();
}
#endif

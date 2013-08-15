#include "CMS2.h"
CMS2 cms2;
namespace tas {
	const float &met() { return cms2.met(); }
	const vector<ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > > &jets_p4() { return cms2.jets_p4(); }
	const vector<int> &type() { return cms2.type(); }
	const vector<ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > > &ll_p4() { return cms2.ll_p4(); }
	const vector<ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > > &lt_p4() { return cms2.lt_p4(); }
	const vector<ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > > &total_p4() { return cms2.total_p4(); }
	const vector<int> &ll_id() { return cms2.ll_id(); }
	const vector<int> &lt_id() { return cms2.lt_id(); }
	const vector<int> &ll_charge() { return cms2.ll_charge(); }
	const vector<int> &lt_charge() { return cms2.lt_charge(); }
	const vector<int> &ll_index() { return cms2.ll_index(); }
	const vector<int> &lt_index() { return cms2.lt_index(); }
	const float &scale_1fb() { return cms2.scale_1fb(); }
	const vector<float> &btag() { return cms2.btag(); }
}

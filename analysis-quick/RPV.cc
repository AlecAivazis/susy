#include "RPV.h"
RPV cms2;
namespace hak {
	const float &met() { return cms2.met(); }
	const float &metPhi() { return cms2.metPhi(); }
	const vector<ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > > &jets_p4() { return cms2.jets_p4(); }
	const vector<float> &jets_p4Correction() { return cms2.jets_p4Correction(); }
	const int &type() { return cms2.type(); }
	const ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > &ll_p4() { return cms2.ll_p4(); }
	const ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > &lt_p4() { return cms2.lt_p4(); }
	const ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > &total_p4() { return cms2.total_p4(); }
	const int &ll_id() { return cms2.ll_id(); }
	const int &lt_id() { return cms2.lt_id(); }
	const int &ll_charge() { return cms2.ll_charge(); }
	const int &lt_charge() { return cms2.lt_charge(); }
	const int &ll_index() { return cms2.ll_index(); }
	const int &lt_index() { return cms2.lt_index(); }
	const int &eventNumber() { return cms2.eventNumber(); }
	const int &runNumber() { return cms2.runNumber(); }
	const int &lumiBlock() { return cms2.lumiBlock(); }
	const float &scale_1fb() { return cms2.scale_1fb(); }
	const vector<float> &btagDiscriminant() { return cms2.btagDiscriminant(); }
	const float &generatedDeltaMass() { return cms2.generatedDeltaMass(); }
	const float &generatedAvgMass() { return cms2.generatedAvgMass(); }
	const int &numEvents() { return cms2.numEvents(); }
}

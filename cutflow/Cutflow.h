#ifndef cutflow_h
#define cutflow_h

// C++ includes
#include <string>
#include <vector>

// ROOT includes
#include "TROOT.h"
#include "TFile.h"
#include "TChain.h"
#include "TTree.h"
#include "TH1F.h"
#include "Math/VectorUtil.h"
#include "Math/Vector4D.h"


class Cutflow {

 public:

  Cutflow() {};
  ~Cutflow() {};

  void draw(TChain* chainZ, int numFiles);

 private:

};
#endif

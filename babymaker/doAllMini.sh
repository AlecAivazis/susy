#! /bin/bash
root -b -q "doSignal.C(\"signal200-mini-actual\", 5)"
root -b -q "doTTbar.C(\"ttjets-mini-actual\", 5)"
root -b -q "doDY.C(\"dy-mini-actual\", 5)"

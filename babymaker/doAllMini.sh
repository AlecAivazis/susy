#! /bin/bash
root -b -q "doSignal.C(\"signal200-mini-before\", 5)"
root -b -q "doTTbar.C(\"ttjets-mini-before\", 5)"
root -b -q "doDY.C(\"dy-mini-before\", 5)"

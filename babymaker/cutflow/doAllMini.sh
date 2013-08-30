#! /bin/bash
root -b -q "doSignal.C(\"signal200-mini\", 5)"
root -b -q "doTTbar.C(\"tt-mini\", 5)"
root -b -q "doDY.C(\"dy-mini\", 5)"

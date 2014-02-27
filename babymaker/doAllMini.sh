#! /bin/bash
root -b -q "doSignal.C(5, \"-mini\")"
root -b -q "doTTbar.C(5, \"-mini\")"
root -b -q "doDY.C(5, \"-mini\")"
root -b -q "doZZ.C(5, \"-mini\")"

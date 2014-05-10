#! /bin/bash
root -b -q doSignal.C
root -b -q "doTTbar.C(20)"
root -b -q doData.C
root -b -q "doDY.C(20)"
root -b -q doZZ.C

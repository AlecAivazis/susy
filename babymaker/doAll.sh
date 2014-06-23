#! /bin/bash
root -b -q doSignal.C
root -b -q "doTTbar.C(100)"
root -b -q doData.C
root -b -q "doDY.C(50)"
root -b -q doZZ.C
root -b -q doW.C

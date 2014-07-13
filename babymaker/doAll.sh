#! /bin/bash
root -b -q doSignal.C
root -b -q "doTTbar.C(1000000)"
root -b -q doData.C
root -b -q "doDY.C(1000000)"
root -b -q doZZ.C
root -b -q doW.C

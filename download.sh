#!/bin/bash -ex
cd ./data
rm *.dat *.atr *.hea *.dat.* *.atr.* *.hea.*
wget -i files.txt
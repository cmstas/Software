*** you need to run this from within a CMSSW release
*** you need to run this from lxplus

assuming you have a CMSSW release checked out and your environment setup, do:

cd $CMSSW_BASE/src
git cms-init
git cms-addpkg HLTrigger/Tools
git clone git@github.com:cmstas/Software.git
cd Software
git checkout root6
cd ../
cp Software/goodRunList/dcsonly_2015.py HLTrigger/Tools/python/
scram b -j3
cd HLTrigger/Tools/python

*** edit the last line of dcsonly_2015.py to change the first entry of getRunList to the first run you want in your list
*** edit L70 with the outfile path you want the results written to

python dcsonly_2015.py

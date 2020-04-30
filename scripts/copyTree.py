#! /usr/bin/env python

import sys
import glob

if len(sys.argv) < 3:
    print """  
    General-purpose tool for copying, merging, and skimming root files.

    Usage: {0} <input_file> <output_file> <n_events (-1)> <first_entry (0)> <tree_name (\"Events\")> <selection (\"\")>".format(sys.argv[0])

    If input_file contains wildcards (to run over/merge multiple files), it needs to be in quotes
    n_events is the number of events to copy. -1 for all events in tree(s)
    first_entry is the entry number to start copying at
    tree_name is the name of the TTree in the ROOT file
    selection is a TTree::Draw style selection to apply when copying. If blank, just copy all events.
"""
    sys.exit(0)

# dumb root bug
if len(sys.argv)>6:
    sys.argv[6] = sys.argv[6].replace("$","#")

import ROOT

isChain=('*' in sys.argv[1])

if not isChain:
    fin = ROOT.TFile(sys.argv[1])

nevt = -1
if len(sys.argv)>3:
    nevt = int(sys.argv[3])

if nevt==-1:
    nevt = ROOT.TTree.kMaxEntries

first = 0
if len(sys.argv)>4:
    first = int(sys.argv[4])

tname = "Events"
if len(sys.argv)>5:
    tname = sys.argv[5]

sel = ""
if len(sys.argv)>6:
    sel = sys.argv[6].replace("#","$")

if not isChain:
    tree = fin.Get(tname)
else:
    tree = ROOT.TChain(tname)
    for f in glob.glob(sys.argv[1]):
        tree.Add(f)

if not tree or tree.GetEntries()==0:
    print "ERROR! tree doesn't exist or has 0 entries!"
    exit(1)

fout = ROOT.TFile(sys.argv[2], "RECREATE")

tree_new = tree.CopyTree(sel, "", nevt, first)

fout.cd()
tree_new.Write(tname, ROOT.TObject.kWriteDelete)

fout.Close()
if not isChain:
    fin.Close()


#! /usr/bin/env python

import argparse
import sys
import ROOT as r

parser = argparse.ArgumentParser(description="Print branch sizes of a TTree")
parser.add_argument('input_file', help='file containing the TTree')
parser.add_argument('-t', '--tree_name', dest='tree_name', default="Events", help="Name of the tree within the file (default is \"Events\")")
parser.add_argument('-r', '--raw', dest='do_raw', action="store_true", help="Print raw byte counts (default is to print in human readable form)")
parser.add_argument('-e', '--per_event', dest='per_event', action="store_true", help="Normalize sizes to per-event averages")
args = parser.parse_args()

def GetHumanReadable(bytes):
    kb = bytes/1024.
    mb = kb/1024.
    gb = mb/1024.
    if kb < 1.0:
        return "{0:d}".format(int(bytes))
    elif kb < 30:
        return "{0:.1f}K".format(kb)
    elif mb < 1.0:
        return "{0:d}K".format(int(kb))
    elif mb < 30:
        return "{0:.1f}M".format(mb)
    elif gb < 1.0:
        return "{0:d}M".format(int(mb))
    elif gb < 30:
        return "{0:.1f}G".format(gb)
    else:
        return "{0:d}G".format(int(gb))

def GetAllBranches(t, pref=""):
    bs = list(t.GetListOfBranches())
    ret = []
    for b in bs:
        ret += [(pref+b.GetName(), b)]
        ret += GetAllBranches(b,pref+b.GetName()+".")
    return ret

fin = r.TFile(args.input_file)
t = fin.Get(args.tree_name)
Nevt = float(t.GetEntries())
tot_raw = t.GetTotBytes()
tot_zip = t.GetZipBytes()
if args.per_event:
    tot_raw /= Nevt
    tot_zip /= Nevt

bs = GetAllBranches(t)

sizes = []
for bname,b in bs:
    comp = 1.0
    if b.GetZipBytes() > 0:
        comp = 1.0*b.GetTotalSize()/b.GetZipBytes()
    btot = b.GetTotalSize()
    bzip = b.GetZipBytes()
    if args.per_event:
        btot /= Nevt
        bzip /= Nevt
    sizes.append((bname, btot, bzip, comp))

max_len = len(sorted(sizes, key=lambda x:len(x[0]))[-1][0])
sizes = sorted(sizes, key=lambda x:x[2], reverse=True)
f = lambda b:str(b) if args.do_raw else GetHumanReadable(b)

fmt_string =  "{{0:{0}s}} {{1:>12s}} {{2:>12s}} {{3:>12s}} {{4:>9s}}".format(max_len)
print ""
print fmt_string.format("Branch","Raw Size", "Zip Size", "Compression", "% Total")
print "-"*(max_len+13+13+13+10)
fmt_string =  "{{0:{0}s}} {{1:>12s}} {{2:>12s}} {{3:12.3f}} {{4:8.2f}}%".format(max_len)
for s in sizes:
    print fmt_string.format(s[0], f(s[1]), f(s[2]), s[3], 100.0*s[2]/tot_zip)
print "-"*(max_len+13+13+13+10)
print fmt_string.format("TOTAL", f(tot_raw), f(tot_zip), 1.0*tot_raw/tot_zip, 100)
print ""

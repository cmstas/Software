#!/usr/bin/env python
import os
import shutil
import time
import sys
import random
import stat
import subprocess
from optparse import OptionParser


parser = OptionParser()



parser.add_option("-f", "--file", dest="file",type="string",metavar=".txt",
                                    help="choose one input file")

parser.add_option("-S", "--smooth", dest="smooth", default=False,action="store_true",
                                    help="cut values under 200 out and add value per hand")

parser.add_option("-r", "--rinv", dest="rinv", default=False,action="store_true",
                                    help="do inverse r-value plot")

parser.add_option("-t", "--threesig", dest="threesig", default=False,action="store_true",
                                    help="do 3 sigma plot")

parser.add_option("-g", "--graph", dest="graph", default=False,action="store_true",
                                    help="make TGraph file")

parser.add_option("-a", "--smootha", dest="smootha", default=False,action="store_true",
                                    help="cut values under 300 out and add value per hand")


parser.add_option("-A", "--add", dest="add", default=False,action="store_true",
                                    help="add the value 100, 0 ")





(options, args) = parser.parse_args()


def run_bash(cmd):
    proc = subprocess.Popen(cmd, shell=True, stdout=subprocess.PIPE)
    out = proc.stdout.read().strip()
    #out = p.stdout.read().strip()
    return out  #This is the stdout from the shell command     



def my_sort(in_list):

    sorted_list=[]

    sorted_in_list=sorted(in_list)
    #sorted_in_list=in_list

    akt_ele=sorted_in_list.pop(0)
    sorted_list.append(akt_ele)
    while sorted_in_list:
        akt_x=float(akt_ele[1])
        akt_y=float(akt_ele[2])
        min_dist=float("inf")
        pop_i=0
        for test_i, test_ele in enumerate(sorted_in_list):
            test_x=float(test_ele[1])
            test_y=float(test_ele[2])
            test_dist=(test_x-akt_x)**2+(test_y-akt_y)**2
            if test_dist < min_dist:
                min_dist = test_dist
                pop_i=test_i
        akt_ele=sorted_in_list.pop(pop_i)
        sorted_list.append(akt_ele)
        #print pop_i
    
    return sorted_list




run_bash("cp "+options.file+" dummy.txt")
if options.rinv: 
    run_bash("gnuplot gnu_script_rinv.gplot")
elif options.threesig:
    run_bash("gnuplot gnu_script_signif3.gplot")
else:
    run_bash("gnuplot gnu_script.gplot")



in_file_str=""
try:
    in_file=open("dummy.dat",'r')
    in_file_str=in_file.read()
    in_file.close()
except:
    pass

all_xbins=[]
all_ybins=[]

all_srotbins=[]

for akt_line in in_file_str.splitlines():
    if not akt_line.strip():
        continue
    if akt_line[0] =='#':
        continue
    akt_ob=akt_line.split()
    if len(akt_ob) != 3:
        continue
    if options.smooth and float(akt_ob[0])<200:
        continue
    if options.smootha and float(akt_ob[0])<350:
        continue    
    all_xbins.append(akt_ob[0])
    all_ybins.append(akt_ob[1])
    all_srotbins.append([float(akt_ob[0]),akt_ob[0],akt_ob[1]])


if options.smooth:
    all_xbins.append("125")
    all_ybins.append("0")
    all_srotbins.append([125,"125","0"])

if options.smootha:
    all_xbins.append("100")
    all_ybins.append("0")
    all_srotbins.append([100,"100","0"])





if options.add:
    all_srotbins.append([100,"100","0"])

better_sorted=my_sort(all_srotbins)

f_points_name = options.file.replace(".txt","_points.txt")
if options.threesig:
    f_points_name = f_points_name.replace("signif","signif3")
print f_points_name
f_points = open(f_points_name,"w")
for val in better_sorted:
    x_val = val[1]
    y_val = val[2]
    f_points.write("%s %s\n"%(x_val,y_val))

f_points.close()

if options.graph:
    g_cmd = 'root -b -q points_to_graph.C+\(\\"'+f_points_name+'\\"\)'
    print g_cmd
    run_bash(g_cmd)

x_bins_str="x_bins = "
#for x_va in sorted(all_srotbins):
for x_va in better_sorted:
    x_v=x_va[1]
    x_bins_str+=x_v+", "
print x_bins_str.rstrip(", ")


y_bins_str="y_bins = "
#for y_va in sorted(all_srotbins):
for y_va in better_sorted:
    y_v=y_va[2]
    y_bins_str+=y_v+", "
print y_bins_str.rstrip(", ")




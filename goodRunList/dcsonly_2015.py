#!/usr/bin/env python26
import os,string,sys,commands,time,json
from rrapi import RRApi, RRApiError

def toOrdinaryJSON(fromRR3, verbose=False):
    result = {}
    for block in fromRR3:
        if len(block) == 3:
            runNum = block['runNumber']
            lumiStart = block['sectionFrom']
            lumiEnd = block['sectionTo']
            if verbose:
                print " debug: Run ", runNum, " Lumi ", lumiStart, ", ", lumiEnd
            result.setdefault(str(runNum), []).append([lumiStart, lumiEnd])
    return result

def getRunList(minRun, save=False):

    runlist = []
    FULLADDRESS  = "http://runregistry.web.cern.ch/runregistry/"

    print "RunRegistry from: ",FULLADDRESS
    try:
        api = RRApi(FULLADDRESS, debug = True)
    except RRApiError, e:
        print e

    filter = {"runNumber": ">= %d" % minRun, "dataset": {"rowClass": "org.cern.cms.dqm.runregistry.user.model.RunDatasetRowGlobal", "filter": {"online": "= true", "datasetName": "like %Online%ALL", "runClassName" : "Collisions15", "run": {"rowClass": "org.cern.cms.dqm.runregistry.user.model.RunSummaryRowGlobal", "filter": {"bfield": "> 3.7", "pixelPresent": "= true", "trackerPresent": "= true", "cscPresent": "= true", "dtPresent": "= true", "ecalPresent": "= true", "hcalPresent": "= true", "rpcPresent": "= true"}}}}}

    filter.setdefault("fpixReady", "isNull OR = true")
    filter.setdefault("bpixReady", "isNull OR = true")
    filter.setdefault("tecmReady", "isNull OR = true")
    filter.setdefault("tecpReady", "isNull OR = true")    
    filter.setdefault("tobReady",  "isNull OR = true")
    filter.setdefault("tibtidReady", "isNull OR = true")
    filter.setdefault("ebmReady",  "isNull OR = true")
    filter.setdefault("ebpReady",  "isNull OR = true")    
    filter.setdefault("eemReady",  "isNull OR = true")
    filter.setdefault("eepReady",  "isNull OR = true")
    filter.setdefault("esmReady",  "isNull OR = true")
    filter.setdefault("espReady",  "isNull OR = true")
    filter.setdefault("hoReady",   "isNull OR = true")
    filter.setdefault("hfReady",   "isNull OR = true")
    filter.setdefault("hbheaReady", "isNull OR = true")
    filter.setdefault("hbhebReady", "isNull OR = true")
    filter.setdefault("hbhecReady", "isNull OR = true")
    filter.setdefault("cscmReady", "isNull OR = true")
    filter.setdefault("cscpReady", "isNull OR = true")        
    filter.setdefault("dtmReady", "isNull OR = true")
    filter.setdefault("dtpReady", "isNull OR = true")
    filter.setdefault("dt0Ready", "isNull OR = true")
    filter.setdefault("rpcReady", "isNull OR = true")    
    filter.setdefault("cmsActive",   "isNull OR = true")
    filter.setdefault("beam1Present","isNull OR = true")
    filter.setdefault("beam2Present","isNull OR = true")
    filter.setdefault("beam1Stable", "isNull OR = true")
    filter.setdefault("beam2Stable", "isNull OR = true")
    template = 'json'
    table = 'datasetlumis'
    print json.dumps(filter)
    dcs_only = api.data(workspace = 'GLOBAL', table = table, template = template, columns = ['runNumber', 'sectionFrom', 'sectionTo'], filter = filter)

    print json.dumps(dcs_only, indent=2)

    print json.dumps(toOrdinaryJSON(dcs_only, verbose=False), indent=2)
    print len(dcs_only)

    if len(dcs_only)!=0:
        if save:
            lumiSummary = open('/afs/cern.ch/user/f/fgolf/private/CMSSW_7_4_5/src/HLTrigger/Tools/python/json_DCSONLY_Run2015B.txt', 'w')
            json.dump(toOrdinaryJSON(dcs_only, verbose=False), lumiSummary, indent=2, sort_keys=True)
            lumiSummary.close()
    else:
        print " Something wrong, the DCSONLY file has 0 length... skipping it"
                        
#     for line in run_data.split("\n"):
#         #print line
#         run=line.split(',')[0]
#         if "RUN_NUMBER" in run or run == "":
#             continue
#         #print "RUN: " + run
#         runlist.append(int(run))
#     return runlist

# getRunList(190389, save=True)
getRunList(251023, save=True)


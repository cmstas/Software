import os
import ROOT as r
r.gROOT.ProcessLine(".L {0}/dataMCplotMaker.cc+".format(os.path.realpath(__file__).rsplit("/",1)[0]))
from ROOT import dataMCplotMaker

def post_plotting(opts):
    fnamejson = opts["outputName"].replace(".pdf",".json")
    if os.path.isfile(fnamejson):
        clean_json(fnamejson)

def clean_json(fname):
    # replace inf, nan with 1000000
    # remove non-plaintext stuff in TLatex objects
    import re
    buff = ""
    with open(fname,"r") as fhin:
        foundlatex = False
        for line in fhin:
            if "inf" in line or "nan" in line:
                if re.search(r'\binf\b', line): 
                    line = line.replace("inf","1000000")
                elif re.search(r'\bnan\b', line):
                    line = line.replace("nan","1000000")
            if foundlatex and "fTitle" in line:
                line = re.sub("#[a-z]+\[[0-9\.\-]+\]", "", line)
                foundlatex = False
            if "TLatex" in line:
                foundlatex = True
            buff += line
    with open(fname,"w") as fhout:
        fhout.write(buff)



def dataMCplot(data, bgs=[], systs=[], titles=[], sigs=[], sigtitles=[], title="", subtitle="", colors=[], opts={}, opts_str="", total_syst=None):
    v_bgs = r.vector("TH1F*")()
    v_sigs = r.vector("TH1F*")()
    v_titles = r.vector('string')()
    v_sigtitles = r.vector('string')()
    v_colors = r.vector('Color_t')()
    v_bgsysts = r.vector('pair<TH1F*,float>')()
    bgtotalsyst = r.TH1F()

    for k,v in opts.items():
        if type(v) is bool:
            if v: opts_str += "--{0} ".format(k)
        else:
            opts_str += "--{0} {1} ".format(str(k),str(v))

    if "outputName" in opts:
        dir_name = opts["outputName"].rsplit("/",1)[0]
        if not os.path.isdir(dir_name):
            os.system("mkdir -p {0}".format(dir_name))

    the_bgs = None
    for tit in titles: v_titles.push_back(tit)
    for sig in sigs: v_sigs.push_back(sig)
    for sigtit in sigtitles: v_sigtitles.push_back(sigtit)
    for col in colors: v_colors.push_back(col)
    if systs and len(systs) == len(bgs):
        for bg,syst in zip(bgs,systs):
            v_bgsysts.push_back(r.pair('TH1F*,float')(bg,syst))
        the_bgs = v_bgsysts
    else:
        for bg in bgs: 
            v_bgs.push_back(bg)
        the_bgs = v_bgs
    if total_syst:
        bgtotalsyst = total_syst

    if total_syst:
        dataMCplotMaker(data, the_bgs, v_titles, title, subtitle, opts_str, v_sigs, v_sigtitles, v_colors, bgtotalsyst)
    else:
        dataMCplotMaker(data, the_bgs, v_titles, title, subtitle, opts_str, v_sigs, v_sigtitles, v_colors)
    post_plotting(opts)

if __name__ == "__main__":
    h_data = r.TH1F("data", "", 7, 0, 7)
    h_wz = h_data.Clone("wz")
    h_ttz = h_data.Clone("ttz")

    # h_data.FillRandom("gaus",1000)
    # h_wz.FillRandom("gaus",500)
    # h_ttz.FillRandom("gaus",500)
    # h_data.FillRandom("gaus",5)
    h_wz.FillRandom("gaus",5)
    h_ttz.FillRandom("gaus",10)

    for i in range(10): h_data.Fill(0)
    for i in range(2): h_data.Fill(1)

    d_opts = {
            "poissonErrorsNoZeros": True,
            "lumi": 36.8,
            "outputName": "plots/test.pdf",
            "xAxisLabel": "Njets",
            "noXaxisUnit": True,
            "percentageInBox": True,
            "isLinear": True,
            "legendUp": -0.15,
            "legendRight": -0.08,
            "outOfFrame": True,
            "legendTaller": 0.15,
            "yTitleOffset": -0.5,
            "type": "Preliminary",
            "noGrass": True,
            # "flagLocation": "0.6,0.965,0.07",
            # "flagLocation": "0.5,0.7,0.15", # add a US flag because 'merica
            "darkColorLines": True,
            # "flagLocation": "0.6,0.965,0.07",
            "makeTable": True,
            "makeJSON": True,
            "flagLocation": "0.5,0.7,0.15", # add a US flag because 'merica
            }

    dataMCplot(h_data, bgs=[h_wz,h_ttz], titles=["WZ","t#bar{t}Z"], title="test", colors=[r.kGreen+2,r.kBlue-1], opts=d_opts)
    os.system("ic " + d_opts["outputName"])

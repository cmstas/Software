import os
import ROOT as r
r.gROOT.ProcessLine(".L {0}/dataMCplotMaker.cc+".format(os.path.realpath(__file__).rsplit("/",1)[0]))
from ROOT import dataMCplotMaker

def dataMCplot(data, bgs=[], titles=[], title="", subtitle="", colors=[], opts={}):
    v_bgs = r.vector("TH1F*")()
    v_sigs = r.vector("TH1F*")()
    v_titles = r.vector('string')()
    v_sigtitles = r.vector('string')()
    v_colors = r.vector('Color_t')()

    opt_str = ""
    for k,v in opts.items():
        if type(v) is bool:
            if v: opt_str += "--{0} ".format(k)
        else:
            opt_str += "--{0} {1} ".format(str(k),str(v))

    if "outputName" in opts:
        dir_name = opts["outputName"].rsplit("/",1)[0]
        if not os.path.isdir(dir_name):
            os.system("mkdir -p {0}".format(dir_name))

    for bg in bgs: v_bgs.push_back(bg)
    for title in titles: v_titles.push_back(title)
    for color in colors: v_colors.push_back(color)
    dataMCplotMaker(data, v_bgs, v_titles, title, subtitle, opt_str, v_sigs, v_sigtitles, v_colors)

if __name__ == "__main__":
    h_data = r.TH1F("data", "", 7, 0, 7)
    h_wz = h_data.Clone("wz")
    h_ttz = h_data.Clone("ttz")

    h_data.FillRandom("gaus",1000)
    h_wz.FillRandom("gaus",500)
    h_ttz.FillRandom("gaus",500)

    d_opts = {
            "poissonErrorsNoZeros": True,
            "lumi": 36.8,
            "outputName": "plots/test.pdf",
            "xAxisLabel": "Njets",
            "noXaxisUnit": True,
            "isLinear": True,
            "legendUp": -0.15,
            "legendRight": -0.08,
            "outOfFrame": True,
            "legendTaller": 0.15,
            "yTitleOffset": -0.5,
            "type": "Preliminary",
            }

    dataMCplot(h_data, bgs=[h_wz,h_ttz], titles=["WZ","t#bar{t}Z"], title="test", colors=[r.kGreen+2,r.kBlue-1], opts=d_opts)
    os.system("ic " + d_opts["outputName"])

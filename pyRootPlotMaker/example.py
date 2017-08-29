import pyRootPlotMaker as ppm
import ROOT

h_bkg1 = ROOT.TH1F("h_bkg1","Background",50,0,100)
h_bkg2 = ROOT.TH1F("h_bkg2","Background",50,0,100)
h_data = ROOT.TH1F("h_data","Data",50,0,100)

b1 = ROOT.TF1("b1","TMath::Exp(-x/30)",0,100)
b2 = ROOT.TF1("b2","TMath::DiLog(x/10)",0,100)

ROOT.gRandom.SetSeed(0)
h_bkg1.FillRandom("b1",5000)
h_bkg2.FillRandom("b2",5000)
h_data.FillRandom("b1",7500)
h_data.FillRandom("b2",7500)

h_bkg_vec = [h_bkg1, h_bkg2]
bkg_names = ["Background 1","Background 2"]

subtitles = ["subtitle 1", "subtitle 2"]
subLegText = ["MC scaled by: {datamcsf}","# Data Events: {ndata}"]

systematics = [0.8/(11-i/5.) for i in range(50)]

ppm.plotDataMC(h_bkg_vec,bkg_names,h_data, doPause=True, isLog=False, title="Test plot",
               subtitles=subtitles, subLegText=subLegText, scaleMCtoData=True, markerSize=0.9,
               lumi=3.64, lumiUnit="ab", energy=14, saveAs="test.pdf", doBkgError=True,
               drawSystematicBand=True, systematics=systematics)




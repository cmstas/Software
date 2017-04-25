import ROOT as r
import os

filenames = [
        "input_test.pdf",
        ]

for input_filename in filenames:
    r.gROOT.SetBatch(1)
    c1 = r.TCanvas("c1", "", 800, 800)
    c1.SetFillStyle(4000) # make a transparent canvas

    text = r.TLatex(0.18,0.79, "arXiv: 1704.07323" )
    text.SetNDC()
    text.SetTextSize(0.03)
    text.SetLineWidth(2)
    text.SetTextFont(42)
    text.Draw()

    c1.SaveAs("overlay.pdf")
    outname = input_filename.replace(".pdf","_overlay.pdf")
    os.system("pdftk %s multistamp overlay.pdf output %s" % (input_filename,outname))

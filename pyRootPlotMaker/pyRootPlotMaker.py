import ROOT
import ppmUtils as utils

## do not use this manually! call plotDataMC with no h_data argument
def plotBackgrounds(h_bkg_vec_, bkg_names, canvas=None, stack=None, saveAs=None, xRangeUser=None, doPause=False, 
                    isLog=True, xAxisTitle="H_{T}", xAxisUnit="GeV", dataMax=0, userMax=None, userMin=None,
                    doLegend=False, doMT2Colors=False, doOverflow=True, shallowCopy=True, sigMax=0,
                    customColors=None):

    # make shallow copies of hists so we don't overwrite the originals
    if shallowCopy:
        h_bkg_vec = [ROOT.TH1D() for h in h_bkg_vec_]
        for i in range(len(h_bkg_vec_)):
            h_bkg_vec_[i].Copy(h_bkg_vec[i])
    else:
        h_bkg_vec = h_bkg_vec_

    if canvas==None:
        canvas = ROOT.TCanvas()
    if stack==None:
        stack = ROOT.THStack()

    if(isLog):
        canvas.SetLogy(1)

    canvas.cd()

    colors = [ROOT.kAzure+7, ROOT.kSpring-5, ROOT.kOrange-2, ROOT.kRed-7,
              ROOT.kCyan-7, ROOT.kMagenta-7, ROOT.kGray]

    nh = len(h_bkg_vec)
    
    for i in range(nh):
        if doMT2Colors:
            h_bkg_vec[i].SetFillColor(utils.GetMT2Color(bkg_names[i]))
        elif customColors!=None:
            h_bkg_vec[i].SetFillColor(customColors[nh-1-i])
        else:
            h_bkg_vec[i].SetFillColor(colors[nh-1-i])
        h_bkg_vec[i].SetLineColor(ROOT.kBlack)
        if doOverflow:
            utils.PutOverflowInLastBin(h_bkg_vec[i], None if xRangeUser==None else xRangeUser[1])

    for i in range(nh):
        stack.Add(h_bkg_vec[i])

    stack.Draw("HIST")

    if xRangeUser!=None:
        stack.GetXaxis().SetRangeUser(*xRangeUser)

    binWidth = utils.GetBinWidth(h_bkg_vec[0])
    if binWidth == None:  ## uneven binning
        binWidth = 'Bin'

    if xAxisUnit==None:
        stack.GetXaxis().SetTitle(xAxisTitle)
    else:
        stack.GetXaxis().SetTitle(xAxisTitle + " [{0}]".format(xAxisUnit))
    if binWidth != 'Bin':
        binWidth = str(round(binWidth,5)) + " " + (xAxisUnit if xAxisUnit!=None else "")
    stack.GetYaxis().SetTitle("Events / {0}".format(binWidth))
    stack.GetYaxis().SetTitleOffset(1.4)
    stack.GetXaxis().SetTitleOffset(1.2)

    utils.SetYBounds(stack, isLog, h_bkg_vec, max(dataMax, sigMax), xRangeUser)
    if userMax!=None:
        stack.SetMaximum(userMax)
    if userMin!=None:
        stack.SetMinimum(userMin)

    ## legend
    if doLegend:
        leg = ROOT.TLegend(0.65,0.71,0.88,0.88)
        for i in range(len(h_bkg_vec)):
            leg.AddEntry(h_bkg_vec[-i-1],bkg_names[-i-1],"f")
        leg.Draw()

    if saveAs != None:
        canvas.saveAs(saveAs)
        
    if doPause:
        raw_input()

## make a ratio plot. For use within the plotDataMC and plotComparison functions
def plotRatio(h1, h2, canvas=None, ratioHist=None, xRangeUser=None, ratioTitle = None, markerSize=0.7, markerStyle=20, 
              markerColor=ROOT.kBlack, doPull=False, convertToPoisson=False, ratioGraph=None, drawZeros=True, 
              drawSystematicBand=False, systematics=None, h_syst=None, yRangeUser=None, showRatioErrs=True, 
              justDrawPoints=False):

    if doPull:
        convertToPoisson = False

    if canvas==None:
        canvas = ROOT.TCanvas()
    if ratioHist==None:
        ratioHist = ROOT.TH1D()

    if convertToPoisson and type(ratioGraph)!=type(ROOT.TGraphAsymmErrors()):
        raise RuntimeError("must pass a TGraphAsymmErrors as ratioGraph for convertToPoisson option!")

    if ratioTitle==None:
        if not doPull:
            ratioTitle = "Data/MC"
        else:
            ratioTitle = "Pull"

    canvas.cd()
    canvas.SetTicky(1)

    if not doPull:
        h2.Copy(ratioHist)
        ratioHist.Divide(h1)
        if convertToPoisson:
            utils.GetPoissonRatioGraph(h1,h2,ratioGraph,drawZeros=drawZeros)
    else:
        nbins = h1.GetNbinsX()
        h2.Copy(ratioHist)
        for i in range(1,nbins+1):
            diff = h2.GetBinContent(i)-h1.GetBinContent(i)
            err = ROOT.TMath.Sqrt(h2.GetBinError(i)**2 + h1.GetBinError(i)**2)
            ratioHist.SetBinContent(i,diff/err)
            ratioHist.SetBinError(i,1.0)

    if not showRatioErrs:
        for i in range(1,ratioHist.GetNbinsX()+1):
            ratioHist.SetBinError(i,0)

    ratioHist.SetTitle("")
    #yaxis
    if not doPull:
        if yRangeUser == None:
            ratioHist.GetYaxis().SetRangeUser(0,2)
        else:
            ratioHist.GetYaxis().SetRangeUser(yRangeUser[0],yRangeUser[1])            
        ratioHist.GetYaxis().SetNdivisions(505)
    else:
        if yRangeUser == None:
            ratioHist.GetYaxis().SetRangeUser(-4,4)
        else:
            ratioHist.GetYaxis().SetRangeUser(yRangeUser[0],yRangeUser[1])            
        ratioHist.GetYaxis().SetNdivisions(204,False)
    ratioHist.GetYaxis().SetTitle(ratioTitle)        
    ratioHist.GetYaxis().SetTitleSize(0.18)
    ratioHist.GetYaxis().SetTitleOffset(0.17)
    ratioHist.GetYaxis().SetLabelSize(0.13)
    ratioHist.GetYaxis().CenterTitle()
    #xaxis
    ratioHist.GetXaxis().SetLabelSize(0.0)
    ratioHist.GetXaxis().SetTitle("")
    ratioHist.GetXaxis().SetTickSize(0.06)
    #markers
    ratioHist.SetMarkerStyle(markerStyle)
    ratioHist.SetMarkerSize(markerSize)    
    ratioHist.SetMarkerColor(markerColor)
    ratioHist.SetLineColor(markerColor)
    if convertToPoisson:
        ratioGraph.SetMarkerStyle(markerStyle)
        ratioGraph.SetMarkerSize(markerSize)
        ratioGraph.SetMarkerColor(markerColor)
        ratioGraph.SetLineColor(markerColor)
        if justDrawPoints:
            ratioGraph.Draw("SAME PZ")
        else:
            ratioHist.Reset()
            ratioHist.Draw()
            ratioGraph.Draw("PZ")
    else:
        if justDrawPoints:
            ratioHist.Draw("SAME PE")
        else:
            ratioHist.Draw("PE")

    if justDrawPoints:
        return

    # systematics
    if drawSystematicBand:
        h1.Copy(h_syst)
        for i in range(1,h_syst.GetNbinsX()+1):
            h_syst.SetBinContent(i,1)
            h_syst.SetBinError(i, systematics[i-1])
        h_syst.SetFillStyle(1001)
        h_syst.SetFillColor(ROOT.kGray+0)
        h_syst.Draw("SAME E2")

    #line
    line = ROOT.TLine()
    line.SetLineColor(ROOT.kGray+2)
    line.SetLineWidth(2)
    line.SetLineStyle(7)
    xmin = ratioHist.GetXaxis().GetBinLowEdge(1)
    xmax = ratioHist.GetXaxis().GetBinUpEdge(h1.GetNbinsX())
    if xRangeUser!=None:
        xmin = xRangeUser[0]
        xmax = xRangeUser[1]
    if not doPull:
        line.DrawLine(xmin,1,xmax,1)
    else:
        line.DrawLine(xmin,0,xmax,0)
        line.SetLineColor(ROOT.kGray)
        line.SetLineWidth(1)
        line.SetLineStyle(1)
        line.DrawLine(xmin,1,xmax,1)
        line.DrawLine(xmin,2,xmax,2)
        line.DrawLine(xmin,3,xmax,3)
        line.DrawLine(xmin,-1,xmax,-1)
        line.DrawLine(xmin,-2,xmax,-2)
        line.DrawLine(xmin,-3,xmax,-3)

    if convertToPoisson:
        ratioGraph.Draw("SAME PZ")
    else:
        ratioHist.Draw("SAME PE")
    ratioHist.Draw("SAMEAXIS")


## plot data and stacked background hist. See README for argument explanations
def plotDataMC(h_bkg_vec_, bkg_names, h_data=None, title=None, subtitles=None, ratioTitle=None, doRatio=True, yRangeUserRatio=None, scaleMCtoData=False, saveAs=None, 
               isLog=True, dataTitle="Data", xRangeUser=None, doPause=False, lumi=1.0, lumiUnit="fb", noLumi=False,
               energy=13, xAxisTitle="H_{T}", xAxisUnit="GeV", userMax=None, userMin=None, doSort=False,
               doMT2Colors=False, markerSize=0.9, doOverflow=True, titleSize=0.04, subtitleSize=0.03, subLegText=None,
               subLegTextSize=0.03, cmsText="CMS Preliminary", cmsTextSize=0.035, doBkgError=False, functions=[], 
               legCoords=None, doPull=False, convertToPoisson=False, drawZeros=True, drawSystematicBand=False, systematics=None,
               h_sig_vec=[], sig_names=[], customColors=None, verticalLines=[], ratioType=0):    

    if h_data == None:
        doRatio = False
        scaleMCtoData = False
        
    if customColors!=None and len(customColors) < len(h_bkg_vec_):
        raise RuntimeError("Not enough colors for all backgrounds! {0} colors, {1} backgrounds.".format(len(customColors),len(h_bkg_vec_)))

    if drawSystematicBand and systematics==None:
        raise RuntimeError("Must supply a list of systematics to draw uncertainty band!")

    if systematics != None and len(systematics) != h_bkg_vec_[0].GetNbinsX():
        raise RuntimeError("length of systematics list does not equal the number of bins!")
        
    # make shallow copies of hists so we don't overwrite the originals
    h_bkg_vec = [ROOT.TH1D() for h in h_bkg_vec_]
    for i in range(len(h_bkg_vec_)):
        h_bkg_vec_[i].Copy(h_bkg_vec[i])
    if h_data != None:
        if type(h_data) != type(list()):
            h_data = [h_data]
        if len(h_data) > 4:
            print h_data
            raise RuntimeError("currently only supports up to 4 data histograms!")
        h_data_ = [ROOT.TH1D() for h in h_data]
        for i in range(len(h_data)):
            h_data[i].Copy(h_data_[i])
            h_data[i] = h_data_[i]  #so the arg name doesn't have underscore

    ROOT.gStyle.SetOptStat(0)
     
    #### setup canvas and pads ####

    c = ROOT.TCanvas()
    
    if doRatio:
        c.SetCanvasSize(700,600)
        pads = []
        pads.append(ROOT.TPad("1","1",0.0,0.16,1.0,1.0))
        pads.append(ROOT.TPad("2","2",0.0,0.0,1.0,0.17))
        
        pads[0].SetTopMargin(0.08)
        pads[0].SetLeftMargin(0.12)
        pads[0].SetBottomMargin(0.10)
        pads[1].SetLeftMargin(0.12)
        
        pads[0].Draw()
        pads[1].Draw()
        pads[0].cd()
    else:
        c.SetCanvasSize(700,504)
        pads = [c]
        pads[0].SetLeftMargin(0.12)
        pads[0].SetTopMargin(0.08)

    if isLog:
        pads[0].SetLogy()
    pads[0].SetTicky(1)

    pads[0].cd()

    ## MC
    int_errors = [ROOT.Double(0) for i in range(len(h_bkg_vec))]
    integrals = [h_bkg_vec[i].IntegralAndError(0,-1,int_errors[i]) for i in range(len(h_bkg_vec))]
    if doSort:
        zipped = zip(h_bkg_vec,bkg_names)
        sorted_bkg = [x for (y,x) in sorted(zip(integrals,zipped))]
        h_bkg_vec = [x for (x,y) in sorted_bkg]
        bkg_names = [y for (x,y) in sorted_bkg]
    else:
        h_bkg_vec = h_bkg_vec[::-1]
        bkg_names = bkg_names[::-1]

    scaleFactor = 1.0
    scaleFactorError = 1.0
    if(h_data!=None and scaleMCtoData):
        tot_MC_error = ROOT.TMath.Sqrt(sum([x**2 for x in int_errors]))
        tot_MC_integral = sum(integrals)
        data_error = ROOT.Double(0)
        data_integral = h_data[0].IntegralAndError(0,-1,data_error)
        scaleFactor = data_integral/tot_MC_integral
        if data_integral > 0:
            scaleFactorError = scaleFactor * (data_error/data_integral + tot_MC_error/tot_MC_integral)
        else:
            scaleFactorError = 0.0
    for i in range(len(h_bkg_vec)):
        h_bkg_vec[i].Scale(scaleFactor)

    dataMax = 0
    if h_data!=None:
        for ih in range(len(h_data)):
            for i in range(1,h_data[ih].GetNbinsX()+1):
                y = h_data[ih].GetBinContent(i)+h_data[ih].GetBinError(i)
                if y>dataMax:
                    dataMax = y

    sigMax = 0
    if h_sig_vec!=None:
        for ih in range(len(h_sig_vec)):
            for i in range(1,h_sig_vec[ih].GetNbinsX()+1):
                y = h_sig_vec[ih].GetBinContent(i)+h_sig_vec[ih].GetBinError(i)
                if y>sigMax:
                    sigMax = y

    stack = ROOT.THStack("hs","")
    plotBackgrounds(h_bkg_vec, bkg_names, canvas=pads[0], stack=stack, xRangeUser=xRangeUser, isLog=isLog, 
                    xAxisTitle=xAxisTitle, xAxisUnit=xAxisUnit, dataMax=dataMax, shallowCopy=False,
                    userMax=userMax, userMin=userMin, doMT2Colors=doMT2Colors, doOverflow=doOverflow, 
                    sigMax=sigMax, customColors=customColors)

    if doBkgError:
        h_err = ROOT.TH1D()
        h_bkg_vec[0].Copy(h_err)
        for i in range(1,len(h_bkg_vec)):
            h_err.Add(h_bkg_vec[i])
        h_err.SetFillStyle(3244)
        h_err.SetFillColor(ROOT.kGray+3)
        h_err.Draw("E2SAME")


    ## data
    if h_data != None:
        styles = [20,24,21,25]
        colors = [ROOT.kBlack,ROOT.kBlack,ROOT.kRed,ROOT.kBlack]
        N_DATA_EVENTS = [int(h.Integral(0,-1)) for h in h_data] #curretly only support counting of events for first histogram
        for ih in range(len(h_data)):
            h_data[ih].SetMarkerStyle(styles[ih])
            h_data[ih].SetMarkerSize(markerSize)
            h_data[ih].SetMarkerColor(colors[ih])
            h_data[ih].SetLineColor(colors[ih])
            if xRangeUser!=None:
                h_data[ih].GetXaxis().SetRangeUser(*xRangeUser)
            if doOverflow:
                utils.PutOverflowInLastBin(h_data[ih], None if xRangeUser==None else xRangeUser[1])
        if convertToPoisson:
            h_data_poisson = [ROOT.TGraphAsymmErrors() for h in h_data]
            for ih in range(len(h_data)-1,-1,-1):
                utils.ConvertToPoissonGraph(h_data[ih], h_data_poisson[ih], drawZeros=drawZeros)
                h_data_poisson[ih].SetMarkerStyle(styles[ih])
                h_data_poisson[ih].SetMarkerSize(markerSize)
                h_data_poisson[ih].SetMarkerColor(colors[ih])
                h_data_poisson[ih].SetLineColor(colors[ih])
                h_data_poisson[ih].Draw("SAME PZ")
        else:
            for ih in range(len(h_data)-1,-1,-1):
                h_data[ih].Draw("SAME E0")

    ## functions
    for function in functions:
        function.Draw("SAME")

    ## signals
    sig_cols = [ROOT.kMagenta, ROOT.kCyan, ROOT.kOrange+7, ROOT.kGreen]
    for isig in range(len(h_sig_vec)):
        h_sig_vec[isig].SetLineColor(sig_cols[isig])
        h_sig_vec[isig].SetLineWidth(2)
        h_sig_vec[isig].Draw("SAME HIST")

    ## draw vertical lines
    line = ROOT.TLine()
    line.SetLineWidth(2)
    line.SetLineColor(ROOT.kRed)
    for linex in verticalLines:
        lm = pads[0].GetLeftMargin()
        rm = pads[0].GetRightMargin()
        tm = pads[0].GetTopMargin()
        bm = pads[0].GetBottomMargin()
        if xRangeUser!=None:
            xrange = xRangeUser
        else:
            xrange = (h_bkg_vec[0].GetXaxis().GetXmin(), h_bkg_vec[0].GetXaxis().GetXmax())
        xndc = lm + float(linex-xrange[0])/(xrange[1]-xrange[0]) * (1-rm-lm)
        line.DrawLineNDC(xndc,bm,xndc,1-tm)

    ## legend
        
    if legCoords == None:
        legCoords = (0.65,0.72,0.87,0.89)
    leg = ROOT.TLegend(*legCoords)
    if h_data != None:
        if type(dataTitle) != type(list()):
            dataTitle = [dataTitle]
        for ih in range(len(h_data)):
            leg.AddEntry(h_data[ih],dataTitle[ih])
    for i in range(len(h_bkg_vec)):
        leg.AddEntry(h_bkg_vec[-i-1],bkg_names[-i-1],"f")
    for i in range(len(h_sig_vec)):
        leg.AddEntry(h_sig_vec[i], sig_names[i], "l")
    leg.Draw()
    
    # handle all of the text
    text = ROOT.TLatex()
    text.SetNDC(1)
    cursorX = 0.23
    cursorY = 0.89
    # title
    if title!=None and title!="":
        text.SetTextAlign(13) 
        text.SetTextFont(42)
        text.SetTextSize(titleSize)
        text.DrawLatex(cursorX,cursorY,title)
        cursorY -= titleSize + 0.010
    # subtitles
    if subtitles==None:
        subtitles=[]
    if type(subtitles)==type(""):
        subtitles = [subtitles]
    for s in subtitles:
        text.SetTextAlign(13)
        text.SetTextFont(42)
        text.SetTextSize(subtitleSize)
        text.DrawLatex(cursorX,cursorY,s)
        cursorY -= subtitleSize + 0.015
    # lumi
    if not noLumi:
        utils.DrawLumiText(pads[0],lumi=lumi,lumiUnit=lumiUnit,energy=energy,textFont=42,textSize=cmsTextSize)
    # CMS text
    utils.DrawCmsText(pads[0],text=cmsText,textFont=62,textSize=cmsTextSize)
    # Sub-legend text
    cursorX = legCoords[0]
    cursorY = legCoords[1]-0.01
    if subLegText==None:
        subLegText=[]
    if type(subLegText)==type(""):
        subLegText = [subLegText]
    for s in subLegText:
        if h_data==None:
            N_DATA_EVENTS = [0]
        vals = {"ndata":N_DATA_EVENTS[0], "datamcsf":scaleFactor, "datamcsferr":scaleFactorError}
        for i in range(len(N_DATA_EVENTS)):
            vals["ndata{0}".format(i+1)] = N_DATA_EVENTS[i]
        s = s.replace("{datamcsf}","{datamcsf:.2f}")
        s = s.replace("{datamcsferr}","{datamcsferr:.2f}")
        text.SetTextFont(62)
        text.SetTextAlign(13)
        text.SetTextSize(subLegTextSize)
        text.DrawLatex(cursorX,cursorY,s.format(**vals))
        cursorY -= 0.03+0.005


    ######## ratio plot ############
    
    if doRatio:
        pads[1].cd()
    
        h1 = ROOT.TH1D()
        h_bkg_vec[0].Copy(h1)
        for i in range(len(h_bkg_vec)-1):
            h1.Add(h_bkg_vec[i+1])

        ratioHist = [ROOT.TH1D() for h in h_data]
        ratioGraph = [ROOT.TGraphAsymmErrors() for h in h_data]
        h_syst = ROOT.TH1D()
        for ih,hd in list(enumerate(h_data))[::-1]:
            if ih==len(h_data)-1:
                plotRatio(h1, hd, canvas=pads[1], ratioHist=ratioHist[ih], ratioTitle=ratioTitle, xRangeUser=xRangeUser, 
                          markerSize=markerSize, markerStyle=hd.GetMarkerStyle(), markerColor=hd.GetMarkerColor(),
                          doPull=doPull, convertToPoisson=convertToPoisson, ratioGraph=ratioGraph[ih], drawZeros=drawZeros,
                          drawSystematicBand=drawSystematicBand, systematics=systematics, h_syst=h_syst)
            else:
                if ratioType==0:
                    hden = h1
                    hnum = hd
                else:
                    hden = hd
                    hnum = h_data[0]
                plotRatio(hden, hnum, canvas=pads[1], ratioHist=ratioHist[ih], xRangeUser=xRangeUser, 
                          markerSize=markerSize, markerStyle=hd.GetMarkerStyle(), markerColor=hd.GetMarkerColor(),
                          doPull=doPull, convertToPoisson=convertToPoisson, ratioGraph=ratioGraph[ih], drawZeros=drawZeros, justDrawPoints=True)
    
    c.Update()
    c.SetWindowSize(c.GetWw()+4, c.GetWh()+50)

    if saveAs!=None:
        c.SaveAs(saveAs)

    if doPause:
        raw_input()

## make a comparison plot between two histograms. Plots both histos on one axis, as well as a ratio plot
def plotComparison(h1_, h2_, title="", ratioTitle="Data/MC", h1Title="MC", h2Title="Data", saveAs=None,
                   size=(700,600), xRangeUser=None, markerSize=0.65, doPause=False, isLog=True, style=1,
                   doOverflow=True, normalize=False, xAxisTitle="", ratioYRange=None, yRangeUser=None, 
                   showRatioErrs=True, showNEvents=False):

    nEntries = (int(h1_.GetEntries()), int(h2_.GetEntries()))

    h1 = ROOT.TH1D()
    h1_.Copy(h1)
    h2 = ROOT.TH1D()
    h2_.Copy(h2)

    if normalize:
        if h1.Integral(0,-1) > 0:
            h1.Scale(1.0/h1.Integral(0,-1)/h1.GetBinWidth(1))
        if h2.Integral(0,-1) > 0:
            h2.Scale(1.0/h2.Integral(0,-1)/h2.GetBinWidth(1))

    if doOverflow:
        utils.PutOverflowInLastBin(h1, None if xRangeUser==None else xRangeUser[1])
        utils.PutOverflowInLastBin(h2, None if xRangeUser==None else xRangeUser[1])

    ROOT.gStyle.SetOptStat(0)

    c = ROOT.TCanvas()
    c.SetCanvasSize(size[0],size[1])

    pads = []
    pads.append(ROOT.TPad("1","1",0.0,0.16,1.0,1.0))
    pads.append(ROOT.TPad("2","2",0.0,0.0,1.0,0.17))

    pads[0].SetLogy(isLog)
    pads[0].SetTopMargin(0.08)
    pads[0].SetLeftMargin(0.12)
    pads[0].SetBottomMargin(0.10)
    pads[1].SetLeftMargin(0.12)
    
    pads[0].Draw()
    pads[1].Draw()
    pads[0].cd()

    if not isLog:
        h1.SetMinimum(0)
        
    h1.SetTitle(title)
    h1.GetXaxis().SetTitleOffset(1.15)
    h1.SetMaximum((100 if isLog else 1.3)*max(h1.GetMaximum(), h2.GetMaximum()))
    if xRangeUser!=None:
        h1.GetXaxis().SetRangeUser(*xRangeUser)
        h2.GetXaxis().SetRangeUser(*xRangeUser)
    if yRangeUser!=None:
        h1.GetYaxis().SetRangeUser(*yRangeUser)
        h2.GetYaxis().SetRangeUser(*yRangeUser)
    if normalize:
        h1.GetYaxis().SetTitle("Normalized")
    else:
        h1.GetYaxis().SetTitle("Entries / {0} GeV".format(h1.GetXaxis().GetBinWidth(1)))
    h1.GetYaxis().SetTitleOffset(1.2)
    h1.GetXaxis().SetTitle(xAxisTitle)
    if style==2:
        h1.SetLineColor(ROOT.kAzure-6)
        h1.SetFillColor(ROOT.kAzure-9)
        h1.SetLineWidth(1)
        h2.SetLineColor(ROOT.kBlack)
        h2.SetMarkerStyle(20)
        h2.SetMarkerSize(markerSize)
        h2.SetMarkerColor(ROOT.kBlack)
        h1.Draw("HIST")
        h2.Draw("SAME PE")
    elif style==3:
        h1.SetLineColor(ROOT.kRed)
        h2.SetLineColor(ROOT.kBlack)
        h2.Draw("L HIST")
        h1.Draw("SAME L HIST")
    else:
        h1.SetLineColor(ROOT.kRed)
        h2.SetLineColor(ROOT.kBlack)
        h1.Draw("PE")
        h2.Draw("SAME PE")
    
    leg = ROOT.TLegend(0.60,0.75,0.89,0.89)
    leg.AddEntry(h1, h1Title)
    leg.AddEntry(h2, h2Title)
    leg.Draw()

    if showNEvents:
        text = ROOT.TLatex()
        text.SetNDC(1)
        text.SetTextAlign(32)
        text.SetTextFont(42)
        text.SetTextSize(0.04)
        text.DrawLatex(0.585, 0.855, "# Events: " + str(nEntries[0]))
        text.DrawLatex(0.585, 0.785, str(nEntries[1]))
    
    ######## ratio plot ############
    
    pads[1].cd()
    ratio = ROOT.TH1D()
    plotRatio(h1,h2,canvas=pads[1], ratioHist=ratio, ratioTitle=ratioTitle, xRangeUser=xRangeUser, 
              markerSize=markerSize, yRangeUser=ratioYRange, showRatioErrs=showRatioErrs)

    c.Update()
    c.SetWindowSize(c.GetWw()+4, c.GetWh()+50)

    if saveAs!=None:
        c.SaveAs(saveAs)

    if doPause:
        raw_input()


def plotEfficiency(h_num_, h_den_, doOverflow=True, xRangeUser=None, size=(800,700), axisMax=1.3, 
                   xAxisTitle="H_{T}", yAxisTitle="Efficiency", xAxisUnit="GeV", lumi = 1.0, lumiUnit="fb", 
                   energy=13, year=2017, printEffic=False, effCut=None, effVar=None, subtitle=None, 
                   fitwindow=None, fitstart=None, printPlateau=None, saveAs=None):
    
    h_num = ROOT.TH1D()
    h_num_.Copy(h_num)
    h_den = ROOT.TH1D()
    h_den_.Copy(h_den)

    if doOverflow:
        utils.PutOverflowInLastBin(h_num, None if xRangeUser==None else xRangeUser[1])
        utils.PutOverflowInLastBin(h_den, None if xRangeUser==None else xRangeUser[1])

    ROOT.gStyle.SetOptStat(0)

    c = ROOT.TCanvas()
    c.SetCanvasSize(size[0],size[1])

    c.SetTopMargin(0.08)
    c.SetLeftMargin(0.12)
    c.SetBottomMargin(0.12)
    c.SetRightMargin(0.12)

    c.SetTickx(1)

    # scale denom/num histograms
    base_width = h_den.GetBinWidth(1)
    for i in range(1,h_den.GetNbinsX()+1):
        sf = h_den.GetBinWidth(i) / base_width
        h_den.SetBinContent(i, h_den.GetBinContent(i) / sf)
        h_num.SetBinContent(i, h_num.GetBinContent(i) / sf)
    maxval = h_num.GetMaximum()
    sf = 0.5 / maxval
    h_num.Scale(sf)
    h_den.Scale(sf)
        
    h_den.GetYaxis().SetRangeUser(0,axisMax)
    h_den.GetYaxis().SetTitle("")
    if xRangeUser != None:
        h_den.GetXaxis().SetRangeUser(xRangeUser[0], xRangeUser[1])
    h_den.GetXaxis().SetLabelOffset(0.015)
    h_den.GetXaxis().SetTitleOffset(1.40)
    if xAxisUnit != None:
        h_den.GetXaxis().SetTitle("{0} [{1}]".format(xAxisTitle, xAxisUnit))
    else:
        h_den.GetXaxis().SetTitle(xAxisTitle)
    h_den.GetXaxis().SetTitleSize(0.04)
        
    h_den.Draw("AXIS SAME")

    line = ROOT.TLine()
    line.SetLineStyle(3)
    line.SetLineWidth(1)
    line.SetLineColor(ROOT.kGray+2)
    xmin = xRangeUser[0] if xRangeUser!=None else h_den.GetXaxis().GetXmin()
    xmax = xRangeUser[1] if xRangeUser!=None else h_den.GetXaxis().GetXmax()
    line.DrawLine(xmin, 1.0, xmax, 1.0)
    line.DrawLine(xmin, 0.8, xmax, 0.8)
    line.DrawLine(xmin, 0.6, xmax, 0.6)
    line.DrawLine(xmin, 0.4, xmax, 0.4)
    line.DrawLine(xmin, 0.2, xmax, 0.2)

    h_num.SetFillColor(ROOT.kAzure+1)
    h_num.SetLineColor(ROOT.kAzure+3)
    h_num.SetLineWidth(1)
    h_num.SetLineStyle(1)
    h_den.SetFillStyle(0)
    h_den.SetLineColor(ROOT.kAzure+3)
    h_den.SetLineWidth(2)
    h_den.SetLineStyle(2)

    h_num.Draw("HIST SAME")
    h_den.Draw("HIST SAME")

    eff = ROOT.TEfficiency(h_num_, h_den_)
    eff.SetMarkerStyle(20)
    eff.SetMarkerSize(0.9)
    eff.Draw("P SAME")
    c.Update()

    if fitwindow != None:
        fit = ROOT.TF1("fit","[0]/(1+exp(-[1]*(x-[2])))", fitwindow[0], fitwindow[1])
        fit.SetNpx(500)
        if fitstart==None:
            fit.SetParameter(0, 1)
            fit.SetParameter(1, 0.2)
            fit.SetParameter(2, fitwindow[0])
        else:
            fit.SetParameters(fitstart[0], fitstart[1], fitstart[2])
        graph = eff.GetPaintedGraph()
        graph.Fit(fit, "QNR","goff")
        fit.SetLineColor(ROOT.kRed)
        fit.SetLineWidth(2)
        fit.Draw("SAME")
        eff.Draw("P SAME")
        # print -1/fit.GetParameter(1)*ROOT.TMath.Log(1/0.98-1)+fit.GetParameter(2)
    
    h_den.Draw("AXIS SAME")

    c.Update()
    axis = ROOT.TGaxis(c.GetUxmax(), c.GetUymin(), c.GetUxmax(), c.GetUymax(), 0, axisMax / sf, 510, "+L")
    axis.SetLabelFont(h_den.GetYaxis().GetLabelFont())
    axis.SetLabelSize(h_den.GetYaxis().GetLabelSize())
    axis.Draw()

    text = ROOT.TLatex()
    text.SetTextFont(42)
    text.SetTextSize(axis.GetLabelSize() * 1.2)
    text.SetTextAlign(32)
    text.SetTextAngle(90)
    text.DrawLatexNDC(0.04, 0.890, yAxisTitle)
    text.SetTextAlign(12)
    text.SetTextAngle(270)
    text.DrawLatexNDC(0.98, 0.890, "Events / {0} {1}".format(base_width, xAxisUnit))

    text.SetTextAlign(31)
    text.SetTextAngle(0)
    text.SetTextSize(0.04)
    if year!=None:
        string = "{0} {1}^{{-1}} ({2} TeV, {3})".format(lumi, lumiUnit, energy, year)
    else:
        string = "{0} {1}^{{-1}} ({2} TeV)".format(lumi, lumiUnit, energy)
    text.DrawLatexNDC(0.87, 0.93, string)

    text.SetTextFont(62)
    # text.SetTextSize(0.05)
    # text.SetTextAlign(11)
    # text.DrawLatexNDC(0.17, 0.84, "CMS")
    # text.SetTextFont(52)
    # text.SetTextSize(0.04)
    # text.SetTextAlign(13)
    # text.DrawLatexNDC(0.17, 0.83, "Preliminary")
    text.SetTextSize(0.04)
    text.SetTextAlign(11)
    text.DrawLatexNDC(0.13, 0.93, "CMS Preliminary")

    if printEffic and effCut==None:
        raise Exception("must provide an effCut if you want to print efficiency!")
    if printEffic and effCut != None:
        ibin = 1
        while h_den_.GetBinLowEdge(ibin) < effCut:
            ibin += 1
        if h_den_.GetBinLowEdge(ibin) != effCut:
            print "ERROR: effCut must be on a bin edge!!"
        else:
            tot = h_den_.Integral(ibin, -1)
            pas= h_num_.Integral(ibin, -1)
            effic = float(pas)/tot
            errup = ROOT.TEfficiency.ClopperPearson(tot, pas, 0.6827, 1) - effic
            errdown = effic - ROOT.TEfficiency.ClopperPearson(tot, pas, 0.6827, 0)
            text.SetTextFont(62)
            text.SetTextSize(0.030)
            text.SetTextAlign(33)
            if effVar==None:
                effVar = xAxisTitle
            text.DrawLatexNDC(0.83, 0.88, "#varepsilon({0} > {1} GeV) = {2:.1f}^{{+{3:.1f}}}_\
{{-{4:.1f}}} %".format(effVar, effCut, 100*effic, 100*errup, 100*errdown))
            
    if printPlateau != None and fitwindow==None:
        raise Exception("must do a fit if you want to print plateau!")
    if type(printPlateau) not in (int,float) or printPlateau<=0 or printPlateau>=1:
        raise Exception("printPlateau must be a float between 0 and 1!")        
    if printPlateau != None and fitwindow!=None:
        v = -1/fit.GetParameter(1)*ROOT.TMath.Log(1.0/printPlateau-1)+fit.GetParameter(2)
        ycoord = 0.88 if not printEffic else 0.82
        text.SetTextFont(62)
        text.SetTextSize(0.030)
        text.SetTextAlign(33)
        text.DrawLatexNDC(0.83, ycoord, "{0:.0f}% of plateau at {1} = {2:.0f} {3}".format(100*printPlateau, xAxisTitle, v, xAxisUnit))

    if subtitle != None:
        text.SetTextFont(52)
        text.SetTextSize(0.035)
        text.SetTextAlign(33)
        text.DrawLatexNDC(0.83, 0.81, subtitle)
            

    if saveAs != None:
        c.SaveAs(saveAs)





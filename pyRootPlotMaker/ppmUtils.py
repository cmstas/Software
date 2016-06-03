import ROOT

def GetMT2Color(sample):
    
    if 'Top' in sample: return 855
    if 'W+Jets' in sample: return 417
    if 'zinv' in sample: return 418
    if 'QCD' in sample: return 401
    if 'Prompt' in sample: return 18
    if 'Z(#font[12]{ll})+Jets' in sample: return 430
    if 'Frag' in sample: return 38
    if 'Fake' in sample: return 46

    return ROOT.kBlack

def GetLastBin(h, xmax=None):
    nb = h.GetNbinsX()
    if xmax!=None:
        lastbin=1
        while h.GetXaxis().GetBinUpEdge(lastbin) <= xmax and lastbin<nb+1:
            lastbin += 1
        lastbin -= 1
    else:
        lastbin = nb
    return lastbin

def PutOverflowInLastBin(h, xmax=None):

    nb = h.GetNbinsX()
    lastbin = GetLastBin(h,xmax)

    bc1 = h.GetBinContent(lastbin)
    bc2 = h.Integral(lastbin+1,nb+1)
    be1 = h.GetBinError(lastbin)
    be2 = ROOT.TMath.Sqrt(sum([h.GetBinError(i)**2 for i in range(lastbin+1,nb+2)]))
    
    h.SetBinContent(lastbin,bc1+bc2)
    h.SetBinError(lastbin,ROOT.TMath.Sqrt(be1**2+be2**2))


def SetYBounds(stack, isLog, h_bkg_vec, data_max, xRangeUser):
    xmax = None if xRangeUser==None else xRangeUser[1]
    lastbin = GetLastBin(h_bkg_vec[0], xmax)
    tmax = 0
    tmin = float("inf")
    for i in range(1,lastbin+1):
        c = sum([h.GetBinContent(i) for h in h_bkg_vec])
        e = ROOT.TMath.Sqrt(sum([h.GetBinError(i)**2 for h in h_bkg_vec]))
        if c+e > tmax:
            tmax = c+e
        if c < tmin:
            tmin = c

    tmax = max(tmax,data_max)
    if isLog:
        if tmin>0:
            tmin = max(0.1, 0.5*tmin)
        else:
            tmin = 0.1
        stack.SetMinimum(tmin)
        stack.SetMaximum(tmax**(1.0/0.69))
    else:
        stack.SetMaximum(tmax*1.33)




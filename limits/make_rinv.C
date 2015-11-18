#include "TFile.h"
#include "TH1F.h"
#include "TH2F.h"
#include "TTree.h"

#include <iostream>
#include <fstream>
#include <vector>


//writes txt file with 1/rvalue for each mass point
//txt file to be used as input to conv_to_xbins_ybins.py
void make_rinv(std::string name = "T1bbbb"){

  TFile *f = new TFile(Form("r-values_%s.root", name.c_str()), "READ");
  TH2F *h = (TH2F*)f->Get("hExp");

  ofstream outfile;
  outfile.open(Form("rinv_%s.txt", name.c_str()));

  for(int i=1; i<=h->GetNbinsX(); i++){
    for(int j=1; j<=h->GetNbinsY(); j++){
      float rvalue = h->GetBinContent(i,j);
      if(rvalue <= 0) continue;
      int m1 = h->GetXaxis()->GetBinLowEdge(i); 
      int m2 = h->GetYaxis()->GetBinLowEdge(j); 
      outfile << m1 << " " << m2 << " " << 1.0/rvalue << std::endl;
    }
  }

  outfile.close();
  delete h;
  f->Close();
  delete f;

}

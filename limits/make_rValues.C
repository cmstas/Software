#include "TFile.h"
#include "TH1F.h"
#include "TH2F.h"
#include "TTree.h"

#include <iostream>
#include <vector>



void Fill2d(TH2F *&hist, double w, double x, double y){   
  x = std::min(hist->GetXaxis()->GetBinCenter(hist->GetXaxis()->GetLast()) , x); 
  x = std::max(hist->GetXaxis()->GetBinCenter(hist->GetXaxis()->GetFirst()), x); 
  y = std::min(hist->GetYaxis()->GetBinCenter(hist->GetYaxis()->GetLast()) , y); 
  y = std::max(hist->GetYaxis()->GetBinCenter(hist->GetYaxis()->GetFirst()), y); 
  hist->Fill(x, y, w); 
}

void make_rValues(std::string model, int m1, int m2){

  //setup file to hold r-values if it doesn't already exist
  TFile *f_temp = new TFile(Form("r-values_%s.root", model.c_str()), "NEW");
  if(f_temp){
    int m1_max = 2000;
    int m1_min = 0;
    int m2_max = 2000;
    int m2_min = 0;
    int m1_div = 25;
    int m2_div = 25;

    int nbinsx = (m1_max - m1_min)/m1_div;
    int nbinsy = (m2_max - m2_min)/m2_div;
    
    TH2F *hExp   = new TH2F("hExp",   "hExp"  , nbinsx, m1_min, m1_max, nbinsy, m2_min, m2_max);
    TH2F *hObs   = new TH2F("hObs",   "hObs"  , nbinsx, m1_min, m1_max, nbinsy, m2_min, m2_max);
    TH2F *hExp1m = new TH2F("hExp1m", "hExp1m", nbinsx, m1_min, m1_max, nbinsy, m2_min, m2_max);
    TH2F *hExp2m = new TH2F("hExp2m", "hExp2m", nbinsx, m1_min, m1_max, nbinsy, m2_min, m2_max);
    TH2F *hExp1p = new TH2F("hExp1p", "hExp1p", nbinsx, m1_min, m1_max, nbinsy, m2_min, m2_max);
    TH2F *hExp2p = new TH2F("hExp2p", "hExp2p", nbinsx, m1_min, m1_max, nbinsy, m2_min, m2_max);
    TH2F *hSig   = new TH2F("hSig",   "hSig"  , nbinsx, m1_min, m1_max, nbinsy, m2_min, m2_max);

    f_temp->Write();
    f_temp->Close();
  }
  delete f_temp;

  //This file is created earlier by running combine
  TFile *limit_file = new TFile(Form("limit_%s_%d_%d.root", model.c_str(), m1, m2), "READ");
  TTree *limit_tree = (TTree*)limit_file->Get("limit");

  //This file is created earlier by running combine
  TFile *significance_file = new TFile(Form("significance_%s_%d_%d.root", model.c_str(), m1, m2), "READ");
  TTree *significance_tree = (TTree*)significance_file->Get("limit");

  //This file will hold 2d histograms with limit r-values and discovery significance
  TFile *f = new TFile(Form("r-values_%s.root", model.c_str()), "UPDATE");

  double value = -1.0;
  limit_tree->SetBranchAddress("limit", &value);

  double limit   = -1.0; //observed limit
  double rm2s    = -1.0; //expected - 2 sigma
  double rm1s    = -1.0; //expected - 1 sigma
  double rmedian = -1.0; //expected limit
  double rp1s    = -1.0; //expected + 1 sigma
  double rp2s    = -1.0; //expected + 2 sigma

  for(int i=0; i< 6; i++){
    limit_tree->GetEntry(i);
    if(i==0)      rm2s    = value;
    else if(i==1) rm1s    = value;
    else if(i==2) rmedian = value;
    else if(i==3) rp1s    = value;
    else if(i==4) rp2s    = value;
    else if(i==5) limit   = value;
  }

  double sig = -1.0;
  significance_tree->SetBranchAddress("limit", &sig);
  significance_tree->GetEntry(0);

  delete limit_tree;
  limit_file->Close();
  delete limit_file;

  delete significance_tree;
  significance_file->Close();
  delete significance_file;

  f->cd();

  TH2F *hExp   = (TH2F*)f->Get("hExp");
  TH2F *hObs   = (TH2F*)f->Get("hObs");
  TH2F *hExp1m = (TH2F*)f->Get("hExp1m");
  TH2F *hExp2m = (TH2F*)f->Get("hExp2m");
  TH2F *hExp1p = (TH2F*)f->Get("hExp1p");
  TH2F *hExp2p = (TH2F*)f->Get("hExp2p");
  TH2F *hSig   = (TH2F*)f->Get("hSig");

  Fill2d(hExp  , rmedian, m1, m2);    
  Fill2d(hObs  , limit  , m1, m2);  
  Fill2d(hExp1m, rm1s   , m1, m2);  
  Fill2d(hExp2m, rm2s   , m1, m2);  
  Fill2d(hExp1p, rp1s   , m1, m2);  
  Fill2d(hExp2p, rp2s   , m1, m2);  
  Fill2d(hSig  , sig    , m1, m2);  

  hExp  ->Write("",TObject::kOverwrite);
  hObs  ->Write("",TObject::kOverwrite);
  hExp1m->Write("",TObject::kOverwrite);
  hExp2m->Write("",TObject::kOverwrite);
  hExp1p->Write("",TObject::kOverwrite);
  hExp2p->Write("",TObject::kOverwrite);
  hSig  ->Write("",TObject::kOverwrite);
  f->Close();
  delete f;

}

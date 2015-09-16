
//Make plot cumulative function
TH1F* makePlotCumulative(TH1F* hist_bkgd){
  float integ = hist_bkgd->Integral(0,hist_bkgd->GetNbinsX()+1);
  float integ_no_overflow = hist_bkgd->Integral(1,hist_bkgd->GetNbinsX());
  Double_t *integral = hist_bkgd->GetIntegral(); 
  hist_bkgd->SetContent(integral);
  for (int i = 1; i <= hist_bkgd->GetNbinsX(); i++){
    float bin_content = hist_bkgd->GetBinContent(i);
    hist_bkgd->SetBinContent(i, integ-integ_no_overflow*bin_content);
  }
  hist_bkgd->SetBinContent(hist_bkgd->GetNbinsX()+1, 0); 
  return hist_bkgd;
}

//Function to flip vectors of vectors
//Very useful for plot making: start with ex: plot[TTBAR][HT] so you only have to loop over each sample once
//Then use this to flip it (plot[HT][TTBAR]) so that you can place each vector (ex: plot[HT][*]) into the dataMCplotMaker
vector <vector <TH1F*> > flipVectors(vector <vector <TH1F*> > vin){
  int nVectors = vin.size(); 
  int nInEachVector = 0;
  if (nVectors > 0) nInEachVector = vin[0].size(); 
  vector <vector <TH1F*> > vout; 
  for (int i = 0; i < nInEachVector; i++){
    vector <TH1F*> temp;    
    for (int j = 0; j < nVectors; j++){
      temp.push_back(vin[j][i]);  
    }
    vout.push_back(temp); 
  }
  return vout;
}
